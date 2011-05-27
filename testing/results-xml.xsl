<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff -->
<!-- results-xml.xsl -->
<!-- Generate individual test results as XML. -->
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

	<xsl:template name="results-xml">
    <xsl:param name="pdf"/>
    <xsl:param name="results"/>
    <xsl:param name="results-top-base"
      select="($results/ancestor::*/@base)[1]"/>
    <xsl:param name="id"/>

		<xsl:processing-instruction name="xml-stylesheet"> href="../testresults.xsl" type="text/xsl" </xsl:processing-instruction>
		<xsl:for-each select="$results">
		<xsl:call-template name="testsuite">
			<xsl:with-param name="pdf" select="$pdf"/>
			<xsl:with-param name="results" select="$results/.."/>
			<xsl:with-param name="results-top-base" select="$results-top-base"/>
			<xsl:with-param name="id" select="$id"/>
		</xsl:call-template>
		</xsl:for-each>
	</xsl:template>

	<xsl:template name="testsuite">
    <xsl:param name="pdf"/>
    <xsl:param name="results"/>
    <xsl:param name="results-top-base"
      select="($results/ancestor::*/@base)[1]"/>
    <xsl:param name="id"/>

		<testsuite>
			<xsl:copy-of select="ancestor::testsuite/@*" />
			<xsl:attribute name="date">
				<xsl:value-of select="$date" />
			</xsl:attribute>

			<xsl:call-template name="testcases">
				<xsl:with-param name="testcases" select="(ancestor::testcases)" />
				<xsl:with-param name="pdf" select="$pdf"/>
				<xsl:with-param name="results" select="$results/.."/>
				<xsl:with-param name="results-top-base" select="$results-top-base"/>
				<xsl:with-param name="id" select="$id"/>
			</xsl:call-template>
		</testsuite>
	</xsl:template>

	<xsl:template name="testcases">
		<xsl:param name="testcases" />
    <xsl:param name="pdf"/>
    <xsl:param name="results"/>
    <xsl:param name="results-top-base"
      select="($results/ancestor::*/@base)[1]"/>
    <xsl:param name="id"/>

		<testcases>
			<xsl:copy-of select="$testcases[1]/@*" />

			<xsl:choose>
				<xsl:when test="count($testcases) > 1">
					<xsl:call-template name="testcases">
						<xsl:with-param name="testcases" select="$testcases[position() > 1]" />
						<xsl:with-param name="pdf" select="$pdf"/>
						<xsl:with-param name="results" select="$results/.."/>
						<xsl:with-param name="results-top-base" select="$results-top-base"/>
						<xsl:with-param name="id" select="$id"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:otherwise>
					<xsl:call-template name="testresult">
						<xsl:with-param name="pdf" select="$pdf"/>
						<xsl:with-param name="results" select="$results/.."/>
						<xsl:with-param name="results-top-base" select="$results-top-base"/>
						<xsl:with-param name="id" select="$id"/>
					</xsl:call-template>
				</xsl:otherwise>
			</xsl:choose>
		</testcases>
	</xsl:template>

	<xsl:template name="testresult">
    <xsl:param name="pdf"/>
    <xsl:param name="results"/>
    <xsl:param name="results-top-base"
      select="($results/ancestor::*/@base)[1]"/>
    <xsl:param name="id"/>
    <xsl:param name="test"
      select="$testsuite-nodes[@profile = $results-top-base/../@profile]//test[@id = $id]"/>

		<xsl:copy>
			<xsl:copy-of select="@* | node()" />
		</xsl:copy>
		<xsl:copy-of select="$pdf" />
		<xsl:copy-of select="$test" />
	</xsl:template>
</xsl:stylesheet>