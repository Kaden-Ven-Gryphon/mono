extends Node

var startx = 300
var starty = 300
var mult = 0.1
var center = 5000


var client = PacketPeerUDP.new()
var url = "localhost:5050"
var SERVER = "192.168.1.165"
var PORT = 5050

func _ready():
	var err = client.connect_to_host(SERVER, PORT)
	
	if err != OK:
		set_process(false)
		print("unable to connect")
	else:
		var msg = "!STARTBC"
		client.put_packet(msg.to_utf8())
		set_process(true)
	
func _process(_delta):
	if(not client.is_listening()):
		$debug.text += "not listening"
		return
	while(client.get_available_packet_count() > 0):
		var packet = client.get_packet()
		
		var stream = StreamPeerBuffer.new()
		stream.data_array = packet
		stream.big_endian = false
		var bufsize = stream.get_size()
		var x1 = float((stream.get_32())-center)*mult
		var y1 = float((stream.get_32())-center)*mult
		var _z = float(stream.get_32())
		var x2 = float((stream.get_32())-center)*mult
		var y2 = float((stream.get_32())-center)*mult
		var x3 = float((stream.get_32())-center)*mult
		var y3 = float((stream.get_32())-center)*mult
		var x4 = float((stream.get_32())-center)*mult
		var y4 = float((stream.get_32())-center)*mult
		
		var nosepoly = Polygon2D.new()
		nosepoly.set_polygon(PoolVector2Array([
			Vector2(x1+3, y1),
			Vector2(x2+3, y2),
			Vector2(x3+3, y3),
			Vector2(x4+3, y4),
			Vector2(x4-3, y4),
			Vector2(x3-3, y3),
			Vector2(x2-3, y2),
			Vector2(x1-3, y1)
		]))
		
		
		x1 = float((stream.get_32())-center)*mult
		y1 = float((stream.get_32())-center)*mult
		x2 = float((stream.get_32())-center)*mult
		y2 = float((stream.get_32())-center)*mult
		x3 = float((stream.get_32())-center)*mult
		y3 = float((stream.get_32())-center)*mult
		
		var leftbrowpoly = Polygon2D.new()
		leftbrowpoly.set_polygon(PoolVector2Array([
			Vector2(x1, y1),
			Vector2(x2, y2),
			Vector2(x3, y3),
			Vector2(x3, y3+3),
			Vector2(x2, y2+3),
			Vector2(x1, y1+3)
		]))
		
		x1 = float((stream.get_32())-center)*mult
		y1 = float((stream.get_32())-center)*mult
		x2 = float((stream.get_32())-center)*mult
		y2 = float((stream.get_32())-center)*mult
		x3 = float((stream.get_32())-center)*mult
		y3 = float((stream.get_32())-center)*mult
		
		var rightbrowpoly = Polygon2D.new()
		rightbrowpoly.set_polygon(PoolVector2Array([
			Vector2(x1, y1),
			Vector2(x2, y2),
			Vector2(x3, y3),
			Vector2(x3, y3+3),
			Vector2(x2, y2+3),
			Vector2(x1, y1+3)
		]))
		
		
		x1 = float((stream.get_32())-center)*mult
		y1 = float((stream.get_32())-center)*mult
		x2 = float((stream.get_32())-center)*mult
		y2 = float((stream.get_32())-center)*mult
		x3 = float((stream.get_32())-center)*mult
		y3 = float((stream.get_32())-center)*mult
		x4 = float((stream.get_32())-center)*mult
		y4 = float((stream.get_32())-center)*mult
		var x5 = float((stream.get_32())-center)*mult
		var y5 = float((stream.get_32())-center)*mult
		var x6 = float((stream.get_32())-center)*mult
		var y6 = float((stream.get_32())-center)*mult
		var x7 = float((stream.get_32())-center)*mult
		var y7 = float((stream.get_32())-center)*mult
		
		var lefteyepoly = Polygon2D.new()
		lefteyepoly.set_polygon(PoolVector2Array([
			Vector2(x1, y1),
			Vector2(x2, y2),
			Vector2(x3, y3),
			Vector2(x4, y4),
			Vector2(x5, y5),
			Vector2(x6, y6),
			Vector2(x7, y7)
		]))
		
		x1 = float((stream.get_32())-center)*mult
		y1 = float((stream.get_32())-center)*mult
		x2 = float((stream.get_32())-center)*mult
		y2 = float((stream.get_32())-center)*mult
		x3 = float((stream.get_32())-center)*mult
		y3 = float((stream.get_32())-center)*mult
		x4 = float((stream.get_32())-center)*mult
		y4 = float((stream.get_32())-center)*mult
		x5 = float((stream.get_32())-center)*mult
		y5 = float((stream.get_32())-center)*mult
		x6 = float((stream.get_32())-center)*mult
		y6 = float((stream.get_32())-center)*mult
		x7 = float((stream.get_32())-center)*mult
		y7 = float((stream.get_32())-center)*mult
		
		var righteyepoly = Polygon2D.new()
		righteyepoly.set_polygon(PoolVector2Array([
			Vector2(x1, y1),
			Vector2(x2, y2),
			Vector2(x3, y3),
			Vector2(x4, y4),
			Vector2(x5, y5),
			Vector2(x6, y6),
			Vector2(x7, y7)
		]))
		
		x1 = float((stream.get_32())-center)*mult
		y1 = float((stream.get_32())-center)*mult
		x2 = float((stream.get_32())-center)*mult
		y2 = float((stream.get_32())-center)*mult
		x3 = float((stream.get_32())-center)*mult
		y3 = float((stream.get_32())-center)*mult
		x4 = float((stream.get_32())-center)*mult
		y4 = float((stream.get_32())-center)*mult
		x5 = float((stream.get_32())-center)*mult
		y5 = float((stream.get_32())-center)*mult
		x6 = float((stream.get_32())-center)*mult
		y6 = float((stream.get_32())-center)*mult
		x7 = float((stream.get_32())-center)*mult
		y7 = float((stream.get_32())-center)*mult
		var x8 = float((stream.get_32())-center)*mult
		var y8 = float((stream.get_32())-center)*mult
		
		var uplippoly = Polygon2D.new()
		uplippoly.set_polygon(PoolVector2Array([
			Vector2(x1, y1),
			Vector2(x2, y2),
			Vector2(x3, y3),
			Vector2(x4, y4),
			Vector2(x5, y5),
			Vector2(x6, y6),
			Vector2(x7, y7),
			Vector2(x8, y8)
		]))
		
		x1 = float((stream.get_32())-center)*mult
		y1 = float((stream.get_32())-center)*mult
		x2 = float((stream.get_32())-center)*mult
		y2 = float((stream.get_32())-center)*mult
		x3 = float((stream.get_32())-center)*mult
		y3 = float((stream.get_32())-center)*mult
		x4 = float((stream.get_32())-center)*mult
		y4 = float((stream.get_32())-center)*mult
		x5 = float((stream.get_32())-center)*mult
		y5 = float((stream.get_32())-center)*mult
		x6 = float((stream.get_32())-center)*mult
		y6 = float((stream.get_32())-center)*mult
		x7 = float((stream.get_32())-center)*mult
		y7 = float((stream.get_32())-center)*mult
		x8 = float((stream.get_32())-center)*mult
		y8 = float((stream.get_32())-center)*mult
		
		var downlippoly = Polygon2D.new()
		downlippoly.set_polygon(PoolVector2Array([
			Vector2(x1, y1),
			Vector2(x2, y2),
			Vector2(x3, y3),
			Vector2(x4, y4),
			Vector2(x5, y5),
			Vector2(x6, y6),
			Vector2(x7, y7),
			Vector2(x8, y8)
		]))
		
		
		for child in get_node("Mesh").get_children():
			child.queue_free()
		
		
		get_node("Mesh").add_child(nosepoly)
		get_node("Mesh").add_child(leftbrowpoly)
		get_node("Mesh").add_child(rightbrowpoly)
		get_node("Mesh").add_child(lefteyepoly)
		get_node("Mesh").add_child(righteyepoly)
		get_node("Mesh").add_child(uplippoly)
		get_node("Mesh").add_child(downlippoly)
		$debug.text = "Got message from server: " + str(bufsize)



func send(msg):
	client.put_packet(msg.to_utf8())


func _on_Button_pressed():
	send("!END")
