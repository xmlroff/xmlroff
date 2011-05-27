<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff -->
<!-- testsuites2testresults.xsl -->
<!-- Generate 'testresults.xml' file from 'testsuites.xml' file. -->
<!-- Gets configuration from 'config.xsl'. -->
<!-- Example usage:
     xsltproc -\-novalid testsuites2testresults.xsl testsuites.xml > testresults.xml
-->

<!-- Copyright (C) 2011 Mentea -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon"
                version="1.0">

  <xsl:import href="config.xsl"/>
  <xsl:import href="common.xsl"/>
  <xsl:import href="results-doc.xsl"/>

  <xsl:output method="html"/>
	<xsl:param name="date" select="/testsuite/@date" />

	<xsl:template match="testresult">
		<xsl:call-template name="results-html">
			<xsl:with-param name="pdf" select="following-sibling::pdf"/>
			<xsl:with-param name="results" select="."/>
			<xsl:with-param name="results-top-base" select="ancestor::testcases[last()]/@base"/>
			<xsl:with-param name="id" select="@id"/>
			<xsl:with-param name="test" select="following-sibling::test"/>
			<xsl:with-param name="test-file-dirname" select="concat('../../', ancestor::testcases[last()]/@base, '/')"/>
		</xsl:call-template>
	</xsl:template>

<xsl:template match="test"/>
</xsl:stylesheet>