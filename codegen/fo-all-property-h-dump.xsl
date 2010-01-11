<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- fo-all-property-h-dump.xsl -->
<!-- Read the XSL spec and dump fo-all-property.h file -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2008-2010 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:exsl="http://exslt.org/common"
                extension-element-prefixes="exsl"
                version="1.0">

  <xsl:output method="text"/>

  <xsl:include href="conversion-lib.xsl"/>

  <xsl:param name="codegen-info"/>
  <xsl:param name="debug"/>

  <xsl:variable name="codegen-info-doc" select="document($codegen-info)"/>

  <xsl:variable name="all-properties"
    select="/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']
            /table/tbody/tr/td[@class = 'propindex']/specref/@ref"/>

  <xsl:variable name="allowed-properties"
    select="document($codegen-info)/codegen-info/properties/property/@name"/>

  <!-- fo-all-property-h-file -->
  <!-- Generate the fo-all-property.h file -->
  <xsl:template name="fo-all-property-h-file">
    <xsl:param name="properties"/>

    <exsl:document href="./fo-all-property.h"
      method="text">
      <xsl:text>/* Fo
 * fo-all-property.h: Header file that includes all property header files
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2008-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ALL_PROPERTY_H__
#define __FO_ALL_PROPERTY_H__

G_BEGIN_DECLS

#include &lt;libfo/property/fo-property.h>

/* Property objects */

/* font-size goes first because the various new_from_expression()
   functions need to know about the 'font-size' property */
#include &lt;libfo/property/fo-property-font-size.h>

</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:variable name="property" select="."/>

    <xsl:choose>
      <xsl:when test=". = 'font-size'">
        <xsl:text>/* '</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>' property already included above. */&#10;</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>.h>&#10;<xsl:text/>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-within-column.h>&#10;<xsl:text/>
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-within-line.h>&#10;<xsl:text/>
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-within-page.h>&#10;<xsl:text/>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-minimum.h>&#10;<xsl:text/>
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-optimum.h>&#10;<xsl:text/>
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-maximum.h>&#10;<xsl:text/>

        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
          <xsl:value-of select="."/>-precedence.h>&#10;<xsl:text/>
          <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
          <xsl:value-of select="."/>-conditionality.h>&#10;<xsl:text/>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-conditionality.h>&#10;<xsl:text/>
        <xsl:text>#include &lt;libfo/property/fo-property-</xsl:text>
        <xsl:value-of select="."/>-length.h>&#10;<xsl:text/>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>
G_END_DECLS

#endif /* !__FO_ALL_PROPERTY_H__ */
</xsl:text>
</exsl:document>
  </xsl:template>

  <xsl:template match="/">
    <xsl:variable name="properties"
      select="$all-properties
              [not($allowed-properties) or $allowed-properties = .]"/>

    <xsl:if test="$debug">
      <xsl:for-each select="$properties">
        <xsl:message><xsl:value-of select="."/></xsl:message>
      </xsl:for-each>
    </xsl:if>

    <xsl:if test="not($codegen-info) or $properties">
      <xsl:call-template name="fo-all-property-h-file">
        <xsl:with-param name="properties" select="$properties"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>
