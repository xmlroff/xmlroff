dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)

AC_INIT([xmlroff XSL Formatter testsuite],
	[0.6.0],
	[http://xmlroff.org/newticket?component=testsuite],
	xmlroff-testsuite)
AC_CONFIG_SRCDIR([configure.ac])
AM_INIT_AUTOMAKE

AC_CHECK_PROGS(PERL, perl5 perl)

#
# Current directory
#
PWDIR=`pwd`
AC_SUBST(PWDIR)

BASENAME=["`$PERL -e'use English; if(\$ARGV[0] =~ m@branches/@) {print \"\$POSTMATCH\";} else {print \"\$_\"}' $PWDIR`"]
AC_DEFINE_UNQUOTED(BASENAME, "$BASENAME", [Current directory.])
AC_SUBST(BASENAME)

AC_CONFIG_FILES([
Makefile
testsuite.conf
])
AC_OUTPUT
AC_OUTPUT
