# Complete download, build and install of the MIPS cross-compilation toolchain.

# First check/update settings in this file:
. build/mipsel/env.sh

export binutils_version gcc_version

sh ./download.sh

bzcat binutils-$binutils_version.tar.bz2 | tar xf -
bzcat gcc-core-$gcc_version.tar.bz2 | tar xf -

cd build/mipsel/

# see build/mipsel/INSTALL for information about building and installing the
# toolchain. This invocation should do the whole job:
sh ./install-all.sh
