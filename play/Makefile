MIPSDIR=..

include $(MIPSDIR)/mips-shared.make


# LIBOBJS = malloc.o 

all: simple out.s simple.s

simple: simple.o $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

clean:
	$(RM) *.o simple
