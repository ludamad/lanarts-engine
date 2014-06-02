local luv = require('luv')

local zmq = luv.zmq.create(1)

local prod = luv.thread.spawn(function()
   local pub = zmq:socket(luv.zmq.PAIR)
   pub:bind('inproc://#1')

   pub:send("tick: ")
   print(pub:recv())
   pub:close()
end)

local cons = luv.thread.spawn(function()
   local sub = zmq:socket(luv.zmq.PAIR)
   sub:connect('inproc://#1')

   sub:recv()

   sub:send('OK')
   sub:close()
end)

cons:join()


