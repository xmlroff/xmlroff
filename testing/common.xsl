<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff-testing -->
<!-- common.xsl -->
<!-- Templates common to multiple stylesheets. -->

<!-- Copyright (C) 2001, 2004 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <!-- basename
     - $string: Pathname for which to get the basename
     - $suffix: Suffix to also remove from the basename.  Optional.
     - $separator: String separating directory names.  Default is '/'.
     -
     - Gets the basename (the part after the last $separator) of $string.
     - If $suffix is not null and is part of the basename, lops $suffix
     - off the end of the basename.
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
          <xsl:with-param name="separator" select="$separator"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- dirname
     - $string: Pathname for which to get the directory name
     - $separator: String separating directory names.  Default is '/'.
     -
     - Gets the directory name (the part before the last $separator)
     - of $string.
     -->
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

  <!-- merge-dirnames
     - $dirname1: Potential base for a relative directory name
     - $dirname2: directory name to merge
     - $separator: String to use when concatenating directories. Optional.
     -
     - Merge $dirname1 and $dirname2 such that if $dirname2 is
     - a relative path, the result is relative to $dirname1.
     -
     - Also handles if either name or both names are empty.
     -->
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

  <!-- select-command-line -->
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

  <!-- substitute-formats -->
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
