----------------
--LOCAL FIELDS
----------------
local W = 1000
local H = 1000
local x,y = 1,1
local dx,dy = 600,300


----------------
--CALLED ON INIT
----------------
function start()
print("playerController called")
end

----------------
--CALLED ON UPDATE
----------------
function update(deltaTime)
	x = x + dx * deltaTime;
	y = y + dy * deltaTime;
	
	if x > W or x <= 0 then
	 dx = -dx
	end

	if y > H or y <= 0 then
	 dy = -dy
	end

	setPlayerPos(x,y)
end

----------------
--CALLED ON render
----------------
function draw()
end