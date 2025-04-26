from main import arithmetic_arranger

ts1_in = ["32 + 8", "1 - 3801", "9999 + 9999", "523 - 49"]
ts1_out = """\
  32         1      9999      523\n\
+  8    - 3801    + 9999    -  49\n\
----    ------    ------    -----\n"""

ts2_out = """\
  32         1      9999      523\n\
+  8    - 3801    + 9999    -  49\n\
----    ------    ------    -----\n\
  40     -3800     19998      474\n"""

ts2_in = [
	"32 + 698",
	"3801 - 2",
	"45 + 43",
	"123 + 49",
	"123 + 49",
	"123 + 49",
	"123 + 49",
]
ts3_in = ["32 + 698", "3801 - 2", "45 * 43", "123 + 49"]
ts4_in = ["32 + 698", "3801 - 2", "b5 + 43", "123 + 49"]
ts5_in = ["32 + 698", "38011 - 2", "45 + 43", "123 + 49"]

err_1 = "Error: Too many problems."
err_2 = "Error: Operator must be '+' or '-'."
err_3 = "Error: Numbers must only contain digits."
err_4 = "Error: Numbers cannot be more than four digits."


def test_one():
	assert arithmetic_arranger(ts1_in) == ts1_out


def test_two():
	assert arithmetic_arranger(ts2_in) == err_1


def test_three():
	assert arithmetic_arranger(ts3_in) == err_2


def test_four():
	assert arithmetic_arranger(ts4_in) == err_3


def test_five():
	assert arithmetic_arranger(ts5_in) == err_4


def test_six():
	assert arithmetic_arranger(ts1_in, show_answers=True) == ts2_out
