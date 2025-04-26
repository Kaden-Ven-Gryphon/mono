def arithmetic_arranger(problems, show_answers=False):
	count = len(problems)
	ret = ""

	# If there is less than one problem
	if count < 1:
		return "Error: No problems given."
	elif count > 5:
		return "Error: Too many problems."

	# begin parsing input
	a_list = []
	b_list = []
	op_list = []
	w_list = []

	# split problems into units in each list
	for p in problems:
		a, op, b, *rest = p.split(" ")

		# check for errors
		if a is None or op is None or b is None:
			return "Error: Wrong format."
		if op != "+" and op != "-":
			return "Error: Operator must be '+' or '-'."
		if not a.isdigit() or not b.isdigit():
			return "Error: Numbers must only contain digits."
		if len(a) > 4 or len(b) > 4:
			return "Error: Numbers cannot be more than four digits."

		# add the split values to the list
		a_list.append(a)
		b_list.append(b)
		op_list.append(op)
		w_list.append(max(len(a), len(b)))

	# begin printing the output to the ret string
	for i in range(count):
		ret += f"{a_list[i]:{' '}>{w_list[i] + 2}}"
		if i < count - 1:
			ret += "    "
	ret += "\n"

	# second row, adding the operand
	for i in range(count):
		ret += op_list[i]
		ret += f"{b_list[i]:{' '}>{w_list[i] + 1}}"
		if i < count - 1:
			ret += "    "
	ret += "\n"

	# third row made op of the dashes
	for i in range(count):
		ret += "-" * (w_list[i] + 2)
		if i < count - 1:
			ret += "    "
	# //ret += "\n"

	# if show_answers is spcified, add the forth row calculating the answers
	if show_answers:
		ret += "\n"
		for i in range(count):
			answer = 0
			if op_list[i] == "+":
				answer = int(a_list[i]) + int(b_list[i])
			else:
				answer = int(a_list[i]) - int(b_list[i])
			ret += f"{answer:>{w_list[i] + 2}}"
			if i < count - 1:
				ret += "    "
		# //ret += "\n"

	return ret


def main():
	print(arithmetic_arranger(["32 + 8", "1 - 3801", "9999 + 9999", "523 - 49"]))
	ts2_out = """\
  32         1      9999      523\n\
+  8    - 3801    + 9999    -  49\n\
----    ------    ------    -----\n\
  40     -3800     19998      474\n"""
	print(ts2_out)


if __name__ == "__main__":
	main()
