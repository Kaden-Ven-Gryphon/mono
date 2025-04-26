extends Node

#the udp listener
var client = PacketPeerUDP.new()
var SERVER = "192.168.1.165"
var PORT = 5050

var isTracking = false
var drawMesh = false

var nosepoints = []
var leftbrowpoints = []
var rightbrowpoints = []
var lefteyepoints = []
var righteyepoints = []
var uplippoints = []
var downlippoints = []

var bkgdpoints = []

#10 000 is the max value, changes 0 to 10k to -5k to 5k
var center = 5000
#scale agustment
var mult = 0.05

func _ready():
	set_process(false)
	nosepoints.resize(4)
	nosepoints.fill(Vector2(0,0))
	leftbrowpoints.resize(3)
	leftbrowpoints.fill(Vector2(0,0))
	rightbrowpoints.resize(3)
	rightbrowpoints.fill(Vector2(0,0))
	lefteyepoints.resize(7)
	lefteyepoints.fill(Vector2(0,0))
	righteyepoints.resize(7)
	righteyepoints.fill(Vector2(0,0))
	uplippoints.resize(8)
	uplippoints.fill(Vector2(0,0))
	downlippoints.resize(8)
	downlippoints.fill(Vector2(0,0))
	
	bkgdpoints.append(Vector2(-center*mult, center*mult))
	bkgdpoints.append(Vector2(center*mult, center*mult))
	bkgdpoints.append(Vector2(center*mult, -center*mult))
	bkgdpoints.append(Vector2(-center*mult, -center*mult))
	var background = Polygon2D.new()
	background.set_polygon(PoolVector2Array(bkgdpoints))
	background.set_color(Color(0,1,0))
	get_node("greenscreen").add_child(background)

func _process(_delta):
	if isTracking:
		get_facemesh()
		if drawMesh:
			draw_polys()

#function to call to start streaming tracking data
func start_connect():
	var err = client.connect_to_host(SERVER, PORT)
	if err != OK:
		set_process(false)
		print("unable to connect")
	else:
		var msg = "!STARTBC"
		client.put_packet(msg.to_utf8())
		set_process(true)
		isTracking = true

#tell the server to stop streaming tracking data
func end_connect():
	var msg = "!ENDBC"
	client.put_packet(msg.to_utf8())
	isTracking = false

func shut_down_server():
	var msg = "!END"
	client.put_packet(msg.to_utf8())
	isTracking = false

#get all the face mesh points from the server
func get_facemesh():
	if(not client.is_listening()):
		return
	while(client.get_available_packet_count() > 0):
		var stream = StreamPeerBuffer.new()
		stream.data_array = client.get_packet()
		stream.big_endian = false
		for i in 4:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			nosepoints[i] = Vector2(x,y)
		for i in 3:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			leftbrowpoints[i] = Vector2(x,y)
		for i in 3:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			rightbrowpoints[i] = Vector2(x,y)
		for i in 7:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			lefteyepoints[i] = Vector2(x,y)
		for i in 7:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			righteyepoints[i] = Vector2(x,y)
		for i in 8:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			uplippoints[i] = Vector2(x,y)
		for i in 8:
			var x = float((stream.get_32())-center)*mult
			var y = float((stream.get_32())-center)*mult
			downlippoints[i] = Vector2(x,y)

#draw polygons to preview the face mesh
func draw_polys():
	for child in get_node("facemeshpolys").get_children():
			child.queue_free()
		
	var gon1 = Polygon2D.new()
	gon1.set_polygon(PoolVector2Array(nosepoints))
	var gon2 = Polygon2D.new()
	gon2.set_polygon(PoolVector2Array(leftbrowpoints))
	var gon3 = Polygon2D.new()
	gon3.set_polygon(PoolVector2Array(rightbrowpoints))
	var gon4 = Polygon2D.new()
	gon4.set_polygon(PoolVector2Array(lefteyepoints))
	var gon5 = Polygon2D.new()
	gon5.set_polygon(PoolVector2Array(righteyepoints))
	var gon6 = Polygon2D.new()
	gon6.set_polygon(PoolVector2Array(uplippoints))
	var gon7 = Polygon2D.new()
	gon7.set_polygon(PoolVector2Array(downlippoints))
	get_node("facemeshpolys").add_child(gon1)
	get_node("facemeshpolys").add_child(gon2)
	get_node("facemeshpolys").add_child(gon3)
	get_node("facemeshpolys").add_child(gon4)
	get_node("facemeshpolys").add_child(gon5)
	get_node("facemeshpolys").add_child(gon6)
	get_node("facemeshpolys").add_child(gon7)
	
#for the button to togle tracking
func togle_tracking():
	if isTracking:
		end_connect()
	else:
		start_connect()

func togle_mesh():
	drawMesh = not drawMesh
	if not drawMesh:
		for child in get_node("facemeshpolys").get_children():
			child.queue_free()
