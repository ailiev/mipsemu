# CUSTOMIZE: the installation root directory for all the tools. Also
# make sure to add $rootdir/$target/bin to the PATH.
rootdir=$HOME/faerieplay/crosstools

# which versions of the tools do we download and build?
binutils_version=2.20.1
gcc_version=3.4.6

#
# No need to touch the subsequent settings
#

# this is used as a directory name, and as a target name for the cross tools
# (binutils and gcc)
target=mipsel-linux

# where are the sources?
srcdir=../..
