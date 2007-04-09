<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff -->
<!-- test2sh.xsl -->
<!-- $Id: common.xsl,v 1.2 2006/07/24 16:44:56 tonygraham Exp $ -->
<!-- Generate 'test.sh' files for each test suite referred to from
     $testsuites. -->
<!-- Process with Saxon, since uses Saxon extension to make named
     output files.
     e.g.: java com.icl.saxon.StyleSheet  test2sh.xsl test2sh.xsl testsuites=../../TestSuite/coverage/testsuites.xml

     xsltproc also supports the Saxon extension for named output files:
     e.g.: xsltproc -\-novalid -\-stringparam testsuites testsuites.xml test2sh.xsl test2sh.xsl
-->

<!-- Copyright (C) 2001, 2004 Sun Microsystems -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <!-- Gets the basename (the part after the last '/') of $string.
       If $suffix is not null and is part of the basename, lops $suffix
       off the end of the basename.
  -->
  <xsl:template name="basename">
    <xsl:param name="string"/>
    <xsl:param name="suffix"/>
    <xsl:param name="separator" select="'/'"/>
    
    <xsl:variable name="the-rest">
      <xsl:choose>
        <xsl:when test="contains($string, $separator)">
          <xsl:value-of select="substring-after($string, $separator)"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$string"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:if test="$DEBUG >= 2">
      <xsl:message>
        <xsl:text>basename:: $string: '</xsl:text>
        <xsl:value-of select="$string"/>
        <xsl:text>'; $suffix: '</xsl:text>
        <xsl:value-of select="$suffix"/>
        <xsl:text>'; $the-rest: '</xsl:text>
        <xsl:value-of select="$the-rest"/>
        <xsl:text>'&#10;</xsl:text>
      </xsl:message>
    </xsl:if>

    <xsl:choose>
      <xsl:when test="not(contains($the-rest, $separator))">
        <xsl:choose>
          <xsl:when test="$suffix">
            <xsl:choose>
              <xsl:when test="substring($the-rest,
                                        string-length($the-rest) -
                                        string-length($suffix) + 1)
                              = $suffix">
                <xsl:value-of select="substring($the-rest,
                                                1,
                                                string-length($the-rest) -
                                                string-length($suffix))"/>
              </xsl:when>
              <xsl:otherwise>
                <xsl:value-of select="$the-rest"/>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="$the-rest"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="basename">
          <xsl:with-param name="string" select="$the-rest"/>
          <xsl:with-param name="suffix" select="$suffix"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="dirname">
    <xsl:param name="string"/>
    <xsl:param name="separator" select="'/'"/>

    <xsl:variable name="the-rest" select="substring-after($string,
																										      $separator)"/>

    <xsl:if test="$DEBUG >= 2">
      <xsl:message>
        <xsl:text>dirname:: $string: '</xsl:text>
        <xsl:value-of select="$string"/>
        <xsl:text>'; $the-rest: '</xsl:text>
        <xsl:value-of select="$the-rest"/>
        <xsl:text>'&#10;</xsl:text>
      </xsl:message>
    </xsl:if>
    <xsl:value-of select="substring-before($string, $separator)"/>

    <xsl:if test="contains($the-rest, '/')">
      <xsl:text>/</xsl:text>
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="$the-rest"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

  <xsl:template name="merge-dirnames">
    <xsl:param name="dirname1"/>
    <xsl:param name="dirname2"/>
    <xsl:param name="separator" select="'/'"/>
    
    <xsl:if test="$DEBUG >= 2">
      <xsl:message>
        <xsl:text>merge-dirname:: dirname1: '</xsl:text>
        <xsl:value-of select="$dirname1"/>
        <xsl:text>'; dirname2: '</xsl:text>
        <xsl:value-of select="$dirname2"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
    </xsl:if>

    <xsl:variable name="merged-dirname">
      <xsl:choose>
        <xsl:when test="substring($dirname2, 1, 5) = 'http:'">
          <xsl:value-of select="$dirname2"/>
        </xsl:when>
        <xsl:when test="$dirname1 != ''">
          <xsl:choose>
            <xsl:when test="$dirname2 != ''">
              <xsl:choose>
                <xsl:when test="substring($dirname2, 1, 1) = $separator">
                  <xsl:value-of select="$dirname2"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="concat($dirname1, $separator, $dirname2)"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="$dirname1"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="$dirname2">
              <xsl:value-of select="$dirname2"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:text>.</xsl:text>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:if test="$DEBUG >= 2">
      <xsl:message>
        <xsl:text>merge-dirname:: merged dirname: '</xsl:text>
        <xsl:value-of select="$merged-dirname"/>
        <xsl:text>'</xsl:text>
      </xsl:message>
      <xsl:message><xsl:text>&#10;</xsl:text></xsl:message>
    </xsl:if>

    <xsl:value-of select="$merged-dirname"/>
  </xsl:template>

</xsl:stylesheet>
