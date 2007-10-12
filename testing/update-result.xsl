<?xml version="1.0" encoding="utf-8"?>
<!-- xmlroff -->
<!-- update-result.xsl -->
<!-- Update one result in a 'testresults.xml' file. -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:output method="xml"
    encoding="iso-8859-1"/>

  <xsl:param name="id"/>
  <xsl:param name="path"/>
  <xsl:param name="top-base"/>
  <xsl:param name="agreement"/>
  <xsl:param name="futuresupport" select="-1"/>
  <xsl:param name="specproblem"/>
  <xsl:param name="testproblem"/>
  <xsl:param name="comment"/>
  <xsl:param name="debug"/>

  <xsl:template match="/">
    <xsl:if test="$debug">
      <xsl:message>id: <xsl:value-of select="$id"/></xsl:message>
      <xsl:message>path: <xsl:value-of select="$path"/></xsl:message>
      <xsl:message>top-base: <xsl:value-of select="$top-base"/></xsl:message>
      <xsl:message>agreement: <xsl:value-of select="$agreement"/></xsl:message>
      <xsl:message>futuresupport: <xsl:value-of select="$futuresupport"/></xsl:message>
      <xsl:message>specproblem: <xsl:value-of select="$specproblem"/></xsl:message>
      <xsl:message>testproblem: <xsl:value-of select="$testproblem"/></xsl:message>
      <xsl:message>comment: <xsl:value-of select="$comment"/></xsl:message>
    </xsl:if>
    <!-- Children may include processing instructions specifying
         'configure' defaults. -->
    <xsl:apply-templates select="node()"/>
  </xsl:template>

  <xsl:template match="comment()">
    <xsl:comment>
      <xsl:value-of select="."/>
    </xsl:comment>
  </xsl:template>

  <xsl:template match="processing-instruction()">
    <xsl:copy-of select="."/>
  </xsl:template>

  <xsl:template match="testresult">
    <xsl:choose>
      <xsl:when test="@id=$id and ancestor::testcases[last()]/@base=$top-base">
        <xsl:if test="$debug">
          <xsl:message>id: <xsl:value-of select="$id"/></xsl:message>
          <xsl:message>@base: <xsl:value-of
          select="ancestor::testcases[last()]/@base"/></xsl:message>
        </xsl:if>
        <xsl:copy>
          <xsl:copy-of select="@*[local-name() != 'futuresupport']"/>
          <xsl:if test="$agreement">
            <xsl:attribute name="agreement">
              <xsl:value-of select="$agreement"/>
            </xsl:attribute>
          </xsl:if>
          <xsl:choose>
            <xsl:when test="$futuresupport != -1">
              <xsl:if test="$futuresupport != ''">
                <xsl:attribute name="futuresupport">
                  <xsl:value-of select="$futuresupport"/>
                </xsl:attribute>
              </xsl:if>
            </xsl:when>
            <xsl:when test="@futuresupport">
              <xsl:copy-of select="@futuresupport"/>
            </xsl:when>
          </xsl:choose>
          <xsl:if test="$specproblem">
            <xsl:attribute name="specproblem">
              <xsl:value-of select="$specproblem"/>
            </xsl:attribute>
          </xsl:if>
          <xsl:if test="$testproblem">
            <xsl:attribute name="testproblem">
              <xsl:value-of select="$testproblem"/>
            </xsl:attribute>
          </xsl:if>
          <xsl:choose>
            <xsl:when test="$comment or $comment = ''">
              <xsl:value-of select="$comment" disable-output-escaping="yes"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:apply-templates/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:copy>
      </xsl:when>
      <xsl:otherwise>
        <xsl:copy>
          <xsl:copy-of select="@*"/>
          <xsl:apply-templates/>
        </xsl:copy>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="*">
    <xsl:copy>
      <xsl:copy-of select="@*"/>
      <xsl:apply-templates select="node()"/>
    </xsl:copy>
  </xsl:template>

</xsl:stylesheet>
