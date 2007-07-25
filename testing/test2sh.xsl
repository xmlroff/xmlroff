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
                      <xsl:choose>
                        <xsl:when test="ancestor::*/@base">
                          <xsl:for-each select="ancestor::*/@base">
                            <xsl:value-of select="."/>
                            <xsl:text>/</xsl:text>
                          </xsl:for-each>
                          <xsl:value-of select="@xsl"/>
                        </xsl:when>
                        <xsl:otherwise>
                          <xsl:value-of select="@xsl"/>
                        </xsl:otherwise>
                      </xsl:choose>
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

  
  <!-- Selects the first command-line in $command-patterns where all
       format strings are replaced by values. -->
  <xsl:template name="select-command-line">
    <!-- The patterns, with ';' separating patterns. -->
    <xsl:param name="command-patterns"/>
    <!-- Used in error messages only. -->
    <xsl:param name="original-command-patterns"/>
    <!-- String to substitute for '%p'. -->
    <xsl:param name="xsl-processor"/>
    <!-- String to substitute for '%c'.  Optional. -->
    <xsl:param name="xsl-processor-flags"/>
    <!-- String to substitute for '%o'. -->
    <xsl:param name="output"/>
    <!-- String to substitute for '%i'. -->
    <xsl:param name="input"/>
    <!-- String to substitute for '%s'.  Optional. -->
    <xsl:param name="stylesheet"/>
    
    <xsl:variable name="first-pattern">
      <xsl:choose>
        <xsl:when test="contains($command-patterns, ';')">
          <xsl:value-of
            select="substring-before($command-patterns, ';')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$command-patterns"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="first-command">
      <xsl:call-template name="substitute-formats">
        <xsl:with-param name="command-pattern" select="$first-pattern"/>
        <xsl:with-param name="xsl-processor" select="$xsl-processor"/>
        <xsl:with-param name="xsl-processor-flags" select="$xsl-processor-flags"/>
        <xsl:with-param name="output" select="$output"/>
        <xsl:with-param name="input" select="$input"/>
        <xsl:with-param name="stylesheet" select="$stylesheet"/>
      </xsl:call-template>
    </xsl:variable>
    
    <!-- The command is used only if all formats were replaced. -->
    <xsl:choose>
      <xsl:when test="not(contains($first-command, $unsubstituted-indicator))">
        <xsl:value-of select="$first-command"/>
      </xsl:when>
      <xsl:when test="not(contains($command-patterns, ';'))">
        <xsl:message>
          <xsl:text>No resolvable command patterns: </xsl:text>
          <xsl:value-of select="$original-command-patterns"/>
        </xsl:message>
      </xsl:when>
      <xsl:otherwise>
        <!-- Recurse with remaining patterns if first command unusable. -->
        <xsl:call-template name="select-command-line">
          <xsl:with-param name="command-patterns"
            select="substring($command-patterns,
                              string-length($first-pattern) + 2)"/>
          <xsl:with-param name="original-command-patterns"
            select="$original-command-patterns"/>
          <xsl:with-param name="xsl-processor" select="$xsl-processor"/>
          <xsl:with-param name="xsl-processor-flags" select="$xsl-processor-flags"/>
          <xsl:with-param name="output" select="$output"/>
          <xsl:with-param name="input" select="$input"/>
          <xsl:with-param name="stylesheet" select="$stylesheet"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- Replaces format strings, '%p', etc., with specified values,
       if there is a specified value.  Matches on first format
       string then recursively calls itself on remainder of
       $command-pattern. -->
  <xsl:template name="substitute-formats">
    <!-- The pattern, possibly containing format strings. -->
    <xsl:param name="command-pattern"/>
    <!-- The portion of the command that has already been processed. -->
    <xsl:param name="before"/>
    <!-- String to substitute for '%p'. -->
    <xsl:param name="xsl-processor"/>
    <!-- String to substitute for '%c'.  Optional. -->
    <xsl:param name="xsl-processor-flags"/>
    <!-- String to substitute for '%o'. -->
    <xsl:param name="output"/>
    <!-- String to substitute for '%i'. -->
    <xsl:param name="input"/>
    <!-- String to substitute for '%s'.  Optional. -->
    <xsl:param name="stylesheet"/>
    
    <xsl:choose>
      <xsl:when test="contains($command-pattern, '%')">
        <!-- Portion of $command-pattern before first '%'. -->
        <xsl:variable name="before-format"
          select="substring-before($command-pattern, '%')"/>

        <!-- Format character following first '%'. -->
        <xsl:variable name="format-code"
          select="substring(substring-after($command-pattern, '%'), 1, 1)"/>

        <!-- Portion of $command-pattern after first '%' and its
             following format-code. -->
        <xsl:variable name="after-format"
          select="substring(substring-after($command-pattern, '%'), 2)"/>
        
        <!-- String to replace format string.  If there is no
             replacement for a known format string, reuse the format
             string as a sign that the command string isn't usable. -->
        <xsl:variable name="format-replacement">
          <xsl:choose>
            <xsl:when test="$format-code = 'i'">
              <xsl:value-of select="$input"/>
            </xsl:when>
            <xsl:when test="$format-code = 'o'">
              <xsl:value-of select="$output"/>
            </xsl:when>
            <xsl:when test="$format-code = 's'">
              <xsl:choose>
                <xsl:when test="$stylesheet">
                  <xsl:value-of select="$stylesheet"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$unsubstituted-indicator"/>
                  <xsl:text>s</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:when>
            <xsl:when test="$format-code = 'c'">
              <xsl:choose>
                <xsl:when test="$xsl-processor-flags">
                  <xsl:value-of select="$xsl-processor-flags"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$unsubstituted-indicator"/>
                  <xsl:text>c</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:when>
            <xsl:when test="$format-code = 'p'">
              <xsl:value-of select="$xsl-processor"/>
            </xsl:when>
            <xsl:when test="$format-code = '%'">
              <xsl:text>%</xsl:text>
            </xsl:when>
            <xsl:when test="$format-code = ''">
              <xsl:message>
                <xsl:text>Command pattern ends with a '%'</xsl:text>
              </xsl:message>
            </xsl:when>
            <xsl:otherwise>
              <xsl:message>
                <xsl:text>Unknown format code: </xsl:text>
                <xsl:value-of select="$format-code"/>
              </xsl:message>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:variable>
        
        <!-- Recurse for rest of $command-pattern. -->
        <xsl:call-template name="substitute-formats">
          <xsl:with-param name="before"
            select="concat($before, $before-format, $format-replacement)"/>
          <xsl:with-param name="command-pattern" select="$after-format"/>
          <xsl:with-param name="xsl-processor" select="$xsl-processor"/>
          <xsl:with-param name="xsl-processor-flags" select="$xsl-processor-flags"/>
          <xsl:with-param name="output" select="$output"/>
          <xsl:with-param name="input" select="$input"/>
          <xsl:with-param name="stylesheet" select="$stylesheet"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="concat($before, $command-pattern)"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
