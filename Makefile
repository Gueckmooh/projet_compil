############################################################
#####                                                  #####
#####     @FILE : Makefile                             #####
#####     @AUTHOR : Enzo Brignon                       #####
#####                                                  #####
############################################################
##########     CONFIGURATION OF THE TOOLCHAIN     ##########
#####                                                  #####
CC = gcc
CXX = g++
LD = ld

############################################################
##########      CONFIGURATION OF THE OBJECTS      ##########
#####                                                  #####
EXEC = mlc
SRCDIR = src
OBJDIR = .obj
TESTDIR = test
DEPDIR = .deps
BINDIR = bin
TESTBINDIR = test_bin
CFILES = $(wildcard $(SRCDIR)/*.c)
CXXFILES = $(wildcard $(SRCDIR)/*.cpp)
BASEFILES = $(basename $(notdir $(CFILES) $(CXXFILES)))
OBJFILES = $(addsuffix .o, $(BASEFILES))

############################################################
##########       CONFIGURATION OF THE FLAGS       ##########
#####                                                  #####
DEBUGFLAGS = -gdwarf-2
DEBUGFLAGS = -O0

FLAGS =

CFLAGS = $(FLAGS)
CFLAGS += -std=c99

CXXFLAGS = $(FLAGS)
CXXFLAGS += -std=c++11

LDFLAGS = -lpthread

all: $(EXEC)

$(DEPDIR):
	mkdir $@

$(OBJDIR):
	mkdir $@

$(addprefix $(OBJDIR)/, $(OBJFILES)): $(OBJDIR)/%.o: $(DEPDIR)/%.deps

$(OBJDIR)/%.o :  $(SRCDIR)/%.c $(DEPDIR)/%.deps
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(DEPDIR)/%.deps
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DEPDIR)/%.deps: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MM $< | sed -e "s/\(.*\).o: /$(DEPDIR)\/\1.deps \1.o: /" > $@

$(DEPDIR)/%.deps: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MM $< | sed -e "s/\(.*\).o: /$(DEPDIR)\/\1.deps \1.o: /" > $@

$(EXEC): $(addprefix $(OBJDIR)/, $(OBJFILES))
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(addprefix $(OBJDIR), $(OBJFILES))

clean_deps:
	rm -rf $(DEPDIR)/*.deps

clean_logs:
	rm -rf $(addsuffix .log, $(TESTFILES))

mrproper:  clean clean_deps clean_logs
	rm -rf $(EXEC)
	rm -rf $(TESTFILES)

include $(wildcard .deps/*)
