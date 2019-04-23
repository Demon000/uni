console_cppfiles = \
		Pet.cpp \
		main.cpp

console_hfiles = \
		Pet.h \
		List.h

console_files = \
		$(console_cppfiles) \
		$(console_hfiles)

output_dir = ./bin
gcov_dir = ./gcov
main_file = $(output_dir)/main

.SILENT: main
main: $(console_files)
	-mkdir $(output_dir)

	g++ \
		-std=c++11 \
		-Wall -Wextra \
		-g $(console_cppfiles) \
		-o $(main_file)

	valgrind \
		--leak-check=full \
		--track-origins=yes \
		$(main_file)
