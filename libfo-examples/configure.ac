dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)

AC_INIT([xmlroff XSL Formatter libfo library usage examples],
	0.5.2,
	[http://xmlroff.org/newticket?component=libfo-examples],
	libfo-examples)
AC_CONFIG_SRCDIR([xmlroff-init2.c])
AM_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AM_PROG_LIBTOOL
AC_PROG_INSTALL

# Checks for libraries.

PKG_CHECK_MODULES(LIBFO,
		  libfo-0.5 >= 0.5.0,
		  have_libfo=true,
		  have_libfo=false)


AH_TEMPLATE([ENABLE_GP],
	    [Enable support for GNOME Print backend of xmlroff.])

AH_TEMPLATE([ENABLE_CAIRO],
	    [Enable support for Cairo backend of xmlroff.])

if $have_libfo ; then
  AC_MSG_CHECKING(['GNOME Print' backend enabled])
  enable_gp=`pkg-config --variable=enable_gp libfo-0.5`

  if test x"$enable_gp" = xtrue ; then
    AC_DEFINE(ENABLE_GP,1)
    AC_MSG_RESULT(yes)
  else
    AC_DEFINE(ENABLE_GP,0)
    AC_MSG_RESULT(NO)
  fi

  AC_MSG_CHECKING(['Cairo' backend enabled])
  enable_cairo=`pkg-config --variable=enable_cairo libfo-0.5`

  if test x"$enable_cairo" = xtrue ; then
    AC_DEFINE(ENABLE_CAIRO,1)
    AC_MSG_RESULT(yes)
  else
    AC_DEFINE(ENABLE_CAIRO,0)
    AC_MSG_RESULT(NO)
  fi
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

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
