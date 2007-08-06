# -*- makefile -*-

# dietlibc directory. This is needed both by the emulator (or rather its
# "operating system") and for compiling MIPS executables, using
# mips-shared.make.
# DIETLIBC_DIR = $(HOME)/work/code/src/crossgcc/dietlibc
DIETLIBC_DIR = $(HOME)/work/minime/cross/mipsel-linux

# where the shared directory is, with shared build files.
SHARED_DIR = ../pir

# use the same installation dir as PIR etc.
DIST_ROOT ?= $(LEEDS_ROOT)

##############################
# in case we need to decide the memory impl at compile time (ie. if dynamic
# linking is not possible), this controls which memory implementation we use.
# define for PPIRW, comment out for simple host array.
##############################
# PPIRW_RAM := 1
