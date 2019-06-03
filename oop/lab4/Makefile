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

output_dir = ./bin

main_file = $(output_dir)/main

.SILENT: main
main: $(console_files)
	-mkdir $(output_dir)

	g++ \
		-std=c++11 \
		-Wall -Wextra \
		-g $(console_cppfiles) \
		-o $(main_file)

gui_cppfiles = \
		$(program_cppfiles) \
		ui/CommonWindow.cpp \
		ui/MainWindow.cpp \
		ui/AddTenantWindow.cpp \
		ui/UpdateTenantWindow.cpp \
		ui/NotificationsWindow.cpp \
		ui/VisualWindow.cpp \
		main_gui.cpp

gui_hfiles = \
		$(program_files) \
		observe/Observe.h \
		services/ObservableTenantService.h \
		ui/TenantsTable.h \
		ui/CommonWindow.h \
		ui/MainWindow.h \
		ui/AddTenantWindow.h \
		ui/UpdateTenantWindow.h \
		ui/NotificationsWindow.h \
		ui/VisualWindow.h

gui_files = \
		$(gui_cppfiles) \
		$(gui_hfiles)


gui_file = $(output_dir)/gui
pro_file = gui.pro
pro_makefile = Makefile.pro

.SILENT: gui
gui: $(gui_files)
	-mkdir $(output_dir)

	echo "SOURCES = $(gui_cppfiles)" >> $(pro_file)
	echo "HEADERS = $(gui_hfiles)" >> $(pro_file)
	echo "DESTDIR = $(output_dir)/" >> $(pro_file)
	echo "OBJECTS_DIR = $(output_dir)/" >> $(pro_file)
	echo "QT += widgets" >> $(pro_file)

	qmake \
		$(pro_file) \
		-o $(pro_makefile)

	make -f $(pro_makefile)

	$(gui_file)

	-rm $(pro_file)
	-rm $(pro_makefile)

test_cppfiles = \
		$(program_cppfiles) \
		test.cpp

test_hfiles = \
		$(program_hfiles)

test_files = \
		$(test_cppfiles) \
		$(test_hfiles)

gcov_dir = ./gcov
test_file = $(output_dir)/test
gcov_files = *.gcov
gcov_ignored_files = *.gcda *.gcno
test_csv_files = ./tenants_test_*.csv ./notifications_test_*.csv

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
