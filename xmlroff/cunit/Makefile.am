## Process this file with automake to create Makefile.in.

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\" \
	$(CUNIT_CFLAGS)

bin_PROGRAMS = test

test_SOURCES = \
	test.c \
	test-fo-expr-eval.c\
	test-fo-expr-eval.h

#test_LDFLAGS = -static

test_LDADD = \
	$(CUNIT_LIBS)		\
	../libfo/libfo-0.5.la