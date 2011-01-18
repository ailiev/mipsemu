MY_MIPSDIR=..

include $(MY_MIPSDIR)/config.make

make_incl_dir=$(DIST_ROOT)/make_include/faerieplay/common

include $(make_incl_dir)/header.make

# use one of these includes to decide what target to build for, whether native
# host, or mips:
# include $(MAKE_INCL_DIR)/header.make
include $(MY_MIPSDIR)/mips-shared.make

# LIBOBJS = malloc.o 

EXES = gcd multdiv rodata add-consts strlen strcat strcmp

all: $(EXES)

simple: simple.o $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

clean:
	$(RM) *.o $(EXES)
