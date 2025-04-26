import numpy as np
from PIL import Image


def hello():
	return "hello"


def grayImage():
	data = np.zeros([100, 100], dtype=np.uint8)
	data += 127
	return Image.fromarray(data)


def grayscale(img: Image.Image):
	data = np.array(img.convert("RGB"))
	print(np.shape(data))
	data = (
		(data[:, :, 0] * 0.2126) + (data[:, :, 1] * 0.7152) + (data[:, :, 2] * 0.0722)
	)

	print("gray", np.shape(data))
	return Image.fromarray(data)


def threshold_bit(img: Image.Image, thres: int):
	img = grayscale(img)
	data = np.array(img)
	data = data > thres
	print(np.shape(data))
	return Image.fromarray(data)


def floyd_steinberg(img: Image.Image):
	img = grayscale(img)
	data = np.array(img).astype(np.float16) / 255
	hight, width = np.shape(data)

	for i in range(0, hight):
		for j in range(0, width):
			err = 0
			if data[i, j] < 0.5:
				err = data[i, j]

			else:
				err = data[i, j] - 1

			err = err / 16
			print(err)

			if j < width - 1:
				data[i, j + 1] += err * 7
			if i < hight - 1:
				if j > 0:
					data[i + 1, j - 1] += err * 3
				data[i + 1, j] += err * 5
				if j < width - 1:
					data[i + 1, j + 1] += err * 1

	data *= 255
	return threshold_bit(Image.fromarray(data.astype(np.uint8)), 128)
	# return threshold_bit(Image.fromarray(data, mode="L"), 128)


def err_diffusion_1(img: Image.Image):
	img = grayscale(img)
	data = np.array(img).astype(np.int16)

	hight, width = np.shape(data)

	for i in range(0, hight):
		err: int = 0
		for j in range(0, width):
			if data[i, j] + err < 128:
				err = data[i, j] + err
				data[i, j] = 0
			else:
				err = (data[i, j] + err) - 255
				data[i, j] = 255
	return Image.fromarray(data.astype(np.uint8))


def false_floyd_steinberg(img: Image.Image):
	img = grayscale(img)
	data = np.array(img).astype(np.int16)
	hight, width = np.shape(data)

	for i in range(0, hight - 1):
		for j in range(1, width - 1):
			err = 0
			if data[i, j] < 128:
				err = data[i, j]

			else:
				err = data[i, j] - 255

			err = err >> 3
			data[i + 1, j] += err * 3
			data[i, j + 1] += err * 3
			data[i + 1, j + 1] += err * 2

	return threshold_bit(Image.fromarray(data.astype(np.uint8)), 128)
