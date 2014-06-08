local BoolGrid = require "BoolGrid"

local bg = BoolGrid.create(100,100)

for x=1,100 do
    for y=1,100 do
        bg:set(x, y, (x == y))
    end
end

for x=1,100 do
    for y=1,100 do
        assert(bg:get(x, y) == (x == y), "Failed for " .. x .. " and " .. y)
    end
end

print "Passed BoolGrid tests!"

