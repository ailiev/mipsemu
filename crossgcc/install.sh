sh ./download.sh

bzcat binutils-2.20.1.tar.bz2 | tar xf -
bzcat gcc-core-3.4.6.tar.bz2 | tar xf -

exit

cd build/mipsel/

# see build/mipsel/INSTALL for information about building and installing the
# toolchain.
sh ./install-all.sh
