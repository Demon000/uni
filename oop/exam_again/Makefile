program_cppfiles =

program_hfiles = \
	entities/TTTTable.h \
	validators/TTTTableValidator.h \
	repositories/TTTTableRepository.h \
	services/TTTTableService.h

program_files = \
	$(program_hfiles)

output_dir = ./bin

gui_cppfiles = \
		$(program_cppfiles) \
		main_gui.cpp

gui_hfiles = \
		$(program_hfiles) \
		ui/MainWindow.h \
		ui/AddTableWindow.h

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
test_csv_files = test_table_service.csv

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
		$(program_files)

	-mv $(gcov_files) $(gcov_dir)

	-rm $(gcov_ignored_files) $(test_csv_files)
