export PATH := /opt/gnu/arm/bin:$(PATH)

CC=arm-none-eabi-gcc

AS=arm-none-eabi-as
LD=arm-none-eabi-ld

CSOURCES = $(wildcard *.c)

ASM=$(wildcard *.s)
ASM+=$(CSOURCES:.c=.s)
PRG=default.arm

.PHONY: all echo test clean mrproper

all: ${PRG}

echo:
	echo ${ASM}
	echo ${PRG}

%.s: %.c
	$(CC) -S -O0 $<

%.o : %.s
	${AS} -o $@ $^

$(PRG) : $(ASM:.s=.o)
	${LD} -o $@ $^

test: ${PRG}
	@for p in ${PRG} ; do \
	  echo "*** Launching $$p"; \
	  qemu-arm ./$$p ; \
	done

clean:
	rm -f *.o

mrproper: clean
	rm -f $(CSOURCES:.c=.o)
	rm -f $(PRG)
