XSLTPROC = xsltproc
XSLSPEC = xslspec.xml

# The $(CODEGENINFO) file will be opened by the XSLT processor.
# When $(CODEGENINFO) is a relative URL (e.g., "codegen-info.xml"), it is
# interpreted relative to the stylesheet.  Consequently, when the dump info
# file is in the same directory as the stylesheet, do not change
# $(CODEGENINFO) just because processing is happening in a different
# directory to the stylesheet.
CODEGENINFO = codegen-info.xml
CODEGENINFOPARAM = --stringparam codegen-info $(CODEGENINFO)

DUMPFLAGS=

CONVERSIONLIB = conversion-lib.xsl
FOALLPROPERTYHDUMP = fo-all-property-h-dump.xsl
FOCONTEXTDUMP = fo-context-dump.xsl
FOOBJECTDUMP = fo-object-dump.xsl
FOPROPERTYOBJECTDUMP = fo-property-object-dump.xsl
FOPROPERTYEVALDUMP = fo-property-eval-dump.xsl
PROPERTYENTITYDECL = xmlroff-property-decl-dump.xsl
PROPERTYENTITYREF = xmlroff-property-ref-dump.xsl

.PHONY:	all

all:	fo-context-dump fo-object-dump fo-property-object-dump \
	fo-property-eval-dump fo-all-property-h-dump property-entity-decl-dump \
	property-entity-ref-dump

fo-all-property-h-dump:	$(XSLSPEC) $(FOALLPROPERTYHDUMP) \
		$(CONVERSIONLIB) $(CODEGENINFO)
	cd property ; $(XSLTPROC) \
	$(DUMPFLAGS) \
        $(CODEGENINFOPARAM) ../$(FOALLPROPERTYHDUMP) ../$(XSLSPEC)

fo-context-dump: $(XSLSPEC) $(FOCONTEXTDUMP) $(CODEGENINFO)
	$(XSLTPROC) $(CODEGENINFOPARAM) \
	$(DUMPFLAGS) \
        $(FOCONTEXTDUMP) $(XSLSPEC)

fo-object-dump: $(XSLSPEC) $(FOOBJECTDUMP) $(CONVERSIONLIB) $(CODEGENINFO)
	-mkdir fo
	cd fo; $(XSLTPROC) \
	$(DUMPFLAGS) \
        $(CODEGENINFOPARAM) ../$(FOOBJECTDUMP) ../$(XSLSPEC)

fo-property-object-dump: $(XSLSPEC) $(FOPROPERTYOBJECTDUMP) $(CONVERSIONLIB) $(CODEGENINFO)
	-mkdir property
	cd property ; $(XSLTPROC) \
	$(DUMPFLAGS) \
	$(CODEGENINFOPARAM) \
        ../$(FOPROPERTYOBJECTDUMP) ../$(XSLSPEC)

fo-property-eval-dump: $(XSLSPEC) $(FOPROPERTYEVALDUMP) $(CONVERSIONLIB) $(CODEGENINFO)
	$(XSLTPROC) \
	$(DUMPFLAGS) \
	$(CODEGENINFOPARAM) \
        $(FOPROPERTYEVALDUMP) $(XSLSPEC)

property-entity-decl-dump:	$(XSLSPEC) $(PROPERTYENTITYDECL) $(CODEGENINFO)
	$(XSLTPROC) \
		-o xmlroff-property-decl.ent \
		$(DUMPFLAGS) \
	       	$(CODEGENINFOPARAM) $(PROPERTYENTITYDECL) $(XSLSPEC)

property-entity-ref-dump:	$(XSLSPEC) $(PROPERTYENTITYREF) $(CODEGENINFO)
	$(XSLTPROC) \
		-o xmlroff-property-ref.ent \
		$(DUMPFLAGS) \
	       	$(CODEGENINFOPARAM) $(PROPERTYENTITYREF) $(XSLSPEC)

CLEANFILES = \
	*.c *.c~ *.h *.h~ *.txt *.txt~ *.mk *.mk~ *.ent *.ent~ fo/* property/*

EXTRA_DIST = \
	conversion-lib.xsl	\
	codegen-info.dtd	\
	codegen-info.xml	\
	fo-all-property-h-dump.xsl	\
	fo-context-dump.xsl	\
	fo-object-dump.xsl	\
	fo-property-eval-dump.xsl	\
	fo-property-object-dump.xsl	\
	xmlroff-property-decl-dump.xsl	\
	xmlroff-property-ref-dump.xsl \
	xslspec.xml

dist-hook:
	mkdir $(distdir)/fo $(distdir)/property
