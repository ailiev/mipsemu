PIR = ../pir

include $(PIR)/utils.make
include $(PIR)/header.make

LIBSRCS = status.cc \
	instructions.cc cpu.cc alu.cc memory.cc \
	os.cc mman.cc

# this controls which memory implementation we use
LIBSRCS += memory-impl-simple.o


# SRCS = cpu-main.cc

TESTSRCS=$(wildcard test-*.cc)

LIB = mips
EXES = 

# needs dietlibc/syscall.h
os.o : CPPFLAGS += -I$(HOME)/work/src/crossgcc

# for header files within pir, which include other pir headers without the pir/
# prefix
CPPFLAGS += -I$(PIR)


#
# this section is pretty generic
#
LIBFILE = lib$(LIB).$(LIBEXT)

TARGETS=$(LIBFILE) $(EXES)

all: build

lib$(LIB).so: $(LIBOBJS)
	$(CXXLINK)
lib$(LIB).a: $(LIBOBJS)
	ar -ru $@ $^


-l$(LIB): $(LIBFILE)

build: $(TARGETS)
#
# end generic
#


install: build
#	strip $(EXES)
	$(INSTALL) $(LIBFILE)	$(LEEDS_LIB)
#	$(INSTALL) $(EXES)	$(LEEDS_BIN)


# external libraries. they get added into LDLIBS in common.make
LIBDIRS		+= $(LEEDS_LIB) .
LDLIBFILES	+= -lcommon




$(TESTEXES): $(LIBOBJS)

tests: $(TESTEXES)


include $(PIR)/footer.make
