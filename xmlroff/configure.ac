dnl Process this file with autoconf to create configure.
set
# require autoconf 2.53
AC_PREREQ(2.53)


dnl The following version number definitions apply to xmlroff and libfo
dnl as a whole, so if changes occurred in any of them, they are all
dnl treated with the same interface and binary age.
dnl
dnl Making releases:
dnl   xmlroff_micro += 1;
dnl   xmlroff_interface_age += 1;
dnl if any functions have been added:
dnl   xmlroff_interface_age = 0
dnl if backwards compatibility has been broken:
dnl   xmlroff_binary_age = 0;
dnl   xmlroff_interface_age = 0;

m4_define([xmlroff_major],0)
m4_define([xmlroff_minor],5)
m4_define([xmlroff_micro],0)
m4_define([xmlroff_interface_age],0)

m4_define([xmlroff_binary_age],0)
dnl m4_define([xmlroff_binary_age],m4_eval(100 * xmlroff_minor + xmlroff_micro))

AC_INIT([xmlroff XSL Formatter],
	xmlroff_major.xmlroff_minor.xmlroff_micro,
	[http://xmlroff.iseer.nl/newticket],
	xmlroff)
AM_CONFIG_HEADER(config.h)

dnl libtool versioning
m4_define([lt_current],m4_eval(100 * xmlroff_minor + xmlroff_micro - xmlroff_interface_age))
m4_define([lt_revision],xmlroff_interface_age)
m4_define([lt_age],m4_eval(xmlroff_binary_age - xmlroff_interface_age))

AC_SUBST(LT_RELEASE,"xmlroff_major.xmlroff_minor")
AC_SUBST(LT_VERSION_INFO,"lt_current:lt_revision:lt_age")
AC_SUBST(LT_CURRENT_MINUS_AGE,m4_eval(lt_current - lt_age))

AC_CONFIG_SRCDIR(fo-object.c)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

AC_PROG_CC
AM_PROG_LIBTOOL

dnl
dnl Debug for TG (-Wunreachable-code)
dnl
AH_TEMPLATE([LIBFO_DEBUG],
            [Enable development debugging messages.])
AC_ARG_WITH(libfo_debug,
	    AC_HELP_STRING([--enable-libfo-debug],
                           [Enable development debugging messages (off)]))

if test "`pwd`" = "/usr/local/src/xslfo/xmlroff" ; then
    if test "${enable_libfo_debug}" = "" ; then
	enable_libfo_debug="yes"
    fi
dnl    CFLAGS="-Wall -g -O -ansi -pedantic -W -Wunused -Wimplicit -Wreturn-type -Wswitch -Wcomment -Wtrigraphs -Wformat -Wchar-subscripts -Wuninitialized -Wparentheses -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Winline "
    CFLAGS="-Wall -g -O -W "
fi

if test "$enable_libfo_debug" = "yes" ; then
    echo Enabling development debug support
    LIBFO_DEBUG=1
    AC_DEFINE(LIBFO_DEBUG)
else    
    LIBFO_DEBUG=0
fi
AC_SUBST(LIBFO_DEBUG)

# Search for Popt in a common location.
# Popt is needed for xmlroff executable but not for libfo.
#
AC_CHECK_HEADERS(popt.h)
SAVED_LIBS=$LIBS
LIBS=
AC_CHECK_LIB(popt, poptGetContext)
POPT_LIBS=$LIBS
LIBS=$SAVED_LIBS
AC_SUBST(POPT_CFLAGS)
AC_SUBST(POPT_LIBS)

#
# Find pkg-config
#
AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
if test "x$PKG_CONFIG" = "xno" ; then
  AC_MSG_ERROR([*** pkg-config not found. See http://pkgconfig.sourceforge.net])
fi

if ! pkg-config --atleast-pkgconfig-version=0.5 ; then
  AC_MSG_ERROR([*** pkg-config too old; version 0.5 or better required.])
fi

#
# Checks for GLib
#
GLIB_REQUIRED_VERSION=2.6.0

AM_PATH_GLIB_2_0($GLIB_REQUIRED_VERSION, :,
  AC_MSG_ERROR([
*** Glib $GLIB_REQUIRED_VERSION or better is required. The latest version of 
*** Glib is always available from ftp://ftp.gtk.org/.]),
  gobject gmodule)

GLIB_CFLAGS=`$PKG_CONFIG --cflags gobject-2.0 gmodule-2.0 gthread-2.0`

# See if it's safe to turn G_DISABLE_DEPRECATED on.
GLIB_VERSION_MAJOR_MINOR=`$PKG_CONFIG --modversion glib-2.0 | sed "s/\.@<:@^.@:>@*\$//"`
GLIB_REQUIRED_VERSION_MAJOR_MINOR=`echo $GLIB_REQUIRED_VERSION | sed "s/\.@<:@^.@:>@*\$//"`
if test "x$GLIB_VERSION_MAJOR_MINOR" = "x$GLIB_REQUIRED_VERSION_MAJOR_MINOR"; then
  GLIB_CFLAGS="-DG_DISABLE_DEPRECATED $GLIB_CFLAGS"
fi

AC_SUBST(GLIB_LIBS)
AC_SUBST(GLIB_CFLAGS)

dnl **************************
dnl *** Checks for gtk-doc ***
dnl **************************

AC_ARG_WITH(html-dir,
	    AC_HELP_STRING([--with-html-dir=PATH],
			   [Path to installed docs]))

if test "x$with_html_dir" = "x" ; then
  HTML_DIR='${datadir}/gtk-doc/html'
else
  HTML_DIR=$with_html_dir
fi

AC_SUBST(HTML_DIR)


#
# Check for sufficiently new gtk-doc
#
gtk_doc_min_version=0.10

AC_CHECK_PROG(GTKDOC, gtkdoc-mkdb, true, false)
if $GTKDOC ; then 
    gtk_doc_version=`gtkdoc-mkdb --version`
    AC_MSG_CHECKING([gtk-doc version ($gtk_doc_version) >= $gtk_doc_min_version])

    IFS="${IFS= 	}"; xmlroff_save_IFS="$IFS"; IFS="."
    set $gtk_doc_version
    for min in $gtk_doc_min_version ; do
        cur=$1; shift
        if test -z $min ; then break; fi
        if test -z $cur ; then GTKDOC=false; break; fi
        if test $cur -gt $min ; then break ; fi
        if test $cur -lt $min ; then GTKDOC=false; break ; fi
    done
    IFS="$xmlroff_save_IFS"

    if $GTKDOC ; then
      AC_MSG_RESULT(yes)
    else
      AC_MSG_RESULT(no)
    fi
fi

AM_CONDITIONAL(HAVE_GTK_DOC, $GTKDOC)
AC_SUBST(HAVE_GTK_DOC)

AC_CHECK_PROG(DB2HTML, db2html, true, false)
AM_CONDITIONAL(HAVE_DOCBOOK, $DB2HTML)

dnl Let people disable the gtk-doc stuff.
AC_ARG_ENABLE(gtk-doc, [  --enable-gtk-doc        use gtk-doc to build documentation [default=no]], enable_gtk_doc="$enableval", enable_gtk_doc=no)

if test "x$enable_gtk_doc" = "xyes" ; then
  if test "x$GTKDOC" = "xtrue" ; then
    enable_gtk_doc=yes
  else
    enable_gtk_doc=no 
  fi
fi

dnl NOTE: We need to use a separate automake conditional for this
dnl       to make this work with the tarballs.
AM_CONDITIONAL(ENABLE_GTK_DOC, test "x$enable_gtk_doc" = "xyes")

#
# Checks for libxml-2.0
#
LIBXML_PACKAGES="libxml-2.0"
LIBXML_REQUIRED_VERSION=2.4.3

AC_MSG_CHECKING(for libxml2 libraries >= $LIBXML_REQUIRED_VERSION) 
if $PKG_CONFIG --atleast-version $LIBXML_REQUIRED_VERSION libxml-2.0 ; then
      LIBXML_CFLAGS=`$PKG_CONFIG --cflags $LIBXML_PACKAGES`
      LIBXML_LIBS=`$PKG_CONFIG --libs $LIBXML_PACKAGES`

      AC_MSG_RESULT(yes)
else
      AC_MSG_ERROR([
*** libxml $LIBXML_REQUIRED_VERSION or newer is required. The latest version of libxml
*** is always available from http://www.xmlsoft.org/.
  ])
fi

AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)

dnl
dnl The following new parameters were added to offer
dnl the ability to specify the location of the libxslt
dnl library during linking and compilation.
dnl Mathieu Lacage 30/03/2000
dnl
LIBXSLT_PREFIX=""
AC_ARG_WITH(libxslt-prefix,
            AC_HELP_STRING([--with-libxslt-prefix=[PFX]],
			   [Specify location of libxslt]),
	    LIBXSLT_PREFIX=$withval)
        
AC_ARG_WITH(libxslt-include-prefix,
            AC_HELP_STRING([--with-libxslt-include-prefix=[PFX]],
			   [Specify location of libxslt headers]),
            LIBXSLT_CFLAGS="-I$withval")

AC_ARG_WITH(libxslt-libs-prefix,
            AC_HELP_STRING([--with-libxslt-libs-prefix=[PFX]],
			   [Specify location of libxslt libs]),
            LIBXSLT_LIBS="-L$withval -lxslt")


dnl
dnl find libxslt
dnl
XSLT_CONFIG="xslt-config"
AC_MSG_CHECKING(for libxslt libraries >= 1.0.3) 
if test "x$LIBXSLT_PREFIX" != "x"
then
	if ${LIBXSLT_PREFIX}/bin/xslt-config --libs print > /dev/null 2>&1
	then
		XSLT_CONFIG=${LIBXSLT_PREFIX}/bin/xslt-config
	else
		XSLT_CONFIG=xslt-config
	fi
fi

AC_DEFUN([VERSION_TO_NUMBER],
[`$1 | sed -e 's/libxml //' | awk 'BEGIN { FS = "."; } { printf "%d", ([$]1 * 1000 + [$]2) * 1000 + [$]3;}'`])

dnl
dnl test version and init our variables
dnl
LIBXSLT_REQUIRED_VERSION=1.0.3
if test "x$XSLT_CONFIG" != "x"
then
	vers=VERSION_TO_NUMBER($XSLT_CONFIG --version)
	if test "$vers" -ge VERSION_TO_NUMBER(echo $LIBXSLT_REQUIRED_VERSION)
	then
		LIBXSLT_LIBS="`$XSLT_CONFIG --libs`"
		LIBXSLT_CFLAGS="`$XSLT_CONFIG --cflags`"
		AC_MSG_RESULT(found)
	else
		AC_MSG_ERROR([
You need at least libxslt $LIBXSLT_REQUIRED_VERSION for this version of xmlroff
])
	fi
else
	AC_MSG_ERROR(Could not find libxslt anywhere, check ftp://xsltsoft.org/.)
fi


AC_SUBST(XSLT_CONFIG)
AC_SUBST(LIBXSLT_LIBS)
AC_SUBST(LIBXSLT_CFLAGS)

AC_ARG_ENABLE(rebuilds, [  --disable-rebuilds      disable all source autogeneration rules],,enable_rebuilds=yes)

# define a MAINT-like variable REBUILD which is set if Perl
# is found, so autogenerated sources can be rebuilt

AC_CHECK_PROGS(PERL, perl5 perl)

REBUILD=\#
if test "x$enable_rebuilds" = "xyes" && \
     test -n "$PERL" && \
     $PERL -e 'exit !($] >= 5.002)' > /dev/null 2>&1 ; then
  REBUILD=
fi
AC_SUBST(REBUILD)

#
# Checks for FreeType
#
FREETYPE_LIBS=
FREETYPE_CFLAGS=
have_freetype=false
AC_PATH_PROG(FREETYPE_CONFIG, freetype-config, no)
if test "x$FREETYPE_CONFIG" != "xno" ; then
  FREETYPE_CFLAGS=`$FREETYPE_CONFIG --cflags`
  FREETYPE_LIBS=`$FREETYPE_CONFIG --libs`

  AC_CHECK_LIB(freetype, FT_New_Face, have_freetype=true
	       ,:,$FREETYPE_LIBS)
fi
AC_SUBST(FREETYPE_LIBS)
AC_SUBST(FREETYPE_CFLAGS)
AM_CONDITIONAL(HAVE_FREETYPE, $have_freetype) 

AH_TEMPLATE([ENABLE_GP],
	    [Enable support for GNOME Print backend of xmlroff.])

AC_ARG_ENABLE(gp,
	      AC_HELP_STRING([--enable-gp],
			     [build GNOME Print output capability (default=yes)]),
	      enable_gp_arg="$enableval", enable_gp_arg=yes)

if test "x$enable_gp_arg" != "xyes" ; then
  enable_gp_arg=no
fi

enable_gp=false
GNOMEPRINT_REQUIRES=""

if test "x$enable_gp_arg" = "xyes" ; then
  #
  # Check for libgnomeprint support requirement
  #
  have_gnomeprint=false

  PKG_CHECK_MODULES(GNOMEPRINT,
		    libgnomeprint-2.2 >= 2.8,
		    have_gnomeprint=true,
		    :)

  if $have_gnomeprint; then
    enable_gp=true

    AC_DEFINE(ENABLE_GP,1)
    GNOMEPRINT_REQUIRES="pango"
  else
    AC_DEFINE(ENABLE_GP,0)
    GNOMEPRINT_LIBS=""
    GNOMEPRINT_CFLAGS=""
  fi
fi

AC_SUBST(GNOMEPRINT_ENABLED, [$enable_gp])
AC_SUBST(GNOMEPRINT_REQUIRES)
AC_SUBST(GNOMEPRINT_LIBS)
AC_SUBST(GNOMEPRINT_CFLAGS)
AC_SUBST(ENABLE_GP, [$enable_gp])
AM_CONDITIONAL(ENABLE_GP, [$enable_gp])

#
# Checks for Cairo
#
AH_TEMPLATE([ENABLE_CAIRO],
	    [Enable support for Cairo backend of xmlroff.])

AC_ARG_ENABLE(cairo,
	      AC_HELP_STRING([--enable-cairo],
			     [build Cairo output capability (default=yes)]),
	      enable_cairo_arg="$enableval", enable_cairo_arg=yes)

if test "x$enable_cairo_arg" != "xyes" ; then
  enable_cairo_arg=no
fi

enable_cairo=false
CAIRO_REQUIRES=""

have_cairo=false
have_cairo_freetype=false
have_cairo_win32=false

if test "x$enable_cairo_arg" = "xyes" ; then
  PKG_CHECK_MODULES(CAIRO, cairo >= 1.2.4, have_cairo=true, :)
   
  if $have_cairo ; then
    pango_save_ldflags=$LDFLAGS
    m4_pattern_allow([PKG_CONFIG_DISABLE_UNINSTALLED])
    INSTALLED_CAIRO_LIBS=`PKG_CONFIG_DISABLE_UNINSTALLED=yes $PKG_CONFIG --libs cairo`
    LDFLAGS="$LDFLAGS $INSTALLED_CAIRO_LIBS"
    enable_cairo=true
    AC_CHECK_LIB(cairo, cairo_win32_scaled_font_select_font, have_cairo_win32=true, :)
    AC_DEFINE(ENABLE_CAIRO,1)
    if $have_cairo_win32 && $have_win32; then
      AC_DEFINE(HAVE_CAIRO_WIN32, 1, [Whether Cairo uses the Win32 GDI for fonts])
    else			  
      AC_CHECK_LIB(cairo, cairo_ft_scaled_font_lock_face, have_cairo_freetype=true, :)
      if $have_cairo_freetype && $have_freetype ; then
        AC_DEFINE(HAVE_CAIRO_FREETYPE, 1, [Whether Cairo uses FreeType for fonts])
      else
        have_cairo=false
	AC_DEFINE(ENABLE_CAIRO,0)
      fi
    fi
    LDFLAGS=$pango_save_ldflags
  fi
fi

AC_SUBST(CAIRO_ENABLED, [$enable_cairo])
AC_SUBST(ENABLE_CAIRO, [$enable_cairo])
AM_CONDITIONAL(ENABLE_CAIRO, [$enable_cairo])
AM_CONDITIONAL(HAVE_CAIRO, $have_cairo)
AM_CONDITIONAL(HAVE_CAIRO_WIN32, $have_cairo_win32 && $have_win32)
AM_CONDITIONAL(HAVE_CAIRO_FREETYPE, $have_cairo_freetype && $have_freetype)

#
# Check have at least one backend enabled
#
if $enable_gp || $enable_cairo ; then : ; else
  AC_MSG_ERROR([
*** No backends are enabled.
*** Must have at least one backend to build xmlroff.])
fi

#
# Checks for Pango
#
PANGO_PACKAGES=
PANGO_REQUIRED_VERSION=1.10

if $enable_gp ; then
   PANGO_PACKAGES="$GNOMEPRINT_REQUIRES"
fi
if $enable_cairo ; then
   PANGO_PACKAGES="$PANGO_PACKAGES pangocairo"
fi
have_pango=false

PKG_CHECK_MODULES(PANGO,
		  $PANGO_PACKAGES >= $PANGO_REQUIRED_VERSION,
		  have_pango=true,
		  :)

if $have_pango ; then : ; else
      AC_MSG_ERROR([
*** Pango $PANGO_REQUIRED_VERSION or newer is required.
*** Pango is available at http://pango.org/.
  ])
fi

AC_SUBST(PANGO_LIBS)
AC_SUBST(PANGO_CFLAGS)

#
# Checks for GdkPixBuf
#
GDKPIXBUF_PACKAGES=gdk-pixbuf-2.0
GDKPIXBUF_REQUIRED_VERSION=2.2

have_gdkpixbuf=false

PKG_CHECK_MODULES(GDKPIXBUF,
		  $GDKPIXBUF_PACKAGES >= $GDKPIXBUF_REQUIRED_VERSION,
		  have_gdkpixbuf=true,
		  :)

if $have_gdkpixbuf ; then : ; else
      AC_MSG_ERROR([
*** GdkPixbuf $GDKPIXBUF_REQUIRED_VERSION or newer is required.
*** GdkPixbuf is available at http://gtk.org.
  ])
fi

AC_SUBST(GDKPIXBUF_LIBS)
AC_SUBST(GDKPIXBUF_CFLAGS)

AC_MSG_CHECKING([for some Win32 platform])
case "$host" in
  *-*-mingw*|*-*-cygwin*)
    xmlroff_platform_win32=yes
    ;;
  *)
    xmlroff_platform_win32=no
    ;;
esac
AC_MSG_RESULT([$xmlroff_platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$xmlroff_platform_win32" = "yes")

AH_TEMPLATE([PIXELS_PER_INCH],
	    [Pixels per inch for use with graphics without intrinsic size.])

pixels_per_inch_default=96

AC_ARG_WITH(pixels_per_inch,
	      AC_HELP_STRING([--with-pixels-per-inch],
			     [Pixels per inch (default=pixels_per_inch_default)]),
	      pixels_per_inch="$withval", :)

if test "x$with_pixels_per_inch" = "x" ; then
  PIXELS_PER_INCH=$pixels_per_inch_default
else
  PIXELS_PER_INCH=$with_pixels_per_inch
fi

AC_DEFINE_UNQUOTED(PIXELS_PER_INCH,$PIXELS_PER_INCH)

AH_TEMPLATE([ENABLE_CLIP],
            [Enable clipping to area extent.  Clipping should only be disabled when debugging.])
AC_ARG_ENABLE(clip,
	      AC_HELP_STRING([--enable-clip],
			     [enable clipping to area extent (default=yes)]),
	      enable_clip_arg="$clipval", enable_clip_arg=yes)

if test "x$enable_clip_arg" = "xyes" ; then
  AC_DEFINE(ENABLE_CLIP,1)
else
    AC_DEFINE(ENABLE_CLIP,0)
fi

CFLAGS="$CFLAGS $GLIB_CFLAGS"

AC_OUTPUT([
INSTALL
Makefile 
area/Makefile
datatype/Makefile
docs/Makefile
expr/Makefile
fo/Makefile
property/Makefile
libfo/Makefile
examples/Makefile
examples/xml2003/Makefile
util/Makefile
libfo-0.5.pc
xmlroff.spec
catalog.xml
])

fo_doc_subtypes=""
if $enable_cairo  ; then fo_doc_subtypes="$fo_doc_subtypes 'Cairo'"; fi
if $enable_gp     ; then fo_doc_subtypes="$fo_doc_subtypes 'GNOME Print'"; fi

echo "
Configuration:
  Enabled FoDoc subtypes:$fo_doc_subtypes"

echo "
Now type 'make' to compile xmlroff.
"
