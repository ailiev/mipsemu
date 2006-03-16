CC=gcc

dietdir=$(HOME)/work/src/crossgcc/dietlibc

diet = $(dietdir)/bin-i386/diet
#diet = diet
arch=mipsel
cross=$(arch)-linux-

CC:=$(diet) $(cross)$(CC)
LD:=$(cross)$(LD)

# cflags from the dietlibc MIPS makefile
# note especially the -fno-pic, which is how dietlibc on MIPS is compiled.
CFLAGS += -Wall -Os -G 0 -fstrict-aliasing -fno-pic -mno-abicalls

CFLAGS += -O2
CPPFLAGS += -I$(dietdir)/include
LDFLAGS += -static

VPATH = $(dietdir)/bin-$(ARCH)

# LIBOBJS = malloc.o 

all: simple out.s simple.s

%.s : CFLAGS += -fverbose-asm

%.s: %.c
	$(CC) -S -o $@ $(CPPFLAGS) $(CFLAGS) $<

simple: simple.o $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

out.s: simple
	mipsel-linux-objdump -d $< > $@

clean:
	$(RM) *.o simple
