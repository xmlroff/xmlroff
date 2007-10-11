# xmlroff testsuite makefile
# $Id: Makefile.am,v 1.1 2005/01/28 10:51:52 tonygraham Exp $

EXTRA_DIST = \
	testsuite.xml

dist-hook:
	(tar cf - `find . -name \*.fo` | (cd $(distdir) ; tar xf -))
	(tar cf - `find . -name \*.pdf` | (cd $(distdir) ; tar xf -))

svn-tag:
	-svn mkdir -m"Tag for modules of xmlroff $(VERSION)." \
	   svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)
	svn cp -m"Tagging xmlroff-testsuite $(VERSION)." \
	   svn://svn.xmlroff.org/trunk/testsuite \
	   svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)/testsuite
