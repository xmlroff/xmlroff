# libfo and xmlroff Makefile.am

if ENABLE_CUNIT
CUNIT_DIRS = cunit
endif

SUBDIRS = libfo xmlroff . examples docs $(CUNIT_DIRS)

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

INCLUDES = \
	-DG_LOG_DOMAIN=\"libfo\"	\
	$(LIBXSLT_CFLAGS)	\
	$(GLIB_CFLAGS)		\
	-Ilibfo


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libfo-0.5.pc

xmldir = $(datadir)/xml/libfo-@VERSION@
xml_DATA = \
	catalog.xml		\
	libfo-compat.xsl

EXTRA_DIST = \
	catalog.xml.in		\
	libfo-compat.xsl	\
	xmlroff.fo		\
	xmlroff.spec		\
	xmlroff.spec.in		\
	tools/insert-file-as-string.pl

srpm:
	rpmbuild -ts --nodeps $(PACKAGE)-$(VERSION).tar.gz

svn-tag:
	-svn mkdir -m"Tagging xmlroff $(VERSION)." svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)
	-svn cp -m"Tagging xmlroff $(VERSION)." svn://svn.xmlroff.org/trunk/xmlroff svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)/xmlroff
