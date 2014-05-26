-------------------------------------------------------------------------------
-- Find base path.
-- Ensure files from src/ are loaded, and that we do not load any system files.
-------------------------------------------------------------------------------

-- Taken from command-line, or defaults to current folder.
local command_line_args = arg
local BASE_FOLDER = (command_line_args[1] or ".")

package.cpath = ''
package.path = '?.lua;src/?.lua;' .. BASE_FOLDER .. "/.lua-deps/?.lua"

-- Additional path component from environment variable:
if os.getenv("p") then
    package.path = package.path .. ';' .. os.getenv("p")
end

-------------------------------------------------------------------------------
-- Global utilities required for bootstrap.
-- Specifically, this is used in our 'require' logic.
-------------------------------------------------------------------------------

-- Lua string API extension:
function string:split(sep) 
    local t = {}
    self:gsub(("([^%s]+)"):format(sep), 
        function(s) table.insert(t, s) end
    )
    return t 
end

-------------------------------------------------------------------------------
-- Mount lua-deps.zip, provided by our engine.
-------------------------------------------------------------------------------

-- Note, for development, it is preferrable to have a folder available, for better
-- error reporting (has source citations). 
-- 
-- TODO: Integrate MOAIFileSystem with ErrorReporting.

local success = MOAIFileSystem.mountVirtualDirectory("lua-deps", BASE_FOLDER .. "/.lua-deps.zip")
assert(success, "Could not mount " .. BASE_FOLDER .. "/.lua-deps.zip!")

-------------------------------------------------------------------------------
-- Make 'require' aware of the MOAI filesystem.
-------------------------------------------------------------------------------

local BUFF_SIZE = 4096

-- Returns object that represents a required directory, ie a package.
local function required_directory(vpath, path)
    if not MOAIFileSystem.checkPathExists(path) then
        return nil
    end
    local object,meta = {},{}
    -- Try to require. Note, only occurs if object[k] == nil.
    function meta:__index(k)
        local req = require(vpath .. '.' .. k)
        object[k] = req -- Cache
        return req
    end
    return setmetatable(object, meta)
end

local function require_moai_directory(vpath)
    -- We determine whether we are loading a path as a Lua object.
    -- Note this can name-clash with Lua files, which are resolved first.
    -- To explicitly specify a directory, include a leading '.' or '/'

    local dpath = vpath:gsub('%.', '/') 

    for _, root in ipairs(package.path:split ';') do
        local obj = required_directory(vpath, root:gsub('%?%.lua', dpath))
        if obj then 
            return obj 
        end
    end

    return nil -- Path not existent
end

local function require_moai_file(vpath)
    local partial_path = vpath:gsub('%.', '/')

    -- First, we ask whether we can load a Lua file
    local stream = MOAIFileStream.new()
    for _, root in ipairs(package.path:split ';') do
        local fpath = root:gsub("%?", partial_path)
        if not stream:open(fpath) then
            -- Next, we ask whether we can load a directory as a collection
            local obj = require_moai_directory(vpath)
            if obj then -- We must return a loader function:
                return function() 
                    return obj 
                end
            else
                return nil
            end
        else
            break
        end
    end

    local func,err = load(
        --[[Chunks]] function() 
            -- Will terminate on empty string:
            return stream:read(BUFF_SIZE)
        end, 
        --[[Name]] vpath
    )

    if err then error(err) end

    return func
end

table.insert(package.loaders, require_moai_file)

-------------------------------------------------------------------------------
-- Disable logging.
-------------------------------------------------------------------------------

MOAILogMgr.setLogLevel(MOAILogMgr.LOG_NONE)

-------------------------------------------------------------------------------
-- Expose 'inspect', which brings up the interactive shell.
-- Places any passed value in the global 'VAL'.
-------------------------------------------------------------------------------

local repl = require "repl.console"

for _, plugin in ipairs { 'linenoise', 'history', 'completion', 'autoreturn' } do
    repl:loadplugin(plugin)
end

function inspect(val)
    _G.VAL = val
    local r = repl:clone()
    function r:run()
        self:prompt(1)
        for line in self:lines() do
            if line:trim() == "q" or line:trim() == "quit" then 
                return
            end
            local level = self:handleline(line)
            self:prompt(level)
        end
        self:shutdown()
    end
    r:run()
end

-------------------------------------------------------------------------------
-- Handle '-e <argument>' flag. 
-------------------------------------------------------------------------------

local function get_param(flag)
    for i,v in pairs(command_line_args) do
        if v == flag then
            return command_line_args[i+1]
        end
    end
    return nil
end

local exec_argument = get_param("-e")
if exec_argument then
    local f, err = loadstring(exec_argument)
    if not f then
        print("Error when processing '-e' flag, given string:")
        print(exec_argument) 
        error(err) 
    end
    -- Run the passed string:
    f()
end

-------------------------------------------------------------------------------
-- Are we a debug server? 
-------------------------------------------------------------------------------

if os.getenv('LANARTS_MOBDEBUG_SERVER') then 
    -- Run a debug server:
    require("mobdebug").listen()
    return -- Do not attempt normal loading
end

-------------------------------------------------------------------------------
-- Finally, if we are not a debug server, run the file provided by command-line.
-- We default to loading the 'main' module.
-------------------------------------------------------------------------------

local main_module = command_line_args[#command_line_args] or 'main'

-- If we are passed a .lua file, be more literal:
if main_module:match("%.lua$") then
    dofile(main_module)
else
    require(main_module)
end
