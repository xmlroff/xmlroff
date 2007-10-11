<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- XSLT stylesheet to bring an XSL FO document into compatibility
     with the capabilities of the libfo library of the xmlroff XSL
     Formatter. -->

<!-- Author: Tony Graham -->

<!--
     Copyright (c) 2003-2006 Sun Microsystems. All Rights Reserved.
     Copyright (c) 2007 Menteith Consulting

     Redistribution and use in source and binary forms, with or without
     modification, are permitted provided that the following conditions are
     met:

      - Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

      - Redistribution in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the
        distribution.

     Neither the name of Sun Microsystems or the names of contributors may
     be used to endorse or promote products derived from this software
     without specific prior written permission.

     This software is provided "AS IS," without a warranty of any kind. ALL
     EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES,
     INCLUDING ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A
     PARTICULAR PURPOSE OR NON INFRINGEMENT, ARE HEREBY EXCLUDED. SUN
     MICROSYSTEMS AND ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES
     SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
     THE SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL SUN MICROSYSTEMS OR
     ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR FOR
     DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE
     DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY,
     ARISING OUT OF THE USE OF OR INABILITY TO USE SOFTWARE, EVEN IF SUN
     MICROSYSTEMS HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

     You acknowledge that this Software is not designed, licensed or
     intended for use in the design, construction, operation or maintenance
     of any nuclear facility.
-->
<xsl:stylesheet
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:fo="http://www.w3.org/1999/XSL/Format"
  version="1.0">

  <xsl:output method="xml"/>

  <xsl:param name="verbose" select="false()"/>
  <xsl:param name="keep-threshold" select="20"/>
  
  <xsl:template match="text()[normalize-space() = '']">
    <xsl:variable name="previous-is-inline">
      <xsl:choose>
        <xsl:when test="preceding-sibling::*[1]">
          <xsl:call-template name="is-inline">
            <xsl:with-param name="fo" select="preceding-sibling::*[1]"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>no</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="following-is-inline">
      <xsl:choose>
        <xsl:when test="following-sibling::*[1]">
          <xsl:call-template name="is-inline">
            <xsl:with-param name="fo" select="following-sibling::*[1]"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>no</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:if test="$previous-is-inline = 'yes' or $following-is-inline = 'yes'">
      <xsl:value-of select="."/>
    </xsl:if>
  </xsl:template>
  
  <xsl:template name="is-inline">
    <xsl:param name="fo"/>
    
    <xsl:variable name="local-name" select="local-name($fo)"/>
    <xsl:choose>
      <xsl:when
        test="$local-name = 'bidi-override' or
        $local-name = 'character' or
        $local-name = 'external-graphic' or
        $local-name = 'instream-foreign-object' or
        $local-name = 'inline' or
        $local-name = 'inline-container' or
        $local-name = 'leader' or
        $local-name = 'page-number' or
        $local-name = 'page-number-citation' or
        $local-name = 'page-number-citation-last' or
        $local-name = 'scaling-value-citation' or
        $local-name = 'basic-link' or
        $local-name = 'multi-toggle' or
        $local-name = 'index-page-citation-list' or
        $local-name = 'multi-switch' or
        $local-name = 'multi-properties' or
        $local-name = 'index-range-begin' or
        $local-name = 'index-range-end' or
        $local-name = 'wrapper' or
        $local-name = 'retrieve-marker' or
        $local-name = 'float' or
        $local-name = 'footnote'">yes</xsl:when>
      <xsl:otherwise>no</xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="fo:list-item-label/text()">
    <xsl:if test="$verbose">
      <xsl:message>Correcting text child of fo:list-item-label by removing text</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="text()[. = '&#xA0;']">
    <xsl:if test="$verbose">
      <xsl:message>Removing "&amp;#xA0;".</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="@display-align[.='middle']">
    <xsl:if test="$verbose">
      <xsl:message>Correcting 'display-align="middle"' to 'display-align="center"'.</xsl:message>
    </xsl:if>
    <xsl:attribute name="{name()}">center</xsl:attribute>
  </xsl:template>


  <!-- Unsupported properties to be removed. -->
  <xsl:template match="@background-attachment |
           @background-image |
           @background-position-horizontal |
           @background-position-vertical |
           @background-repeat |
           @blank-or-not-blank |
           @column-count |
           @column-gap |
           @content-type |
           @extent |
           @external-destination |
           @font-selection-strategy |
           @force-page-count |
           @height |
           @hyphenate |
           @hyphenation-character |
           @hyphenation-push-character-count |
           @hyphenation-remain-character-count |
           @initial-page-number |
           @internal-destination |
           @language |
           @last-line-end-indent |
           @leader-alignment |
           @leader-pattern |
           @leader-pattern-width |
           @line-height-shift-adjustment |
           @margin |
           @odd-or-even |
           @page-position |
           @text-align-last">
    <xsl:if test="$verbose">
      <xsl:message>Removing unsupported '<xsl:value-of select="name()"/>' property.</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="@keep-together |
    @keep-together.within-line |
    @keep-together.within-column |
    @keep-together.within-page |
    @keep-with-previous |
    @keep-with-previous.within-line |
    @keep-with-previous.within-column |
    @keep-with-previous.within-page |
    @keep-with-next |
    @keep-with-next.within-line |
    @keep-with-next.within-column |
    @keep-with-next.within-page">
    <xsl:choose>
      <xsl:when test="node() &lt; $keep-threshold">
        <xsl:attribute name="{name()}">auto</xsl:attribute>
      </xsl:when>
      <xsl:otherwise>
        <xsl:attribute name="{name()}">
          <xsl:value-of select="."/>
        </xsl:attribute>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="@*">
    <xsl:attribute name="{name()}">
      <xsl:value-of select="."/>
    </xsl:attribute>
  </xsl:template>

  <xsl:template match="fo:block-container[@reference-orientation]">
    <xsl:if test="$verbose">
      <xsl:message>Removing 'fo:block-container' with unsupported 'reference-orientation' property.</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="fo:block-container/text()">
    <xsl:if test="$verbose">
      <xsl:message>Correcting 'fo:block-container' containing only text.</xsl:message>
    </xsl:if>
    <fo:block>
      <xsl:copy/>
    </fo:block>
  </xsl:template>

  <xsl:template match="fo:region-body/@region-name">
    <xsl:if test="$verbose">
      <xsl:message>Removing 'fo:region-body' region-name attribute.</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="fo:float">
    <xsl:if test="$verbose">
      <xsl:message>Removing unsupported 'fo:float'.</xsl:message>
    </xsl:if>
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="fo:footnote">
    <xsl:if test="$verbose">
      <xsl:message>Removing unsupported 'fo:footnote'.</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="fo:inline-container/fo:block">
    <xsl:if test="$verbose">
      <xsl:message>Removing unsupported 'fo:block' in 'fo:inline-container'.</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="fo:simple-page-master[name(child::*[1]) = 'fo:region-before' and
    name(child::*[2]) = 'fo:region-after' and
    name(child::*[3]) = 'fo:region-body']">
    <xsl:if test="$verbose">
      <xsl:message>Correcting 'fo:region-before', 'fo:region-after', and 'fo:region-body' order.</xsl:message>
    </xsl:if>
    <xsl:copy>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates select="fo:region-body"/>
      <xsl:apply-templates select="fo:region-before"/>
      <xsl:apply-templates select="fo:region-after"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="fo:root[name(child::*[1]) = 'fo:declarations' and
    name(child::*[2]) = 'fo:layout-master-set']">
    <xsl:if test="$verbose">
      <xsl:message>Correcting 'fo:declarations' and 'fo:layout-master-set' order.</xsl:message>
    </xsl:if>
    <xsl:copy>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates select="fo:layout-master-set"/>
      <xsl:apply-templates select="fo:declarations"/>
      <xsl:apply-templates select="fo:page-sequence"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="fo:static-content">
    <xsl:if test="$verbose">
      <xsl:message>Removing unsupported 'fo:static-content'.</xsl:message>
    </xsl:if>
  </xsl:template>

  <xsl:template match="fo:table[@table-layout='fixed' and not(@width)]">
    <xsl:if test="$verbose">
      <xsl:message>Auto table layout unsupported. Adding 'width' property.</xsl:message>
    </xsl:if>
    <xsl:copy>
      <xsl:attribute name="width">100%</xsl:attribute>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates select="node()"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="fo:table[not(@table-layout) and @width]">
    <xsl:if test="$verbose">
      <xsl:message>Auto table layout unsupported. Adding 'table-layout' property.</xsl:message>
    </xsl:if>
    <xsl:copy>
      <xsl:attribute name="table-layout">fixed</xsl:attribute>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates select="node()"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="fo:table[not(@table-layout) and not(@width)]">
    <xsl:if test="$verbose">
      <xsl:message>Auto table layout unsupported. Adding 'table-layout' and 'width' properties.</xsl:message>
    </xsl:if>
    <xsl:copy>
      <xsl:attribute name="table-layout">fixed</xsl:attribute>
      <xsl:attribute name="width">
        <xsl:choose>
          <xsl:when test="count(fo:table-column/@column-width) != 0">
            <xsl:if test="$verbose">
              <xsl:message>Computing table-width from 'fo:table-column/@column-width' properties.</xsl:message>
            </xsl:if>
            <xsl:for-each select="fo:table-column/@column-width">
              <xsl:value-of select="."/>
              <xsl:if test="position() != last()">
                <xsl:text> + </xsl:text>
              </xsl:if>
            </xsl:for-each>
          </xsl:when>
          <xsl:otherwise>
            <xsl:if test="$verbose">
              <xsl:message>Using 'width="100%"'.</xsl:message>
            </xsl:if>
            <xsl:text>100%</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:attribute>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates select="node()"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="fo:wrapper[fo:list-item]">
    <xsl:if test="$verbose">
      <xsl:message>Removing 'fo:wrapper' used in an unsupported context.</xsl:message>
    </xsl:if>
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="*">
    <xsl:copy>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates select="node()"/>
    </xsl:copy>
  </xsl:template>

</xsl:stylesheet>
