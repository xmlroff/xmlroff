# xmlroff Makefile.am

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\"	\
	$(LIBXSLT_CFLAGS)	\
	$(GLIB_CFLAGS)

bin_PROGRAMS = \
	xmlroff

#-release $(VERSION)


xmlroff_SOURCES = \
	xmlroff.c

xmlroff_LDFLAGS = -static

xmlroff_LDADD = \
	../libfo/libfo-0.6.la \
	$(PANGO_LIBS) \
	$(GNOMEPRINT_LIBS) \
	$(LIBXSLT_LIBS) \
	$(FREETYPE_LIBS)
