
ast-parser: parser ast.c ast.h
	gcc -o ast-parser ast.c parser.y.o parser.lex.o -ll -lm -lfl
parser:
	make clean
	bison -d parser.y
	mv parser.tab.h parser.h
	mv parser.tab.c parser.y.c
	flex lexer.yy
	mv lex.yy.c parser.lex.c
	gcc -o parser.lex.o -c parser.lex.c
	gcc -c parser.y.c -o parser.y.o

clean: 
	rm -f parser.lex.o parser.y.o parser.h parser.y.c parser.lex.c

.PHONY: parser clean
