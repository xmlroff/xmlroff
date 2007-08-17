<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff -->
<!-- testsuites2testresults.xsl -->
<!-- Generate 'testresults.xml' file from 'testsuites.xml' file. -->
<!-- Example usage:
     xsltproc -\-novalid testsuites2testresults.xsl testsuites.xml > testresults.xml
-->

<!-- Copyright (C) 2004 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon"
                version="1.0">

  <xsl:import href="config.xsl"/>
  <xsl:import href="common.xsl"/>

  <xsl:output method="xml" omit-xml-declaration="yes"/>
  
  <xsl:variable name="testsuite-hrefs"
    select="document($TESTSUITES)/testsuites/testsuite/@href"/>

  <xsl:variable name="testsuites-dirname">
    <xsl:call-template name="dirname">
      <xsl:with-param name="string" select="$TESTSUITES"/>
    </xsl:call-template>
  </xsl:variable>

  <!--<xsl:strip-space elements="*"/>-->
  
  <xsl:template match="/">
    <testsuite profile="xmlroff with PDF output">
      <xsl:apply-templates select="$testsuite-hrefs"/>
    </testsuite>
  </xsl:template>
  
  <xsl:template match="@href">
    <xsl:variable name="href-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="."/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="base">
      <xsl:call-template name="basename">
        <xsl:with-param name="string" select="$href-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:if test="$DEBUG">
      <xsl:message>base: '<xsl:value-of select="$base"/>'</xsl:message>
    </xsl:if>
    <xsl:apply-templates select="document(.)/testsuite">
      <xsl:with-param name="base" select="$base"/>
    </xsl:apply-templates>
    
  </xsl:template>
    
  <xsl:template match="@* | node()">
    <xsl:copy>
      <xsl:apply-templates select="@* | node()"/>
    </xsl:copy>
  </xsl:template>
  
  <xsl:template match="testsuite">
    <xsl:param name="base"/>
    <testcases>
      <xsl:if test="$base">
        <xsl:attribute name="base">
          <xsl:value-of select="$base"/>
        </xsl:attribute>
      </xsl:if>
      <xsl:apply-templates select="@* | node()"/>
    </testcases>
  </xsl:template>
  
  <xsl:template match="test">
    <testresult id="{@id}" results="{@id}.pdf" agreement="issues" specproblem="no" testproblem="no">Results not yet verified</testresult>
  </xsl:template>
  
</xsl:stylesheet>
