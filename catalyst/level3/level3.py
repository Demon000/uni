import sys

base_input_file_name = "level3_"
base_output_file_name = "level3_"

for i in range(6):
	input_file_name = base_input_file_name + str(i) + ".in"
	output_file_name = base_output_file_name + str(i) + ".out"

	with open(input_file_name, "r") as file:
		lines = file.readlines()
		height, width = lines[0].strip().split(" ")
		height = int(height)
		width = int(width)

		matrix = []
		border_matrix = []
		country_dict_x = {}
		country_dict_y = {}
		country_dict_count = {}
		arrayy = [0, -1, 0, 1]
		arrayx = [-1, 0, 1, 0]

		for i in range(height):
			values = lines[i + 1].strip().split(" ")
			real_values = []
			border_values = []
			for j in range(width):
				real_height = int(values[j * 2 + 1])
				real_values.append(real_height)
				border_values.append(0)
			matrix.append(real_values)
			border_matrix.append(border_values)


		for i in range(height):
			for j in range(width):
				country = matrix[i][j]
				has_border = 0

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
					border_matrix[i][j] = 1

				if country not in country_dict_x:
					country_dict_y[country] = 0
					country_dict_x[country] = 0
					country_dict_count[country] = 0

				country_dict_y[country] = country_dict_y[country] + i# + 0.5
				country_dict_x[country] = country_dict_x[country] + j# + 0.5
				country_dict_count[country] = country_dict_count[country] + 1

		#print(border_matrix)

		capital_dict_capital = {}
		for country in sorted(country_dict_count):
			count = country_dict_count[country]

			capital_float_y = country_dict_y[country] / count# - 0.5
			capital_float_x = country_dict_x[country] / count# - 0.5

			#print(capital_float_x, capital_float_y)

			capital_y = int(capital_float_y)
			capital_x = int(capital_float_x)
			#print(capital_x, capital_y)

			new_capital_y = sys.maxsize
			new_capital_x = sys.maxsize
			new_capital_distance = sys.maxsize

			if border_matrix[capital_y][capital_x] == 1 or matrix[capital_y][capital_x] != country:
				# found = False
				# for mod in range(1, height):
				# 	if found:
				# 		break

				# 	for ii in range(capital_y - mod, capital_y + mod + 1):
				# 		for jj in range(capital_x - mod, capital_x + mod + 1):
				# 			if ii < 0 or ii >= height or jj < 0 or jj >= width:
				# 				continue

				# 			if border_matrix[ii][jj] == 1:
				# 				continue

				# 			if matrix[ii][jj] != country:
				# 				continue

				# 			distance = (capital_float_y - ii) ** 2 + (capital_float_x - jj) ** 2
				# 			if distance < new_capital_distance:
				# 				new_capital_distance = distance
				# 				new_capital_y = ii
				# 				new_capital_x = jj
				# 				found = True

				# if found:
				# 	capital_y = int(new_capital_y)
				# 	capital_x = int(new_capital_x)


				for ii in range(height):
					for jj in range(width):
						if border_matrix[ii][jj] == 1:
							continue

						if matrix[ii][jj] != country:
							continue

						distance = (capital_y - ii) ** 2 + (capital_x - jj) ** 2
#						distance = (capital_float_y - ii) ** 2 + (capital_float_x - jj) ** 2
#						distance = (capital_float_y - ii - 0.5) ** 2 + (capital_float_x - jj - 0.5) ** 2
						if distance < new_capital_distance:
							new_capital_distance = distance
							new_capital_y = ii
							new_capital_x = jj
	
							# capital_y = int(new_capital_y)
							# capital_x = int(new_capital_x)

			if new_capital_x != sys.maxsize:
				capital_y = int(new_capital_y)
				capital_x = int(new_capital_x)

			capital_dict_capital[country] = (capital_y, capital_x)
			#print(capital_x, capital_y, country, matrix[capital_y][capital_x])
			#print(capital_x, capital_y, country)

	with open(output_file_name, "w") as file:
		for country in capital_dict_capital:
			capital = capital_dict_capital[country]
			file.write(str(capital[1]) + " " + str(capital[0]) + "\n")

		# for i in range(height):
		# 	for j in range(width):
		# 		country = matrix[i][j]
		# 		if capital_dict_capital[country] == (i, j):
		# 			file.write("x" + str(country) + " ")
		# 		else:
		# 			file.write(str(country) + " ")
		# 	file.write("\n")
		# for country in sorted(country_dict_count):
		# 	file.write(str(border_dict[country]) + "\n")
