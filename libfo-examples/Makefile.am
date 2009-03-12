# libfo-examples Makefile.am

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo-examples\"	\
	$(LIBFO_CFLAGS)

LDADD = \
	$(LIBFO_LIBS)

ADJUST_MODULES=gmodule-area-tree.la

noinst_PROGRAMS = \
	xmlroff-basic	\
	xmlroff-init2	\
	xmlroff-gmodule	\
	xmlroff-gtktree	\
	xmlroff-libfo	\
	xmlroff-text-tree	\
	xmlroff-text-tree2

pkglib_LTLIBRARIES = $(ADJUST_MODULES)

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

xmlroff_gtktree_SOURCES = \
	xmlroff-gtktree.c

xmlroff_gtktree_CFLAGS = \
	$(INCLUDES) \
	$(GTK_CFLAGS)

xmlroff_gtktree_LDADD = \
	$(LDADD) \
	$(GTK_LIBS)

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

FORCE:

ChangeLog:	FORCE
if ENABLE_SVN2CL
	svn2cl --include-actions --authors=AUTHORS --group-by-day --separate-daylogs --include-rev --ignore-message-starting='#' --revision HEAD:$(CHANGELOG_OLDEST)
endif

svn-tag:
	-svn mkdir -m"Tag for modules of xmlroff $(VERSION)." \
	  svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)
	-svn cp -m"Tagging libfo-examples $(VERSION)." \
	  svn://svn.xmlroff.org/trunk/libfo-examples \
	  svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)/libfo-examples
