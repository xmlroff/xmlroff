dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)

AC_INIT([xmlroff XSL Formatter libfo library usage examples],
	[0.6.0],
	[http://xmlroff.org/newticket?component=libfo-examples],
	libfo-examples)
AC_CONFIG_SRCDIR([xmlroff-init2.c])
AM_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AM_PROG_LIBTOOL
AC_PROG_INSTALL

dnl
dnl Debug for TG (-Wall)
dnl
if test "`pwd`" = "/usr/local/src/xslfo/libfo-examples" ; then
    CFLAGS="-Wall -g -O -W "
fi

# Checks for libraries.

LIBFO_REQUIRED_VERSION=0.6.0
PKG_CHECK_MODULES(LIBFO,
		  libfo-0.6 >= $LIBFO_REQUIRED_VERSION,
		  have_libfo=true,
		  have_libfo=false)


AH_TEMPLATE([ENABLE_GP],
	    [Enable support for GNOME Print backend of xmlroff.])

AH_TEMPLATE([ENABLE_CAIRO],
	    [Enable support for Cairo backend of xmlroff.])

if $have_libfo ; then
  AC_MSG_CHECKING(['GNOME Print' backend enabled])
  enable_gp=`pkg-config --variable=enable_gp libfo-0.6`

  if test x"$enable_gp" = xtrue ; then
    AC_DEFINE(ENABLE_GP,1)
    AC_MSG_RESULT(yes)
  else
    AC_DEFINE(ENABLE_GP,0)
    AC_MSG_RESULT(NO)
  fi

  AC_MSG_CHECKING(['Cairo' backend enabled])
  enable_cairo=`pkg-config --variable=enable_cairo libfo-0.6`

  if test x"$enable_cairo" = xtrue ; then
    AC_DEFINE(ENABLE_CAIRO,1)
    AC_MSG_RESULT(yes)
  else
    AC_DEFINE(ENABLE_CAIRO,0)
    AC_MSG_RESULT(NO)
  fi
else
      AC_MSG_ERROR([
*** libfo $LIBFO_REQUIRED_VERSION or newer is required.
*** libfo is part of xmlroff, which is available at http://xmlroff.org/.
  ])
fi

AC_SUBST(LIBFO_LIBS)
AC_SUBST(LIBFO_CFLAGS)

PKG_CHECK_MODULES(GTK,
		  gtk+-2.0 >= 2.2,
		  have_gtk=true,
		  have_gtk=false)

AC_SUBST(GTK_LIBS)
AC_SUBST(GTK_CFLAGS)

PKG_CHECK_MODULES(GMODULE,
		  gmodule-2.0 >= 2.2,
		  have_gmodule=true,
		  have_gmodule=false)

AC_SUBST(GMODULE_LIBS)
AC_SUBST(GMODULE_CFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC

dnl
dnl Check for svn2cl for generating ChangeLog
dnl
enable_svn2cl=yes
AC_PATH_PROG([SVN2CL], [svn2cl])
if test -z "$SVN2CL"; then
  enable_svn2cl=no
fi

AM_CONDITIONAL(ENABLE_SVN2CL, test x$enable_svn2cl != xno)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
