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
MKDIR_P = mkdir -p
RM = rm -rf
QUIET =@

############################################################
##########      CONFIGURATION OF THE OBJECTS      ##########
#####                                                  #####
EXEC = mincamlc

SRCDIR = src
OBJDIR = .obj
TESTDIR = test
DEPDIR = .deps
BINDIR = bin
TESTBINDIR = .test_bin
LOGDIR = .log
INCLUDEDIR = include

CFILES = $(wildcard $(SRCDIR)/*.c)
CXXFILES = $(wildcard $(SRCDIR)/*.cpp)
BASEFILES = $(basename $(notdir $(CFILES) $(CXXFILES)))
OBJFILES = $(addsuffix .o, $(BASEFILES))
OBJWOMAIN:=$(shell echo $(OBJFILES) | sed -e "s/main.o//g")

CTESTS = $(wildcard $(TESTDIR)/*.c)
CXXTESTS = $(wildcard $(TESTDIR)/*.cpp)
BASETESTS = $(basename $(notdir $(CTESTS) $(CXXTESTS)))
OBJTESTS = $(addsuffix .o, $(BASETESTS))
TESTFILES = $(addprefix $(TESTBINDIR)/, $(BASETESTS))
LOGTESTS = $(addsuffix .log, $(BASETESTS))

SRCINCFILES = $(wildcard $(SRCDIR)/*.h)
INCFILES = $(notdir $(wildcard $(INCLUDEDIR)/*.h))

############################################################
##########       CONFIGURATION OF THE FLAGS       ##########
#####                                                  #####
DEBUGFLAGS = -gdwarf-2
DEBUGFLAGS = -O0

INCLUDE = $(INCLUDEDIR)

INCLUDEFLAGS = $(addprefix -I, $(INCLUDE)) -I../BackEnd/parser_asml/src

FLAGS = -Wall
FLAGS += -Werror

DEBUG =

DEBUGFLAGS =
ifneq ("$(DEBUG)", "")
DEBUGFLAGS += -O0
DEBUGFLAGS += -gdwarf-2
else
DEBUGFLAGS = -O2
endif

CFLAGS = $(FLAGS) $(DEBUGFLAGS)
CFLAGS += -std=c99

CXXFLAGS = $(FLAGS) $(DEBUGFLAGS)
CXXFLAGS += -std=c++11

LDFLAGS = -lpthread -L../libs -larm -lasml

.PHONY: clean mrproper clean_deps clean_logs run directories clean_dirs testdirectories inc test

all: directories inc $(EXEC)

obj: directories inc $(EXEC).o

test: testdirectories inc $(TESTFILES)

run: all
	./$(EXEC)

test_run: test
	$(QUIET)for file in $(BASETESTS); do echo "$(TESTBINDIR)/$$file > $(LOGDIR)/$$file.log"; $(TESTBINDIR)/$$file > $(LOGDIR)/$$file.log; done

$(DEPDIR):
	$(QUIET)$(MKDIR_P) $@

$(OBJDIR):
	$(QUIET)$(MKDIR_P) $@

$(LOGDIR):
	$(QUIET)$(MKDIR_P) $@

$(TESTBINDIR):
	$(QUIET)$(MKDIR_P) $@

$(INCLUDEDIR):
	$(QUIET)$(MKDIR_P) $@

testdirectories: $(LOGDIR) $(TESTBINDIR) directories
directories: $(OBJDIR) $(DEPDIR)

inc: $(INCLUDEDIR)
	$(QUIET)for file in $(INCFILES); do if test ! -e $(SRCDIR)/$$file; then $(RM) $(INCLUDEDIR)/$$file; fi; done
	$(QUIET)for file in $(SRCDIR)/*.h; do cp -u $$file $(INCLUDEDIR)/. 2> /dev/null | :; done

%.o: $(OBJDIR)
%.deps: $(DEPDIR)

$(addprefix $(OBJDIR)/, $(OBJFILES)): $(OBJDIR)/%.o: $(DEPDIR)/%.deps
$(addprefix $(OBJDIR)/, $(OBJTESTS)): $(OBJDIR)/%.o: $(DEPDIR)/%.deps

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.deps
	$(CC) $(CFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(DEPDIR)/%.deps
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : $(TESTDIR)/%.c $(DEPDIR)/%.deps
	$(CC) $(CFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : $(TESTDIR)/%.cpp $(DEPDIR)/%.deps
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

$(DEPDIR)/%.deps: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDEFLAGS) -MM $< | sed -e "s/\(.*\).o: /$(DEPDIR)\/\1.deps \1.o: /" > $@

$(DEPDIR)/%.deps: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -MM $< | sed -e "s/\(.*\).o: /$(DEPDIR)\/\1.deps \1.o: /" > $@

$(DEPDIR)/%.deps: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDEFLAGS) -MM $< | sed -e "s/\(.*\).o: /$(DEPDIR)\/\1.deps \1.o: /" > $@

$(DEPDIR)/%.deps: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -MM $< | sed -e "s/\(.*\).o: /$(DEPDIR)\/\1.deps \1.o: /" > $@

$(EXEC): $(addprefix $(OBJDIR)/, $(OBJFILES))
	$(CXX) $^ -o $@ $(LDFLAGS)

$(EXEC).o: $(addprefix $(OBJDIR)/, $(OBJFILES))
	$(LD) -r -o $@ $^

$(TESTBINDIR)/%: $(addprefix $(OBJDIR)/, $(OBJWOMAIN) %.o)
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	$(QUIET)$(RM) $(addprefix $(OBJDIR)/, $(OBJFILES))

clean_deps:
	$(QUIET)$(RM) $(DEPDIR)/*.deps

clean_logs:
	$(QUIET)$(RM) $(addprefix $(LOGDIR)/, $(LOGTESTS))

clean_dirs:
	$(QUIET)$(RM) $(OBJDIR) $(DEPDIR) $(LOGDIR) $(TESTBINDIR)

mrproper:  clean clean_deps clean_logs clean_dirs
	$(QUIET)$(RM) $(EXEC)
	$(QUIET)$(RM) $(TESTFILES)
	$(QUIET)$(RM) $(EXEC).o

include $(wildcard .deps/*)
