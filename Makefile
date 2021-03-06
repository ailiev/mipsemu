include config.make

make_incl_dir=$(DIST_ROOT)/make_include/faerieplay/common

include $(make_incl_dir)/utils.make
include $(make_incl_dir)/header.make
include $(make_incl_dir)/shared-targets.make

# no optimize
CXXFLAGS:=-march=i586

LIBSRCS = status.cc \
	instructions.cc cpu.cc alu.cc memory.cc \
	os.cc mman.cc bfd.c


ifeq "$(LINKING)" "static"

	CPPFLAGS += -DSTATIC_LINK

# need to have a memory impl specified here, if we are static-linking!
ifdef PPIRW_RAM
	# fetch RAM impl from the ORAM module.
	LDLIBFILES += -lmemory-impl-ppirw
else
	# just use our simple impl.
	LIBSRCS += memory-impl-simple.cc
endif

# else: dynamic linking.
else
	CPPFLAGS += -DDYNAMIC_LINK
	LDLIBFILES += -ldl
endif



# pick up (links to) some system headers from this dir. In order to avoid the
# compiler finding some ancient versions in /usr/local/include/
CPPFLAGS += -I../shared/system-override/include


# external libraries. they get added into LDLIBS in common.make
LIBDIRS		+= $(DIST_LIB) .
LDLIBFILES	+= -lfaerieplay-common -lbfd -liberty


TESTSRCS=$(wildcard test-*.cc test-*.c)

MAKE_INCLUDES=mips-shared.make config.make

LIB = mips
EXES = runmips

MEMIMPLS = simple
MEMIMPLS_LIBS = $(patsubst %,libmemory-impl-%.$(LIBEXT),$(MEMIMPLS))

# os.cc needs mips/syscalls.h
os.o : CPPFLAGS += -I$(DIETLIBC_DIR)

# dietlibc MIPS header mips/syscalls.h, used in os.cc
os.cc : CPPFLAGS += $(DIETLIBC_DIR)

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

make_incl_install_dir=$(DIST_ROOT)/make_include/mips
# install the mips env.sh in the same relative directory as it is in the source tree
mips_env_dir=$(make_incl_install_dir)/crossgcc/build/mipsel

install: build
#	strip $(EXES)
	$(INSTALL) $(LIBFILE)	$(DIST_LIB)
	$(INSTALL) $(MEMIMPLS_LIBS) $(DIST_LIB)
	$(INSTALL) $(EXES)	$(DIST_BIN)
	mkdir -p $(make_incl_install_dir)
	$(INSTALL) $(MAKE_INCLUDES) $(make_incl_install_dir)/
	mkdir -p $(mips_env_dir)
	$(INSTALL) crossgcc/build/mipsel/env.sh $(mips_env_dir)/

$(TESTEXES): $(LIBOBJS)

tests: $(TESTEXES)


include $(make_incl_dir)/footer.make
