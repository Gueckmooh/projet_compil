CC=gcc
CFLAGS= -Wall -Wshadow -g -I../../BackEnd/parser_asml/src

OBJ = lexer.o parser.o type.o list.o ast.o knorm.o env.o alpha_conv.o utils.o reduce_nested_let.o ast_to_asmlt.o front_end.o print_and_write.o beta_red.o closure.o constant_folding.o map_var_and_func.o
OBJWOMAIN:=$(shell echo $(OBJ) | sed -e "s/main.o//g")
FLEXFILES = lexer.l
YACCFILES = parser.y
TARGET = min-ml

all: $(TARGET)

lexer.l: parser.h ast.h
parser.y: ast.h

%.c: %.l
	flex -o $@ $<

%.c: %.y
	bison -t -d -o $@ $<

%.h: %.c
	@touch $@

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

../libs:
	@mkdir $@

static: $(OBJWOMAIN)
	ar rcs libAsmlGen.a $^

$(TARGET): $(OBJ)
		$(CC) -o $@ $(OBJ) $(CFLAGS)

.PHONY: clean cleanest
clean:
	rm -rf *.o lexer.c lexer.h minml parser.c parser.h
cleanest: clean
	rm min-ml
