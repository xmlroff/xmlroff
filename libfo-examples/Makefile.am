# libfo-examples Makefile.am
# $Id: Makefile.am,v 1.6 2004/06/02 10:16:38 tonygraham Exp $

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo-examples\"	\
	$(LIBFO_CFLAGS)

LDADD = \
	$(LIBFO_LIBS)	\
	$(POPT_LIBS)

ADJUST_MODULES=gmodule-area-tree.la

noinst_PROGRAMS = \
	xmlroff-basic	\
	xmlroff-init2	\
	xmlroff-gmodule	\
	xmlroff-libfo	\
	xmlroff-text-tree	\
	xmlroff-text-tree2

module_LTLIBRARIES = $(ADJUST_MODULES)
moduledir = $(pkglibdir)

xmlroff_basic_SOURCES = \
	xmlroff-basic.c

xmlroff_gmodule_SOURCES = \
	xmlroff-gmodule.c

xmlroff_gmodule_CFLAGS = \
	$(INCLUDES) \
	$(GMODULE_CFLAGS)

xmlroff_gmodule_LDADD = \
	$(LDADD) \
	$(GMODULE_LIBS)

xmlroff_init2_SOURCES = \
	xmlroff-init2.c

xmlroff_libfo_SOURCES = \
	xmlroff-libfo.c

xmlroff_text_tree_SOURCES = \
	xmlroff-text-tree.c

xmlroff_text_tree_CFLAGS = \
	$(INCLUDES) \
	$(GTK_CFLAGS)

xmlroff_text_tree_LDADD = \
	$(LDADD) \
	$(GTK_LIBS)

xmlroff_text_tree2_SOURCES = \
	xmlroff-text-tree2.c

xmlroff_text_tree2_CFLAGS = \
	$(INCLUDES) \
	$(GTK_CFLAGS)

xmlroff_text_tree2_LDADD = \
	$(LDADD) \
	$(GTK_LIBS)

gmodule_area_tree_la_SOURCES = \
	gmodule-area-tree.c
gmodule_area_tree_la_CFLAGS = \
	$(INCLUDES) \
	$(GTK_CFLAGS)
gmodule_area_tree_la_LDFLAGS = \
	-export-dynamic -avoid-version -module
gmodule_area_tree_la_LIBADD = \
	$(LDADD) \
	$(GTK_LIBS)
