## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(PANGOXSL_CFLAGS)	\
	$(PANGO_CFLAGS)	\
	-I$(top_srcdir)		\
	-I$(top_srcdir)/fo	\
	-I$(top_srcdir)/property	\
	-I$(top_srcdir)/datatype

LDADDS = @STRIP_BEGIN@	\
	@GLIB_LIBS@	\
@STRIP_END@

noinst_LTLIBRARIES = libfo-area.la

libfo_area_includedir = $(includedir)/libfo-0.4/area

libfo_area_include_HEADERS = \
	fo-area.h

libfo_area_la_SOURCES =	\
	$(libfo_area_include_HEADERS)		\
	fo-area.c				\
	fo-area-private.h			\
	fo-area-area.c				\
	fo-area-area.h				\
	fo-area-area-private.h			\
	fo-area-graphic.c			\
	fo-area-graphic.h			\
	fo-area-inline.c			\
	fo-area-inline.h			\
	fo-area-inline-private.h		\
	fo-area-layout.c			\
	fo-area-layout.h			\
	fo-area-layout-private.h		\
	fo-area-list-item.c			\
	fo-area-list-item.h			\
	fo-area-normal.c			\
	fo-area-normal.h			\
	fo-area-page.c				\
	fo-area-page.h				\
	fo-area-reference.c			\
	fo-area-reference.h			\
	fo-area-reference-private.h		\
	fo-area-spanning-table-cell.c		\
	fo-area-spanning-table-cell.h		\
	fo-area-spanning-table-cell-private.h	\
	fo-area-table-body.c			\
	fo-area-table-body.h			\
	fo-area-table-cell-private.h		\
	fo-area-table-cell-proxy.c		\
	fo-area-table-cell-proxy.h		\
	fo-area-table-cell.c			\
	fo-area-table-cell.h			\
	fo-area-table-continuation-private.h	\
	fo-area-table-continuation.c		\
	fo-area-table-continuation.h		\
	fo-area-table-footer.c			\
	fo-area-table-footer.h			\
	fo-area-table-header.c			\
	fo-area-table-header.h			\
	fo-area-table-part.c			\
	fo-area-table-part.h			\
	fo-area-table-part-private.h		\
	fo-area-table-private.h			\
	fo-area-table-row.c			\
	fo-area-table-row.h			\
	fo-area-table.c				\
	fo-area-table.h				\
	fo-area-tree.c				\
	fo-area-tree.h				\
	fo-area-viewport-reference.c		\
	fo-area-viewport-reference.h		\
	fo-area-viewport-reference-private.h
