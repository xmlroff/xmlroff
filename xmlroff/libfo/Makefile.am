## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(LIBXSLT_CFLAGS)	\
	$(PANGOXSL_CFLAGS)	\
	$(PANGO_CFLAGS)		\
	-I$(top_srcdir)		\
	-I$(top_srcdir)/area	\
	-I$(top_srcdir)/fo	\
	-I$(top_srcdir)/property	\
	-I$(top_srcdir)/datatype

LDADDS = @STRIP_BEGIN@	\
	@GLIB_LIBS@	\
@STRIP_END@

noinst_LTLIBRARIES = libfo-libfo.la libfo-fodoc.la

if ENABLE_GP
GP_headers = fo-doc-gp.h fo-doc-gp-private.h fo-layout-gp.h fo-layout-gp-private.h
GP_sources = $(GP_headers) fo-doc-gp.c fo-layout-gp.c
else
GP_headers=
GP_sources=
endif

if ENABLE_CAIRO
CAIRO_headers = fo-doc-cairo.h fo-doc-cairo-private.h fo-layout-cairo.h fo-layout-cairo-private.h
CAIRO_sources = $(CAIRO_headers) fo-doc-cairo.c fo-layout-cairo.c
else
CAIRO_headers=
CAIRO_sources=
endif

libfo_headers =			\
	fo-utils.h		\
	fo-font-desc.h		\
	fo-font-desc-private.h	\
	fo-layout.h		\
	fo-layout-private.h	\
	fo-libfo.h		\
	fo-libfo-basic.h	\
	fo-libfo-context.h	\
	fo-xml-doc-private.h	\
	fo-xml-doc.h		\
	fo-xml-node-private.h	\
	fo-xml-node.h		\
	fo-xsl-formatter.h	\
	fo-xsl-formatter.c	\
	fo-xslt-transformer.h	\
	libfo-compat.h

fodoc_headers =			\
	$(CAIRO_headers)	\
	$(GP_headers)		\
	fo-doc.h		\
	fo-doc-private.h

libfoincludedir = $(includedir)/libfo-0.5/libfo

libfoinclude_HEADERS = \
	$(fodoc_headers)	\
	$(libfo_headers)

libfo_libfo_la_SOURCES =	\
	$(libfo_headers)	\
	fo-font-desc.c		\
	fo-layout.c		\
	fo-libfo-basic.c	\
	fo-libfo-context.c	\
	fo-xml-doc.c		\
	fo-xml-node.c		\
	fo-xslt-transformer.c	\
	libfo-compat.c		\
	libfo-pango.c		\
	libfo-pango.h

libfo_fodoc_la_SOURCES =	\
	$(CAIRO_sources)	\
	$(GP_sources)		\
	$(fodoc_headers)	\
	fo-doc.c		\
	fo-doc-commands.h

libfo_fodoc_la_CFLAGS = $(PANGOXSL_CFLAGS) $(PANGO_CFLAGS) $(GNOMEPRINT_CFLAGS) $(GDKPIXBUF_CFLAGS)
libfo_fodoc_la_LIBADD = $(PANGOXSL_LIBS) $(PANGO_LIBS) $(GNOMEPRINT_LIBS) $(GDKPIXBUF_LIBS)

libfo-compat.c: s-libfo-compat-c
	@true
s-libfo-compat-c: ../libfo-compat.xsl libfo-compat.c.tmpl ../tools/insert-file-as-string.pl
	$(PERL) ../tools/insert-file-as-string.pl --file ../libfo-compat.xsl libfo-compat.c.tmpl > libfo-compat.c \
	&& echo timestamp > $(@F)

EXTRA_DIST = \
	libfo-compat.c.tmpl

CLEANFILES =			\
	libfo-compat.c		\
	s-libfo-compat-c
