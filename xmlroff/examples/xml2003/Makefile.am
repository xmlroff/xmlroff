# Makefile for XML 2003 "XSL FO Chef's Tools Exhibition" sample files
# $Id: Makefile.am,v 1.2 2004/10/20 21:35:38 tonygraham Exp $

XMLROFF=../../xmlroff
XMLROFF_FLAGS=
XSLTPROC=xsltproc
#STYLESHEET=http://xmlroff.org/release/libfo/current/libfo-compat.xsl
STYLESHEET=../../libfo-compat.xsl

%.pdf:	%.fix.fo $(XMLROFF)
	$(XMLROFF) $(XMLROFF_FLAGS) -o $@ $<

%.fix.fo:	%.fo
	$(XSLTPROC) -param verbose 'true()' -o $@ $(STYLESHEET) $<

EXTRA_DIST = \
	README		\
	Sample1.fo	\
	Sample2.zip	\
	Sample3.fo	\
	Sample4.fo.zip	\
	Sample5.fo	\
	Sample6.fo	\
	Sample7.fo.gz	\
	Sample8.zip
