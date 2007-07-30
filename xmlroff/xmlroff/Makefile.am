# libfo and xmlroff Makefile.am
# $Id: Makefile.am,v 1.34 2006/12/07 05:31:51 menteith Exp $

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\"	\
	$(LIBXSLT_CFLAGS)	\
	$(GLIB_CFLAGS)

bin_PROGRAMS = \
	xmlroff

#-release $(VERSION)


xmlroff_SOURCES = \
	xmlroff.c

xmlroff_LDFLAGS = -static

xmlroff_LDADD = \
	../libfo/libfo-0.5.la \
	$(PANGO_LIBS) \
	$(GNOMEPRINT_LIBS) \
	$(LIBXSLT_LIBS) \
	$(FREETYPE_LIBS)
