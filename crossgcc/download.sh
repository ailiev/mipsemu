wget -c http://ftp.gnu.org/gnu/binutils/binutils-$binutils_version.tar.bz2
#http://ftp.gnu.org/gnu/binutils/binutils-2.16.1.tar.bz2
wget -c http://ftp.gnu.org/gnu/gcc/gcc-$gcc_version/gcc-core-$gcc_version.tar.bz2
#http://ftp.gnu.org/gnu/gcc/gcc-3.4.4/gcc-core-3.4.4.tar.bz2

if [ -f dietlibc/CVS/Root ]; then
	( cd dietlibc && cvs update )
else
	cvs -d :pserver:cvs@cvs.fefe.de:/cvs -z9 co dietlibc
fi
