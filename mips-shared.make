# -*- makefile -*-

# this reading of MAKEFILE_LIST has to be done before any other files are
# include-d!
this_file := $(lastword $(MAKEFILE_LIST))
this_dir := $(dir $(realpath $(this_file)))

# include our local config.make
include $(this_dir)/config.make

base_cc := gcc

diet = $(DIETLIBC_DIR)/bin-i386/diet
#diet = diet
arch=mipsel
cross=$(arch)-linux-

DIETMIPSCC=$(diet) $(cross)$(base_cc)
MIPSLD=$(cross)$(LD)

CC:=$(DIETMIPSCC)
LD:=$(MIPSLD)

# cflags from the dietlibc MIPS makefile
# note especially the -fno-pic, which is how dietlibc on MIPS is compiled.
CFLAGS += -G 0 -fstrict-aliasing -fno-pic -mno-abicalls

CFLAGS += -Os

CPPFLAGS += -I$(DIETLIBC_DIR)/include
LDFLAGS += -static

VPATH = $(DIETLIBC_DIR)/bin-$(ARCH)

%.s : CFLAGS += -fverbose-asm

%.s: %.c
	$(CC) -S -o $@ $(CPPFLAGS) $(CFLAGS) $<

%.exe.s: %
	mipsel-linux-objdump -d $< > $@
