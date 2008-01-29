<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- conversion-lib.xsl -->
<!-- Common templates used when generating C code from XSL spec -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:output method="text"/>

  <xsl:variable name="spaces"
    select="'                                           '"/>

  <xsl:template name="to-upper">
    <xsl:param name="string"/>
    <xsl:value-of select="translate($string,
                                    'abcdefghijklmnopqrstuvwxyz',
                                    'ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
  </xsl:template>

  <xsl:template name="to-lower">
    <xsl:param name="string"/>
    <xsl:value-of select="translate($string,
                                    'ABCDEFGHIJKLMNOPQRSTUVWXYZ',
                                    'abcdefghijklmnopqrstuvwxyz')"/>
  </xsl:template>

  <xsl:template name="hyphen-colon-to-underscore">
    <xsl:param name="string"/>
    <xsl:value-of select="translate($string,
                                    '-:',
                                    '__')"/>
  </xsl:template>

  <xsl:template name="hyphen-colon-dot-to-underscore">
    <xsl:param name="string"/>
    <xsl:value-of select="translate($string,
      '-:.',
      '___')"/>
  </xsl:template>

  <xsl:template name="hyphen-colon-to-space">
    <xsl:param name="string"/>
    <xsl:value-of select="translate($string,
                                    '-:',
                                    '  ')"/>
  </xsl:template>

  <xsl:template name="c-comment">
    <xsl:param name="string"/>

    <xsl:text>/* </xsl:text>
    <xsl:value-of select="$string"/>
    <xsl:text> */&#10;</xsl:text>
  </xsl:template>

  <xsl:template name="to-camel">
    <xsl:param name="string"/>
    <xsl:if test="$string">
      <xsl:variable name="the-rest"
        select="substring($string, 2)"/>
      <xsl:variable name="before-hyphen"
        select="string-length(substring-before($the-rest, '-'))"/>
      <xsl:variable name="before-colon"
        select="string-length(substring-before($the-rest, ':'))"/>

      <xsl:call-template name="to-upper">
        <xsl:with-param name="string"
          select="substring($string, 1, 1)"/>
      </xsl:call-template>

      <xsl:choose>
        <xsl:when test="$before-hyphen != 0 or
                        substring($the-rest, 1, 1) = '-' or
                        $before-colon != 0 or
                        substring($the-rest, 1, 1) = ':'">
          <xsl:choose>
            <xsl:when test="$before-colon = 0 or
                            substring($the-rest, 1, 1) = '-' or
                            $before-hyphen > $before-colon">
              <xsl:value-of select="substring($the-rest,
                                              1,
                                              $before-hyphen)"/>
              <xsl:call-template name="to-camel">
                <xsl:with-param name="string"
                  select="substring($the-rest, $before-hyphen + 2)"/>
              </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="substring($the-rest,
                                              1,
                                              $before-colon)"/>
              <xsl:call-template name="to-camel">
                <xsl:with-param name="string"
                  select="substring($the-rest, $before-colon + 2)"/>
              </xsl:call-template>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:when>
        <xsl:otherwise>
          <!-- if no hyphen or colon, just do value of the rest of string -->
          <xsl:value-of select="$the-rest"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <xsl:template name="to-proper-noun">
    <xsl:param name="string"/>
    <xsl:if test="$string">
      <xsl:variable name="the-rest"
        select="substring($string, 2)"/>
      <xsl:variable name="before-space"
        select="string-length(substring-before($the-rest, ' '))"/>

      <xsl:call-template name="to-upper">
        <xsl:with-param name="string"
          select="substring($string, 1, 1)"/>
      </xsl:call-template>

      <xsl:choose>
        <xsl:when test="$before-space != 0 or
                        substring($the-rest, 1, 1) = ' '">
          <xsl:value-of select="substring($the-rest,
                                          1,
                                          $before-space)"/>
          <xsl:text> </xsl:text>
          <xsl:call-template name="to-proper-noun">
            <xsl:with-param name="string"
              select="substring($the-rest, $before-space + 2)"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <!-- if no space, just do value of the rest of string -->
          <xsl:value-of select="$the-rest"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- property-to-get-set-prototypes
       Generate the prototypes for the functions to get and set
       a property of an object -->
  <xsl:template name="property-to-get-set-prototypes">
    <xsl:param name="property"/>
    <xsl:param name="object"/>
    <xsl:param name="specialise-property-type" select="false()"/>

    <xsl:variable name="is-datatype"
      select="document($codegen-info)/codegen-info/properties/property[@name = $property]/@is-datatype = 'yes'"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-property-spaces"
      select="substring($spaces, 1, string-length($lowercase-property))"/>

    <xsl:variable name="camelcase-property">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$property"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object-spaces"
      select="substring($spaces, 1, string-length($lowercase-object))"/>

    <!-- Start of generated text -->
    <!-- _get_ -->
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>FoProperty</xsl:text>
        <xsl:if test="$specialise-property-type">
          <xsl:value-of select="$camelcase-property"/>
        </xsl:if>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoDatatype</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_</xsl:text><xsl:value-of select="$lowercase-property"/><xsl:text> (</xsl:text>

    <xsl:choose>
      <xsl:when test="$object = 'context'">
        <xsl:text>FoContext  *fo_context</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoFo       *fo_fo</xsl:text>
      </xsl:otherwise>
    </xsl:choose>

    <xsl:text>);&#10;</xsl:text>

    <!-- _set_ -->
    <xsl:text>void         fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_set_</xsl:text>
<xsl:value-of select="$lowercase-property"/>
<xsl:text> (</xsl:text>

    <xsl:choose>
      <xsl:when test="$object = 'context'">
        <xsl:text>FoContext  *fo_context</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoFo       *fo_fo</xsl:text>
      </xsl:otherwise>
    </xsl:choose>

    <xsl:text>,&#10;</xsl:text>

<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:value-of select="$lowercase-property-spaces"/>
<xsl:text>                       </xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>FoProperty</xsl:text>
        <xsl:if test="$specialise-property-type">
          <xsl:value-of select="$camelcase-property"/>
        </xsl:if>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoDatatype</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> *new_</xsl:text><xsl:value-of select="$lowercase-property"/><xsl:text>);
</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- property-to-prop-enum
       Generate an enum symbol for the property -->
  <xsl:template match="@id" mode="property-to-prop-enum" name="property-to-prop-enum">
    <xsl:param name="property"/>

    <xsl:variable name="uppercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:text>  PROP_</xsl:text><xsl:value-of select="$uppercase-property"/>
<xsl:if test="position() != last()">,</xsl:if>
<xsl:text>&#10;</xsl:text>
  </xsl:template>

  <!-- property-to-instance-variable
       Generate an instance variable for the property -->
  <xsl:template match="@id" mode="property-to-instance-variable"
    name="property-to-instance-variable">
    <xsl:param name="property"/>

    <xsl:variable name="is-datatype"
      select="document($codegen-info)/codegen-info/properties/property[@name = $property]/@is-datatype = 'yes'"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="camelcase-property">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$property"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>  </xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>FoProperty</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoDatatype</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> *</xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text>;&#10;</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- property-to-install-property
       Generate the g_object_class_install_property call for property -->
  <xsl:template name="property-to-install-property">
    <xsl:param name="property"/>
    <xsl:param name="property-abbrev"/>
    <xsl:param name="param-flags">G_PARAM_READABLE</xsl:param>

    <xsl:variable name="is-datatype"
      select="document($codegen-info)/codegen-info/properties/property[@name = $property]/@is-datatype = 'yes'"/>

    <xsl:variable name="use-property">
      <xsl:choose>
        <xsl:when test="$property-abbrev">
          <xsl:value-of select="$property-abbrev"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$property"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="uppercase-use-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$use-property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="noun-property">
      <xsl:call-template name="to-proper-noun">
        <xsl:with-param name="string">
          <xsl:call-template name="hyphen-colon-to-space">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:text>  g_object_class_install_property
    (object_class,
     PROP_</xsl:text><xsl:value-of select="$uppercase-use-property"/><xsl:text>,
     g_param_spec_object ("</xsl:text><xsl:value-of select="$property"/><xsl:text>",
			  _("</xsl:text><xsl:value-of select="$noun-property"/><xsl:text>"),
			  _("</xsl:text><xsl:value-of select="$noun-property"/><xsl:text> property"),
			  </xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>FO_TYPE_PROPERTY</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FO_TYPE_DATATYPE</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>,
			  </xsl:text><xsl:value-of select="$param-flags"/><xsl:text>));
</xsl:text>
  </xsl:template>

  <!-- property-to-set-property-case
       Generate the case statement to set a property of an object -->
  <xsl:template name="property-to-set-property-case">
    <xsl:param name="property"/>
    <xsl:param name="object"/>

    <xsl:variable name="is-datatype"
      select="document($codegen-info)/codegen-info/properties/property[@name = $property]/@is-datatype = 'yes'"/>

    <xsl:variable name="fo-or-context">
      <xsl:choose>
        <xsl:when test="$object = 'context'">context</xsl:when>
        <xsl:otherwise>fo</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="uppercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>    case PROP_</xsl:text><xsl:value-of select="$uppercase-property"/><xsl:text>:
      fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text><xsl:value-of select="$lowercase-property"/><xsl:text> (fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>, </xsl:text>
    <xsl:choose>
      <xsl:when test="$is-datatype">
        <xsl:text>FO_DATATYPE (g_value_get_object (value)));&#10;</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>g_value_get_object (value));&#10;</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>      break;
</xsl:text>
    <!-- End of generated text -->
</xsl:template>

  <!-- property-to-get-property-case
       Generate the case statement to set a property of an object -->
  <xsl:template name="property-to-get-property-case">
    <xsl:param name="property"/>
    <xsl:param name="object"/>

    <xsl:variable name="fo-or-context">
      <xsl:choose>
        <xsl:when test="$object = 'context'">context</xsl:when>
        <xsl:otherwise>fo</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="uppercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>    case PROP_</xsl:text><xsl:value-of select="$uppercase-property"/><xsl:text>:
      g_value_set_object (value, G_OBJECT (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_</xsl:text><xsl:value-of select="$lowercase-property"/><xsl:text> (fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>)));
      break;
</xsl:text>
    <!-- End of generated text -->
</xsl:template>

  <!-- property-to-get-set-functions
       Generate the functions to get and set a property of an object -->
  <xsl:template name="property-to-get-set-functions">
    <xsl:param name="property"/>
    <xsl:param name="property-abbrev"/>
    <xsl:param name="object"/>
    <xsl:param name="specialise-property-type" select="false()"/>

    <xsl:variable name="is-datatype"
      select="document($codegen-info)/codegen-info/properties/property[@name = $property]/@is-datatype = 'yes'"/>

    <xsl:variable name="fo-or-context">
      <xsl:choose>
        <xsl:when test="$object = 'context'">context</xsl:when>
        <xsl:otherwise>fo</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="fo-or-context-object">
      <xsl:text>Fo</xsl:text>
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$fo-or-context"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="use-property">
      <xsl:choose>
        <xsl:when test="$property-abbrev">
          <xsl:value-of select="$property-abbrev"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$property"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="lowercase-use-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$use-property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="hyphen-lowercase-property">
      <xsl:call-template name="to-lower">
        <xsl:with-param name="string" select="$property"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="uppercase-use-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$use-property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="camelcase-use-property">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$use-property"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="uppercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="camelcase-object">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$object"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <!-- _get_ -->
    <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>:
 * @fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>: The @</xsl:text><xsl:value-of select="$fo-or-context-object"/><xsl:text> object.
 * 
 * Gets the "</xsl:text><xsl:value-of select="$property"/><xsl:text>" property of @fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>.
 *
 * Return value: The "</xsl:text><xsl:value-of select="$property"/><xsl:text>" property value.
**/
</xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>FoProperty</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoDatatype</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> *
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text> (</xsl:text><xsl:value-of select="$fo-or-context-object"/><xsl:text> *fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>)
{
</xsl:text>
  <xsl:if test="$object != 'context'">
    <xsl:text>  Fo</xsl:text>
    <xsl:value-of select="$camelcase-object"/>
    <xsl:text> *fo_</xsl:text>
    <xsl:value-of select="$lowercase-object"/>
    <xsl:text> = (Fo</xsl:text>
    <xsl:value-of select="$camelcase-object"/>
    <xsl:text> *) fo_fo;&#10;&#10;</xsl:text>
  </xsl:if>

  <xsl:text>  g_return_val_if_fail (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text> != NULL, NULL);
  g_return_val_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>), NULL);

  return fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>-></xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>;
}
</xsl:text>

    <!-- _set_ -->
    <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>:
 * @fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>: The #</xsl:text><xsl:value-of select="$fo-or-context-object"/><xsl:text> object.
 * @new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>: The new "</xsl:text><xsl:value-of select="$property"/><xsl:text>" property value.
 * 
 * Sets the "</xsl:text><xsl:value-of select="$property"/><xsl:text>" property of @fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text> to @new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text> (</xsl:text><xsl:value-of select="$fo-or-context-object"/><xsl:text> *fo_</xsl:text><xsl:value-of select="$fo-or-context"/><xsl:text>,
		         </xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>FoProperty</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoDatatype</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> *new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>)
{
</xsl:text>

  <xsl:if test="$object != 'context'">
    <xsl:text>  Fo</xsl:text>
    <xsl:value-of select="$camelcase-object"/>
    <xsl:text> *fo_</xsl:text>
    <xsl:value-of select="$lowercase-object"/>
    <xsl:text> = (Fo</xsl:text>
    <xsl:value-of select="$camelcase-object"/>
    <xsl:text> *) fo_fo;&#10;&#10;</xsl:text>
  </xsl:if>

  <xsl:text>  g_return_if_fail (</xsl:text>fo_<xsl:value-of select="$lowercase-object"/><xsl:text> != NULL);
  g_return_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>));
  g_return_if_fail ((new_</xsl:text>
    <xsl:value-of select="$lowercase-use-property"/>
    <xsl:text> == NULL) ||&#10;		    FO_IS_</xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>PROPERTY_</xsl:text>
        <xsl:value-of select="$uppercase-use-property"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>DATATYPE</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> (new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>));

  if (new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text> != NULL)
    {
      g_object_ref (new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>);
    }
  if (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>-></xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text> != NULL)
    {
      g_object_unref (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>-></xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>);
    }
  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>-></xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text> = </xsl:text>
    <xsl:choose>
      <xsl:when test="not($is-datatype)">
        <xsl:text>new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>;</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FO_DATATYPE (new_</xsl:text><xsl:value-of select="$lowercase-use-property"/><xsl:text>);</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>&#10;  /*g_object_notify (G_OBJECT (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>), "</xsl:text><xsl:value-of select="$hyphen-lowercase-property"/><xsl:text>");*/
}
</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- debug-dump-properties-function -->
  <xsl:template name="debug-dump-properties-function">
    <xsl:param name="object"/>
    <xsl:param name="properties"/>

    <xsl:variable name="uppercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="camelcase-object">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$object"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="lowercase-object-spaces"
      select="substring($spaces, 1, string-length($lowercase-object))"/>

    <xsl:text>/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_debug_dump_properties:
</xsl:text>
    <xsl:choose>
      <xsl:when test="$object = 'context'">
        <xsl:text> * @fo_context: The #FoContext object.</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text> * @fo:    The #FoFo object.</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_debug_dump_properties (</xsl:text>
    <xsl:choose>
      <xsl:when test="$object = 'context'">
        <xsl:text>FoContext *fo_context</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>FoFo *fo</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>,&#10;                           </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
    <xsl:text>gint  depth)
{
</xsl:text>

<xsl:if test="not($object = 'context')">
  <xsl:text>  Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> *fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>;
</xsl:text>  
</xsl:if>
<xsl:text>
  g_return_if_fail (fo</xsl:text>

  <xsl:if test="$object = 'context'">
    <xsl:text>_context</xsl:text>
  </xsl:if>
  <xsl:text> != NULL);
  g_return_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (</xsl:text>

  <xsl:choose>
    <xsl:when test="$object = 'context'">
      <xsl:text>fo_context</xsl:text>
    </xsl:when>
    <xsl:otherwise>
      <xsl:text>fo</xsl:text>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:text>));
</xsl:text>

<xsl:if test="not($object = 'context')">
  <xsl:text>
  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text> = FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo);
</xsl:text>
</xsl:if>

<xsl:text>&#10;</xsl:text>

<xsl:choose>
  <xsl:when test="$properties">
    <xsl:for-each select="$properties">
      <xsl:sort/>
      <xsl:variable name="property" select="."/>

      <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
      <xsl:value-of select="$lowercase-object"/>
      <xsl:text>-></xsl:text>
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string" select="."/>
      </xsl:call-template>
      <xsl:text>, depth);&#10;</xsl:text>

      <xsl:choose>
        <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
          <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
          <xsl:value-of select="$lowercase-object"/>
          <xsl:text>-></xsl:text>
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string" select="concat(., '-within-column')"/>
          </xsl:call-template>
          <xsl:text>, depth);&#10;</xsl:text>
          <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
          <xsl:value-of select="$lowercase-object"/>
          <xsl:text>-></xsl:text>
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string" select="concat(., '-within-line')"/>
          </xsl:call-template>
          <xsl:text>, depth);&#10;</xsl:text>
          <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
          <xsl:value-of select="$lowercase-object"/>
          <xsl:text>-></xsl:text>
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string" select="concat(., '-within-page')"/>
          </xsl:call-template>
          <xsl:text>, depth);&#10;</xsl:text>
        </xsl:when>
        <xsl:when test="$object = 'context' and $allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
          <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
          <xsl:value-of select="$lowercase-object"/>
          <xsl:text>-></xsl:text>
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string" select="concat(., '-minimum')"/>
          </xsl:call-template>
          <xsl:text>, depth);&#10;</xsl:text>
          <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
          <xsl:value-of select="$lowercase-object"/>
          <xsl:text>-></xsl:text>
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string" select="concat(., '-optimum')"/>
          </xsl:call-template>
          <xsl:text>, depth);&#10;</xsl:text>
          <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
          <xsl:value-of select="$lowercase-object"/>
          <xsl:text>-></xsl:text>
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string" select="concat(., '-maximum')"/>
          </xsl:call-template>
          <xsl:text>, depth);&#10;</xsl:text>
          <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
            <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
            <xsl:value-of select="$lowercase-object"/>
            <xsl:text>-></xsl:text>
            <xsl:call-template name="hyphen-colon-to-underscore">
              <xsl:with-param name="string" select="concat(., '-precedence')"/>
            </xsl:call-template>
            <xsl:text>, depth);&#10;</xsl:text>
            <xsl:text>  fo_object_debug_dump (fo_</xsl:text>
            <xsl:value-of select="$lowercase-object"/>
            <xsl:text>-></xsl:text>
            <xsl:call-template name="hyphen-colon-to-underscore">
              <xsl:with-param name="string" select="concat(., '-condity')"/>
            </xsl:call-template>
            <xsl:text>, depth);&#10;</xsl:text>
          </xsl:if>
        </xsl:when>
      </xsl:choose>
    </xsl:for-each>
  </xsl:when>
  <xsl:otherwise>
    <xsl:text>  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
         "(No properties)");&#10;</xsl:text>
  </xsl:otherwise>
</xsl:choose>

<xsl:if test="not($object = 'context')">
  <xsl:text>
  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
</xsl:text>
</xsl:if>
<xsl:text>}
</xsl:text>

  </xsl:template>

</xsl:stylesheet>
