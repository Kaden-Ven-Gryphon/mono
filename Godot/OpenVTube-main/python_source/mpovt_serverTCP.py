import socket
import threading
import cv2
import mediapipe as mp
import numpy as np

HEADER_SIZE = 64
PACKET_SIZE = 64
FORMAT = 'utf-8'

PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)

DISCONNECT_MESSAGE = '!DISCONNECT'
END_MESSAGE = '!END'

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

run_server = True

def handle_client(conn, addr):
	print(f"[NEW CONNECTION] {addr} connected")
	global run_server
	
	connected = True
	while connected:
		msg_length = conn.recv(HEADER_SIZE).decode(FORMAT)
		if msg_length:
			msg_length = int(msg_length)
			msg = conn.recv(msg_length).decode(FORMAT)
			
			if msg == DISCONNECT_MESSAGE:
				connected = False
			if msg == END_MESSAGE:
				connected = False
				run_server = False
			
			print(f"[{addr}] {msg}")
	if not run_server:
		conn.shutdown(socket.SHUT_RDWR)
	conn.close()

def start():
	server.listen()
	server.settimeout(1)
	print(f"[LISTENING] server is listening on {SERVER}")
	while run_server:
		print(f"[STATUS] run_server is {run_server}")
		try:
			conn, addr = server.accept()
			thread = threading.Thread(target=handle_client, args=(conn, addr))
			thread.start()
			print(f"[ACTIVE CONNECTION] active connections {threading.activeCount() - 1}")
		except:
			pass
	return
		

print("[STARTING] server is starting uwu...")
start()
print("[CLOSEING] server is ending, bye...")
exit()

