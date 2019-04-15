program_cfiles = \
		entities/Product.c \
		repositories/ProductRepository.c \
		services/ProductService.c \
		utils/Vector.c

program_hfiles = \
		entities/Product.h \
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

output_dir = ./bin
gcov_dir = ./gcov
main_file = $(output_dir)/main
test_file = $(output_dir)/test
gcov_files = *.gcov
gcov_ignored_files = *.gcda *.gcno

.SILENT: main
main: $(console_files)
	-mkdir $(output_dir)

	gcc \
		-Wall -Wextra \
		-std=c99 \
		-g $(console_cfiles) \
		-o $(main_file)

.SILENT: test
test: $(test_files)
	-mkdir $(output_dir)
	-mkdir $(gcov_dir)

	gcc \
		-Wall -Wextra \
		--coverage \
		-std=c99 \
		-g $(test_cfiles) \
		-o $(test_file)

	valgrind \
		--leak-check=full \
		--track-origins=yes \
		$(test_file)

	gcov \
		-r \
		-o . \
		$(program_cfiles)

	mv $(gcov_files) $(gcov_dir)

	rm $(gcov_ignored_files)
