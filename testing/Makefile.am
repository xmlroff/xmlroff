# xmlroff test results makefile

TESTSUITES=@TESTSUITES@
XSLTPROC=xsltproc

REPORT_HTML = index.html
STYLE_CSS = style.css
REPORT_PARAM =
TESTING_PARAM=config.xsl

RESULTS_PACKAGE=$(PROJECT_NAME)-$(BASENAME)

EXTRA_DIST = \
	$(STYLE_CSS)			\
	bottom-left.png			\
	bottom-right.png		\
	cairo-pdf-results.xml		\
	cairo-ps-results.xml		\
	common.xsl			\
	coverage.xsl			\
	docbook-testdocs.conf		\
	dotests.pl			\
	h2pl.pl				\
	h2xsl.pl			\
	identity.xsl			\
	make-fop-testsuite.pl		\
	make-success-report.sh		\
	make-fop-testsuite.pl		\
	make-testsuite.pl		\
	png+ref2stereo.pl		\
	regenerate-testsuccess.pl	\
	results-doc.xsl			\
	test2makefile.xsl		\
	test2sh.xsl			\
	testing.conf.in			\
	testing-server.pl		\
	testsuccess.pl			\
	testsuccess.xsl			\
	testsuites.xml			\
	testsuites2testresults.xsl	\
	top-left.png			\
	top-right.png			\
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
@TEST_RESULTS@:
	$(XSLTPROC) --novalid testsuites2testresults.xsl $(TESTSUITES) > \
		@TEST_RESULTS@

testresults.stamp $(TESTSUCCESS): testsuccess.pl $(TESTING_PARAM) $(XSL_PROCESSOR) png+ref2stereo.stamp @TEST_RESULTS@
	perl testsuccess.pl . > $(TESTSUCCESS)
	touch $@

$(REPORT_HTML):	testsuccess.xsl results-doc.xsl $(TESTSUCCESS) $(TESTING_PARAM) testresults.stamp config.pl $(STYLE_CSS)
	$(XSLTPROC) -o $@ --novalid \
	--stringparam date "`date`" $(REPORT_PARAM) \
	testsuccess.xsl @TEST_RESULTS@
	chmod 666 $@

clean:
	rm */*.png */*.pdf */*.log

#find . \( -name diff -o -name ref -prune  -exec true \; -o \( -name \*.png -o -name \*.log -o -name \*.pdf \) -exec ls {} \; \)

# Make a bundle of the results.
# Use 'static' version of the reports and do not
# include reference or stereo versions of the results.
dist-results:
	rm $(REPORT_HTML)
	$(MAKE) REPORT_PARAM='--param FORM "false()" --param REFERENCE "false()"' $(REPORT_HTML)
	-rm -rf $(RESULTS_PACKAGE)-$(VERSION)
	mkdir $(RESULTS_PACKAGE)-$(VERSION)
	cp $(TEST_RESULTS) $(RESULTS_PACKAGE)-$(VERSION)/testresults.xml
	(tar cf - `find . -maxdepth 2 -name \*.html` | (cd $(RESULTS_PACKAGE)-$(VERSION) ; tar xf -))
	(tar cf - `find . -maxdepth 2 -name \*.png` | (cd $(RESULTS_PACKAGE)-$(VERSION) ; tar xf -))
	(tar cf - `find . -maxdepth 2 -name \*.log` | (cd $(RESULTS_PACKAGE)-$(VERSION) ; tar xf -))
	(tar cf - `find . -maxdepth 2 -name \*.pdf` | (cd $(RESULTS_PACKAGE)-$(VERSION) ; tar xf -))
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
