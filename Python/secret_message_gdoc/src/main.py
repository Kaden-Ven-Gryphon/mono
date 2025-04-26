import requests
from bs4 import BeautifulSoup


# Takes a url to a table, parses out the data from the table, prints the secret message
def print_secret_message(url):
	# get the web page at the url
	doc = requests.get(url)

	# varify the request was successful
	if doc.status_code != 200:
		print("Unable to get webpage")
		return None

	# find the text of the table
	soup = BeautifulSoup(doc.content, "html.parser")
	if soup is None:
		print("Unable to parse html")
		return None

	table = soup.find("table")

	# varify that a table was found
	if table is None:
		print("Unable to locate table at that url")
		return None

	# get a list of each utf8 character and its x and y cord stored as a touple  (x, y, uchar)
	uchars = []

	# start with getting each table row (tr)
	for row in table.find_all("tr")[1:]:
		# then get each column of that row (td) should return 3 elements
		columns = row.find_all("td")

		# get the text of the table elements and remove the whitspace
		x, uchar, y = (v.text.strip() for v in columns)

		# add to the list changing the order to x, y, char and converting cords to ints
		uchars.append((int(x), int(y), uchar))

	# sort the list so that they are listed from left to right, top to bottom
	uchars.sort(key=lambda tup: (tup[1], -tup[0]), reverse=True)

	# interate through the list, any time the next char is on a diffrent line add newlines
	# any time the next char is more then 1 x cord to the right add spaces
	# other wise print the char from the list

	# the starting point x = 0, and y = max y cord given
	lastcord = (-1, uchars[0][1])
	for c in uchars:
		if lastcord[1] != c[1]:
			# add new lines
			for n in range(lastcord[1] - c[1]):
				print("")
			lastcord = (-1, lastcord[1])

		if lastcord[0] + 1 < c[0]:
			# add spaces
			for n in range(c[0] - (lastcord[0] + 1)):
				print(" ", end="")
		# print char and update last cord
		print(c[2], end="")
		lastcord = c[0:2]

	print("")
	print("")
	return 1
	# end of func


def main():
	# // print_secret_message('https://docs.google.com/document/d/e/2PACX-1vRMx5YQlZNa3ra8dYYxmv-QIQ3YJe8tbI3kqcuC7lQiZm-CSEznKfN_HYNSpoXcZIV3Y_O3YoUB1ecq/pub')
	# // print_secret_message('https://docs.google.com/document/d/e/2PACX-1vSHesOf9hv2sPOntssYrEdubmMQm8lwjfwv6NPjjmIRYs_FOYXtqrYgjh85jBUebK9swPXh_a5TJ5Kl/pub')
	print_secret_message(
		"https://docs.google.com/document/d/e/2PACX-1vSZ1vDD85PCR1d5QC2XwbXClC1Kuh3a4u0y3VbTvTFQI53erafhUkGot24ulET8ZRqFSzYoi3pLTGwM/pub"
	)


if __name__ == "__main__":
	main()
