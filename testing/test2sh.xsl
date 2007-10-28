<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff-testing -->
<!-- test2sh.xsl -->
<!-- Generate 'test.sh' files for each test suite referred to from
     $testsuites. -->
<!-- Process with xsltproc, e.g.:
        xsltproc -\-novalid test2sh.xsl test2sh.xsl
-->

<!-- Copyright (C) 2001, 2004 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon"
                version="1.0">

  <xsl:import href="config.xsl"/>
  <xsl:import href="common.xsl"/>
  
  <xsl:output method="text" omit-xml-declaration="yes"/>

  <xsl:strip-space elements="*"/>

  <xsl:param name="debug" select="false()"/>

  <!-- Use an unlikely character as indication of unsubstituted
       format string.   U+FFFD is REPLACEMENT CHARACTER. -->
  <xsl:variable name="unsubstituted-indicator">&#xFFFD;</xsl:variable>

  <xsl:variable name="testsuite-hrefs"
    select="document($TESTSUITES)/testsuites/testsuite/@href"/>

  <xsl:variable name="testsuites-dirname">
    <xsl:call-template name="dirname">
      <xsl:with-param name="string" select="$TESTSUITES"/>
    </xsl:call-template>
  </xsl:variable>

  <xsl:template match="/">
    <xsl:apply-templates select="$testsuite-hrefs"/>
  </xsl:template>

  <xsl:template match="@href">
    <xsl:variable name="href-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="."/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="use-pwd">
      <xsl:call-template name="basename">
        <xsl:with-param name="string" select="$href-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="use-testsuites-dirname">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="'..'"/>
        <xsl:with-param name="dirname2" select="$testsuites-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="use-default-stylesheet">
      <xsl:if test="$DEFAULT_STYLESHEET">
        <xsl:call-template name="merge-dirnames">
          <xsl:with-param name="dirname1" select="'..'"/>
          <xsl:with-param name="dirname2" select="$DEFAULT_STYLESHEET"/>
        </xsl:call-template>
      </xsl:if>
    </xsl:variable>

    <xsl:variable name="use-xsl-processor">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="'..'"/>
        <xsl:with-param name="dirname2" select="$XSL_PROCESSOR"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="data-dir">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="$use-testsuites-dirname"/>
        <xsl:with-param name="dirname2" select="$href-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:if test="$DEBUG">
      <xsl:message>
        <xsl:text>pwd: '</xsl:text>
        <xsl:value-of select="$use-pwd"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
      <xsl:message>
        <xsl:text>testsuites dirname: '</xsl:text>
        <xsl:value-of select="$use-testsuites-dirname"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
      <xsl:message>
        <xsl:text>default-stylesheet: '</xsl:text>
        <xsl:value-of select="$use-default-stylesheet"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
      <xsl:message>
        <xsl:text>xsl-processor: '</xsl:text>
        <xsl:value-of select="$use-xsl-processor"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
      <xsl:message>
        <xsl:text>data-dir: '</xsl:text>
        <xsl:value-of select="$data-dir"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
      <xsl:message><xsl:text>&#10;</xsl:text></xsl:message>
    </xsl:if>

    <!--
    <xsl:text>cd </xsl:text>
    <xsl:value-of select="$use-pwd"/>
    <xsl:text>&#10;</xsl:text>
    -->
    <xsl:message>Creating ./<xsl:value-of select="$use-pwd"/>/test.sh</xsl:message>
    <saxon:output href="./{$use-pwd}/test.sh"
      method="text">
      <xsl:text>#!/bin/sh&#10;</xsl:text>
      <xsl:text>date&#10;</xsl:text>
      <xsl:text>rm -f /var/tmp/magic*&#10;</xsl:text>
      <xsl:text>rm -f *.pdf&#10;</xsl:text>

      <xsl:for-each select="document(.)/testsuite/testcases/test |
        document(.)/testsuite/testcases/testcases/test |
        document(.)/testsuite/testcases/testcases/testcases/test">

        <xsl:variable name="input-xml">
          <xsl:call-template name="merge-dirnames">
            <xsl:with-param name="dirname1" select="$data-dir"/>
            <xsl:with-param name="dirname2">
              <xsl:choose>
                <xsl:when test="ancestor::*/@base">
                  <xsl:for-each select="ancestor::*/@base">
                    <xsl:value-of select="."/>
                    <xsl:text>/</xsl:text>
                  </xsl:for-each>
                  <xsl:value-of select="@xml"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="@xml"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:variable>
        
        <xsl:variable name="input-xsl">
          <xsl:choose>
            <xsl:when test="@xsl">
              <xsl:choose>
                <xsl:when test="substring(@xsl, 1, 5) = 'http:'">
                  <xsl:value-of select="@xsl"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:call-template name="merge-dirnames">
                    <xsl:with-param name="dirname1" select="$data-dir"/>
                    <xsl:with-param name="dirname2">
                      <xsl:call-template name="merge-dirnames">
                        <xsl:with-param name="dirname1">
                          <xsl:for-each select="ancestor::*/@base">
                            <xsl:value-of select="."/>
                            <xsl:text>/</xsl:text>
                          </xsl:for-each>
                        </xsl:with-param>
                        <xsl:with-param name="dirname2" select="@xsl"/>
                      </xsl:call-template>
                    </xsl:with-param>
                  </xsl:call-template>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
              <xsl:if test="$use-default-stylesheet">
                <xsl:value-of select="$use-default-stylesheet"/>
              </xsl:if>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:variable>

        <!-- Command line to run the XSL processor -->
        <xsl:variable name="command-line">
          <xsl:call-template name="select-command-line">
            <xsl:with-param name="command-patterns" select="$COMMAND_PATTERNS"/>
            <!-- Used in error messages only. -->
            <xsl:with-param name="original-command-patterns" select="$COMMAND_PATTERNS"/>
            <xsl:with-param name="xsl-processor" select="$use-xsl-processor"/>
            <xsl:with-param name="xsl-processor-flags" select="$XSL_PROCESSOR_FLAGS"/>
            <xsl:with-param name="output" select="concat(@id, '.pdf')"/>
            <xsl:with-param name="input" select="$input-xml"/>
            <xsl:with-param name="stylesheet" select="$input-xsl"/>
          </xsl:call-template>
        </xsl:variable>

        <!-- Output shell command to echo $command-line. -->
        <xsl:text>echo </xsl:text>
        <xsl:value-of select="$command-line"/>
        <xsl:text> > </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.log</xsl:text>
        <xsl:text>&#10;</xsl:text>
        <!-- Output the actual $command-line to be executed. -->
        <xsl:value-of select="$command-line"/>
        <xsl:text> 2>> </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.log</xsl:text>
        <xsl:if test="$DEBUG">
          <xsl:text> #</xsl:text>
          <xsl:value-of select="@id"/>
        </xsl:if>
        <xsl:text>&#10;</xsl:text>

      </xsl:for-each>

      <!-- Munge the creation date of the PDFs to a constant date so
           diffs can match -->
      <xsl:text>#perl -pi -e 's/^\/CreationDate \(D:\d+\)/\/CreationDate \(D:20041007013806\)/' *.pdf&#10;</xsl:text>
      <!-- Remove the process IDs from error messages in log files so
           diffs can match -->
      <xsl:text>perl -pi -e 's/^\(process:[0-9]+\): //' *.log&#10;</xsl:text>

      <xsl:text>for FILE in `ls *.log`; do&#10;</xsl:text>
      <xsl:text>diff -N ref/$FILE $FILE > diff/$FILE&#10;</xsl:text>
      <xsl:text>done&#10;</xsl:text>
      
      <!-- Remove a core file if there is one -->
      <xsl:text>rm -f core&#10;</xsl:text>
      <xsl:text>date&#10;</xsl:text>
    </saxon:output>
  </xsl:template>

</xsl:stylesheet>
