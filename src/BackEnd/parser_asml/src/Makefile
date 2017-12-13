all:
	bison -o asml_parser.c --defines=asml_parser.h asml_parser.y
	flex -o asml_lexer.c asml_lexer.l

clean:
	rm asml_parser.c asml_parser.h asml_lexer.c
