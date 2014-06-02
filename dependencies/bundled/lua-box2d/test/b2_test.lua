--[[------------------------------------------------------

  b2 test
  -------

  ...

--]]------------------------------------------------------
require 'lubyk'

local should = test.Suite('b2')

function should.autoLoad()
  assertTrue(b2)
end

function should.runHelloWorld()
  -- Define the gravity vector.
  local gravity = b2.Vec2(0.0, -10.0)

  -- Construct a world object, which will hold and simulate the rigid bodies.
  local world = b2.World(gravity)

  -- Define the ground body.
  local groundBodyDef = b2.BodyDef()
  groundBodyDef.position:Set(0.0, -10.0)
  -- Call the body factory which allocates memory for the ground body
  -- from a pool and creates the ground box shape (also from a pool).
  -- The body is also added to the world.
  local groundBody = world:CreateBody(groundBodyDef)

  -- Define the ground box shape.
  local groundBox = b2.PolygonShape()
  -- The extents are the half-widths of the box.
  groundBox:SetAsBox(50.0, 10.0)

  -- Add the ground fixture to the ground body.
  groundBody:CreateFixture(groundBox, 0.0)
  
  -- Define the dynamic body. We set its position and call the body factory.
  local bodyDef = b2.BodyDef()
  bodyDef.type = b2.dynamicBody
  bodyDef.position:Set(0.0, 4.0)
  local body = world:CreateBody(bodyDef)
  -- Define another box shape for our dynamic body.
  local dynamicBox = b2.PolygonShape()
  dynamicBox:SetAsBox(1.0, 1.0)

  -- Define the dynamic body fixture.
  local fixtureDef = b2.FixtureDef()

  fixtureDef.shape = dynamicBox

  -- Set the box density to be non-zero, so it will be dynamic.
  fixtureDef.density = 1.0

  -- Override the default friction.
  fixtureDef.friction = 0.3

  -- Add the shape to the body.
  body:CreateFixture(fixtureDef)
  -- Prepare for simulation. Typically we use a time step of 1/60 of a
  -- second (60Hz) and 10 iterations. This provides a high quality simulation
  -- in most game scenarios.
  local timeStep = 1.0 / 60.0
  local velocityIterations = 6
  local positionIterations = 2

  -- This is our little game loop.
  for i=1,60 do
    -- Instruct the world to perform a single step of simulation.
    -- It is generally best to keep the time step and iterations fixed.
    world:Step(timeStep, velocityIterations, positionIterations)

    -- Now print the position and angle of the body.
    local position = body:GetPosition()
    local angle = body:GetAngle()

    --printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle)
  end

  -- When the world destructor is called, all bodies and joints are freed. This can
  -- create orphaned pointers, so be careful about your world management.
end

function should.callDrawer()
  -- Define the gravity vector.
  local gravity = b2.Vec2(0.0, -10.0)

  -- Construct a world object, which will hold and simulate the rigid bodies.
  local world = b2.World(gravity)

  -- Define the ground body.
  local groundBodyDef = b2.BodyDef()
  groundBodyDef.position:Set(0.0, -10.0)
  -- Call the body factory which allocates memory for the ground body
  -- from a pool and creates the ground box shape (also from a pool).
  -- The body is also added to the world.
  local groundBody = world:CreateBody(groundBodyDef)

  -- Define the ground box shape.
  local groundBox = b2.PolygonShape()
  -- The extents are the half-widths of the box.
  groundBox:SetAsBox(50.0, 10.0)

  -- Add the ground fixture to the ground body.
  groundBody:CreateFixture(groundBox, 0.0)
  
  local called = false
  -- Create drawing engine
  local drawer = b2.Drawer()
	world:SetDebugDraw(drawer)
	drawer:SetFlags(bit.bor(b2.Draw.e_shapeBit, b2.Draw.e_jointBit))
  
  
  function drawer:DrawSolidPolygon()
    called = true
  end

  world:Step(1/60, 6, 2)

	world:DrawDebugData()
  assertTrue(called)
end

test.all()
