import socket
import time

HEADER_SIZE = 64
PACKET_SIZE = 1024
FORMAT = 'utf-8'

PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)

DISCONNECT_MESSAGE = '!DISCONNECT'
ENDBC_MESSAGE = '!ENDBC'
STARTBC_MESSAGE = '!STARTBC'
END_MESSAGE = '!END'
ECHO_MESSAGE = '!ECHO'

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


def send(msg):
	message = msg.encode(FORMAT)
	client.sendto(message, ADDR)


#send(END_MESSAGE)

send(STARTBC_MESSAGE)

for i in range(0, 10):
	msg, addr = client.recvfrom(PACKET_SIZE)
	#msg = msg.decode(FORMAT)
	x = msg[:4]
	y = msg[4:8]
	z = msg[8:]
	x = int.from_bytes(x, 'little', signed=True)
	y = int.from_bytes(y, 'little', signed=True)
	z = int.from_bytes(z, 'little', signed=True)
	print(f"[{addr}] message: {x}, {y}, {z}")
send(ENDBC_MESSAGE)

time.sleep(5)

send(END_MESSAGE)


