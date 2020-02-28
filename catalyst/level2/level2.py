import sys

base_input_file_name = "level2_"
base_output_file_name = "level2_"

for i in range(6):
	input_file_name = base_input_file_name + str(i) + ".in"
	output_file_name = base_output_file_name + str(i) + ".out"

	with open(input_file_name, "r") as file:
		lines = file.readlines()
		height, width = lines[0].strip().split(" ")
		height = int(height)
		width = int(width)

		matrix = []
		border_dict = {}
		arrayy = [0, 1, 0, -1]
		arrayx = [-1, 0, 1, 0]

		for i in range(height):
			values = lines[i + 1].strip().split(" ")
			real_values = []
			for i in range(width):
				real_height = int(values[i * 2 + 1])
				real_values.append(real_height)
			matrix.append(real_values)

		for i in range(height):
			for j in range(width):
				has_border = 0
				country = matrix[i][j]
				for k in range(4):
					ii = i + arrayy[k]
					jj = j + arrayx[k]
					if ii < 0 or ii >= height or jj < 0 or jj >= width:
						has_border = 1
						break

					if matrix[ii][jj] != country:
						has_border = 1
						break

				if has_border:
					if country not in border_dict:
						border_dict[country] = 0

					border_dict[country] += 1

	with open(output_file_name, "w") as file:
		for country in sorted(border_dict):
			file.write(str(border_dict[country]) + "\n")
