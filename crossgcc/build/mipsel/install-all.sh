#!/bin/sh -e

. ./env.sh
mkdir -p $rootdir

# Install binutils:
(
    mkdir binutils
    cd binutils
    sh ../conf-binutils
    make
    make install
)

# Then add the mipsel-linux directory to the PATH (and set this up as part of
# your working shell environment in future):
export PATH=$rootdir/$target/bin:$PATH

# Install gcc:
(
    mkdir gcc
    cd gcc
    sh ../conf-gcc
    make
    make install
)

# Install dietlibc:
./build-diet.sh
