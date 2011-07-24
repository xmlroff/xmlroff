## libfo
## Process this file with automake to produce Makefile.in

SUBDIRS = area fo datatype property expr util .

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(LIBXSLT_CFLAGS)	\
	$(LIBRSVG_CFLAGS)	\
	$(PANGO_CFLAGS)

LDADDS = @STRIP_BEGIN@	\
	@GLIB_LIBS@	\
@STRIP_END@

BUILT_SOURCES = libfo-features.h

noinst_LTLIBRARIES = libfo-libfo.la libfo-fodoc.la

lib_LTLIBRARIES = libfo-0.6.la

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
	fo-libfo-module.h	\
	fo-libfo-module-private.h	\
	fo-xml-doc-private.h	\
	fo-xml-doc.h		\
	fo-xml-node-private.h	\
	fo-xml-node.h		\
	fo-xsl-formatter.h	\
	fo-xslt-transformer.h	\
	libfo-compat.h

fodoc_headers =			\
	$(CAIRO_headers)	\
	$(GP_headers)		\
	fo-doc.h		\
	fo-doc-private.h

libfoinclude_HEADERS = \
	$(fodoc_headers)        \
	$(libfo_headers)

libfoincludedir = $(includedir)/libfo-0.6/libfo

libfo_libfo_la_SOURCES =	\
	$(libfo_headers)	\
	fo-font-desc.c		\
	fo-layout.c		\
	fo-libfo-basic.c	\
	fo-libfo-context.c	\
	fo-libfo-module.c	\
	fo-xml-doc.c		\
	fo-xml-node.c		\
	fo-xslt-transformer.c	\
	fo-xsl-formatter.c	\
	libfo-compat.c		\
	libfo-pango.c		\
	libfo-pango.h

libfo_fodoc_la_SOURCES =	\
	$(CAIRO_sources)	\
	$(GP_sources)		\
	$(fodoc_headers)	\
	fo-doc.c		\
	fo-doc-commands.h

libfo_fodoc_la_CFLAGS = $(PANGO_CFLAGS) $(GNOMEPRINT_CFLAGS) $(GDKPIXBUF_CFLAGS)
libfo_fodoc_la_LIBADD = $(PANGO_LIBS) $(GNOMEPRINT_LIBS) $(GDKPIXBUF_LIBS)

fo_context_cfiles= \
	fo-context.c		\
	fo-context-private.h	\
	fo-context-util.c	\
	fo-context-util.h

fo_base_cfiles = \
	fo-object.c		\
	fo-node.c		\
	fo-node-private.h

libfo_0_6_la_LDFLAGS = \
	-version-info $(LT_VERSION_INFO)	\
	$(no_undefined)

libfo_0_6_includedir = $(includedir)/libfo-0.6/libfo

libfo_0_6_include_HEADERS = \
	fo-object.h		\
	fo-node.h		\
	fo-context.h		\
	libfo-features.h	\
	libfo-version.h

libfo_0_6_la_SOURCES = \
	$(libfo_0_6_include_HEADERS) \
	$(fo_base_cfiles)	\
	$(fo_context_cfiles)	\
	area-to-pdf.c		\
	area-to-pdf.h		\
	libfo-version.c

libfo_0_6_la_LIBADD = \
	util/libfo-util.la		\
	area/libfo-area.la		\
	expr/libfo-expr.la		\
	fo/libfo-fo.la			\
	datatype/libfo-datatype.la	\
	property/libfo-property.la	\
	property/libfo-text-property.la	\
	libfo-libfo.la		\
	libfo-fodoc.la		\
	$(LIBRSVG_LIBS)		\
	$(PANGO_LIBS)			\
	$(GNOMEPRINT_LIBS) 		\
	$(LIBXSLT_LIBS)			\
	$(FREETYPE_LIBS)

libfo-features.h:
	cd $(top_builddir) && ./config.status libfo/libfo-features.h

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
