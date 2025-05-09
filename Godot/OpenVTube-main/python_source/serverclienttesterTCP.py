import socket

HEADER_SIZE = 64
PACKET_SIZE = 64
FORMAT = 'utf-8'

PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)

DISCONNECT_MESSAGE = '!DISCONNECT'
END_MESSAGE = '!END'

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)


def send(msg):
	message = msg.encode(FORMAT)
	msg_length = len(message)
	send_length = str(msg_length).encode(FORMAT)
	send_length += b' ' * (HEADER_SIZE - len(send_length))
	client.send(send_length)
	client.send(message)


send("Hello World!")
send(END_MESSAGE)
