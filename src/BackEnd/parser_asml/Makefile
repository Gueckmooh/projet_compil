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
AR = ar
BISON = bison
FLEX = flex
LD = ld
MKDIR_P = mkdir -p
RM = rm -rf
QUIET =@

############################################################
##########      CONFIGURATION OF THE OBJECTS      ##########
#####                                                  #####
EXEC = mlc

SRCDIR = src
OBJDIR = .obj
TESTDIR = test
DEPDIR = .deps
BINDIR = bin
TESTBINDIR = .test_bin
LOGDIR = .log
INCLUDEDIR = include
LIBDIR = libs

ARFLAGS = rcs

FFILES = $(wildcard $(SRCDIR)/*.l)
BFILES = $(wildcard $(SRCDIR)/*.y)

LPFILES = $(addsuffix .c, $(basename $(BFILES)))
LPFILES += $(addsuffix .c, $(basename $(FFILES)))

CFILES = $(wildcard $(SRCDIR)/*.c)
CFILES += $(LPFILES)
CXXFILES = $(wildcard $(SRCDIR)/*.cpp)
BASEFILES = $(basename $(notdir $(CFILES) $(CXXFILES)))
OBJFILES = $(addsuffix .o, $(BASEFILES))
OBJWOMAIN:=$(shell echo $(OBJFILES) | sed -e "s/main.o//g")

LIBARM:=$(shell echo $(OBJWOMAIN) | sed -e "s/asml[a-z,_]*\.o//g")
LIBASML:=$(shell echo $(OBJWOMAIN) | sed -e "s/arm[a-z,_]*\.o//g")

CTESTS = $(wildcard $(TESTDIR)/*.c)
CXXTESTS = $(wildcard $(TESTDIR)/*.cpp)
BASETESTS = $(basename $(notdir $(CTESTS) $(CXXTESTS)))
OBJTESTS = $(addsuffix .o, $(BASETESTS))
TESTFILES = $(addprefix $(TESTBINDIR)/, $(BASETESTS))
LOGTESTS = $(addsuffix .log, $(BASETESTS))

SRCINCFILES = $(wildcard $(SRCDIR)/*.h)
TESTINCFILES = $(wildcard $(TESTDIR)/*.h)
INCFILES = $(notdir $(wildcard $(INCLUDEDIR)/*.h))

############################################################
##########       CONFIGURATION OF THE FLAGS       ##########
#####                                                  #####
DEBUGFLAGS = -gdwarf-2
DEBUGFLAGS = -O0

INCLUDE = $(INCLUDEDIR)

INCLUDEFLAGS = $(addprefix -I, $(INCLUDE))

FLAGS = -Wall
FLAGS += -Werror
#FLAGS += -Wshadow
#FLAGS += -D__USE_POSIX

DEBUG =

DEBUGFLAGS =
ifneq ("$(DEBUG)", "")
DEBUGFLAGS += -O0
DEBUGFLAGS += -gdwarf-2
DEBUGFLAGS += -D__DEBUG
else
DEBUGFLAGS = -O2
endif
ifneq ("$(VERBOSE)", "")
DEBUGFLAGS += -D__VERBOSE
endif
ifneq ("$(ASML)", "")
DEBUGFLAGS += -D__TO_ASML
endif
ifneq ("$(WORD_SIZE)", "")
DEBUGFLAGS += -D__WORD_SIZE=$(WORD_SIZE)
endif

CFLAGS = $(FLAGS) $(DEBUGFLAGS)
CFLAGS += -std=gnu99

CXXFLAGS = $(FLAGS) $(DEBUGFLAGS)
CXXFLAGS += -std=c++14

LDFLAGS = -lpthread
LDFLAGS += -lfl

FLEXFLAGS =
BISONFLAGS =

.PHONY: clean mrproper clean_deps clean_logs run directories clean_dirs testdirectories inc test clean_lex_pars lib static dynamic

all: lexpars directories inc $(EXEC)

asml_parser.h: asml_parser.c
lexpars: $(LPFILES)

test: lexpars testdirectories inc_test $(TESTFILES)

run: all
	./$(EXEC)

lib: static dynamic

#static: FLAGS += -fPIC
static: directories
static: $(LIBDIR)/libasml.a $(LIBDIR)/libarm.a

$(LIBDIR)/libasml.a: $(addprefix $(OBJDIR)/, $(LIBASML))
	$(AR) $(ARFLAGS) $@ $^

$(LIBDIR)/libarm.a: $(addprefix $(OBJDIR)/, $(LIBARM))
	$(AR) $(ARFLAGS) $@ $^

dynamic: FLAGS += -fPIC
dynamic: clean
dynamic: directories $(LIBDIR)/libasml.so $(LIBDIR)/libarm.so

$(LIBDIR)/libasml.so: $(addprefix $(OBJDIR)/, $(LIBASML))
	$(CXX) --shared -o $@ $^ $(LDFLAGS)

$(LIBDIR)/libarm.so: $(addprefix $(OBJDIR)/, $(LIBARM))
	$(CXX) --shared -o $@ $^ $(LDFLAGS)

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

$(LIBDIR):
	$(QUIET)$(MKDIR_P) $@

$(INCLUDEDIR):
	$(QUIET)$(MKDIR_P) $@

testdirectories: directories $(TESTBINDIR)
directories: $(OBJDIR) $(DEPDIR) $(LIBDIR) $(INCLUDEDIR)

inc: $(INCLUDEDIR)
	$(QUIET)for file in $(INCFILES); do if test ! -e $(SRCDIR)/$$file; then $(RM) $(INCLUDEDIR)/$$file; fi; done
	$(QUIET)for file in $(SRCDIR)/*.h; do cp -u $$file $(INCLUDEDIR)/. 2> /dev/null | :; done

inc_test: $(INCLUDEDIR)
	$(QUIET)for file in $(INCFILES); do if test ! -e $(SRCDIR)/$$file; then $(RM) $(INCLUDEDIR)/$$file; fi; done
	$(QUIET)for file in $(TESTDIR)/*.h; do cp -u $$file $(INCLUDEDIR)/. 2> /dev/null | :; done
	$(QUIET)for file in $(SRCDIR)/*.h; do cp -u $$file $(INCLUDEDIR)/. 2> /dev/null | :; done

%.o: $(OBJDIR)
%.deps: $(DEPDIR)

$(addprefix $(OBJDIR)/, $(OBJFILES)): $(OBJDIR)/%.o: $(DEPDIR)/%.deps
$(addprefix $(OBJDIR)/, $(OBJTESTS)): $(OBJDIR)/%.o: $(DEPDIR)/%.deps

$(SRCDIR)/%.c: $(SRCDIR)/%.l
	$(FLEX) -o $@ $<

$(SRCDIR)/%.c: $(SRCDIR)/%.y
	$(BISON) -o $@ --defines=$(basename $<).h $<

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

clean_lex_pars:
	$(QUIET)$(RM) $(LPFILES) #$(addsuffix .h, $(basename $(LPFILES)))

clean_inc:
	$(QUIET)$(RM) $(INCLUDEDIR)

mrproper:  clean clean_deps clean_logs clean_dirs clean_lex_pars
	$(QUIET)$(RM) $(EXEC)
	$(QUIET)$(RM) $(TESTFILES)
	$(QUIET)$(RM) $(LIBDIR)

include $(wildcard .deps/*)
