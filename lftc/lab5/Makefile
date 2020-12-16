#.PHONY: c_subset
#c_subset: c_subset.l c_subset.y
#	bison --debug -b c_subset -d c_subset.y
#	flex -o c_subset.lex.c c_subset.l
#	gcc -o c_subset c_subset.lex.c c_subset.tab.c -lfl
#	cat test_c_asm_subset_1.txt | ./c_subset

.PHONY: c_asm_subset
c_asm_subset: c_asm_subset.l c_asm_subset.y
	bison --debug -b c_asm_subset -d c_asm_subset.y
	flex -o c_asm_subset.lex.c c_asm_subset.l
	gcc -o c_asm_subset c_asm_subset.lex.c c_asm_subset.tab.c -lfl
	cat test_c_asm_subset_1.txt | ./c_asm_subset
