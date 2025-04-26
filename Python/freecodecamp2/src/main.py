# add time function
def add_time(start, duration, day_of_week=None):
	# dictionary to make converting days past to weekday
	weekday_lookup = {
		"monday": 0,
		"tuesday": 1,
		"wednesday": 2,
		"thursday": 3,
		"friday": 4,
		"saturday": 5,
		"sunday": 6,
	}

	# return var
	new_time = ""
	days_passed = 0

	# get the time and PM/AM marker
	buf = start.split(" ")
	# get hour and min
	buf2 = buf[0].split(":")

	time_hour = int(buf2[0])
	time_min = int(buf2[1])
	time_marker = buf[1]

	# keep record of start time for 12:00 edge case for marker change
	start_hour = time_hour

	# parse duration
	buf = duration.split(":")

	# add duration to original
	add_hour = int(buf[0])
	add_min = int(buf[1])

	time_hour += add_hour
	time_min += add_min

	# if min when past 60 add an hour and subtract 60
	if time_min >= 60:
		time_hour += 1
		time_min %= 60

	# if the hour is past 12 or just hit 12 need to update varibles
	if time_hour > 12 or (time_hour == 12 and time_hour != start_hour):
		# find number of 12 hour units that passed
		days_passed = int(time_hour / 12)
		# if 12 hour units is even then AM/PM marker does not change
		# else if odd then the marker needs to swap
		if days_passed % 2 == 1:
			# flip marker and add or subtract 12 unit to match how many PM to AM changes
			if time_marker == "AM":
				time_marker = "PM"
				days_passed -= 1
			else:
				time_marker = "AM"
				days_passed += 1
		# get days passed by dividing the 12 hour units
		days_passed = int(days_passed / 2)

	# compress to 12 hours
	time_hour %= 12
	if time_hour == 0:
		time_hour = 12

	# create the return string
	new_time = f"{time_hour}:{time_min:02} {time_marker}"

	# if a day of week was given then add it to output
	if day_of_week is not None:
		# get day of week number
		day_index = weekday_lookup[day_of_week.lower()]
		# add days passed
		day_index += days_passed
		# mod back to 0-6
		day_index %= 7
		# get the keys of dictionary and use new index to get current day of week
		buf = list(weekday_lookup.keys())[day_index].capitalize()
		new_time += ", " + buf

	# add days passed to output
	if days_passed > 0:
		if days_passed == 1:
			new_time += " (next day)"
		else:
			new_time += f" ({days_passed} days later)"

	return new_time


def main():
	print("Hello from freecodecamp2!")


if __name__ == "__main__":
	main()
