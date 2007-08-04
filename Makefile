include config.make

include $(SHARED_DIR)/utils.make
include $(SHARED_DIR)/header.make

LIBSRCS = status.cc \
	instructions.cc cpu.cc alu.cc memory.cc \
	os.cc mman.cc bfd.c


ifeq "$(LINKING)" "static"

	CPPFLAGS += -DSTATIC_LINK

# need to have a memory impl specified here!
ifdef PPIRW_RAM
	# fetch RAM impl from the ORAM module.
	LDLIBFILES += -lmemory-impl-ppirw
else
	# just use our simple impl.
	LIBSRCS += memory-impl-simple.cc
endif


else
	CPPFLAGS += -DDYNAMIC_LINK
	LDLIBFILES += -ldl
endif


# external libraries. they get added into LDLIBS in common.make
LIBDIRS		+= $(DIST_LIB) .
LDLIBFILES	+= -lcommon -lbfd



TESTSRCS=$(wildcard test-*.cc test-*.c)


LIB = mips
EXES = runmips

MEMIMPLS = simple
MEMIMPLS_LIBS = $(patsubst %,libmemory-impl-%.$(LIBEXT),$(MEMIMPLS))

# os.cc needs mips/syscalls.h
os.o : CPPFLAGS += -I$(DIETLIBC_DIR)

# for header files within pir, which include other pir headers without the pir/
# prefix
# currently this is needed just for the logging code, we have no other
# dependencies on PIR here.
CPPFLAGS += -I$(SHARED_DIR)



#
# this section is pretty generic
#
LIBFILE = $(patsubst %,lib%.$(LIBEXT),$(LIB))

TARGETS=$(LIBFILE) $(EXES) $(MEMIMPLS_LIBS)

all: build

libmemory-impl-%.so: memory-impl-%.o
	$(CXXLINK)
libmemory-impl-%.a: memory-impl-%.o
	$(AR_CMD)


$(LIBFILE): $(LIBOBJS)
	$(CXXLINK)

#lib$(LIB).a: $(LIBOBJS)
#	$(AR_CMD)


# -l$(LIB): $(LIBFILE)

build: $(TARGETS)
#
# end generic
#


runmips: $(LIBOBJS) runmips.o
	$(CXXLINK)

install: build
#	strip $(EXES)
	$(INSTALL) $(LIBFILE)	$(DIST_LIB)
	$(INSTALL) $(MEMIMPLS_LIBS) $(DIST_LIB)
	$(INSTALL) $(EXES)	$(DIST_BIN)



$(TESTEXES): $(LIBOBJS)

tests: $(TESTEXES)


include $(SHARED_DIR)/footer.make
