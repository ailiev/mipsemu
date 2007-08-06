MY_MIPSDIR=..
MY_SHARED_DIR=../../pir

# use one of these includes to decide what target to build for, whether native
# host, or mips:
# include $(MY_SHARED_DIR)/header.make
include $(MY_MIPSDIR)/mips-shared.make


# LIBOBJS = malloc.o 

EXES = gcd multdiv rodata

all: $(EXES)

simple: simple.o $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

clean:
	$(RM) *.o $(EXES)
