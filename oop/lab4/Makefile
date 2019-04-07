program_cppfiles = \
		entities/Tenant.cpp \
		repositories/TenantRepository.cpp \
		services/TenantService.cpp \
		list/List.cpp

program_hfiles = \
		entities/Tenant.h \
		repositories/TenantRepository.h \
		services/TenantService.h \
		list/List.h

program_files = \
		$(program_cppfiles) \
		$(program_hfiles)

console_cppfiles = \
		$(program_cppfiles) \
		ui/Console.cpp \
		main.cpp

console_hfiles = \
		$(program_files) \
		ui/Console.h

console_files = \
		$(console_cppfiles) \
		$(console_hfiles)

test_cppfiles = \
		$(program_cppfiles) \
		test.cpp

test_hfiles = \
		$(program_hfiles)

test_files = \
		$(test_cppfiles) \
		$(test_hfiles)

.SILENT: main
main: $(console_files)
	g++ \
		-std=c++11 \
		-Wall -Wextra \
		-o main \
		-g $(console_cppfiles)

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
