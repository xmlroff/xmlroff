# libfo and xmlroff Makefile.am
# $Id: Makefile.am,v 1.34 2006/12/07 05:31:51 menteith Exp $

SUBDIRS = libfo area fo datatype property expr util . examples docs

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\"	\
	$(LIBXSLT_CFLAGS)	\
	$(POPT_CFLAGS)		\
	-I$(srcdir)/area	\
	-I$(srcdir)/expr	\
	-I$(srcdir)/fo		\
	-I$(srcdir)/datatype	\
	-I$(srcdir)/property	\
	-I$(srcdir)/util


fo_context_cfiles= \
	fo-context.c		\
	fo-context-private.h	\
	fo-context-util.c	\
	fo-context-util.h

fo_base_cfiles = \
	fo-object.c		\
	fo-node.c		\
	fo-node-private.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfo-0.5.pc

lib_LTLIBRARIES = libfo-0.5.la

bin_PROGRAMS = \
	xmlroff

#-release $(VERSION)

libfo_0_5_la_LDFLAGS = \
	-version-info $(LT_VERSION_INFO)	\
	$(no_undefined)

libfo_0_5_includedir = $(includedir)/libfo-0.5

libfo_0_5_include_HEADERS = \
	fo-object.h		\
	fo-node.h		\
	fo-context.h

libfo_0_5_la_SOURCES = \
	$(libfo_0_5_include_HEADERS) \
	$(fo_base_cfiles)	\
	$(fo_context_cfiles)	\
	fo-all-area.h		\
	fo-all-datatype.h	\
	fo-all-fo.h		\
	area-to-pdf.c		\
	area-to-pdf.h

libfo_0_5_la_LIBADD = \
	util/libfo-util.la		\
	area/libfo-area.la		\
	expr/libfo-expr.la		\
	fo/libfo-fo.la			\
	datatype/libfo-datatype.la	\
	property/libfo-property.la	\
	property/libfo-text-property.la	\
	libfo/libfo-libfo.la		\
	libfo/libfo-fodoc.la		\
	$(PANGOXSL_LIBS)		\
	$(PANGO_LIBS)			\
	$(GNOMEPRINT_LIBS) 		\
	$(LIBXSLT_LIBS)			\
	$(FREETYPE_LIBS)


xmlroff_SOURCES = \
	xmlroff.c

xmlroff_LDFLAGS = -static

xmlroff_LDADD = \
	libfo-0.5.la \
	$(PANGOXSL_LIBS) \
	$(PANGO_LIBS) \
	$(GNOMEPRINT_LIBS) \
	$(LIBXSLT_LIBS) \
	$(FREETYPE_LIBS) \
	$(POPT_LIBS)

xmldir = $(datadir)/xml/libfo-@VERSION@
xml_DATA = \
	catalog.xml		\
	libfo-compat.xsl

EXTRA_DIST = \
	catalog.xml.in		\
	libfo-compat.xsl	\
	xmlroff.fo		\
	xmlroff.spec		\
	xmlroff.spec.in		\
	tools/insert-file-as-string.pl

srpm:
	rpmbuild -ts --nodeps $(PACKAGE)-$(VERSION).tar.gz
