-- Simple adapter
local busted = require 'busted.core'
for k, v in pairs(busted) do
    _G[k] = v
end
return busted
