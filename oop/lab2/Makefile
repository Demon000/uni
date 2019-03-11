cfiles = entities/Product.c \
		repositories/ProductRepository.c \
		services/ProductService.c \
		ui/Console.c \
		utils/Vector.c \
		main.c

files = $(cfiles) \
		entities/Product.h \
		repositories/ProductRepository.h \
		services/ProductService.h \
		ui/Console.h \
		utils/Vector.h

lab2: $(files)
	gcc -o lab2 -std=c99 $(cfiles)
