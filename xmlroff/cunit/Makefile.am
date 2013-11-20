## libfo CUnit tests Makefile.am
## Process this file with automake to create Makefile.in.

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(CUNIT_CFLAGS)	\
	$(PANGO_CFLAGS)

if ENABLE_CUNIT
  noinst_PROGRAMS = test
endif

test_SOURCES = \
	test.c \
	test-fo-color.c	\
	test-fo-color.h	\
	test-fo-context.c	\
	test-fo-context.h	\
	test-fo-doc.c	\
	test-fo-doc.h	\
	test-fo-expr-eval.c	\
	test-fo-expr-eval.h	\
	test-fo-length-range.c	\
	test-fo-length-range.h	\
	test-fo-libfo-context.c	\
	test-fo-libfo-context.h	\
	test-fo-libfo-module.c	\
	test-fo-libfo-module.h	\
	test-libfo-version.c	\
	test-libfo-version.h

test_LDFLAGS = -static

test_LDADD = \
	$(CUNIT_LIBS)		\
	$(PANGO_LIBS)		\
	../libfo/libfo-0.6.la	\
	-lm