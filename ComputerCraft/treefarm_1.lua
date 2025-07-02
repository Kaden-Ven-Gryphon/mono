-- Tree Farm
-- Version 1.0
-- Nox

RunMainLoop = true;
StartCord = {x=-81,y=106,z=-79};
RowLength = 12;
RowCount = 1;
FarmDir = "East";
DropCord = {x=-84,y=107,z=-81};

DigWhileMove = true;
SuckWhileMove = true;

FuelType = "thermal:charcoal_block"

LeftTurnDirUpdate = {["North"] = "West", ["West"] = "South", ["South"] = "East", ["East"] = "North"};
RightTrunDirUpdate = {["North"] = "East", ["West"] = "North", ["South"] = "West", ["East"] = "South"};
Pos = {x=0,y=0,z=0};
Direction = "South";


local function getdirection(a, b)
	-- print("DEBUG: a: ", a.x, " b: ", b.x)
	if a.x > b.x and a.y == b.y and a.z == b.z then
		return "West";
	elseif a.x < b.x and a.y == b.y and a.z == b.z then
		return "East";
	elseif a.x == b.x and a.y == b.y and a.z > b.z then
		return "North";
	elseif a.x == b.x and a.y == b.y and a.z < b.z then
		return "South";
	elseif a.x == b.x and a.y == b.y and a.z == b.z then
		return "Same";
	end
	return nil;
end

local function updatePos()
	Pos.x, Pos.y, Pos.z = gps.locate();
end

local function turnTo(dir)
	while Direction ~= dir do
		turtle.turnLeft();
		Direction = LeftTurnDirUpdate[Direction];
	end
end

local function moveDirection(dir, dis)
	if dir == "Up" then
		for i=1,dis,1 do
			turtle.up();
			if DigWhileMove then
				turtle.digUp();
			end
			if SuckWhileMove then
				turtle.suck();
			end
		end
		return;
	end
	if dir == "Down" then
		for i=1,dis,1 do
			turtle.down();
			if DigWhileMove then
				turtle.digDown()
			end
			if SuckWhileMove then
				turtle.suck();
			end
		end
		return;
	end
	turnTo(dir);
	for i=1,dis,1 do
		turtle.forward();
		if DigWhileMove then
			turtle.dig()
		end
		if SuckWhileMove then
			turtle.suck();
		end
	end
end

local function moveToPos(p)
	updatePos()
	local xDif = p.x - Pos.x;
	local yDif = p.y - Pos.y;
	local zDif = p.z - Pos.z;

	print("DEBUG: moving ", xDif, " ", yDif, " ", zDif)

	if yDif > 0 then
		moveDirection("Up", yDif);
	elseif yDif < 0 then
		moveDirection("Down", -1*yDif);
	end
	if xDif > 0 then
		moveDirection("East", xDif);
	elseif xDif < 0 then
		moveDirection("West", -1*xDif);
	end
	if zDif > 0 then
		moveDirection("South", zDif);
	elseif zDif < 0 then
		moveDirection("North", -1*zDif);
	end
end




-- States
LastState = "patrol";
State = "findDir";


local function stop()
	RunMainLoop = false
end



-- State Functions
local function updateDirState()
	print("LOG: Updateing stored direction");

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
			local result = getdirection(a, b);
			turtle.back();
			if result ~= nil then
				Direction = result;
				break;
			else
				print("ERROR: Turtle is stuck and can not figure out direction");
			end
		end	
		turtle.turnLeft();
	end

	print("LOG: Is facing " .. Direction);
	State = LastState;
end

local function cutDownTree()
	print("LOG: Cutting Down Tree");
	turtle.dig();
	turtle.forward();
	for i=1,5,1 do
		turtle.digUp();
		turtle.up();
	end
	for i=1,5,1 do
		turtle.down();
	end
	turtle.back();
end

local function plantSappling()
	print("LOG: Planting Sappling")
	turtle.select(1);
	local item = turtle.getItemDetail();
	if item.name == "minecraft:oak_sapling" then
		if item.count > 1 then
			turtle.place();
		else
			print("OUT OF SAPPLINGS");
		end
	end
end

local function goToFarmStart()
	print("LOG: Going to farm start location");
	if FarmDir == "North" or FarmDir == "South" then
		local a = {};
		a.x, a.y, a.z = gps.locate();
		a.z = StartCord.z;
		moveToPos(a);
	else
		local a = {};
		a.x, a.y, a.z = gps.locate();
		a.x = StartCord.x;
		moveToPos(a);
	end

	moveToPos(StartCord);
	turnTo(RightTrunDirUpdate[FarmDir])

	turtle.turnLeft();
	turtle.forward();
	turtle.turnRight();

	State = LastState;
end



local function patrolFarm()
	print("LOG: Starting patrol");
	updatePos();
	goToFarmStart();

	for row=1,RowCount,1 do
		-- Look for tree
		for i=1,RowLength,1 do
			local hasBlock, data = turtle.inspect();
			if hasBlock and data.name == "minecraft:oak_log" then
				cutDownTree();
				plantSappling();
			else
				plantSappling();
			end
			turtle.turnLeft();
			turtle.dig();
			turtle.forward();
			turtle.suck();
			turtle.turnRight();
		end
		turtle.dig();
		turtle.forward();
		turtle.dig();
		turtle.forward();
		turtle.turnRight();
		turtle.dig();
		turtle.forward();
		turtle.turnLeft();
		for i=1,RowLength,1 do
			local hasBlock, data = turtle.inspect();
			if hasBlock and data.name == "minecraft:oak_log" then
				cutDownTree();
				plantSappling();
			else
				plantSappling();
			end
			turtle.turnRight();
			turtle.dig();
			turtle.forward();
			turtle.suck();
			turtle.turnLeft();
		end
		turtle.dig();
		turtle.forward();
		turtle.dig();
		turtle.forward();
		turtle.turnLeft();
		turtle.dig();
		turtle.forward();
		turtle.turnRight();

	end
	goToFarmStart();
	State = "restock";
end



local function restockAndFuel()
	turtle.digUp();
	turtle.up();
	moveToPos(DropCord);
	turnTo(RightTrunDirUpdate[FarmDir]);
	turtle.turnRight();
	for i=3,16,1 do
		turtle.select(i);
		turtle.drop();
	end
	local item = turtle.getItemDetail(2);
	if item.name ~= FuelType then
		turtle.select(2);
		turtle.drop();
	end
	item = turtle.getItemDetail(1);
	if item.name ~= "minecraft:oak_sapling" then
		turtle.select(1);
		turtle.drop();
	end
	turtle.select(1)
	turtle.turnLeft();
	turtle.forward();
	turtle.turnRight();
	turtle.select(2);
	turtle.refuel();
	item = turtle.getItemDetail();
	if item ~= nil then
		local missing = 64 - item.count;
		turtle.suck(missing);
	else
		turtle.suck(64);
	end

	turtle.turnLeft();
	turtle.forward();
	turtle.turnRight();
	turtle.select(1);
	item = turtle.getItemDetail();
	if item ~= nil then
		local missing = 64 - item.count;
		turtle.suck(missing);
	else
		turtle.suck(64);
	end
	
	turtle.turnRight();
	turtle.turnRight();
	turtle.dig();
	turtle.forward();

	State = patrolFarm();

end


-- State table
States = {
	findDir=updateDirState,
	patrol=patrolFarm,
	returnToStart=goToFarmStart,
	restock=restockAndFuel
};

while RunMainLoop do
	States[State]();
end



-- Planner

-- Get orientation
-- Get to farmstart
-- Loop
--  Patrol for trees
--    cut down tree
--  Suck items
--  Plant sapplings
--  Deposit Items get sapplings and fuel
--  Optional bonemeal

-- Interupts
--   Low Fuel
--   Lost
--   Low sapplings
--   idle