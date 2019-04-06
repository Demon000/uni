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

.SILENT: test
test: $(test_files)
	g++ \
		-std=c++11 \
		-Wall -Wextra \
		--coverage \
		-o test \
		-g $(test_cppfiles)

	valgrind \
		--leak-check=full \
		--track-origins=yes \
		./test

	gcov \
		-r \
		-o . \
		$(program_cppfiles)

	rm -rf gcov
	mkdir gcov
	mv *.gcov gcov

	rm test \
		*.gcda \
		*.gcno
