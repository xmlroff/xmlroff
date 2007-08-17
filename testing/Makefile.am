# xmlroff test results makefile
# $Id: Makefile.am,v 1.13 2007/04/09 20:16:54 menteith Exp $

TESTSUITES=testsuites.xml
XSLTPROC=xsltproc

REPORT_HTML = index.html
REPORT_PARAM =
TESTING_PARAM=config.xsl

RESULTS_PACKAGE=xmlroff-testresults

EXTRA_DIST = \
	cairo-pdf-results.xml		\
	cairo-ps-results.xml		\
	common.xsl			\
	coverage.xsl			\
	dotests.pl			\
	h2pl.pl				\
	h2xsl.pl			\
	identity.xsl			\
	make-success-report.sh		\
	png+ref2stereo.pl		\
	regenerate-testsuccess.pl	\
	test2sh.xsl			\
	testing.conf.in			\
	testsuccess.pl			\
	testsuccess.xsl			\
	testsuites.xml			\
	testsuites2testresults.xsl	\
	update-result.xsl		\
	update-results.pl		\
	xmlroff-testing.conf		\
	xmlroff-testing-cairo-pdf.conf	\
	xmlroff-testing-cairo-ps.conf

noinst_HEADERS = \
	$(REPORT_HTML) \
	config.xsl \
	config.pl

config.xsl:	config.h h2xsl.pl
	perl h2xsl.pl config.h

config.pl:	config.h h2pl.pl
	perl h2pl.pl config.h

test2sh.stamp: test2sh.xsl $(TESTSUITES) $(TESTING_PARAM) common.xsl config.xsl
	xsltproc --novalid test2sh.xsl test2sh.xsl
	touch $@

dotests.stamp: dotests.pl $(TESTING_PARAM) $(XSL_PROCESSOR) test2sh.stamp
	perl dotests.pl .
	touch $@

png+ref2stereo.stamp: png+ref2stereo.pl dotests.stamp
	perl png+ref2stereo.pl .
	touch $@

#
# Generate the initial test results file if it doesn't already exist.
#
$(TEST_RESULTS):
	$(XSLTPROC) --novalid testsuites2testresults.xsl $(TESTSUITES) > \
		$(TEST_RESULTS)

testresults.stamp $(TESTSUCCESS): testsuccess.pl $(TESTING_PARAM) $(XSL_PROCESSOR) png+ref2stereo.stamp $(TEST_RESULTS)
	perl testsuccess.pl . > $(TESTSUCCESS)
	touch $@

$(REPORT_HTML):	testsuccess.xsl $(TESTSUCCESS) $(TESTING_PARAM) testresults.stamp config.pl
	$(XSLTPROC) -o $@ --novalid \
	--stringparam date "`date`" $(REPORT_PARAM) \
	testsuccess.xsl testsuccess.xsl
	chmod 666 $@

clean:
	rm */*.png */*.pdf */*.log

#find . \( -name diff -o -name ref -prune  -exec true \; -o \( -name \*.png -o -name \*.log -o -name \*.pdf \) -exec ls {} \; \)

dist1:	$(FILES)
	-rm -rf $(PACKAGE)-$(VERSION)
	mkdir $(PACKAGE)-$(VERSION)
	(tar cf - $(FILES) | (cd $(PACKAGE)-$(VERSION) ; tar xf -))
	(tar cf - $(PACKAGE)-$(VERSION) | gzip -c > $(PACKAGE)-$(VERSION).tar.gz)
	-rm -rf $(PACKAGE)-$(VERSION)

install-data-local:
	-rm -rf $(RESULTS_PACKAGE)-$(VERSION)
	mkdir $(RESULTS_PACKAGE)-$(VERSION)
	(tar cf - `find . -name \*.html -o -name \*.png -o -name \*.log -o -name \*.pdf` | (cd $(RESULTS_PACKAGE)-$(VERSION) ; tar xf -))
	(tar cf - $(RESULTS_PACKAGE)-$(VERSION) | gzip -c > $(RESULTS_PACKAGE)-$(VERSION).tar.gz)
	-rm -rf $(RESULTS_PACKAGE)-$(VERSION)

#
# Reliably "tag" the Subversion repository to mark the current release.
#
svn-tag:
	-svn mkdir -m"Tag for modules of xmlroff $(VERSION)." \
	   svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)
	svn cp -m"Tagging xmlroff-testing $(VERSION)." \
	   svn://svn.xmlroff.org/trunk/testing \
	   svn://svn.xmlroff.org/tags/xmlroff-$(VERSION)/testing
