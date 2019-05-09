program_cppfiles = \
		Colectie.cpp \
		IteratorColectie.cpp

program_hfiles = \
		Colectie.h

test_cppfiles = \
		$(program_cppfiles) \
		TestScurt.cpp \
		TestExtins.cpp \
		test.cpp

test_hfiles = \
		$(program_hfiles) \
		TestScurt.h \
		TestExtins.h

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
