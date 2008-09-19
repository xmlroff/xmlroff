<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff-testing -->
<!-- test2makefile.xsl -->
<!-- Generate 'Makefile' files for each test suite referred to from
     $testsuites. -->
<!-- Process with xsltproc, e.g.:
        xsltproc -\-novalid test2makefile.xsl test2makefile.xsl
-->

<!-- Copyright (C) 2001, 2004 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:exsl="http://exslt.org/common"
                extension-element-prefixes="exsl"
                version="1.0">

  <xsl:import href="config.xsl"/>
  <xsl:import href="common.xsl"/>

  <xsl:output method="text" omit-xml-declaration="yes"/>

  <xsl:strip-space elements="*"/>

  <xsl:param name="debug" select="false()"/>

  <!-- Use an unlikely character as indication of unsubstituted
       format string.   U+FFFD is REPLACEMENT CHARACTER. -->
  <xsl:variable name="unsubstituted-indicator">&#xFFFD;</xsl:variable>

  <!-- Each @href refers to a testsuite definition file (e.g.,
       'testsuite.xml') of a separate testsuite. -->
  <xsl:variable name="testsuite-hrefs"
    select="document($TESTSUITES)/testsuites/testsuite/@href"/>

  <!-- The directory containing the file that refers to individual
       testsuite definition files. -->
  <xsl:variable name="testsuites-dirname">
    <xsl:call-template name="dirname">
      <xsl:with-param name="string" select="$TESTSUITES"/>
    </xsl:call-template>
  </xsl:variable>

  <xsl:template match="/">
    <!-- Ignore the source tree and instead process each
         attribute that refers to a testsuite definition file. -->
    <xsl:apply-templates select="$testsuite-hrefs"/>
  </xsl:template>

  <!-- Process the attribute that refers to an individual testsuite
       definition file. -->
  <xsl:template match="@href">

    <!-- The directory containing the testsuite definition file. -->
    <xsl:variable name="href-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="."/>
      </xsl:call-template>
    </xsl:variable>

    <!-- The last component of the directory containing the
         testsuite definition file. -->
    <xsl:variable name="use-pwd">
      <xsl:call-template name="basename">
        <xsl:with-param name="string" select="$href-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- In a generated makefile, a relative path to the directory
         containing $TESTSUITES will be relative to the parent
         directory. -->
    <xsl:variable name="use-testsuites-dirname">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="'..'"/>
        <xsl:with-param name="dirname2" select="$testsuites-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- A relative path to the individual testsuite file will be
         relative to the directory containing $TESTSUITES. -->
    <xsl:variable name="data-dir">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="$use-testsuites-dirname"/>
        <xsl:with-param name="dirname2" select="$href-dirname"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- In a generated makefile, a relative path to the default
         stylesheet, if any, will be relative to the parent
         directory. -->
    <xsl:variable name="use-default-stylesheet">
      <xsl:if test="$DEFAULT_STYLESHEET">
        <xsl:call-template name="merge-dirnames">
          <xsl:with-param name="dirname1" select="'..'"/>
          <xsl:with-param name="dirname2" select="$DEFAULT_STYLESHEET"/>
        </xsl:call-template>
      </xsl:if>
    </xsl:variable>

    <!-- In a generated makefile, a relative path to the xsl processor
         will be relative to the parent directory. -->
    <xsl:variable name="use-xsl-processor">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="'..'"/>
        <xsl:with-param name="dirname2" select="$XSL_PROCESSOR"/>
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

    <xsl:message>Creating ./<xsl:value-of select="$use-pwd"/>/Makefile</xsl:message>
    <exsl:document href="./{$use-pwd}/Makefile"
      method="text">

      <xsl:variable name="tests"
        select="document(.)/testsuite/testcases/test |
        document(.)/testsuite/testcases/testcases/test |
        document(.)/testsuite/testcases/testcases/testcases/test"/>

      <xsl:text># Automatically generated file.  Do not edit.&#10;</xsl:text>

      <!-- The 'all' rule that potentially runs every test. -->
      <xsl:text>&#10;all:&#9;</xsl:text>
      <xsl:for-each select="$tests">
        <xsl:value-of select="concat(@id, '.pdf')"/>
        <xsl:text> </xsl:text>
      </xsl:for-each>
      <xsl:text>&#10;&#10;</xsl:text>

      <!-- Individual rule for each test. -->
      <xsl:for-each select="$tests">

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

        <xsl:value-of select="concat(@id, '.pdf')"/>
        <xsl:text>:&#9;</xsl:text>
        <xsl:value-of select="$input-xml"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="$input-xsl"/>
        <xsl:text> </xsl:text>
        <xsl:value-of select="$use-xsl-processor"/>
        <xsl:text>&#10;</xsl:text>
        <!-- Output shell command to echo $command-line. -->
        <xsl:text>&#9;@echo </xsl:text>
        <xsl:value-of select="$command-line"/>
        <xsl:text> > </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.log</xsl:text>
        <xsl:text>&#10;&#9;@</xsl:text>
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

      <!-- Rule to replace results in testsuite with current results -->
      <xsl:text>&#10;&#10;replace-testsuite-results:&#10;</xsl:text>
      <xsl:for-each select="$tests[@results]">

        <xsl:variable name="results">
          <xsl:call-template name="merge-dirnames">
            <xsl:with-param name="dirname1" select="$data-dir"/>
            <xsl:with-param name="dirname2">
              <xsl:choose>
                <xsl:when test="ancestor::*/@base">
                  <xsl:for-each select="ancestor::*/@base">
                    <xsl:value-of select="."/>
                    <xsl:text>/</xsl:text>
                  </xsl:for-each>
                  <xsl:value-of select="@results"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="@results"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:variable>

        <!-- Output the actual $command-line to be executed. -->
        <xsl:text>&#9;@-cp </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.pdf </xsl:text>
        <xsl:value-of select="$results"/>
        <xsl:if test="$DEBUG">
          <xsl:text> #</xsl:text>
          <xsl:value-of select="@id"/>
        </xsl:if>
        <xsl:text>&#10;</xsl:text>

      </xsl:for-each>

      <!-- Rule to seed reference with current testsuite results -->
      <xsl:text>&#10;&#10;replace-ref:&#10;</xsl:text>
      <xsl:for-each select="$tests[@results]">

        <xsl:variable name="results">
          <xsl:call-template name="merge-dirnames">
            <xsl:with-param name="dirname1" select="$data-dir"/>
            <xsl:with-param name="dirname2">
              <xsl:choose>
                <xsl:when test="ancestor::*/@base">
                  <xsl:for-each select="ancestor::*/@base">
                    <xsl:value-of select="."/>
                    <xsl:text>/</xsl:text>
                  </xsl:for-each>
                  <xsl:value-of select="@results"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="@results"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:variable>

        <!-- Output the actual $command-line to be executed. -->
        <xsl:text>&#9;@-cp </xsl:text>
        <xsl:value-of select="$results"/>
        <xsl:text> ref/</xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.pdf </xsl:text>
        <xsl:if test="$DEBUG">
          <xsl:text> #</xsl:text>
          <xsl:value-of select="@id"/>
        </xsl:if>
        <xsl:text>&#10;</xsl:text>
        <xsl:text>&#9;@-(cd ref; convert -depth 8 -type palette </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.pdf </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.%02d.png; touch </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.log)&#10;</xsl:text>

      </xsl:for-each>

      <!-- Rule to accept all current results as new reference results -->
      <xsl:text>&#10;&#10;accept-all:&#10;</xsl:text>
      <xsl:for-each select="$tests[@results]">

        <!-- Output the actual $command-line to be executed. -->
        <xsl:text>&#9;@-cp </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.pdf </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.*.png </xsl:text>
        <xsl:value-of select="@id"/>
        <xsl:text>.log ref</xsl:text>
        <xsl:if test="$DEBUG">
          <xsl:text> #</xsl:text>
          <xsl:value-of select="@id"/>
        </xsl:if>
        <xsl:text>&#10;</xsl:text>
      </xsl:for-each>

      <xsl:text>&#9;@-for FILE in `ls diff/*`; do \&#10;&#9;
      <xsl:text>&#9;@-for FILE in `ls stereo/*.png`; do ; rm $$FILE ; done&#10;</xsl:text>
      <xsl:text>&#9;@-touch ../</xsl:text>
      <xsl:value-of select="$TEST_RESULTS"/>
      <xsl:text>&#10;</xsl:text>

    </exsl:document>
  </xsl:template>

</xsl:stylesheet>
