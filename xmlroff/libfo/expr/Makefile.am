## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(GLIB_CFLAGS)	\
	-I..

LDADDS = @STRIP_BEGIN@	\
	@GLIB_LIBS@	\
@STRIP_END@

noinst_LTLIBRARIES = libfo-expr.la

libfo_expr_la_SOURCES =	\
	fo-expr-context.c	\
	fo-expr-context-private.h	\
	fo-expr-env.c	\
	fo-expr-eval.c	\
	fo-expr-eval.h	\
	fo-expr-func.c	\
	fo-expr-func-private.h	\
	fo-xml-char-util.c	\
	fo-xml-char-util.h
