CC=gcc
CXX=g++
CFLAGS=-Wfatal-errors -Wall -g

OBJ = lexer.o parser.o type.o list.o ast.o
TRUC = $(wildcard *.cpp)
OBJ += $(addsuffix .o, $(basename $(TRUC)))
OBJWOMAIN:=$(shell echo $(OBJ) | sed -e "s/main.o//g")
# OBJ += $($(wildcard *.c):.c=.o)
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
%.o: %.cpp
	$(CXX)  -c -o $@ $< $(CFLAGS)

static: $(OBJWOMAIN)
	ar rcs libast.a $^

$(TARGET): $(OBJ)
		$(CXX) -o $@ $(OBJ) $(CFLAGS) -lfl

.PHONY: clean cleanest
clean:
	rm -rf *.o lexer.c lexer.h minml parser.c parser.h
cleanest: clean
	rm min-ml
