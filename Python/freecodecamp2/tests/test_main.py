import pytest

from main import add_time


@pytest.mark.parametrize(
	"start_time,added_time,day,expected",
	[
		("3:00 PM", "3:10", None, "6:10 PM"),
		("11:30 AM", "2:32", "Monday", "2:02 PM, Monday"),
		("11:43 AM", "00:20", None, "12:03 PM"),
		("10:10 PM", "3:30", None, "1:40 AM (next day)"),
		("11:43 PM", "24:20", "tueSday", "12:03 AM, Thursday (2 days later)"),
		("6:30 PM", "205:12", None, "7:42 AM (9 days later)"),
		("3:30 PM", "2:12", None, "5:42 PM"),
		("11:55 AM", "3:12", None, "3:07 PM"),
		("2:59 AM", "24:00", None, "2:59 AM (next day)"),
		("11:59 PM", "24:05", None, "12:04 AM (2 days later)"),
		("8:16 PM", "466:02", None, "6:18 AM (20 days later)"),
		("5:21 AM", "00:00", None, "5:21 AM"),
		("3:30 PM", "2:12", "Monday", "5:42 PM, Monday"),
		("2:59 AM", "24:00", "saturDay", "2:59 AM, Sunday (next day)"),
		("11:59 PM", "24:05", "Wednesday", "12:04 AM, Friday (2 days later)"),
		("8:16 PM", "466:02", "tuesday", "6:18 AM, Monday (20 days later)"),
	],
)
def test_add_time(start_time, added_time, day, expected):
	assert add_time(start_time, added_time, day) == expected
