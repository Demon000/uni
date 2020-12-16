all: c_subset.l c_subset.y
	bison --debug -b c_subset -d c_subset.y
	flex -o c_subset.lex.c c_subset.l
	gcc -o c_subset c_subset.lex.c c_subset.tab.c -lfl
	cat test.c.txt | ./c_subset
