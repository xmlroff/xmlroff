# libfo and xmlroff Makefile.am
# $Id: Makefile.am,v 1.34 2006/12/07 05:31:51 menteith Exp $

SUBDIRS = libfo xmlroff . examples docs cunit

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
