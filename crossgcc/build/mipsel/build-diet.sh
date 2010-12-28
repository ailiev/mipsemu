#!/bin/sh -e

. ./env.sh

srcdir=$srcdir/dietlibc

thisdir=$(pwd)

cd $srcdir

[ -r diet.c ] || {
    echo $srcdir does not contain a dietlibc source 1>&2
    exit 1
}

# build the native version, which builds the cross diet executable
make prefix=$rootdir/$target

# install the native stuff, hopefully will not interfere with the mips pieces.
# All we really need is the native diet executable, eg. bin-i386/diet
make install prefix=$rootdir/$target
# install -D bin-i386/diet $rootdir/$target/bin/diet

# Tinker the makefile to avoid using a compile flag which the cross-gcc doesnt
# understand ( -fno-stack-protector )
ed Makefile <<EOF
g/stackgap.c/s/-fno-stack-protector//
wq
EOF

# and now the mipsel version
make -f $thisdir/Makefile-dietlibc mipsel \
    prefix=$rootdir/$target

# install:
make -f $thisdir/Makefile-dietlibc install \
    prefix=$rootdir/$target ARCH=mipsel

# and the syscalls.h, into the root target directory.

# NOTE: this is not a standard setup. As far as I can tell, syscalls.h do not
# get installed normally, so deciding to install them in some particular
# location is bound to be non-standard.

# NOTE: we're getting mips/syscalls.h and not mipsel/ as they're both the same,
# and mipsel links to mips anyway.

for h in syscalls.h mips/syscalls.h; do
    install -D $h $rootdir/$target/$h
done
