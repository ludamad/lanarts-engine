import zmq, thread, net from require 'luv'

-- ZMQ Context
Z = zmq.create 1

prod = thread.spawn () ->
   with Z\socket zmq.PAIR
      \bind('inproc://#1')
      \send("tick: ")
      \recv()
      \close()

cons = thread.spawn () ->
   with Z\socket zmq.PAIR
       \connect('inproc://#1')
       \recv()
       \send('OK')
       \close()

cons\join()



