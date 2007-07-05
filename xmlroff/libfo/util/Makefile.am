## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(GLIB_CFLAGS)		\
	$(LIBXSLT_CFLAGS)	\
	$(GDKPIXBUF_CFLAGS)	\
	-I..

LDADDS = @STRIP_BEGIN@	\
	@GLIB_LIBS@	\
@STRIP_END@

noinst_LTLIBRARIES = libfo-util.la

libfo_util_includedir = $(includedir)/libfo-0.5/util

libfo_util_include_HEADERS = \
	fo-hash-table.h		\
	fo-image.h		\
	fo-pixbuf.h

libfo_util_la_SOURCES =	\
	$(libfo_util_include_HEADERS) \
	fo-hash-table.c	\
	fo-image.c	\
	fo-pixbuf.c

libfo_util_la_LIBADD = $(GDKPIXBUF_LIBS) $(LIBXSLT_LIBS)
