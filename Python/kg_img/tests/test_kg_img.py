from PIL import Image

import kg_img.kg_img as kg_img


def test_main():
	img = Image.open("./testimages/cube.jpg")
	# img = kg_img.grayImage()
	img = kg_img.floyd_steinberg(img)
	img.show()
	# DEBUG
	print(kg_img.hello())  # DEBUG
	# TODO

	# XXX
	# BUG
	# [x]
	# [ ]
	# FIXME
