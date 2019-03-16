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


lab2: $(console_files)
	gcc -o lab2 -std=c99 $(console_cfiles)
