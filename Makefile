PIR = ../pir

include $(PIR)/common.make

LIBSRCS = instructions.cc cpu.cc

TESTSRCS=$(wildcard test-*.cc)

# external libraries. they get added into LDLIBS in common.make
LIBDIRS		+= $(LEEDS_LIB) .
LDLIBFILES	+= -lcommon


$(TESTEXES): $(LIBOBJS)

tests: $(TESTEXES)


include $(PIR)/footer.make
