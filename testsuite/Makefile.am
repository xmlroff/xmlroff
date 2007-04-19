# xmlroff testsuite makefile
# $Id: Makefile.am,v 1.1 2005/01/28 10:51:52 tonygraham Exp $

EXTRA_DIST = \
	testsuite.xml

dist-hook:
	(tar cf - `find . -name \*.fo` | (cd $(distdir) ; tar xf -))

