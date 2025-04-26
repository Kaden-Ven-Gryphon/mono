import socket
import threading
import cv2
import time
import mediapipe as mp
import numpy as np

#Protocal info
HEADER_SIZE = 64
PACKET_SIZE = 1024
FORMAT = 'utf-8'
BROADCAST_FRAME_RATE = 0.05

#address info
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)

#special messages
DISCONNECT_MESSAGE = '!DISCONNECT'
ENDBC_MESSAGE = '!ENDBC'
STARTBC_MESSAGE = '!STARTBC'
END_MESSAGE = '!END'
ECHO_MESSAGE = '!ECHO'
NOTRACKING_MESSAGE = '!NOTRACK'

#socket vars
global server
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(ADDR)

#mp vars
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(min_detection_confidence=0.5, min_tracking_confidence=0.5)


run_server = True
broadcast = True

#this is a thread that broadcast the tracking info at regular intervals
def broadcast_tracking(addr):
	global broadcast
	print(f"[BROADCASTING] starting broadcast to [{addr}]")
	#first open the cammera
	cap = cv2.VideoCapture(0)
	while broadcast:
		
		
		if cap.isOpened():
			#get the frame
			success, image = cap.read()
			img_h, img_w, img_c, = image.shape
			multi = 10000
			ratio = multi*(img_h/img_w)
			#proccess frame
			image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
			image.flags.writeable = False
			results = face_mesh.process(image)
			image.flags.writeable = True
			#get cords for important points
			if results.multi_face_landmarks:
				for face_landmarks in results.multi_face_landmarks:
					#nose
					msg = int(face_landmarks.landmark[5].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[5].y*multi).to_bytes(4, 'little', signed=True)
					#msg += int(face_landmarks.landmark[5].z*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[4].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[4].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[1].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[1].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[2].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[2].y*multi).to_bytes(4, 'little', signed=True)
					#left brow
					msg += int(face_landmarks.landmark[46].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[46].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[52].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[52].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[55].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[55].y*multi).to_bytes(4, 'little', signed=True)
					#right brow
					msg += int(face_landmarks.landmark[285].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[285].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[282].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[282].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[276].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[276].y*multi).to_bytes(4, 'little', signed=True)
					#left eye
					msg += int(face_landmarks.landmark[33].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[33].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[161].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[161].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[159].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[159].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[157].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[157].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[133].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[133].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[153].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[153].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[144].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[144].y*multi).to_bytes(4, 'little', signed=True)
					#right eye
					msg += int(face_landmarks.landmark[362].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[362].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[384].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[384].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[386].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[386].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[388].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[388].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[263].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[263].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[373].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[373].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[380].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[380].y*multi).to_bytes(4, 'little', signed=True)
					#lip up
					msg += int(face_landmarks.landmark[61].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[61].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[39].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[39].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[0].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[0].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[269].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[269].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[291].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[291].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[310].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[310].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[13].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[13].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[80].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[80].y*multi).to_bytes(4, 'little', signed=True)
					#lip down
					msg += int(face_landmarks.landmark[61].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[61].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[88].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[88].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[14].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[14].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[318].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[318].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[291].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[291].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[405].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[405].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[17].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[17].y*multi).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[181].x*ratio).to_bytes(4, 'little', signed=True)
					msg += int(face_landmarks.landmark[181].y*multi).to_bytes(4, 'little', signed=True)
					
			
				#convert to str and send
			
				#msg = msg.encode(FORMAT)
				server.sendto(msg, addr)
			else:
				#else no tracking info send report
				msg = NOTRACKING_MESSAGE
				msg = msg.encode(FORMAT)
				server.sendto(msg, addr)
	
		#limit frame rate to save resourses
		time.sleep(BROADCAST_FRAME_RATE)
		
	#end broadcast, release resources
	cap.release()
	return

def start():
	global run_server
	global broadcast
	#set timeout interval
	server.settimeout(1)
	print(f"[LISTENING] server is listening on {SERVER}")
	while run_server:
		print(f"[STATUS] run_server is {run_server}")
		try:
			#try to recive a packet
			msg, addr = server.recvfrom(PACKET_SIZE)
			msg = msg.decode(FORMAT)
			
			if msg == END_MESSAGE:
				broadcast = False
				run_server = False
				server.close()
				print("[CLOSING SERVER]  server has been requested to close")
			
			if msg == STARTBC_MESSAGE:
				broadcast = True
				thread = threading.Thread(target=broadcast_tracking, args=[(addr)])
				thread.start()
				print(f"[ACTIVE CONNECTION] active connections {threading.activeCount() - 1}")
			
			if msg == ENDBC_MESSAGE:
				broadcast = False
				print(f"[END BROADCAST] ending broadcast to [{addr}]")
			
			print(f"[{addr}] message: {msg}")
		except:
			pass
	return
		

print("[STARTING] server is starting uwu...")
start()
print("[CLOSEING] server is ending, bye...")
#exit()

