## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(GLIB_CFLAGS)		\
	-I..

LDADDS = @STRIP_BEGIN@	\
	@GLIB_LIBS@	\
@STRIP_END@

noinst_LTLIBRARIES = libfo-datatype.la

libfo_datatype_includedir = $(includedir)/libfo-0.6/libfo/datatype

libfo_datatype_include_HEADERS = \
	fo-datatype.h		\
	fo-enum.h

libfo_datatype_la_SOURCES =	\
	$(libfo_datatype_include_HEADERS) \
	fo-all-datatype.h	\
	fo-datatype.c		\
	fo-datatype-private.h	\
	fo-unknown.c		\
	fo-unknown.h		\
	fo-expression.c		\
	fo-expression.h		\
	fo-boolean.c		\
	fo-boolean.h		\
	fo-char.c		\
	fo-char.h		\
	fo-color.c		\
	fo-color.h		\
	fo-enum.c		\
	fo-error.c		\
	fo-error.h		\
	fo-id.c			\
	fo-id.h			\
	fo-integer.c		\
	fo-integer.h		\
	fo-keep.c		\
	fo-keep.h		\
	fo-length-conditional.c \
	fo-length-conditional.h \
	fo-length-range.c	\
	fo-length-range.h	\
	fo-length-range-private.h	\
	fo-length-bp-ip-d.c	\
	fo-length-bp-ip-d.h	\
	fo-length.c		\
	fo-length.h		\
	fo-name.c		\
	fo-name.h		\
	fo-number.c		\
	fo-number.h		\
	fo-numeric.c		\
	fo-numeric.h		\
	fo-numeric-private.h	\
	fo-pcw.c		\
	fo-pcw.h		\
	fo-percentage.c		\
	fo-percentage.h		\
	fo-space.c		\
	fo-space.h		\
	fo-string.c		\
	fo-string.h		\
	fo-tblr.c		\
	fo-tblr.h		\
	fo-wsc.c		\
	fo-wsc.h		\
	fo-uri-specification.c	\
	fo-uri-specification.h
