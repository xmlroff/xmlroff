#!/bin/sh
# Run this to generate all the initial makefiles, etc.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

ORIGDIR=`pwd`
cd $srcdir
PROJECT=xmlroff
TEST_TYPE=-f
FILE=xmlroff/xmlroff.c
AC_CONFIG_AUX_DIR=config

DIE=0

have_libtool=false
if libtoolize --version < /dev/null > /dev/null 2>&1 ; then
	libtool_version=`libtoolize --version |	 libtoolize --version | sed 's/^[^0-9]*\([0-9].[0-9.]*\).*/\1/'`
	case $libtool_version in
	    1.4*|1.5*|2.*)
		have_libtool=true
		;;
	esac
fi
if $have_libtool ; then : ; else
	echo
	echo "You must have libtool 1.4 or later installed to compile $PROJECT."
	echo "Install the appropriate package for your distribution,"
	echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
	DIE=1
fi

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have autoconf installed to compile $PROJECT."
	echo "Download the appropriate package for your distribution,"
	echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
	DIE=1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
	echo
	echo "You must have automake installed to compile $PROJECT."
	echo "Get ftp://sourceware.cygnus.com/pub/automake/automake-1.4.tar.gz"
	echo "(or a newer version if it is available)"
	DIE=1
}

if test "$DIE" -eq 1; then
	exit 1
fi

test $TEST_TYPE $FILE || {
	echo "You must run this script in the top-level $PROJECT directory"
	exit 1
}

test -d config || {
	echo "Creating AC_CONFIG_AUX_DIR, \`$AC_CONFIG_AUX_DIR'."
	mkdir config
}

if test -z "$*"; then
	echo "I am going to run ./configure with no arguments - if you wish "
        echo "to pass any to it, please specify them on the $0 command line."
fi

libtoolize --copy --force
aclocal $ACLOCAL_FLAGS

# optionally run autoheader
(autoheader --version)  < /dev/null > /dev/null 2>&1 && autoheader

automake -a $am_opt
autoconf
cd $ORIGDIR

$srcdir/configure --enable-maintainer-mode "$@"

echo 
echo "Now type 'make' to compile $PROJECT."
