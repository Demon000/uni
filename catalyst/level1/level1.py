import sys

base_input_file_name = "level1_"
base_output_file_name = "level1_"

for i in range(1, 6):
	input_file_name = base_input_file_name + str(i) + ".in"
	output_file_name = base_output_file_name + str(i) + ".out"

	with open(input_file_name, "r") as file:
		lines = file.readlines()
		height, width = lines[0].strip().split(" ")
		height = int(height)
		width = int(width)

		border_dict = {}
		max_value = 0
		min_value = sys.maxsize
		values_sum = 0

		for i in range(height):
			values = lines[i + 1].strip().split(" ")
			for j in range(width):
				value = int(values[j])
				max_value = max(value, max_value)
				min_value = min(value, min_value)
				values_sum += value

	with open(output_file_name, "w") as file:
		file.write(str(min_value) + " " + str(max_value) + " " + str(values_sum // height // width) + "\n")
