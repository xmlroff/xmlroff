dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)

AC_INIT([xmlroff XSL Formatter testing framework],
	[0.5.2],
	[http://xmlroff.org/newticket],
	xmlroff-testing)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([configure.ac])
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER(config.h)

############################################################
#
# Symbols that are used in config.xsl.
#

#
# Title used in generated reports.
#
title_default="xmlroff Test Results"

AC_ARG_WITH(title,
	    AC_HELP_STRING([--with-title],
			   [Title used in generated reports. (default=$title_default)]),
	      title="$withval", :)

if test "x$with_title" = "x" ; then
  TITLE=$title_default
else
  TITLE=$with_title
fi
AC_DEFINE_UNQUOTED(TITLE,"$TITLE", [Title used in generated reports.])

#
# ImageMagick 'convert' program.
#
AC_PATH_PROG(CONVERT, convert, no)
if test "x$CONVERT" = "xno" ; then
  AC_MSG_ERROR([
*** ImageMagick 'convert' is required. The latest version of ImageMagick
*** is always available from http://www.imagemagick.org/.
  ])
fi
AC_DEFINE_UNQUOTED(CONVERT, "$CONVERT", [Full path to ImageMagick 'convert' program.])

#
# ImageMagick 'composite' program.
#
AC_PATH_PROG(COMPOSITE, composite, no)
if test "x$COMPOSITE" = "xno" ; then
  AC_MSG_ERROR([
*** ImageMagick 'composite' is required. The latest version of ImageMagick
*** is always available from http://www.imagemagick.org/.
  ])
fi
AC_DEFINE_UNQUOTED(COMPOSITE, "$COMPOSITE", [Full path to ImageMagick 'composite' program.])

#
# Current date.  Meant to be set on the command line.
#
AC_DEFINE(DATE,
	  0,
	  [The current date.  This is meant to be set on the command line, so no default value.])

#
# Whether to output debugging messages and how verbose to be.
#
debug_default=0
AC_ARG_WITH(debug,
	    AC_HELP_STRING([--with-debug],
			   [1 enables debugging messages.  2 or greater enables more verbose output. (default is 0)]),
	    debug="$withval", :)
if test "x$with_debug" = "x" ; then
  DEBUG=$debug_default
else
  DEBUG=$with_debug
fi
AC_DEFINE_UNQUOTED(DEBUG,
		   $DEBUG,
		   [1 enables debugging messages.  2 or greater enables more verbose output. (default=0)])

#
# Default command patterns
#
command_patterns_default="%p -o %o %c %i %s;%p -o %o %c %i;%p -o %o %i"
AC_ARG_WITH(command_patterns,
	    AC_HELP_STRING([--with-oommand-patterns],
			   [Patterns for running processor. (default works for xmlroff)]),
	    command_patterns="$withval", :)
if test "x$with_command_patterns" = "x" ; then
  COMMAND_PATTERNS=$command_patterns_default
else
  COMMAND_PATTERNS=$with_command_patterns
fi
AC_DEFINE_UNQUOTED(COMMAND_PATTERNS,
	           "$COMMAND_PATTERNS",
	           [Patterns for running processor.])

#
# Default stylesheet, if any, to use with tests that don't specify
# a stylesheet.
#
default_stylesheet_default=0
AC_ARG_WITH(default_stylesheet,
	    AC_HELP_STRING([--with-default-stylesheet],
			   [Full path to default stylesheet used in tests. (default=no stylesheet)]),
	    default_stylesheet="$withval", :)
if test "x$with_default_stylesheet" = "x" ; then
  DEFAULT_STYLESHEET=$default_stylesheet_default
else
  DEFAULT_STYLESHEET=$with_default_stylesheet
fi
AC_DEFINE_UNQUOTED(DEFAULT_STYLESHEET,
	           $DEFAULT_STYLESHEET,
	           [Full path to default stylesheet, if any.  (default=false)])

#
# Whether or not to output form for updating results interactively.
#
AH_TEMPLATE([FORM],
            [Output form in HTML reports.])
AC_ARG_ENABLE(form,
	      AC_HELP_STRING([--enable-form],
			     [Output form in HTML reports (default=yes)]),
	      enable_form_arg="$formval", enable_form_arg=yes)

if test "x$enable_form_arg" = "xyes" ; then
  AC_DEFINE(FORM,1)
else
  AC_DEFINE(FORM,0)
fi

#
# Whether or not to output reference and stereo in reports.
#
AH_TEMPLATE([REFERENCE],
            [Output refence images in reports.])
AC_ARG_ENABLE(reference,
	      AC_HELP_STRING([--enable-reference],
			     [Output reference images in reports (default=yes)]),
	      enable_reference_arg="$referenceval", enable_reference_arg=yes)

if test "x$enable_reference_arg" = "xyes" ; then
  AC_DEFINE(REFERENCE,1)
else
  AC_DEFINE(REFERENCE,0)
fi

#
# Whether or not to output a HTML report for each test result.
#
AH_TEMPLATE([OUTPUT_INDIVIDUAL],
            [Whether or not to output a HTML report file for each test result. Set to 'true()' to output individual reports.])
AC_ARG_ENABLE(individual,
	      AC_HELP_STRING([--enable-individual],
			     [Output a HTML report file for each test result (default=yes).]),
	      enable_individual_arg="$individualval", enable_individual_arg=yes)

if test "x$enable_individual_arg" = "xyes" ; then
  AC_DEFINE(OUTPUT_INDIVIDUAL,1)
else
  AC_DEFINE(OUTPUT_INDIVIDUAL,0)
fi

#
# File of file size data that is created by testsuccess.pl.
#
TESTSUCCESS=testsuccess.xml
AC_DEFINE_UNQUOTED(TESTSUCCESS,
	           "$TESTSUCCESS",
	           [File of file size data that is created by testsuccess.pl.])
AC_SUBST(TESTSUCCESS)

#
# Filename of test results XML file.
#
test_results_default=testresults.xml
AC_ARG_WITH(test_results,
	    AC_HELP_STRING([--with-test-results],
			   [Filename of test results XML file. (default=testresults.xml)]),
	    test_results="$withval", :)
if test "x$with_test_results" = "x" ; then
  TEST_RESULTS=$test_results_default
else
  TEST_RESULTS=$with_test_results
fi
AC_DEFINE_UNQUOTED(TEST_RESULTS,
	           "$TEST_RESULTS",
	           [Filename of test results XML file.])
AC_SUBST(TEST_RESULTS)

#
# Filename of testsuites XML file.
#
testsuites_default=testsuites.xml
AC_ARG_WITH(testsuites,
	    AC_HELP_STRING([--with-testsuites],
			   [Filename of testsuites XML file that references individual 'testsuite.xml' files from one or more test suites. (default=testsuites.xml)]),
	    testsuites="$withval", :)
if test "x$with_testsuites" = "x" ; then
  TESTSUITES=$testsuites_default
else
  TESTSUITES=$with_testsuites
fi
AC_DEFINE_UNQUOTED(TESTSUITES,
	           "$TESTSUITES",
	           [Filename of test results XML file.])
AC_SUBST(TESTSUITES)

#
# XSL processor.
#
xsl_processor_default=../xmlroff/xmlroff/xmlroff
AC_ARG_WITH(xsl_processor,
	    AC_HELP_STRING([--with-xsl-processor],
			   [Path to XSL processor to test.]),
	    xsl_processor="$withval", :)
if test "x$with_xsl_processor" = "x" ; then
  XSL_PROCESSOR=$xsl_processor_default
else
  XSL_PROCESSOR=$with_xsl_processor
fi
AC_MSG_CHECKING([for XSL processor])
if test -f "$XSL_PROCESSOR" ; then
  AC_MSG_RESULT($XSL_PROCESSOR)
else
  AC_MSG_ERROR([
*** XSL processor "$XSL_PROCESSOR" does not exist.
  ])
fi
AC_DEFINE_UNQUOTED(XSL_PROCESSOR,
	           "$XSL_PROCESSOR",
	           [Path to XSL processor to test.])
AC_SUBST(XSL_PROCESSOR)

#
# XSL processor options.
#
xsl_processor_flags_default=
AC_ARG_WITH(xsl_processor_flags,
	    AC_HELP_STRING([--with-xsl-processor-flags],
			   [Flags to pass to the XSL processor.]),
	    xsl_processor_flags="$withval", :)
if test "x$with_xsl_processor_flags" = "x" ; then
  XSL_PROCESSOR_FLAGS=$xsl_processor_flags_default
else
  XSL_PROCESSOR_FLAGS=$with_xsl_processor_flags
fi
AC_DEFINE_UNQUOTED(XSL_PROCESSOR_FLAGS,
	           "$XSL_PROCESSOR_FLAGS",
	           [Flags to pass to the XSL processor.])
AC_SUBST(XSL_PROCESSOR_FLAGS)

#
# Current directory
#
PWD=`pwd`
BASENAME=`basename $PWD`
AC_DEFINE_UNQUOTED(BASENAME, "$BASENAME", [Current directory.])

############################################################
#
# Other required programs
#

xsltproc_default=xsltproc
AC_ARG_WITH(xsltproc,
	    AC_HELP_STRING([--with-xsltproc],
			   [Full path to xsltproc XSLT processor for transforming reports.]),
	    xsltproc="$withval", :)
if test "x$with_xsltproc" = "x" ; then
  XSLTPROC=$xsltproc_default
else
  XSLTPROC=$with_xsltproc
fi
AC_PATH_PROG(XSLTPROC, $XSLTPROC, no)
AC_DEFINE_UNQUOTED(XSLTPROC,
	           "$XSLTPROC",
	           [Full path to xsltproc XSLT processor for transforming reports.])
AC_SUBST(XSLTPROC)
if test "x$XSLTPROC" = "xno" ; then
  AC_MSG_ERROR([
*** xslproc is required. The latest version of xsltproc
*** is always available from http://www.xmlsoft.org/.
  ])
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

echo "
The 'configure' options that you used are recorded in 'config.log'."
