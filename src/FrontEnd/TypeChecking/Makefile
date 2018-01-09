CC=gcc
CXX=g++
CFLAGS=-Wfatal-errors -Wall -g -O2

OBJ = lexer.o parser.o type.o list.o ast.o print_ast.o
TRUC = $(wildcard *.cpp)
OBJ += $(addsuffix .o, $(basename $(TRUC)))
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
	$(CXX)  -c -o $@ $< -std=c++11 $(CFLAGS)
$(TARGET): $(OBJ)
		$(CXX) -o $@ $(OBJ) $(CFLAGS) -lfl

.PHONY: clean cleanest
clean:
	rm -rf *.o lexer.c lexer.h minml parser.c parser.h
cleanest: clean
	rm min-ml
