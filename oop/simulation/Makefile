program_cppfiles = \
		entities/Program.cpp \
		repositories/ProgramRepository.cpp \
		services/ProgramService.cpp

program_hfiles = \
		entities/Program.h \
		repositories/ProgramRepository.h \
		services/ProgramService.h

program_files = \
		$(program_cppfiles) \
		$(program_hfiles)

gui_cppfiles = \
		$(program_cppfiles) \
		ui/GUI.cpp \
		main_gui.cpp

gui_hfiles = \
		$(program_hfiles) \
		ui/GUI.h

gui_files = \
		$(gui_cppfiles) \
		$(gui_hfiles)

output_dir = ./bin

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
		main_test.cpp

test_hfiles = \
		$(program_hfiles)

test_files = \
		$(test_cppfiles) \
		$(test_hfiles)

gcov_dir = ./gcov
test_file = $(output_dir)/test
gcov_files = *.gcov
gcov_ignored_files = *.gcda *.gcno

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

	-mv $(gcov_files) $(gcov_dir)

	-rm $(gcov_ignored_files)
