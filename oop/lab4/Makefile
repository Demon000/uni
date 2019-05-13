program_cppfiles = \
		entities/Tenant.cpp \
		repositories/BaseRepository.cpp \
		repositories/ExceptionRepository.cpp \
		repositories/TenantRepository.cpp \
		repositories/NotificationRepository.cpp \
		services/TenantService.cpp

program_hfiles = \
		entities/Tenant.h \
		repositories/BaseRepository.h \
		repositories/ExceptionRepository.h \
		repositories/TenantRepository.h \
		repositories/NotificationRepository.h \
		services/TenantService.h

program_files = \
		$(program_cppfiles) \
		$(program_hfiles)

console_cppfiles = \
		$(program_cppfiles) \
		ui/Console.cpp \
		main_console.cpp

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

output_dir = ./bin
gcov_dir = ./gcov
main_file = $(output_dir)/main
test_file = $(output_dir)/test
gcov_files = *.gcov
gcov_ignored_files = *.gcda *.gcno
test_csv_files = ./tenants_test_*.csv ./notifications_test_*.csv

.SILENT: main
main: $(console_files)
	-mkdir $(output_dir)

	g++ \
		-std=c++11 \
		-Wall -Wextra \
		-g $(console_cppfiles) \
		-o $(main_file)

.SILENT: test
test: $(test_files)
	-mkdir $(output_dir)
	-mkdir $(gcov_dir)

	g++ \
		-std=c++11 \
		-Wall -Wextra \
		--coverage \
		-g $(test_cppfiles) \
		-o $(test_file)

	valgrind \
		--leak-check=full \
		--track-origins=yes \
		$(test_file)

	gcov \
		-r \
		-o . \
		$(program_cppfiles)

	mv $(gcov_files) $(gcov_dir)

	rm $(gcov_ignored_files) $(test_csv_files)
