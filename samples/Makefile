MY_MIPSDIR=..

include $(MY_MIPSDIR)/config.make

make_incl_dir=$(DIST_ROOT)/make_include/faerieplay/common

include $(make_incl_dir)/header.make

# use one of these includes to decide what target to build for, whether native
# host, or mips:
# include $(MAKE_INCL_DIR)/header.make
include $(MY_MIPSDIR)/mips-shared.make

# LIBOBJS = malloc.o 

CXXFLAGS += -O2

SRCS = gcd.c multdiv.c rodata.c add-consts.c strlen.c strcat.c strcmp.c

objs = $(subst .c,.o,$(SRCS))
asms = $(subst .c,.s,$(SRCS))
exe_files = $(subst .c,.exe,$(SRCS))
disasms = $(subst .exe,.exe.s,$(exe_files))

%.exe: %
	cp $< $@

all: $(exe_files) $(disasms) $(asms) $(objs)

simple: simple.o $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

clean:
	$(RM) *.o $(EXES)
