# -*- makefile -*-

# this reading of MAKEFILE_LIST has to be done before any other files are
# include-d!
this_file := $(lastword $(MAKEFILE_LIST))
this_dir := $(dir $(realpath $(this_file)))

# dietlibc directory. This is needed both by the emulator (or rather its
# "operating system") and for compiling MIPS executables, using
# mips-shared.make.
# Fetch it from the canonical source: env.sh
DIETLIBC_DIR = $(shell source $(this_dir)/../src/crossgcc/build/mipsel/env.sh && echo $$rootdir/$$target)

$(debug DIETLIBC_DIR = $(DIETLIBC_DIR))

# where the shared directory is, with shared build files.
SHARED_DIR = $(realpath $(this_dir)/../pir)

# use the same installation dir as PIR etc.
DIST_ROOT ?= $(LEEDS_ROOT)

##############################
# in case we need to decide the memory impl at compile time (ie. if dynamic
# linking is not possible), this controls which memory implementation we use.
# define for PPIRW, comment out for simple host array.
##############################
# PPIRW_RAM := 1
