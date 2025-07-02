---@diagnostic disable: undefined-field
-- Turtle Base Modual
-- Version 1.0
-- Nox
-- A set up common functions for all turtles to use.  Including navigation
-- orientations, states, refueling, and such

-- The modual to be returned
M = {}


-- Run the main loop
M.RunMainLoop = true;
M.State = "Idle";
M.InteruptState = "Idle";
M.IdleTime = 5;
M.States = {};
M.EventHandlers = {};

-- Where to go when idle, and where to go when to retire
M.HomeCord = {x=0,y=0,z=0};
M.RetireCord = {x=0,y=0,z=0};


-- Info about the fuel type and refuel location
M.FuelType = "termal:charcoal_block";
M.FuelCord = {x=0,y=0,z=0};

-- Position and Direction of turtle
M.Pos = {x=0,y=0,z=0};
M.Dir = "North";

-- Movment behaviors
M.DigWhileMove = true;
M.SuckWhileMove = true;
M.MoveOrder = {"y", "x", "z"};

-- Blocks the turtle is not alowed to break
M.DigList = {["minecraft:chest"] = false};

-- List of cords for the turtle to use for navigations
M.WayPoints = {}

-- Static vars
M.LeftTurnDirUpdate = {["North"] = "West", ["West"] = "South", ["South"] = "East", ["East"] = "North"};
M.RightTrunDirUpdate = {["North"] = "East", ["West"] = "North", ["South"] = "West", ["East"] = "South"};
M.ReverseTurnDirUpdate = {["North"] = "South", ["West"] = "East", ["South"] = "North", ["East"] = "West"};
M.DirToAxis = {North = "z", South = "z", East = "x", West = "x", Up = "y", Down = "y"};
M.DirToAxisDir = {North = -1, South = 1, East = 1, West = -1, Up = 1, Down = -1};

-- Calulation Functions 

-- Returns West, East, North, South, Down, Up, Same,
-- or if not in a stright line nil
function M.getDirection(a, b)
	if a.x > b.x and a.y == b.y and a.z == b.z then
		return "West";
	elseif a.x < b.x and a.y == b.y and a.z == b.z then
		return "East";
	elseif a.x == b.x and a.y == b.y and a.z > b.z then
		return "North";
	elseif a.x == b.x and a.y == b.y and a.z < b.z then
		return "South";
	elseif a.x == b.x and a.y > b.y and a.z == b.z then
		return "Down";
	elseif a.x == b.x and a.y < b.y and a.z == b.z then
		return "Up";
	elseif a.x == b.x and a.y == b.y and a.z == b.z then
		return "Same";
	end
	return nil;
end

-- Use GPS to update stored position
function M.updatePos()
	M.Pos.x, M.Pos.y, M.Pos.z = gps.locate();
end


-- Basic Turtle Function Overrides

-- Turns the turtle while updating its internal Dir state
function M.turnLeft()
	turtle.turnLeft();
	M.Dir = M.LeftTurnDirUpdate[M.Dir];
end

function M.turnRight()
	turtle.turnRight();
	M.Dir = M.RightTrunDirUpdate[M.Dir];
end

function M.reverse()
	turtle.turnRight();
	turtle.turnRight();
	M.Dir = M.ReverseTurnDirUpdate[M.Dir];
end

-- Uses the DigList to decide if it should dig
-- returns true if it digged, or false if not allowed
-- or there was no block
function M.dig()
	local hasBlock, data = turtle.inspect();
	if hasBlock then
		if M.DigList[data.name] or M.DigList[data.name] == nil then
			return turtle.dig();
		end
	end
	return false;
end

function M.digUp()
	local hasBlock, data = turtle.inspectUp();
	if hasBlock then
		if M.DigList[data.name] or M.DigList[data.name] == nil then
			return turtle.digUp();
		end
	end
	return false;
end

function M.digDown()
	local hasBlock, data = turtle.inspectDown();
	if hasBlock then
		if M.DigList[data.name] or M.DigList[data.name] == nil then
			return turtle.digDown();
		end
	end
	return false;
end

-- Uses the digwhilemove and suckwhilemove
-- Updates the internal Pos
-- returns the turtle.move bool
function M.forward()
	if M.SuckWhileMove then
		turtle.suck();
	end
	if M.DigWhileMove then
		M.dig();
	end
	local move = turtle.forward();
	if move then
		M.Pos[M.DirToAxis[M.Dir]] = M.Pos[M.DirToAxis[M.Dir]] + M.DirToAxisDir[M.Dir];
	end
	return move;
end

function M.back()
	if M.SuckWhileMove then
		turtle.suck();
	end
	local move = turtle.back();
	if move then
		M.Pos[M.DirToAxis[M.Dir]] = M.Pos[M.DirToAxis[M.Dir]] - M.DirToAxisDir[M.Dir];
	end
	return move;
end

function M.up()
	if M.SuckWhileMove then
		turtle.suckUp();
	end
	if M.DigWhileMove then
		M.digUp();
	end
	local move = turtle.up();
	if move then
		M.Pos.y = M.Pos.y + 1;
	end
	return move;
end

function M.down()
	if M.SuckWhileMove then
		turtle.suckDown();
	end
	if M.DigWhileMove then
		M.digDown();
	end
	local move = turtle.down();
	if move then
		M.Pos.y = M.Pos.y - 1;
	end
	return move;
end


-- Turn the turtle torwards a cardinal direction
function M.turnTo(dir)
	if dir == M.Dir then
		return;
	end
	if dir == LeftTurnDirUpdate[M.Dir] then
		M.turnLeft();
	elseif dir == M.RightTrunDirUpdate[M.Dir] then
		M.turnRight();
	elseif dir == M.ReverseTurnDirUpdate[M.Dir] then
		M.reverse();
	end
end

-- Move X spaces in given direction
function M.moveDir(dir, dis)
	if dir == "Up" then
		for i=1,dis,1 do
			M.up();
		end
		return;
	end
	if dir == "Down" then
		for i=1,dis,1 do
			M.down();
		end
		return;
	end
	M.turnTo(dir);
	for i=1,dis,1 do
		M.forward();
	end
end

-- Move to Cord using the moveOrder
function M.moveToCord(p)
	M.updatePos();
	local xDif = p.x - Pos.x;
	local yDif = p.y - Pos.y;
	local zDif = p.z - Pos.z;

	for _, axis in M.MoveOrder do
		if axis == "x" then
			if xDif > 0 then
				M.moveDir("East", xDif);
			elseif xDif < 0 then
				M.moveDir("West", -1*xDif);
			end
		elseif axis == "y" then
			if yDif > 0 then
				M.moveDir("Up", yDif);
			elseif yDif < 0 then
				M.moveDir("Down", -1*yDif);
			end
		elseif axis == "z" then
			if zDif > 0 then
				M.moveDir("South", zDif);
			elseif zDif < 0 then
				M.moveDir("North", -1*zDif);
			end
		end
	end
end

-- Does a wiggle to figureout current orientation
-- Disables dig, and suck during wiggle
function M.findOrientation()
	-- Try Each Direction
	for i = 1, 4, 1 do
		-- Get Start position
		local a = {};
		a.x, a.y, a.z = gps.locate();
		
		-- Try to move
		local moved = turtle.forward();
		if moved then
			-- Get new postion and determen direction
			local b = {};
			b.x, b.y, b.z = gps.locate();
			local result = M.getdirection(a, b);
			turtle.back();
			if result ~= nil then
				Direction = result;
				for j = 1,i-1,1 do
					M.turnRight();
				end
				break;
			else
				printError("ERROR: Turtle is stuck and can not figure out direction");
			end
		end	
		turtle.turnLeft();
	end
end


-- Inventory Functions

function M.countEmptySlots()
	local count = 0;
	for i=1,16,1 do
		local info = turtle.getItemDetail(i);
		if info == nil then
			count = count + 1;
		end
	end
	return count;
end

function M.dropAll()
	for i=1,16,1 do
		turtle.select(i);
		turtle.drop();
	end
end

function M.dropAllUp()
	for i=1,16,1 do
		turtle.select(i);
		turtle.dropUp();
	end
end

function M.dropAllDown()
	for i=1,16,1 do
		turtle.select(i);
		turtle.dropDown();
	end
end

-- Drop Non protected
-- Drops all inventory except for protected slots

-- TODO

-- Filter Slot

-- Filter All

--TODO add filter globals

-- The Idle state function, and 
function M.EventHandlers.Idle()
	if M.State == "Idle" then
		print("IdleEvent");
		os.sleep(M.IdleTime);
		os.queueEvent("Wake");
		os.queueEvent("Idle");
	end
end

function M.States.Idle()
	print("IdleState");
	os.sleep(M.IdleTime);
end

function M.Stop()
	M.RunMainLoop = false;
end

-- The main loop
-- Pulls next event and handles it
-- Then runs the state function
function M.Run()
	while RunMainLoop do
		local event = {os.pullEvent()}
		if M.EventHandlers[event[1]] ~= nil then
			M.EventHandlers[event[1]](event);
		end
		if M.States[M.state] ~= nil then
			M.States[M.state]();
		end
	end
end

-- Return the modual to the calling 'require' function
return M;
