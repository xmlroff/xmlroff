dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)

AC_INIT([xmlroff XSL Formatter 'codegen'],
	[0.6.0],
	[http://xmlroff.org/newticket],
	xmlroff-codegen)
AC_CONFIG_SRCDIR([fo-object-dump.xsl])
AM_INIT_AUTOMAKE

dnl
dnl Check for svn2cl for generating ChangeLog
dnl
enable_svn2cl=yes
AC_PATH_PROG([SVN2CL], [svn2cl])
if test -z "$SVN2CL"; then
  enable_svn2cl=no
fi

AM_CONDITIONAL(ENABLE_SVN2CL, test x$enable_svn2cl != xno)

AC_ARG_WITH(changelog-oldest,
	    AC_HELP_STRING([--with-changelog-oldest=NUMBER],
			   [Oldest revision to include in ChangeLog]))

if test "x$with_changelog_oldest" = "x" ; then
  # Update this when moving current ChangeLog to ChangeLog.pre-nn.
  CHANGELOG_OLDEST=306
else
  CHANGELOG_OLDEST=$with_changelog_oldest
fi

AC_SUBST(CHANGELOG_OLDEST)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
