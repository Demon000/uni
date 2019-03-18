program_cfiles = \
		entities/Product.c \
		entities/ProductsList.c \
		repositories/ProductRepository.c \
		services/ProductService.c \
		utils/Vector.c

program_files = \
		$(program_cfiles) \
		entities/Product.h \
		entities/ProductsList.h \
		repositories/ProductRepository.h \
		services/ProductService.h \
		utils/Vector.h

console_cfiles = \
		$(program_cfiles) \
		ui/Console.c \
		main.c

console_files = \
		$(console_cfiles) \
		ui/Console.h

test_cfiles = \
		$(program_cfiles) \
		test.c

test_files = $(test_cfiles)

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
		-o . \
		$(test_cfiles)

	rm -rf gcov
	mkdir gcov
	mv *.gcov gcov

	rm test \
		*.gcda \
		*.gcno
