<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- fo-property-object-dump.xsl -->
<!-- Read the XSL spec and generate .c and .h files for FoProperty
     subtypes for each property. -->
<!-- If a named template isn't in this file, see conversion-lib.xsl. -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2007-2010 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:exsl="http://exslt.org/common"
                extension-element-prefixes="exsl"
                version="1.0">

  <xsl:output method="text"/>

  <!-- Templates common to multiple 'spec-dump' stylesheets. -->
  <xsl:include href="conversion-lib.xsl"/>

  <!-- 'codegen-info.xml' that controls what is dumped. -->
  <xsl:param name="codegen-info"/>

  <!-- debug level.  Set to non-false value to enable emitting
       of debugging messages.  Set to 2 or higher to enable more
       debugging messages. -->
  <xsl:param name="debug"/>

  <!-- Restrict the XSL properties generated to those listed in
       'codegen-info.xml'.  If this doesn't select anything, e.g., if
       $codegen-info is not specified, then all properties will be
       dumped. -->
  <xsl:variable name="allowed-properties"
    select="document($codegen-info)/codegen-info/properties/property/@name"/>

  <!-- expand-datatype -->
  <!-- Some things that look like datatypes in the property values are
       really shorthands for two or more enumerated values.  This named
       template expands the $datatype parameter, if possible.

       This named template is used by the various other named templates
       that each do something for each enumeration token.  When the result
       of this template is an empty string, the calling template typically
       goes on to process the tokens after the token for the current
       datatype.  When the result of this template is an expansion into
       multiple enumeration tokens, the calling template typically
       processes the concatenation of this result and the
       remainder of the original value string that came after the
       datatype. -->
  <xsl:template name="expand-datatype">
    <xsl:param name="datatype"/>

    <xsl:choose>
      <xsl:when test="$datatype = 'absolute-size'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;absolute-size></xsl:message>
        </xsl:if>
        <xsl:text>xx-small | x-small | small | medium | large | x-large | xx-large </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'keep'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;keep></xsl:message>
        </xsl:if>
        <xsl:text>auto | always | &lt;integer> </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'margin-width'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;margin-width></xsl:message>
        </xsl:if>
        <xsl:text>auto | &lt;length> | &lt;percentage> </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'padding-width'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;padding-width></xsl:message>
        </xsl:if>
        <xsl:text>&lt;length> | &lt;percentage> </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'relative-size'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;relative-size></xsl:message>
        </xsl:if>
        <xsl:text>larger | smaller </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'border-style'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;border-style></xsl:message>
        </xsl:if>
        <xsl:text>none | hidden | dotted | dashed | solid | double | groove | ridge | inset | outset </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'border-width'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;border-width></xsl:message>
        </xsl:if>
        <xsl:text>thin | medium | thick | &lt;length> </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'generic-family'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;generic-family></xsl:message>
        </xsl:if>
        <xsl:text>serif | sans-serif | cursive | fantasy | monospace </xsl:text>
      </xsl:when>
      <xsl:when test="$datatype = 'family-name'">
        <xsl:if test="$debug">
          <xsl:message>Expanding &lt;family-name></xsl:message>
        </xsl:if>
        <xsl:text>&lt;string></xsl:text>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <!-- is-punctuation-token -->
  <!-- Result is text 'TRUE' if $token is a "punctuation token", i.e.,
       if it's recognisably not a datatype name in a property value
       definition. -->
  <xsl:template name="is-punctuation-token">
    <xsl:param name="token"/>

    <xsl:if test="$token = '[[' or
                  $token = '[' or
                  $token = '||' or
                  $token = '|' or
                  $token = '/' or
                  $token = ',]*' or
                  $token = ',]' or
                  $token = ',' or
                  starts-with($token, ']')">TRUE</xsl:if>
  </xsl:template>

  <!-- is-datatype-token -->
  <!-- Result is text 'TRUE' if $token is a "datatype token", i.e.,
       if it's recognised as a datatype name in a property value
       definition because it contains '<'. -->
  <xsl:template name="is-datatype-token">
    <xsl:param name="token"/>

    <xsl:if test="starts-with($token, '&lt;') or
                  starts-with($token, '[&lt;') or
                  starts-with($token, '[[&lt;')">TRUE</xsl:if>
  </xsl:template>

  <!-- fo-property-h-file -->
  <xsl:template name="fo-property-h-file">
    <xsl:param name="property"/>
    <xsl:param name="property-filename"/>
    <xsl:param name="property-macro"/>
    <xsl:param name="property-identifier"/>
    <xsl:param name="property-identifier-spaces"/>
    <xsl:param name="property-type"/>
    <xsl:param name="value-string"/>
    <xsl:param name="shorthand"/>
    <xsl:param name="inherited"/>
    <xsl:param name="initial-value-string"/>

    <exsl:document href="./fo-property-{$property-filename}.h"
      method="text">
      <xsl:text>/* Fo
 * fo-property-</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>.h: '</xsl:text><xsl:value-of select="$property"/><xsl:text>' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>_H__
#define __FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>_H__

#include &lt;libfo/fo-utils.h>
#include &lt;libfo/property/fo-property.h>

G_BEGIN_DECLS

</xsl:text>
<xsl:call-template name="c-comment">
  <xsl:with-param name="string"
    select="$property"/>
</xsl:call-template>

<xsl:call-template name="c-comment">
  <xsl:with-param name="string">
    <xsl:text>Inherited: </xsl:text>
    <xsl:choose>
      <xsl:when test="$inherited = true()">TRUE</xsl:when>
      <xsl:otherwise>FALSE</xsl:otherwise>
    </xsl:choose>
  </xsl:with-param>
</xsl:call-template>

<xsl:call-template name="c-comment">
  <xsl:with-param name="string">
    <xsl:text>Shorthand: </xsl:text>
    <xsl:choose>
      <xsl:when test="$shorthand = true()">TRUE</xsl:when>
      <xsl:otherwise>FALSE</xsl:otherwise>
    </xsl:choose>
  </xsl:with-param>
</xsl:call-template>

<xsl:call-template name="c-comment">
  <xsl:with-param name="string"
    select="normalize-space(../../following-sibling::td[1])"/>
</xsl:call-template>

<xsl:call-template name="c-comment">
  <xsl:with-param name="string"
    select="concat('Initial value: ', $initial-value-string)"/>
</xsl:call-template>

    <xsl:text>
#define FO_TYPE_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>              (fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_type ())
#define FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>, FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>))
#define FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>, FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class))
#define FO_IS_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>))
#define FO_IS_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>))
#define FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>, FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class))


/**
 * FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>:
 *
 * Instance of the '</xsl:text><xsl:value-of select="$property"/><xsl:text>' property.
 **/
typedef struct _FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>      FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>;

/**
 * FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class:
 *
 * Class structure for the '</xsl:text><xsl:value-of select="$property"/><xsl:text>' property.
 **/
typedef struct _FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class;

GType        fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_new         (void);
FoProperty * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text>_H__ */
</xsl:text>
  </exsl:document>
</xsl:template>

  <!-- value-string-to-validate-ifs -->
  <xsl:template name="value-string-to-validate-ifs">
    <xsl:param name="value-string"/>
    <xsl:param name="property-identifier"/>
    <xsl:param name="property-macro"/>
    <xsl:param name="resolve-enum"/>
    <xsl:param name="first" select="true()"/>
    <xsl:param name="seen-enum" select="false()"/>

    <xsl:if test="$value-string">
      <xsl:variable name="token">
        <xsl:choose>
          <xsl:when test="contains($value-string, ' ')">
            <xsl:value-of select="substring-before($value-string, ' ')"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="$value-string"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:variable>
      <xsl:variable name="after-token"
        select="substring-after($value-string, ' ')"/>

      <xsl:variable name="is-punctuation-token">
        <xsl:call-template name="is-punctuation-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="is-datatype-token">
        <xsl:call-template name="is-datatype-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="datatype"
        select="substring-before(substring-after($token, '&lt;'), '>')"/>

      <xsl:variable name="expanded-datatype">
        <xsl:call-template name="expand-datatype">
          <xsl:with-param name="datatype" select="$datatype"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:if test="$debug >= 3">
        <xsl:message>token: '<xsl:value-of select="$token"/>'</xsl:message>
      </xsl:if>

      <xsl:choose>
        <xsl:when test="$is-punctuation-token = 'TRUE'">
          <xsl:call-template name="value-string-to-validate-ifs">
            <xsl:with-param
              name="value-string"
              select="$after-token"/>
            <xsl:with-param
              name="property-identifier"
              select="$property-identifier"/>
            <xsl:with-param
              name="property-macro"
              select="$property-macro"/>
            <xsl:with-param
              name="resolve-enum"
              select="$resolve-enum"/>
            <xsl:with-param name="first" select="$first"/>
            <xsl:with-param name="seen-enum" select="$seen-enum"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="$is-datatype-token = 'TRUE' and
                        string-length($expanded-datatype) != 0">
          <xsl:call-template name="value-string-to-validate-ifs">
            <xsl:with-param
              name="value-string"
              select="concat($expanded-datatype, $after-token)"/>
            <xsl:with-param
              name="property-identifier"
              select="$property-identifier"/>
            <xsl:with-param
              name="property-macro"
              select="$property-macro"/>
            <xsl:with-param
              name="resolve-enum"
              select="$resolve-enum"/>
            <xsl:with-param name="first" select="$first"/>
            <xsl:with-param name="seen-enum" select="$seen-enum"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
        <!-- To get here, it's either a real datatype or it's an
             enumeration token -->

          <xsl:if test="$debug >= 2">
            <xsl:message>token: '<xsl:value-of select="$token"/>', is-punctuation-token: '<xsl:value-of select="$is-punctuation-token"/>'</xsl:message>
          </xsl:if>

          <xsl:if test="$is-datatype-token = 'TRUE' or not($seen-enum)">
            <xsl:text>  </xsl:text>
            <xsl:if test="not($first)">
              <xsl:text>else </xsl:text>
            </xsl:if>
          </xsl:if>

          <xsl:choose>
            <xsl:when test="$is-datatype-token = 'TRUE'">
              <xsl:choose>
                <xsl:when test="$datatype = 'character'">
                  <xsl:text>if (FO_IS_CHAR (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'color'">
                  <xsl:text>if (FO_IS_COLOR (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'id'">
                  <xsl:text>if (FO_IS_ID (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'idref'">
                  <xsl:text>if (FO_IS_NAME (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'integer'">
                  <xsl:text>if (FO_IS_INTEGER (datatype))
    {
      return datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      new_datatype =
        fo_integer_new_with_value ((gint) fo_number_get_value (datatype));

      g_object_unref (datatype);

      return new_datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'length'">
                  <xsl:text>if (FO_IS_LENGTH (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'length-conditional'">
                  <xsl:text>if (FO_IS_LENGTH_COND (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'length-bp-ip-direction'">
                  <xsl:text>if (FO_IS_LENGTH_BPD_IPD (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'length-range'">
                  <xsl:text>if (FO_IS_LENGTH_RANGE (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'name'">
                  <xsl:text>if (FO_IS_NAME (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'number'">
                  <xsl:text>if (FO_IS_NUMBER (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'percentage'">
                  <xsl:text>if (FO_IS_PERCENTAGE (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'space'">
                  <xsl:text>if (FO_IS_SPACE (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'string'">
                  <xsl:text>if (FO_IS_STRING (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:when test="$datatype = 'uri-specification'">
                  <xsl:text>if (FO_IS_URI_SPECIFICATION (datatype))
    {
      return datatype;
    }
</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:message terminate="no">Unsupported datatype: <xsl:value-of select="$datatype"/></xsl:message>
                </xsl:otherwise>
              </xsl:choose>
              <xsl:call-template name="value-string-to-validate-ifs">
                <xsl:with-param
                  name="value-string"
                  select="$after-token"/>
                <xsl:with-param
                  name="property-identifier"
                  select="$property-identifier"/>
                <xsl:with-param
                  name="property-macro"
                  select="$property-macro"/>
                <xsl:with-param
                  name="resolve-enum"
                  select="$resolve-enum"/>
                <xsl:with-param name="first" select="false()"/>
                <xsl:with-param name="seen-enum" select="$seen-enum"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:if test="not($seen-enum)">
                <xsl:variable name="clean-token"
                  select="translate($token, '[]|,?', '')"/>
                <xsl:text>if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

</xsl:text>
<xsl:call-template name="value-string-to-validate-enum-ifs">
  <xsl:with-param name="value-string" select="$value-string"/>
  <xsl:with-param name="property-identifier" select="$property-identifier"/>
</xsl:call-template>
<xsl:text>)
	{
	  return datatype;
	}
      else
	{
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);

	  g_set_error (error,
		       FO_FO_ERROR,
		       FO_FO_ERROR_ENUMERATION_TOKEN,
		       _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		       class_name,
		       datatype_sprintf,
		       g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

	  g_object_unref (datatype);

	  g_free (datatype_sprintf);

	  return NULL;
	}
    }
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        </xsl:text>
        <xsl:choose>
          <xsl:when test="$resolve-enum">
            <xsl:value-of select="$resolve-enum"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>fo_property_</xsl:text>
            <xsl:value-of select="$property-identifier"/>
            <xsl:text>_resolve_enum</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
        <xsl:text> (token, context, &amp;tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        </xsl:text>
        <xsl:choose>
          <xsl:when test="$resolve-enum">
            <xsl:value-of select="$resolve-enum"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:text>fo_property_</xsl:text>
            <xsl:value-of select="$property-identifier"/>
            <xsl:text>_resolve_enum</xsl:text>
          </xsl:otherwise>
        </xsl:choose>
        <xsl:text> (token, context, &amp;tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
</xsl:text>
              </xsl:if>
              <xsl:call-template name="value-string-to-validate-ifs">
                <xsl:with-param
                  name="value-string"
                  select="$after-token"/>
                <xsl:with-param
                  name="property-identifier"
                  select="$property-identifier"/>
                <xsl:with-param
                  name="property-macro"
                  select="$property-macro"/>
                <xsl:with-param
                  name="resolve-enum"
                  select="$resolve-enum"/>
                <xsl:with-param name="first" select="false()"/>
                <xsl:with-param name="seen-enum" select="true()"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- value-string-to-resolve-enum-ifs -->
  <xsl:template name="value-string-to-resolve-enum-ifs">
    <xsl:param name="value-string"/>
    <xsl:param name="property-identifier"/>
    <xsl:param name="resolve-enum"/>
    <xsl:param name="first" select="true()"/>
    
    <xsl:if test="$value-string">
      <xsl:variable name="token">
        <xsl:choose>
          <xsl:when test="contains($value-string, ' ')">
            <xsl:value-of select="substring-before($value-string, ' ')"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="$value-string"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:variable>
      <xsl:variable name="after-token"
        select="substring-after($value-string, ' ')"/>

      <xsl:variable name="is-punctuation-token">
        <xsl:call-template name="is-punctuation-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="is-datatype-token">
        <xsl:call-template name="is-datatype-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:if test="$debug >= 2">
        <xsl:message>token: '<xsl:value-of select="$token"/>', is-punctuation-token: '<xsl:value-of select="$is-punctuation-token"/>'</xsl:message>
      </xsl:if>

      <xsl:choose>
        <xsl:when test="$is-punctuation-token = 'TRUE'">
          <xsl:call-template name="value-string-to-resolve-enum-ifs">
            <xsl:with-param
              name="value-string"
              select="$after-token"/>
            <xsl:with-param
              name="property-identifier"
              select="$property-identifier"/>
            <xsl:with-param
              name="resolve-enum"
              select="$resolve-enum"/>
            <xsl:with-param name="first" select="$first"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="$is-datatype-token = 'TRUE'">
          <xsl:variable name="datatype"
            select="substring-before(substring-after($token, '&lt;'), '>')"/>
          <xsl:variable name="expanded-datatype">
            <xsl:call-template name="expand-datatype">
              <xsl:with-param name="datatype" select="$datatype"/>
            </xsl:call-template>
          </xsl:variable>
          <xsl:choose>
            <xsl:when test="string-length($expanded-datatype) = 0">
              <xsl:call-template name="value-string-to-resolve-enum-ifs">
                <xsl:with-param
                  name="value-string"
                  select="$after-token"/>
                <xsl:with-param
                  name="property-identifier"
                  select="$property-identifier"/>
                <xsl:with-param
                  name="resolve-enum"
                  select="$resolve-enum"/>
                <xsl:with-param name="first" select="$first"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="value-string-to-resolve-enum-ifs">
                <xsl:with-param
                  name="value-string"
                  select="concat($expanded-datatype, $after-token)"/>
                <xsl:with-param
                  name="property-identifier"
                  select="$property-identifier"/>
                <xsl:with-param
                  name="resolve-enum"
                  select="$resolve-enum"/>
                <xsl:with-param name="first" select="$first"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>

          <xsl:variable name="clean-token"
            select="translate($token, '-[]|,?', '_')"/>

          <xsl:if test="$clean-token != 'inherit'">
            <xsl:choose>
              <xsl:when test="$first">
                <xsl:text>  if (</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text> ||
      </xsl:text>
    </xsl:otherwise>
  </xsl:choose>
    <xsl:text>(strcmp (token, "</xsl:text>
    <xsl:value-of select="$token"/>
            <xsl:text>") == 0)</xsl:text>
          </xsl:if>

          <xsl:if test="$after-token">
            <xsl:call-template name="value-string-to-resolve-enum-ifs">
              <xsl:with-param
                name="value-string"
                select="$after-token"/>
              <xsl:with-param
                name="property-identifier"
                select="$property-identifier"/>
              <xsl:with-param
                name="resolve-enum"
                select="$resolve-enum"/>
              <xsl:with-param name="first" select="false()"/>
            </xsl:call-template>
          </xsl:if>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- value-string-to-validate-enum-ifs -->
  <xsl:template name="value-string-to-validate-enum-ifs">
    <xsl:param name="value-string"/>
    <xsl:param name="property-identifier"/>
    <xsl:param name="resolve-enum"/>
    <xsl:param name="first" select="true()"/>
    
    <xsl:if test="$value-string">
      <xsl:variable name="token">
        <xsl:choose>
          <xsl:when test="contains($value-string, ' ')">
            <xsl:value-of select="substring-before($value-string, ' ')"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="$value-string"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:variable>
      <xsl:variable name="after-token"
        select="substring-after($value-string, ' ')"/>

      <xsl:variable name="is-punctuation-token">
        <xsl:call-template name="is-punctuation-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="is-datatype-token">
        <xsl:call-template name="is-datatype-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:if test="$debug >= 2">
        <xsl:message>token: '<xsl:value-of select="$token"/>', is-punctuation-token: '<xsl:value-of select="$is-punctuation-token"/>'</xsl:message>
      </xsl:if>

      <xsl:choose>
        <xsl:when test="$is-punctuation-token = 'TRUE'">
          <xsl:call-template name="value-string-to-validate-enum-ifs">
            <xsl:with-param
              name="value-string"
              select="$after-token"/>
            <xsl:with-param
              name="property-identifier"
              select="$property-identifier"/>
            <xsl:with-param
              name="resolve-enum"
              select="$resolve-enum"/>
            <xsl:with-param name="first" select="$first"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="$is-datatype-token = 'TRUE'">
          <xsl:variable name="datatype"
            select="substring-before(substring-after($token, '&lt;'), '>')"/>
          <xsl:variable name="expanded-datatype">
            <xsl:call-template name="expand-datatype">
              <xsl:with-param name="datatype" select="$datatype"/>
            </xsl:call-template>
          </xsl:variable>
          <xsl:choose>
            <xsl:when test="string-length($expanded-datatype) = 0">
              <xsl:call-template name="value-string-to-validate-enum-ifs">
                <xsl:with-param
                  name="value-string"
                  select="$after-token"/>
                <xsl:with-param
                  name="property-identifier"
                  select="$property-identifier"/>
                <xsl:with-param
                  name="resolve-enum"
                  select="$resolve-enum"/>
                <xsl:with-param name="first" select="$first"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="value-string-to-validate-enum-ifs">
                <xsl:with-param
                  name="value-string"
                  select="concat($expanded-datatype, $after-token)"/>
                <xsl:with-param
                  name="property-identifier"
                  select="$property-identifier"/>
                <xsl:with-param
                  name="resolve-enum"
                  select="$resolve-enum"/>
                <xsl:with-param name="first" select="$first"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>

          <xsl:variable name="clean-token"
            select="translate($token, '-[]|,?', '_')"/>

          <xsl:if test="$clean-token != 'inherit'">
            <xsl:choose>
              <xsl:when test="$first">
                <xsl:text>      if (</xsl:text>
                <xsl:if test="$after-token">
                  <xsl:text>(</xsl:text>
                </xsl:if>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>) ||
          (</xsl:text>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:text>value == FO_ENUM_ENUM_</xsl:text>
  <xsl:call-template name="hyphen-colon-to-underscore">
    <xsl:with-param name="string">
      <xsl:call-template name="to-upper">
        <xsl:with-param name="string" select="$token"/>
      </xsl:call-template>
    </xsl:with-param>
  </xsl:call-template>
</xsl:if>

<xsl:choose>
  <xsl:when test="$after-token">
    <xsl:call-template name="value-string-to-validate-enum-ifs">
      <xsl:with-param
        name="value-string"
        select="$after-token"/>
      <xsl:with-param
        name="property-identifier"
        select="$property-identifier"/>
      <xsl:with-param
        name="resolve-enum"
        select="$resolve-enum"/>
      <xsl:with-param name="first" select="false()"/>
    </xsl:call-template>
  </xsl:when>
  <xsl:otherwise>
    <xsl:if test="not($first)">
      <xsl:text>)</xsl:text>
    </xsl:if>
  </xsl:otherwise>
</xsl:choose>
</xsl:otherwise>
</xsl:choose>
</xsl:if>
</xsl:template>

<!-- value-string-to-enum-object-action -->
  <xsl:template name="value-string-to-enum-object-action">
    <xsl:param name="value-string"/>
    <xsl:param name="property-name"/>
    <xsl:param name="action" select="false()"/>

    <xsl:if test="$value-string">
      <xsl:variable name="token">
        <xsl:choose>
          <xsl:when test="contains($value-string, ' ')">
            <xsl:value-of select="substring-before($value-string, ' ')"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="$value-string"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:variable>
      <xsl:variable name="after-token"
        select="substring-after($value-string, ' ')"/>

      <xsl:variable name="is-punctuation-token">
        <xsl:call-template name="is-punctuation-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="is-datatype-token">
        <xsl:call-template name="is-datatype-token">
          <xsl:with-param name="token" select="$token"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="datatype"
        select="substring-before(substring-after($token, '&lt;'), '>')"/>

      <xsl:variable name="expanded-datatype">
        <xsl:call-template name="expand-datatype">
          <xsl:with-param name="datatype" select="$datatype"/>
        </xsl:call-template>
      </xsl:variable>

      <xsl:if test="$debug >= 2">
        <xsl:message>token: '<xsl:value-of select="$token"/>', is-punctuation-token: '<xsl:value-of select="$is-punctuation-token"/>'</xsl:message>
      </xsl:if>

      <xsl:choose>
        <xsl:when test="$is-punctuation-token = 'TRUE' or
                        ($is-datatype-token = 'TRUE' and
                         string-length($expanded-datatype) = 0)">
          <xsl:call-template name="value-string-to-enum-object-action">
            <xsl:with-param
              name="value-string"
              select="$after-token"/>
            <xsl:with-param
              name="property-name"
              select="$property-name"/>
            <xsl:with-param
              name="action"
              select="$action"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="$is-datatype-token = 'TRUE'">
          <xsl:choose>
            <xsl:when test="string-length($expanded-datatype) = 0">
              <xsl:message>Shouldn't get here.</xsl:message>
              <xsl:call-template name="value-string-to-enum-object-action">
                <xsl:with-param
                  name="value-string"
                  select="$after-token"/>
                <xsl:with-param
                  name="property-name"
                  select="$property-name"/>
                <xsl:with-param
                  name="action"
                  select="$action"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="value-string-to-enum-object-action">
                <xsl:with-param
                  name="value-string"
                  select="concat($expanded-datatype, $after-token)"/>
                <xsl:with-param
                  name="property-name"
                  select="$property-name"/>
                <xsl:with-param
                  name="action"
                  select="$action"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>

          <!-- Translate '-' to '_' and get rid of undesirables -->
          <xsl:variable name="clean-token"
            select="translate($token, '-[]|,?', '_')"/>

          <xsl:if test="$clean-token != 'inherit'">
            <xsl:choose>
              <xsl:when test="$action = 'set'">
                <xsl:variable name="enumeration-name">
                  <xsl:call-template name="to-upper">
                    <xsl:with-param name="string">
                      <xsl:call-template name="hyphen-colon-to-underscore">
                        <xsl:with-param name="string"
                          select="concat('FO_ENUM_', $property-name, '_', $clean-token)"/>
                      </xsl:call-template>
                    </xsl:with-param>
                  </xsl:call-template>
                </xsl:variable>

                <xsl:text/>
  enum_<xsl:value-of select="$clean-token"/> =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_<xsl:value-of select="$property-name"/>),
                  "value",
                  <xsl:value-of select="$enumeration-name"/>,
                  NULL);</xsl:when>
              <xsl:when test="$action = 'unref'">
                <xsl:text>  g_object_unref (enum_</xsl:text>
                <xsl:value-of select="$clean-token"/>
                <xsl:text>);&#10;</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:message terminate="yes">Unrecognised enum object action: <xsl:value-of select="$action"/></xsl:message>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:if>

          <xsl:if test="$after-token">
            <xsl:call-template name="value-string-to-enum-object-action">
              <xsl:with-param
                name="value-string"
                select="$after-token"/>
              <xsl:with-param
                name="property-name"
                select="$property-name"/>
              <xsl:with-param
                name="action"
                select="$action"/>
            </xsl:call-template>
          </xsl:if>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- fo-property-c-file -->
  <xsl:template name="fo-property-c-file">
    <xsl:param name="property"/>
    <xsl:param name="property-filename"/>
    <xsl:param name="property-macro"/>
    <xsl:param name="property-identifier"/>
    <xsl:param name="property-identifier-spaces"/>
    <xsl:param name="property-type"/>
    <xsl:param name="value-string"/>
    <xsl:param name="initial-value-string"/>
    <xsl:param name="inherited"/>
    <xsl:param name="shorthand"/>
    <xsl:param name="resolve-enum"/>
    <xsl:param name="validate"/>
    <xsl:param name="is-text-property"/>
    <xsl:param name="expr-eval"/>
    
    <xsl:variable name="enum-object-sets">
      <xsl:call-template name="value-string-to-enum-object-action">
        <xsl:with-param
          name="value-string"
          select="normalize-space(../../following-sibling::td[1])"/>
        <xsl:with-param
          name="action"
          select="'set'"/>
        <xsl:with-param
          name="property-name"
          select="$property-macro"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="enum-object-unrefs">
      <xsl:call-template name="value-string-to-enum-object-action">
        <xsl:with-param
          name="value-string"
          select="normalize-space(../../following-sibling::td[1])"/>
        <xsl:with-param
          name="action"
          select="'unref'"/>
      </xsl:call-template>
    </xsl:variable>

    <exsl:document href="./fo-property-{$property-filename}.c"
      method="text">
  <xsl:text>/* Fo
 * fo-property-</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>.c: '</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include &lt;string.h>
</xsl:text>
<xsl:text>#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
</xsl:text>
<xsl:if test="$is-text-property">
  <xsl:text>#include "property/fo-property-text-property.h"&#10;</xsl:text>
</xsl:if>
<xsl:text>#include "property/fo-property-font-size.h"
#include "property/fo-property-</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>.h"
</xsl:text>
<xsl:if test="$resolve-enum">
  <xsl:text>#include "property/fo-property-util.h"&#10;</xsl:text>
</xsl:if>
<xsl:text>
</xsl:text>

<xsl:copy-of select="document($codegen-info)/codegen-info/properties/property[@name = $property]/defines"/>

<xsl:text>/**
 * SECTION:fo-property-</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>
 * @short_description: '</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>' property
 *
 * Inherited: </xsl:text>
<xsl:choose>
  <xsl:when test="$inherited = true()">TRUE</xsl:when>
  <xsl:otherwise>FALSE</xsl:otherwise>
</xsl:choose><xsl:text>
 *
 * Shorthand: </xsl:text>
<xsl:choose>
  <xsl:when test="$shorthand = true()">TRUE</xsl:when>
  <xsl:otherwise>FALSE</xsl:otherwise>
</xsl:choose><xsl:text>
 *
 * Value: </xsl:text><xsl:value-of select="normalize-space($value-string)"/><xsl:text>
 *
 * Initial value: </xsl:text><xsl:value-of select="normalize-space($initial-value-string)"/><xsl:text>
 *
 * Definition: &lt;ulink url="http://www.w3.org/TR/xsl11/&amp;num;</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>">http://www.w3.org/TR/xsl11/&amp;num;</xsl:text><xsl:value-of select="$property-filename"/><xsl:text>&lt;/ulink>
 */
</xsl:text>

    <xsl:text>
struct _FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>
{
  FoProperty parent_instance;
};

struct _FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class
{
  FoPropertyClass parent_class;
};

static void fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_init         (FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>      *property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>);
</xsl:text>

<xsl:text>static void fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_class_init   (FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class *klass);
static void fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_finalize     (GObject       *object);
</xsl:text>
  <xsl:if test="$is-text-property">
    <xsl:text>static void fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_text_property_init (FoPropertyTextPropertyIface *iface);&#10;</xsl:text>
</xsl:if>
<xsl:text>
</xsl:text>

<xsl:if test="not($resolve-enum)">
    <xsl:text>static FoDatatype * fo_property_</xsl:text>
<xsl:value-of select="$property-identifier"/>
<xsl:text>_resolve_enum (const gchar *token,
                                </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>               FoContext   *context,
                                </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>               GError     **error);
</xsl:text>
</xsl:if>

<xsl:if test="not($validate)">
  <xsl:text>static FoDatatype * fo_property_</xsl:text>
<xsl:value-of select="$property-identifier"/>
<xsl:text>_validate (FoDatatype *datatype,
                                </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>           FoContext  *context,
                                </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>           GError    **error);
</xsl:text>
</xsl:if>

<xsl:if test="$is-text-property">
  <xsl:text>static PangoAttribute * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_new_attr (FoProperty *property);
</xsl:text>
</xsl:if>

<xsl:text>
static const gchar class_name[] = "</xsl:text><xsl:value-of select="$property"/><xsl:text>";
static gpointer parent_class;

/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_type:
 * 
 * Register the #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text> type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>.
 **/
GType
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_init,
	NULL		/* value_table */
      };
</xsl:text>
<xsl:if test="$is-text-property">
  <xsl:text>
      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_text_property_init, /* interface_init */
        NULL,
        NULL
      };
</xsl:text>
</xsl:if>
  <xsl:text>
      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &amp;object_info, 0);
</xsl:text>
<xsl:if test="$is-text-property">
  <xsl:text>
      g_type_add_interface_static (object_type,
                                   FO_TYPE_PROPERTY_TEXT_PROPERTY,
                                   &amp;fo_property_text_property_info);
</xsl:text>
</xsl:if>
  <xsl:text>    }

  return object_type;
}

/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_init:
 * @</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>: #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text> object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>.
 **/
void
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_init (FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text> *</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>)
{
  FO_PROPERTY (</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>)->value =
    </xsl:text><xsl:choose>
      <xsl:when test="$initial-value-string">
        <xsl:text>g_object_ref (fo_enum_get_enum_by_nick ("</xsl:text>
        <xsl:value-of select="$initial-value-string"/>
        <xsl:text>"))</xsl:text>
      </xsl:when>
      <xsl:otherwise>NULL</xsl:otherwise>
    </xsl:choose><xsl:text>;
}

/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_class_init:
 * @klass: #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class object to initialise.
 * 
 * Implements #GClassInitFunc for #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class.
 **/
void
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_class_init (FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>Class *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_finalize;
</xsl:text>

    <xsl:if test="$expr-eval">
      <xsl:text>
  property_class->expr_eval = </xsl:text><xsl:value-of select="$expr-eval"/><xsl:text>;</xsl:text>
    </xsl:if>

<xsl:text>
  property_class->is_inherited = </xsl:text>
    <xsl:choose>
      <xsl:when test="$inherited = true()">TRUE</xsl:when>
      <xsl:otherwise>FALSE</xsl:otherwise>
    </xsl:choose><xsl:text>;
  property_class->is_shorthand = </xsl:text>
    <xsl:choose>
      <xsl:when test="$shorthand = true()">TRUE</xsl:when>
      <xsl:otherwise>FALSE</xsl:otherwise>
    </xsl:choose><xsl:text>;
  property_class->resolve_enum =
    </xsl:text>

      <xsl:choose>
        <xsl:when test="$resolve-enum">
          <xsl:value-of select="$resolve-enum"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_resolve_enum</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:text>;
  property_class->validate =
    </xsl:text>
      <xsl:choose>
        <xsl:when test="$validate">
          <xsl:value-of select="$validate"/>
        </xsl:when>
        <xsl:otherwise>
  <xsl:text>fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_validate</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
<xsl:text>;
  property_class->get_initial =
    fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_initial;
}

/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_finalize:
 * @object: #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text> object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>.
 **/
void
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_finalize (GObject *object)
{
  FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text> *</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>;

  </xsl:text><xsl:value-of select="$property-identifier"/><xsl:text> = FO_PROPERTY_</xsl:text><xsl:value-of select="$property-macro"/><xsl:text> (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

</xsl:text>
<xsl:if test="$is-text-property">
  <xsl:text>/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_new_attr;
}
</xsl:text>
</xsl:if>
  <xsl:text>
/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_new:
 * 
 * Creates a new #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text> initialized to default value.
 * 
 * Return value: the new #FoProperty</xsl:text><xsl:value-of select="$property-type"/><xsl:text>.
 **/
FoProperty*
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_new (void)
{
  FoProperty* </xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>;

  </xsl:text><xsl:value-of select="$property-identifier"/><xsl:text> =
    FO_PROPERTY (g_object_new (fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_type (),
                               NULL));

  return </xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>;
}
</xsl:text>
<xsl:if test="not($resolve-enum)">
  <xsl:text>
/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_resolve_enum:
 * @token:   Token from the XML attribute value to be evaluated as an
 *           enumeration token.
 * @context: #FoContext object from which to possibly inherit values.
 * @error:   Information about any error that has occurred.
 * 
 * Compare @token against the enumeration tokens that are valid for the
 * current FO property.  If @token is valid, returns either an #FoEnum datatype
 * representing the enumeration token or a different datatype representing
 * the enumeration token's resolved value.  If @token is not valid,
 * sets @error and returns NULL.
 * 
 * Return value: Resolved enumeration value or NULL.
 **/
FoDatatype*
fo_property_</xsl:text>
<xsl:value-of select="$property-identifier"/>
<xsl:text>_resolve_enum (const gchar *token,
            </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>               FoContext   *context,
            </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>               GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

</xsl:text>
<xsl:call-template name="value-string-to-resolve-enum-ifs">
  <xsl:with-param
    name="value-string"
    select="normalize-space($value-string)"/>
  <xsl:with-param
    name="property-identifier"
    select="$property-identifier"/>
</xsl:call-template>
<xsl:text>)
    {
      return g_object_ref (fo_enum_get_enum_by_nick (token));
    }
  else
    {
      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_ENUMERATION_TOKEN,
		   _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		   class_name,
		   token);
      return NULL;
    }
}
</xsl:text>
</xsl:if>
<xsl:if test="not($validate)">
  <xsl:text>
/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_validate:
 * @datatype: #FoDatatype to be validated against allowed datatypes and
 *            values for current property.
 * @context:  #FoContext object from which to possibly inherit values.
 * @error:    Information about any error that has occurred.
 * 
 * Validates @datatype against allowed values.  Returns @datatype, a
 * replacement datatype value, or NULL if validation failed.
 * 
 * Return value: Valid datatype value or NULL.
 **/
FoDatatype*
fo_property_</xsl:text>
<xsl:value-of select="$property-identifier"/>
<xsl:text>_validate (FoDatatype *datatype,
            </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>           FoContext  *context,
            </xsl:text>
<xsl:value-of select="$property-identifier-spaces"/>
<xsl:text>           GError    **error)
{
  FoDatatype *new_datatype;
  GError     *tmp_error = NULL;
  gchar      *token;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

</xsl:text>
<xsl:call-template name="value-string-to-validate-ifs">
  <xsl:with-param
    name="value-string"
    select="normalize-space($value-string)"/>
  <xsl:with-param
    name="property-identifier"
    select="$property-identifier"/>
  <xsl:with-param
    name="property-macro"
    select="$property-macro"/>
  <xsl:with-param
    name="resolve-enum"
    select="$resolve-enum"/>
  <xsl:with-param
    name="seen-enum"
    select="not(string-length($enum-object-sets))"/>
</xsl:call-template>
<xsl:text>  else
    {
      gchar *datatype_sprintf = fo_object_sprintf (datatype);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   datatype_sprintf,
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      g_free (datatype_sprintf);

      return NULL;
    }
}
</xsl:text>
</xsl:if>
<xsl:text>
/**
 * fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_get_initial (void)
{
  static FoProperty *</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text> = NULL;

  if (</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text> == NULL)
    {
      </xsl:text><xsl:value-of select="$property-identifier"/><xsl:text> =
	fo_property_</xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>_new ();
    }

  return </xsl:text><xsl:value-of select="$property-identifier"/><xsl:text>;
}
</xsl:text>
</exsl:document>
  </xsl:template>

  <xsl:template match="@ref" name="enum-get-type-definition">
    <xsl:param name="property"/>
    <xsl:param name="value-string"/>

    <xsl:variable name="property-identifier">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="property-type">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$property"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:call-template name="c-comment">
      <xsl:with-param name="string"
        select="$property"/>
    </xsl:call-template>

    <!-- Start of generated text -->
    <xsl:call-template name="c-comment">
      <xsl:with-param name="string"
        select="$value-string"/>
    </xsl:call-template>

    <!-- End of generated text -->
  </xsl:template>

  <!-- / -->
  <!-- This is expected to be the XML for the XSL 1.0 Recommendation. -->
  <xsl:template match="/">
    <!-- Get the list of all properties from the table in the appendix of the spec. -->
    <xsl:for-each
      select="/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']/table/tbody/tr/td[@class = 'propindex']/specref/@ref[not($allowed-properties) or $allowed-properties = .]">
      <xsl:sort/>

      <!-- Some variables controlling the generated code come from the spec. -->

      <!-- Property name as extracted from the XSL spec. -->
      <xsl:variable name="property" select="normalize-space(.)"/>

      <!-- The values allowed for the property, e.g., 'false | true |
           inherit' or '<absolute-size> | <relative-size> | <length> |
           <percentage> | inherit'. -->
      <xsl:variable name="value-string"
        select="normalize-space(/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']/table/tbody/tr/td[@class = 'propindex'][specref/@ref = current()]/following-sibling::td[1])"/>

      <!-- Initial value of the property. -->
      <xsl:variable name="initial-value-string"
        select="normalize-space(/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']/table/tbody/tr/td[@class = 'propindex'][specref/@ref = current()]/following-sibling::td[2])"/>

      <!-- Intermediate result in determining whether or not the
           property is inherited.  Used only by the following
           $inherited variable declaration.-->
      <xsl:variable name="inherited-string"
        select="normalize-space(/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']/table/tbody/tr/td[@class = 'propindex'][specref/@ref = current()]/following-sibling::td[3])"/>
      <!-- Whether or not the property is inherited. -->
      <xsl:variable name="inherited"
        select="substring($inherited-string, 1, 3) = 'yes'"/>

      <!-- Intermediate result in determining whether or not the
           property is a shorthand.  Used only by the following
           $shorthand variable declaration. -->
      <xsl:variable name="shorthand-string"
        select="normalize-space(/spec/back/div1[@id='property-index']/div2[@id = 'prtab2']/table/tbody/tr/td[@class = 'propindex'][specref/@ref = current()]/following-sibling::td[3])"/>
      <!-- Whether or not the property is a shorthand. -->
      <xsl:variable name="shorthand"
        select="$shorthand-string = 'Shorthand'"/>
      
      <!-- Some variables controlling the generated code come from the
           'codegen-info.xml' file either because they're specific to xmlroff
	   or because it's just not worth the effort to automate extracting
	   that information from the spec. -->

      <!-- Function to use to resolve enumeration token values
           (instead of generating a property-specific resolution
           function as part of the generated code). -->
      <xsl:variable name="resolve-enum"
        select="$allowed-properties[. = $property]/../@resolve-enum"/>
        
      <!-- Function to use to validate the property's value (instead
           of generating a property-specific validation function as
           part of the generated code). -->
      <xsl:variable name="validate"
        select="$allowed-properties[. = $property]/../@validate"/>
      
      <!-- FoDatatype to use as the property's initial value (instead
           of NULL). -->
      <xsl:variable name="init-value"
        select="$allowed-properties[. = $property]/../@init-value"/>
      
      <!-- Whether or not to output extra code for a property that
           implements the FoPropertyTextPropertyIface interface. -->
      <xsl:variable name="is-text-property"
        select="$allowed-properties[. = $property]/../@is-text-property[. = 'yes']"/>
      
      <!-- Function to use to evaluate property value expressions
           (instead of the default set in the non-generated
           fo-property.c file). -->
      <xsl:variable name="expr-eval"
        select="$allowed-properties[. = $property]/../@expr-eval"/>
        
      
      <!-- Generate C code for the property. -->
      <xsl:call-template name="process-property">
        <xsl:with-param name="property" select="$property"/>
        <xsl:with-param name="value-string" select="$value-string"/>
        <xsl:with-param name="initial-value-string"
          select="$initial-value-string"/>
        <xsl:with-param name="inherited" select="$inherited"/>
        <xsl:with-param name="shorthand" select="$shorthand"/>
        <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
        <xsl:with-param name="validate" select="$validate"/>
        <xsl:with-param name="init-value" select="$init-value"/>
        <xsl:with-param name="is-text-property" select="$is-text-property"/>
        <xsl:with-param name="expr-eval" select="$expr-eval"/>
      </xsl:call-template>

      <!-- Output code for individual components of 'keep', 'length-range',
           and 'space' properties. -->
      <xsl:choose>
	<!-- Keeps have '.within-column', '.within-line', and '.within-page'
	     components. -->
        <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-within-column')"/>
            <xsl:with-param name="value-string" select="$value-string"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-within-line')"/>
            <xsl:with-param name="value-string" select="$value-string"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-within-page')"/>
            <xsl:with-param name="value-string" select="$value-string"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
        </xsl:when>
	<!-- Length ranges have '.minimum', '.optimum', and '.maximum' components. -->
        <xsl:when test="$allowed-properties[. = $property][../@type = 'length-range']">
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-minimum')"/>
            <xsl:with-param name="value-string" select="'auto | &lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum"
              select="'fo_property_util_resolve_auto_enum'"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value"
              select="'fo_enum_get_enum_auto ()'"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-optimum')"/>
            <xsl:with-param name="value-string" select="'auto | &lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum"
              select="'fo_property_util_resolve_auto_enum'"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value"
              select="'fo_enum_get_enum_auto ()'"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-maximum')"/>
            <xsl:with-param name="value-string" select="'auto | &lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum"
              select="'fo_property_util_resolve_auto_enum'"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value"
              select="'fo_enum_get_enum_auto ()'"/>
          </xsl:call-template>
        </xsl:when>
	<!-- Spaces have '.minimum', '.optimum', '.maximum', '.precedence',
	     and '.conditionality' components. -->
        <xsl:when test="$allowed-properties[. = $property][../@type = 'space']">
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-minimum')"/>
            <xsl:with-param name="value-string" select="'&lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-optimum')"/>
            <xsl:with-param name="value-string" select="'&lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-maximum')"/>
            <xsl:with-param name="value-string" select="'&lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-precedence')"/>
            <xsl:with-param name="value-string" select="'force | &lt;integer>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-conditionality')"/>
            <xsl:with-param name="value-string" select="'discard | retain'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
        </xsl:when>
	<!-- Length-conditionals have '.length' and '.conditionality' components. -->
        <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-length')"/>
            <xsl:with-param name="value-string" select="'&lt;length>'"/>
            <xsl:with-param name="initial-value-string"
              select="$initial-value-string"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
          <xsl:call-template name="process-property">
            <xsl:with-param name="property"
              select="concat($property, '-conditionality')"/>
            <xsl:with-param name="value-string" select="'discard | retain'"/>
            <xsl:with-param name="initial-value-string"
              select="'discard'"/>
            <xsl:with-param name="inherited" select="$inherited"/>
            <xsl:with-param name="shorthand" select="$shorthand"/>
            <xsl:with-param name="resolve-enum" select="$resolve-enum"/>
            <xsl:with-param name="validate" select="$validate"/>
            <xsl:with-param name="init-value" select="$init-value"/>
          </xsl:call-template>
        </xsl:when>
      </xsl:choose>
    </xsl:for-each>
  </xsl:template>

  <!-- Process an individual property (or a component of a compound property). -->
  <xsl:template name="process-property">
    <xsl:param name="property"/>
    <xsl:param name="value-string"/>
    <xsl:param name="initial-value-string"/>
    <xsl:param name="inherited"/>
    <xsl:param name="shorthand"/>
    <xsl:param name="resolve-enum"/>
    <xsl:param name="validate"/>
    <xsl:param name="init-value"/>
    <xsl:param name="is-text-property"/>
    <xsl:param name="expr-eval"/>
    
    <xsl:if test="$debug >= 2">
      <xsl:message>Property: <xsl:value-of select="$property"/></xsl:message>
    </xsl:if>

    <!-- Precompute various forms of the property name that will be
         used in the generated code. -->

    <!-- Possibly alter the property name to use to get around some of
         the verbosity of XSL property names. -->
    <xsl:variable name="use-property">
      <xsl:choose>
        <xsl:when test="contains($property, 'conditionality')">
          <xsl:value-of select="substring-before($property, 'conditionality')"/>
          <xsl:text>condity</xsl:text>
          <xsl:value-of select="substring-after($property, 'conditionality')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$property"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Lower-case form of the property name, e.g. for use as part of
         name of a generated file. -->
    <xsl:variable name="property-filename">
      <xsl:call-template name="to-lower">
        <xsl:with-param name="string" select="$property"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- Upper-case form of the property name with colons replaced by
         underscores, e.g., for use as part of a C macro or constant
         name. -->
    <xsl:variable name="property-macro">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$use-property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Lower-case form of the property name with colons replaced by
         underscores, e.g., for use as part of a C variable name. -->
    <xsl:variable name="property-identifier">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$use-property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Sequence of space characters equivalent to the length of
         $property-identifier for use when indenting second and
         subsequent lines of a function prototype, etc. -->
    <xsl:variable name="property-identifier-spaces"
      select="substring($spaces, 1, string-length($property-identifier))"/>

    <!-- Camel-case form of the property name, e.g., for use as part
         of a C type name in a typedef statement. -->
    <xsl:variable name="property-type">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$use-property"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- Generate the C header file for the property. -->
    <xsl:call-template name="fo-property-h-file">
      <xsl:with-param name="property"
        select="$use-property"/>
      <xsl:with-param name="property-filename"
        select="$property-filename"/>
      <xsl:with-param name="property-macro"
        select="$property-macro"/>
      <xsl:with-param name="property-identifier"
        select="$property-identifier"/>
      <xsl:with-param name="property-identifier-spaces"
        select="$property-identifier-spaces"/>
      <xsl:with-param name="property-type"
        select="$property-type"/>
      <xsl:with-param name="value-string"
        select="$value-string"/>
      <xsl:with-param name="initial-value-string"
        select="$initial-value-string"/>
      <xsl:with-param name="inherited"
        select="$inherited"/>
      <xsl:with-param name="shorthand"
        select="$shorthand"/>
    </xsl:call-template>

    <!-- Generate the C source code file for the property. -->
    <xsl:call-template name="fo-property-c-file">
      <xsl:with-param name="property"
        select="$use-property"/>
      <xsl:with-param name="property-filename"
        select="$property-filename"/>
      <xsl:with-param name="property-macro"
        select="$property-macro"/>
      <xsl:with-param name="property-identifier"
        select="$property-identifier"/>
      <xsl:with-param name="property-identifier-spaces"
        select="$property-identifier-spaces"/>
      <xsl:with-param name="property-type"
        select="$property-type"/>
      <xsl:with-param name="value-string"
        select="$value-string"/>
      <xsl:with-param name="initial-value-string"
        select="$initial-value-string"/>
      <xsl:with-param name="inherited"
        select="$inherited"/>
      <xsl:with-param name="shorthand"
        select="$shorthand"/>
      <xsl:with-param name="resolve-enum"
        select="$resolve-enum"/>
      <xsl:with-param name="validate"
        select="$validate"/>
      <xsl:with-param name="init-value"
        select="$init-value"/>
      <xsl:with-param name="is-text-property"
        select="$is-text-property"/>
      <xsl:with-param name="expr-eval"
        select="$expr-eval"/>
    </xsl:call-template>
  </xsl:template>

</xsl:stylesheet>
