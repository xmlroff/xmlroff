<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- fo-property-util-dump.xsl -->
<!-- Read the XSL spec and dump fo-property-util.c file -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2007-2010 Menteith Consulting Ltd -->
<!-- Copyright (C) 2011 Mentea -->
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

  <xsl:template name="property-to-g-hash-table-insert">
    <xsl:param name="property"/>

    <xsl:variable name="property-identifier">
      <xsl:call-template name="hyphen-colon-dot-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:text>  g_hash_table_insert (hash, "</xsl:text>
    <xsl:value-of select="$property"/>
    <xsl:text>", &amp;fo_property_</xsl:text>
    <xsl:value-of select="$property-identifier"/>
    <xsl:text>_get_type);&#10;</xsl:text>
  </xsl:template>

  <!-- fo-property-eval-c-file -->
  <!-- Generate the fo-property-eval.c file -->
  <xsl:template name="fo-property-eval-c-file">
    <xsl:param name="properties"/>

    <exsl:document href="property/fo-property-eval.c"
      method="text">

      <xsl:text>/* Fo
 * fo-property-eval.c: Functions that relate property attributes to the
 *                     procedures for evaluating them.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-property-eval.h"
#include "fo-all-property.h"

/**
 * fo_property_eval_init_hash:
 * @hash: Null #GHashTable pointer
 * 
 * Initialises @hash and inserts 'get_type' function for
 * every property.
 * 
 * Return value: Initialised #GHashTable
 **/
GHashTable *
fo_property_eval_init_hash (GHashTable *hash)
{

  g_return_val_if_fail (hash == NULL, NULL);

  hash = g_hash_table_new (g_str_hash, g_str_equal);

</xsl:text>

      <xsl:for-each select="$properties">
        <xsl:variable name="property" select="."/>

        <xsl:call-template name="property-to-g-hash-table-insert">
          <xsl:with-param name="property" select="."/>
        </xsl:call-template>

        <xsl:choose>
          <xsl:when
            test="$allowed-properties[. = $property][../@type = 'keep']">
            <xsl:call-template name="property-to-g-hash-table-insert">
              <xsl:with-param name="property">
                <xsl:value-of select="."/>.within-column<xsl:text/>
              </xsl:with-param>
            </xsl:call-template>
            <xsl:call-template name="property-to-g-hash-table-insert">
              <xsl:with-param name="property">
                <xsl:value-of select="."/>.within-line<xsl:text/>
              </xsl:with-param>
            </xsl:call-template>
            <xsl:call-template name="property-to-g-hash-table-insert">
              <xsl:with-param name="property">
                <xsl:value-of select="."/>.within-page<xsl:text/>
              </xsl:with-param>
            </xsl:call-template>
          </xsl:when>
          <xsl:when
            test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
            <xsl:call-template name="property-to-g-hash-table-insert">
              <xsl:with-param name="property">
                <xsl:value-of select="."/>.minimum<xsl:text/>
              </xsl:with-param>
            </xsl:call-template>
            <xsl:call-template name="property-to-g-hash-table-insert">
              <xsl:with-param name="property">
                <xsl:value-of select="."/>.optimum<xsl:text/>
              </xsl:with-param>
            </xsl:call-template>
            <xsl:call-template name="property-to-g-hash-table-insert">
              <xsl:with-param name="property">
                <xsl:value-of select="."/>.maximum<xsl:text/>
              </xsl:with-param>
            </xsl:call-template>

            <xsl:if
              test="$allowed-properties[. = $property][../@type = 'space']">
              <xsl:call-template name="property-to-g-hash-table-insert">
                <xsl:with-param name="property">
                  <xsl:value-of select="."/>.conditionality<xsl:text/>
                </xsl:with-param>
              </xsl:call-template>
              <xsl:call-template name="property-to-g-hash-table-insert">
                <xsl:with-param name="property">
                  <xsl:value-of select="."/>.precedence<xsl:text/>
                </xsl:with-param>
              </xsl:call-template>
            </xsl:if>
          </xsl:when>
        </xsl:choose>
        <xsl:if
                test="$allowed-properties[. = $property][../@type = 'length-conditional']">
                <xsl:call-template name="property-to-g-hash-table-insert">
                <xsl:with-param name="property">
                  <xsl:value-of select="."/>.length<xsl:text/>
                </xsl:with-param>
              </xsl:call-template>
              <xsl:call-template name="property-to-g-hash-table-insert">
                <xsl:with-param name="property">
                  <xsl:value-of select="."/>.conditionality<xsl:text/>
                </xsl:with-param>
              </xsl:call-template>
            </xsl:if>
      </xsl:for-each>

<xsl:text>  return hash;
}
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
      <xsl:call-template name="fo-property-eval-c-file">
        <xsl:with-param name="properties" select="$properties"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>
