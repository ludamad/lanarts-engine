require "src.globals.misc"

--------------------------------------------------------------------------------
-- Networking interchange for an active game.
--------------------------------------------------------------------------------

local enet = require "enet"
local luv = require "luv"

local Z = luv.zmq.create(1)

--------------------------------------------------------------------------------
-- On a separate thread, echo reliable and unreliable to a handler, using ZMQ.
--------------------------------------------------------------------------------

local function server_func(args)
    local host = enet.host_create("localhost:7890", nil, 2)
    local players = {}
    Z:socket()
end

local function client_func(args)
    local host = enet.host_create()
    local server = host:connect("localhost:7890", 2)
end

--------------------------------------------------------------------------------
-- From the main thread set up an echo for reliable and unreliable messages, 
-- using ZMQ.
--------------------------------------------------------------------------------

local function start_server(args)
    -- Create a coroutine that will run our handler functions
    MOAIThread.new():run(function()
        
    end)
end