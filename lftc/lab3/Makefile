all:
	#flex -d c.flex
	flex c.flex
	g++ -std=c++20 -o lex lex.yy.c -lfl
	cat test.c.txt | ./lex
