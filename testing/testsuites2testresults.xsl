<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff -->
<!-- testsuites2testresults.xsl -->
<!-- Generate 'testresults.xml' file from 'testsuites.xml' file. -->
<!-- Gets configuration from 'config.xsl'. -->
<!-- Example usage:
     xsltproc -\-novalid testsuites2testresults.xsl testsuites.xml > testresults.xml
-->

<!-- Copyright (C) 2004 Sun Microsystems -->
<!-- Copyright (C) 2007-2008 Menteith Consulting Ltd -->
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
    <xsl:call-template name="options"/>
    <testsuite profile="{$TITLE}">
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
  
  <xsl:template name="options">
    <xsl:if test="$COMMAND_PATTERNS_SETTER != 'default'">
      <xsl:call-template name="option-pi">
	<xsl:with-param name="option" select="'command-patterns'"/>
	<xsl:with-param name="value" select="$COMMAND_PATTERNS"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="$DEFAULT_STYLESHEET_SETTER != 'default'">
      <xsl:call-template name="option-pi">
	<xsl:with-param name="option" select="'default-stylesheet'"/>
	<xsl:with-param name="value" select="$DEFAULT_STYLESHEET"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="$TESTSUITES_SETTER != 'default'">
      <xsl:call-template name="option-pi">
	<xsl:with-param name="option" select="'testsuites'"/>
	<xsl:with-param name="value" select="$testsuites"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="$TRAC_SETTER != 'default'">
      <xsl:call-template name="option-pi">
	<xsl:with-param name="option" select="'trac'"/>
	<xsl:with-param name="value" select="$TRAC"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="$XSL_PROCESSOR_SETTER != 'default'">
      <xsl:call-template name="option-pi">
	<xsl:with-param name="option" select="'xsl-processor'"/>
	<xsl:with-param name="value" select="$XSL_PROCESSOR"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="$XSL_PROCESSOR_FLAGS_SETTER != 'default'">
      <xsl:call-template name="option-pi">
	<xsl:with-param name="option" select="'xsl-processor-flags'"/>
	<xsl:with-param name="value" select="$XSL_PROCESSOR_FLAGS"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

  <xsl:template name="option-pi">
    <xsl:param name="option"/>
    <xsl:param name="value"/>

    <xsl:processing-instruction
       name="xt-{$option}">
      <xsl:value-of select="$value"/>
    </xsl:processing-instruction>
  </xsl:template>

</xsl:stylesheet>
