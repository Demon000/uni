program_cfiles = entities/Product.c \
		repositories/ProductRepository.c \
		services/ProductService.c \
		utils/Vector.c

program_files = $(program_cfiles) \
		entities/Product.h \
		repositories/ProductRepository.h \
		services/ProductService.h \
		utils/Vector.h

console_cfiles = $(program_cfiles) \
		ui/Console.c \
		main.c

console_files = $(console_cfiles) \
		ui/Console.h

test_cfiles = $(program_cfiles) \
		test.c

test_files = $(test_cfiles)

main: $(console_files)
	gcc \
		-std=c99 \
		-o main \
		-g $(console_cfiles)

test: $(test_files)
	gcc \
		--coverage \
		-std=c99 \
		-o test \
		-g $(test_cfiles)

	./test

	gcov \
		-o . \
		$(test_cfiles)
