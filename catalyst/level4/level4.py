def debug_print(*args, **kwargs):
	if True:
		print(*args, **kwargs)

def is_on_segment(p_x, p_y, q_x, q_y, r_x, r_y):
	return q_x <= max(p_x, r_x) and q_x >= min(p_x, r_x) and \
			q_y <= max(p_y, r_y) and q_y >= min(p_y, r_y)

def get_orientation(p_x, p_y, q_x, q_y, r_x, r_y):
	value = (q_y - p_y) * (r_x - q_x) - \
			(q_x - p_x) * (r_y - q_y)

	# colinear
	if value == 0:
		return 0

	# clockwise
	if value > 0:
		return 1

	# counter clockwise
	if value < 0:
		return 2

def is_intersection(a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y):
	oabc = get_orientation(a_x, a_y, b_x, b_y, c_x, c_y)
	oabd = get_orientation(a_x, a_y, b_x, b_y, d_x, d_y)
	ocda = get_orientation(c_x, c_y, d_x, d_y, a_x, a_y)
	ocdb = get_orientation(c_x, c_y, d_x, d_y, b_x, b_y)

	if oabc != oabd and ocda != ocdb:
		return True

	if oabc == 0 and is_on_segment(a_x, a_y, c_x, c_y, b_x, b_y):
		return True

	if oabd == 0 and is_on_segment(a_x, a_y, d_x, d_y, b_x, b_y):
		return True

	if ocda == 0 and is_on_segment(c_x, c_y, a_x, a_y, d_x, d_y):
		return True

	if ocdb == 0 and is_on_segment(c_x, c_y, b_x, b_y, d_x, d_y):
		return True

	return False

def is_intersection_square(origin_x, origin_y, next_origin_x, next_origin_y, j, i):
	square_sides_first = [(0, 0), (0, 0), (1, 0), (0, 1)]
	square_sides_second = [(1, 0), (0, 1), (1, 1), (1, 1)]
	square_sides_names = ["top", "left", "right", "bottom"]

	debug_print("\tindex:", j, i)

	for k in range(4):
		first_x = j + square_sides_first[k][0]
		first_y = i + square_sides_first[k][1]
		second_x = j + square_sides_second[k][0]
		second_y = i + square_sides_second[k][1]

		debug_print("\t\tside:", square_sides_names[k])

		if is_intersection(origin_x + 0.5, origin_y + 0.5, \
				next_origin_x + 0.5, next_origin_y + 0.5, \
				first_x, first_y, \
				second_x, second_y):

			debug_print("\t\tintersect")

			return True

	return False

def solve_subproblem(origin_x, origin_y, d_x, d_y, width, height, input_file, output_file):
	if abs(d_x) >= abs(d_y):
		dominant_axis = "x"
	else:
		dominant_axis = "y"

	if d_x < 0:
		d_x_step = -1
	else:
		d_x_step = 1

	if d_y < 0:
		d_y_step = -1
	else:
		d_y_step = 1

	coords_set = set()
	coords_list = []

	while origin_x >= 0 and origin_y >= 0 and \
				origin_x < width and origin_y < height:

		next_origin_x = origin_x + d_x
		next_origin_y = origin_y + d_y

		debug_print("from:", origin_x, origin_y)
		debug_print("to:", next_origin_x, next_origin_y)

		def check_intersection(j, i):
			if j < 0 or i < 0 or j >= width or i >= height:
				return

			if is_intersection_square(origin_x, origin_y, next_origin_x, next_origin_y, j, i):
				coord = (j, i)
				if coord not in coords_set:
					coords_set.add(coord)
					coords_list.append(coord)

		if dominant_axis == "x":
			for i in range(origin_y, next_origin_y + d_y_step, d_y_step):
				for j in range(origin_x, next_origin_x + d_x_step, d_x_step):
					check_intersection(j, i)
		else:
			for j in range(origin_x, next_origin_x + d_x_step, d_x_step):
				for i in range(origin_y, next_origin_y + d_y_step, d_y_step):
					check_intersection(j, i)

		origin_x = next_origin_x
		origin_y = next_origin_y

	line_output = ""
	for coord in coords_list:
		line_output += str(coord[0]) + " " + str(coord[1]) + " "
	line_output = line_output.strip()
	line_output += "\n"

	output_file.write(line_output)

	debug_print()

def solve(input_file_name, output_file_name):
	input_file = open(input_file_name, "r")
	output_file = open(output_file_name, "w")

	lines = input_file.readlines()

	width, height = lines.pop(0).strip().split(" ")
	width = int(width)
	height = int(height)

	number = lines.pop(0).strip()
	number = int(number)

	for index in range(number):
		origin_x, origin_y, d_x, d_y = lines.pop(0).strip().split(" ")
		origin_x = int(origin_x)
		origin_y = int(origin_y)
		d_x = int(d_x)
		d_y = int(d_y)

		debug_print("problem:", origin_x, origin_y, d_x, d_y)

		solve_subproblem(origin_x, origin_y, d_x, d_y,
				width, height, input_file, output_file)

base_input_file_name = "level4_"
base_output_file_name = "level4_"

for i in range(1):
	input_file_name = base_input_file_name + str(i) + ".in"
	output_file_name = base_output_file_name + str(i) + ".out"
	solve(input_file_name, output_file_name)
