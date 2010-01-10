dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)

AC_INIT([xmlroff XSL Formatter testing framework],
	[0.6.2],
	[http://xmlroff.org/newticket?component=testing],
	xmlroff-testing)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([configure.ac])
AM_INIT_AUTOMAKE

AM_CONFIG_HEADER(config.h)

############################################################
#
# Required programs
#

xsltproc_default=xsltproc
AC_ARG_WITH(xsltproc,
	    AC_HELP_STRING([--with-xsltproc],
			   [Full path to xsltproc XSLT processor for transforming reports]),
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
*** xsltproc is required. The latest version of xsltproc
*** is always available from http://www.xmlsoft.org/.
  ])
fi

#
# ImageMagick 'convert' program.
#
convert_default=convert
AC_ARG_WITH(convert,
	    AC_HELP_STRING([--with-convert],
			   [Full path to ImageMagick 'convert' program.]),
	    convert="$withval", :)
if test "x$with_convert" = "x" ; then
  CONVERT=$convert_default
else
  CONVERT=$with_convert
fi
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
composite_default=composite
AC_ARG_WITH(composite,
	    AC_HELP_STRING([--with-composite],
			   [Full path to ImageMagick 'composite' program.]),
	    composite="$withval", :)
if test "x$with_composite" = "x" ; then
  COMPOSITE=$composite_default
else
  COMPOSITE=$with_composite
fi
AC_PATH_PROG(COMPOSITE, composite, no)
if test "x$COMPOSITE" = "xno" ; then
  AC_MSG_ERROR([
*** ImageMagick 'composite' is required. The latest version of ImageMagick
*** is always available from http://www.imagemagick.org/.
  ])
fi
AC_DEFINE_UNQUOTED(COMPOSITE, "$COMPOSITE", [Full path to ImageMagick 'composite' program.])

AC_CHECK_PROGS(PERL, perl5 perl)

############################################################
#
# Symbols that are used in config.xsl.
#

# Strings to indicate the source of a setting.
default_setter="default"
option_setter="option"
results_setter="results"

#
# Filename of test results XML file.
#
# Determine it before other config.xsl variables because it
# may include processing instructions that set the default
# value for some of the other variables.
#
test_results_default=testresults.xml
test_results_setter=$default_setter
AC_ARG_WITH(test_results,
	    AC_HELP_STRING([--with-test-results],
			   [Filename of test results XML file (default=testresults.xml)]),
	    test_results="$withval", :)
if test "x$with_test_results" = "x" ; then
  TEST_RESULTS=$test_results_default
else
  TEST_RESULTS=$with_test_results
  test_results_setter=$option_setter
fi
AC_DEFINE_UNQUOTED(TEST_RESULTS,
	           "$TEST_RESULTS",
	           [Filename of test results XML file.])
AC_SUBST(TEST_RESULTS)

#
# Project name.
#
project_name_default="xmlroff"
project_name_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_project_name=["`$PERL -n -e'if(/<\?xt-project-name\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_project_name" != "x" ; then
    project_name_default="$results_project_name"
    project_name_setter=$results_setter
  fi
fi
AC_ARG_WITH(project_name,
	    AC_HELP_STRING([--with-project-name],
			   [Project name used in URLs. (default=$project_name_default)]),
	      project_name="$withval", :)

if test "x$with_project_name" = "x" ; then
  PROJECT_NAME=$project_name_default
else
  PROJECT_NAME=$with_project_name
fi
AC_DEFINE_UNQUOTED(PROJECT_NAME,"$PROJECT_NAME", [Project name used in URLs.])
AC_SUBST(PROJECT_NAME)

#
# Title used in generated reports.
#
title_default="xmlroff Test Results"

AC_ARG_WITH(title,
	    AC_HELP_STRING([--with-title],
			   [Title used in generated reports (default="xmlroff Test Results")]),
	      title="$withval", :)

if test "x$with_title" = "x" ; then
  TITLE=$title_default
else
  TITLE=$with_title
fi
AC_DEFINE_UNQUOTED(TITLE,"$TITLE", [Title used in generated reports.])

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
			   [1 enables debugging messages;  2 or greater enables more verbose output (default is 0)]),
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
# Command patterns to use when running XSL processor.
#
command_patterns_default="%p -o %o %c %i %s;%p -o %o %c %i;%p -o %o %i %s;%p -o %o %i"
command_patterns_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_command_patterns=["`$PERL -n -e'if(/<\?xt-command-patterns\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_command_patterns" != "x" ; then
    command_patterns_default="$results_command_patterns"
    command_patterns_setter=$results_setter
  fi
fi
AC_ARG_WITH(command_patterns,
	    AC_HELP_STRING([--with-command-patterns],
			   [Patterns for running XSL processor (default works for xmlroff)]),
	    command_patterns="$withval", :)
if test "x$with_command_patterns" = "x" ; then
  COMMAND_PATTERNS=$command_patterns_default
else
  COMMAND_PATTERNS=$with_command_patterns
  command_patterns_setter=$option_setter
fi
AC_DEFINE_UNQUOTED(COMMAND_PATTERNS,
	           "$COMMAND_PATTERNS",
	           [Patterns for running processor.])
AC_DEFINE_UNQUOTED(COMMAND_PATTERNS_SETTER,
	           "$command_patterns_setter",
	           [Where COMMAND_PATTERNS was set.])

#
# Default stylesheet, if any, to use with tests that don't specify
# a stylesheet.
#
default_stylesheet_default=
default_stylesheet_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_default_stylesheet=["`$PERL -n -e'if(/<\?xt-default-stylesheet\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_default_stylesheet" != "x" ; then
    default_stylesheet_default="$results_default_stylesheet"
    default_stylesheet_setter=$results_setter
  fi
fi
AC_ARG_WITH(default_stylesheet,
	    AC_HELP_STRING([--with-default-stylesheet],
			   [Full path to default stylesheet used in tests (default=no stylesheet)]),
	    default_stylesheet="$withval", :)
if test "x$with_default_stylesheet" = "x" ; then
  DEFAULT_STYLESHEET=$default_stylesheet_default
else
  DEFAULT_STYLESHEET=$with_default_stylesheet
  default_stylesheet_setter=$option_setter
fi
AC_DEFINE_UNQUOTED(DEFAULT_STYLESHEET,
	           "$DEFAULT_STYLESHEET",
	           [Full path to default stylesheet, if any.  (default=false)])
AC_DEFINE_UNQUOTED(DEFAULT_STYLESHEET_SETTER,
	           "$default_stylesheet_setter",
	           [Where DEFAULT_STYLESHEET was set.])

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
			     [Output a HTML report file for each test result (default=yes)]),
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
# Filename of testsuites XML file.
#
testsuites_default=testsuites.xml
testsuites_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_testsuites=["`$PERL -n -e'if(/<\?xt-testsuites\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_testsuites" != "x" ; then
    testsuites_default="$results_testsuites"
    testsuites_setter=$results_setter
  fi
fi
AC_ARG_WITH(testsuites,
	    AC_HELP_STRING([--with-testsuites],
			   [Filename of testsuites XML file that references individual 'testsuite.xml' files from one or more test suites (default=testsuites.xml)]),
	    testsuites="$withval", :)
if test "x$with_testsuites" = "x" ; then
  TESTSUITES=$testsuites_default
else
  TESTSUITES=$with_testsuites
fi
AC_SUBST(TESTSUITES)
AC_DEFINE_UNQUOTED(TESTSUITES,
	           "$TESTSUITES",
	           [Filename of test results XML file.])
AC_DEFINE_UNQUOTED(TESTSUITES_SETTER,
	           "$testsuites_setter",
	           [Where TESTSUITES was set.])

#
# Subset of testcases to run
#
test_subset_default=
test_subset_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_test_subset=["`$PERL -n -e'if(/<\?xt-test-subset\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_test_subset" != "x" ; then
    test_subset_default="$results_test_subset"
    test_subset_setter=$results_setter
  fi
fi
AC_ARG_WITH(test_subset,
	    AC_HELP_STRING([--with-test-subset],
			   [Subset of tests to run. (default=no subsetting)]),
	    testsuites="$withval", :)
if test "x$with_test_subset" = "x" ; then
  TEST_SUBSET=$test_subset_default
else
  TEST_SUBSET=$with_test_subset
fi
AC_SUBST(TEST_SUBSET)
AC_DEFINE_UNQUOTED(TEST_SUBSET,
	           "$TEST_SUBSET",
	           [Subset of tests to run.])
AC_DEFINE_UNQUOTED(TEST_SUBSET_SETTER,
	           "$test_subset_setter",
	           [Where TEST_SUBSET was set.])

#
# XSL processor.
#
xsl_processor_default=../xmlroff/xmlroff/xmlroff
xsl_processor_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_xsl_processor=["`$PERL -n -e'if(/<\?xt-xsl-processor\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_xsl_processor" != "x" ; then
    xsl_processor_default="$results_xsl_processor"
    xsl_processor_setter=$results_setter
  fi
fi
AC_ARG_WITH(xsl_processor,
	    AC_HELP_STRING([--with-xsl-processor],
			   [Path to XSL processor to test.]),
	    xsl_processor="$withval", :)
if test "x$with_xsl_processor" = "x" ; then
  XSL_PROCESSOR=$xsl_processor_default
else
  XSL_PROCESSOR=$with_xsl_processor
  xsl_processor_setter=$option_setter
fi
AC_MSG_CHECKING([for XSL processor])
if test -f "$XSL_PROCESSOR" ; then
  AC_MSG_RESULT($XSL_PROCESSOR)
else
  AC_MSG_ERROR([
*** XSL processor "$XSL_PROCESSOR" does not exist.
  ])
fi
AC_SUBST(XSL_PROCESSOR)
AC_DEFINE_UNQUOTED(XSL_PROCESSOR,
	           "$XSL_PROCESSOR",
	           [Path to XSL processor to test.])
AC_DEFINE_UNQUOTED(XSL_PROCESSOR_SETTER,
	           "$xsl_processor_setter",
	           [Where XSL_PROCESSOR was set.])

#
# XSL processor flags.
#
xsl_processor_flags_default=
xsl_processor_flags_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_xsl_processor_flags=["`$PERL -n -e'if(/<\?xt-xsl-processor-flags\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_xsl_processor_flags" != "x" ; then
    xsl_processor_flags_default="$results_xsl_processor_flags"
    xsl_processor_flags_setter=$results_setter
  fi
fi
AC_ARG_WITH(xsl_processor_flags,
	    AC_HELP_STRING([--with-xsl-processor-flags],
			   [Flags to pass to the XSL processor.]),
	    xsl_processor_flags="$withval", :)
if test "x$with_xsl_processor_flags" = "x" ; then
  XSL_PROCESSOR_FLAGS=$xsl_processor_flags_default
else
  XSL_PROCESSOR_FLAGS=$with_xsl_processor_flags
  xsl_processor_flags_setter=$option_setter
fi
AC_SUBST(XSL_PROCESSOR_FLAGS)
AC_DEFINE_UNQUOTED(XSL_PROCESSOR_FLAGS,
	           "$XSL_PROCESSOR_FLAGS",
	           [Flags to pass to the XSL processor.])
AC_DEFINE_UNQUOTED(XSL_PROCESSOR_FLAGS_SETTER,
	           "$xsl_processor_flags_setter",
	           [Where XSL_PROCESSOR_FLAGS was set.])

#
# Location of Trac
#
# Ticket numbers refer to tickets in this Trac
#
trac_default=http://xmlroff.org/ticket/
trac_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_trac=["`$PERL -n -e'if(/<\?xt-trac\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_trac" != "x" ; then
    trac_default="$results_trac"
    trac_setter=$results_setter
  fi
fi
AC_ARG_WITH(trac,
	    AC_HELP_STRING([--with-trac],
			   [URL of Trac to which ticket numbers refer. (default=http://xmlroff.org/ticket/)]),
	    trac="$withval", :)
if test "x$with_trac" = "x" ; then
  TRAC=$trac_default
else
  TRAC=$with_trac
  trac_setter=$option_setter
fi
AC_SUBST(TRAC)
AC_DEFINE_UNQUOTED(TRAC,
	           "$TRAC",
	           [URL of Trac to which ticket numbers refer.])
AC_DEFINE_UNQUOTED(TRAC_SETTER,
	           "$trac_setter",
	           [Where TRAC setting was set.])

#
# Current directory
#
PWD=`pwd`
AC_SUBST(PWD)

#
# Basename of project
#
# Used when constructing URLs
#
basename_default=`basename $PWD`
basename_setter=$default_setter

# Default may be overridden by a PI in the results document.
if test -f "$TEST_RESULTS" ; then
  results_basename=["`$PERL -n -e'if(/<\?xt-basename\s+([^?]+)\?>/) {print \$1;}' $TEST_RESULTS`"]
  if test "x$results_basename" != "x" ; then
    basename_default="$results_basename"
    basename_setter=$results_setter
  fi
fi
AC_ARG_WITH(basename,
	    AC_HELP_STRING([--with-basename],
			   [Basename for use in URLs. (default=`basename $PWD`)]),
	    basename="$withval", :)
if test "x$with_basename" = "x" ; then
  BASENAME=$basename_default
else
  BASENAME=$with_basename
  basename_setter=$option_setter
fi
AC_SUBST(BASENAME)
AC_DEFINE_UNQUOTED(BASENAME,
	           "$BASENAME",
                   [Basename for use in URLs.])
AC_DEFINE_UNQUOTED(BASENAME_SETTER,
	           "$basename_setter",
	           [Where BASENAME setting was set.])

AC_CONFIG_FILES([
Makefile
testing.conf
])
AC_OUTPUT

echo "
Configurable settings (and where set):

command-patterns:    \"$COMMAND_PATTERNS\" ($command_patterns_setter)
default-stylesheet:  \"$DEFAULT_STYLESHEET\" ($default_stylesheet_setter)
test-results:        \"$TEST_RESULTS\" ($test_results_setter)
testsuites:          \"$TESTSUITES\" ($testsuites_setter)
test-subset:         \"$TEST_SUBSET\" ($test_subset_setter)
xsl-processor:       \"$XSL_PROCESSOR\" ($xsl_processor_setter)
xsl-processor-flags: \"$XSL_PROCESSOR_FLAGS\" ($xsl_processor_flags_setter)
project-name:        \"$PROJECT_NAME\" ($project_name_setter)
trac:                \"$TRAC\" ($trac_setter)
basename:            \"$BASENAME\" ($basename_setter)

The 'configure' options that you used are recorded in 'config.log'."
