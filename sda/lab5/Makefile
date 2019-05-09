program_cppfiles = \
		P11.cpp

program_hfiles = \
		P11.h

test_cppfiles = \
		$(program_cppfiles) \
		TestP11.cpp \
		test.cpp

test_hfiles = \
		$(program_hfiles) \
		TestP11.h

test_files = \
		$(test_cppfiles) \
		$(test_hfiles)

output_dir = ./bin
test_file = $(output_dir)/test

.SILENT: test
test: $(test_files)
	-mkdir $(output_dir)

	g++ \
		-std=c++11 \
		-Wall -Wextra \
		-g $(test_cppfiles) \
		-o $(test_file)

	valgrind \
		--leak-check=full \
		--track-origins=yes \
		$(test_file)
