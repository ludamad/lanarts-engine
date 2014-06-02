local HostState = newtype()

-- A hosted game can optionally require a password
local Game = typedef [[
    name : string
    password : string
    players : list
]]

-- Username + userid uniquely identify a player
local Player = typedef [[
    username : string
    userid : string
]]



return { HostState = HostState }