CC:=gcc

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

%.s : CFLAGS += -fverbose-asm

%.s: %.c
	$(CC) -S -o $@ $(CPPFLAGS) $(CFLAGS) $<

%.exe.s: %
	mipsel-linux-objdump -d $< > $@

