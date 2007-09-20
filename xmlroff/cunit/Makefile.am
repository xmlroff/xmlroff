## Process this file with automake to create Makefile.in.

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(CUNIT_CFLAGS)

if ENABLE_CUNIT
  noinst_PROGRAMS = test
endif

test_SOURCES = \
	test.c \
	test-fo-color.c	\
	test-fo-color.h	\
	test-fo-expr-eval.c	\
	test-fo-expr-eval.h	\
	test-fo-length-range.c	\
	test-fo-length-range.h

#test_LDFLAGS = -static

test_LDADD = \
	$(CUNIT_LIBS)		\
	../libfo/libfo-0.5.la