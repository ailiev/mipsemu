# -*- makefile -*-

# this reading of MAKEFILE_LIST has to be done before any other files are
# include-d!
this_file := $(lastword $(MAKEFILE_LIST))
this_dir := $(dir $(realpath $(this_file)))


DIST_ROOT ?= $(FAERIEPLAY_DIST_ROOT)

ifeq ($(DIST_ROOT),)
$(error Please set the environment variable FAERIEPLAY_DIST_ROOT)
endif

EXTRA_INCLUDE_DIRS = $(DIST_ROOT)/include

# dietlibc directory. This is needed both by the emulator (or rather its
# "operating system") and for compiling MIPS executables, using
# mips-shared.make.
# Fetch it from the canonical source: env.sh
SHELL:=/bin/bash
env_loc := $(this_dir)/crossgcc/build/mipsel/env.sh
ifeq "$(realpath $(env_loc))" ""
$(error Could not find the cross-tools env.sh, expected at $(env_loc))
endif

DIETLIBC_DIR = $(shell source $(env_loc) && echo $$rootdir/$$target)

$(info DIETLIBC_DIR = $(DIETLIBC_DIR))

##############################
# in case we need to decide the memory impl at compile time (ie. if dynamic
# linking is not possible), this controls which memory implementation we use.
# define for PPIRW, comment out for simple host array.
##############################
# PPIRW_RAM := 1
