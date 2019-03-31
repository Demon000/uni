program_cfiles = \
		entities/Product.c \
		entities/ProductsList.c \
		repositories/ProductRepository.c \
		services/ProductService.c \
		utils/Vector.c

program_hfiles = \
		entities/Product.h \
		entities/ProductsList.h \
		repositories/ProductRepository.h \
		services/ProductService.h \
		utils/Vector.h

program_files = \
		$(program_cfiles) \
		$(program_hfiles)

console_cfiles = \
		$(program_cfiles) \
		ui/Console.c \
		main.c

console_hfiles = \
		$(program_hfiles) \
		ui/Console.h

console_files = \
		$(console_cfiles) \
		$(console_hfiles)

test_cfiles = \
		$(program_cfiles) \
		test.c

test_hfiles = \
		$(program_hfiles)

test_files = \
		$(test_cfiles) \
		$(test_hfiles)

.SILENT: main
main: $(console_files)
	gcc \
		-Wall -Wextra \
		-std=c99 \
		-o main \
		-g $(console_cfiles)

.SILENT: test
test: $(test_files)
	gcc \
		-Wall -Wextra \
		--coverage \
		-std=c99 \
		-o test \
		-g $(test_cfiles)

	valgrind \
		--leak-check=full \
		--track-origins=yes \
		./test

	gcov \
		-r \
		-o . \
		$(test_cfiles)

	rm -rf gcov
	mkdir gcov
	mv *.gcov gcov

	rm test \
		*.gcda \
		*.gcno
