import sys
import os
from PIL import Image

#print("running convert bin to png")

input_file = sys.argv[1]
output_file = input_file
index = input_file.find(".bin")
if index != -1:
	output_file = input_file[:index]
output_file += ".png"
print(input_file)
print(output_file)

with open(input_file, 'rb') as bin_file:
	data = bin_file.read()

width = int.from_bytes(data[:4], 'little')
hight = int.from_bytes(data[4:8], 'little')

image = Image.frombytes('RGBA', (width,hight), data[8:], 'raw')
image.save(output_file)

os.remove(input_file)
