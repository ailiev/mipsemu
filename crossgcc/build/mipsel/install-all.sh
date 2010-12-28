#!/bin/sh -e

. ./env.sh
mkdir -p $rootdir

# Install binutils:
(
    mkdir binutils
    cd binutils
    sh ../conf-binutils

    # Tinker the bintutils configure files to avoid a useless failure
    # when checking result of ls -Lt or ls -t
    for binutils_module in `cat ../fixup-configure-files`; do
        file=../../../binutils-$binutils_version/$binutils_module/configure
        ed $file <<EOF
/.*ls -Lt/i
    # Alex Iliev: do not do this check as it fails without reason on Ubuntu 9.10
    # this exits just the ls -t test sub-shell
    exit
.
wq
EOF
    done

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
