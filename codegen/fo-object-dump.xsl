<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- fo-object-dump.xsl -->
<!-- Read the XSL spec and dump .c and .h files for GLib gobjects for
     each formatting object. -->
<!-- Requires Saxon or Saxon lookalike since it uses Saxon extension
     element for creating multiple output files. -->
<!-- If a named template isn't in this file, see conversion-lib.xsl. -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2007 Menteith Consulting Ltd -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon"
                version="1.0">

  <xsl:output method="text"/>

  <xsl:include href="conversion-lib.xsl"/>

  <xsl:param name="codegen-info"/>
  <xsl:param name="debug"/>

  <xsl:key name="property" match="div3" use="@id"/>
  <xsl:key name="property-group" match="/spec/body/div1[@id='pr-section']/div2[@id]" use="@id"/>
  <xsl:key name="property-table" match="/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']/table/tbody/tr/td[@class = 'propindex']/specref/@ref" use="."/>

  <xsl:variable name="allowed-properties"
    select="document($codegen-info)/codegen-info/properties/property/@name"/>

  <xsl:variable name="allowed-fos"
    select="document($codegen-info)/codegen-info/fos/fo/@name"/>

  <xsl:variable name="stylesheet-name"
    select="substring-before(substring-after('$Id: fo-object-dump.xsl,v 1.13 2006/03/29 17:46:43 tonygraham Exp $', '&#x24;Id: '), ' &#x24;')"/>

  <!-- gobject-header
       Make a "fo-xxxx.h" file -->
  <xsl:template name="gobject-header">
    <xsl:param name="object"/>
    <xsl:param name="properties"/>
    <xsl:param name="uppercase-object"/>

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

    <xsl:variable name="noun-object">
      <xsl:call-template name="to-proper-noun">
        <xsl:with-param name="string">
          <xsl:call-template name="hyphen-colon-to-space">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <saxon:output href="./fo-{$object}.h"
      method="text">
  <xsl:text>/* Fo
 * fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>.h: '</xsl:text><xsl:value-of select="$object"/><xsl:text>' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_H__
#define __FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_H__

#include &lt;libfo/fo-utils.h>
#include &lt;fo/fo-fo.h>
</xsl:text>
<xsl:if test="$properties">
  <xsl:text>#include &lt;property/fo-property.h>&#10;</xsl:text>
</xsl:if>

<xsl:text>
G_BEGIN_DECLS
</xsl:text>

  <xsl:copy-of select="document($codegen-info)/codegen-info/fos/fo[@name = $object]/hdefines"/>

  <xsl:if test="document($codegen-info)/codegen-info/fos/fo[@name = $object]/errors">
    <xsl:variable
      name="errors"
      select="document($codegen-info)/codegen-info/fos/fo[@name = $object]/errors"/>

    <xsl:text>
#define FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_ERROR fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_error_quark ()

GQuark fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_error_quark (void);

typedef enum
{
  FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_ERROR_FAILED,          /* Generic error code */
  FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_ERROR_WARNING,         /* Non-fatal error */&#10;</xsl:text>
    <xsl:for-each select="$errors/error">
      <xsl:text>  FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_ERROR_</xsl:text>
      <xsl:value-of select="@code"/>
      <xsl:text>,&#10;</xsl:text>
    </xsl:for-each>
    <xsl:text>  FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_ERROR_LAST
} Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Error;

extern const char *fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_error_messages[FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_ERROR_LAST];
</xsl:text>
  </xsl:if>

<xsl:text>
/**
 * Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>:
 *
 * Instance of the '</xsl:text><xsl:value-of select="$object"/><xsl:text>' formatting object.
 **/
typedef struct _Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>      Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>;

/**
 * Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class:
 *
 * Class structure for the '</xsl:text><xsl:value-of select="$object"/><xsl:text>' formatting object.
 **/
typedef struct _Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class;

#define FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>              (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_type ())
#define FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>, Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>))
#define FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>, Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class))
#define FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>))
#define FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>))
#define FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>, Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class))


GType        fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_type (void) G_GNUC_CONST;
FoFo *       fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_new      (void);

</xsl:text>

<xsl:for-each select="$properties">
  <xsl:sort/>
  <xsl:variable name="property" select="."/>

  <xsl:call-template name="property-to-get-set-prototypes">
    <xsl:with-param name="property" select="."/>
    <xsl:with-param name="object" select="$object"/>
  </xsl:call-template>

  <xsl:choose>
    <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
      <xsl:call-template name="property-to-get-set-prototypes">
        <xsl:with-param name="property" select="concat(., '-within-column')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-prototypes">
        <xsl:with-param name="property" select="concat(., '-within-line')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-prototypes">
        <xsl:with-param name="property" select="concat(., '-within-page')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
    </xsl:when>
    <!--
    <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
      <xsl:call-template name="property-to-get-set-prototypes">
        <xsl:with-param name="property" select="concat(., '-minimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-prototypes">
        <xsl:with-param name="property" select="concat(., '-optimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-prototypes">
        <xsl:with-param name="property" select="concat(., '-maximum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-precedence')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
      </xsl:if>
    </xsl:when>
    -->
  </xsl:choose>
</xsl:for-each>

<xsl:text>
G_END_DECLS

#endif /* !__FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_H__ */
</xsl:text>
</saxon:output>
  </xsl:template>

  <!-- gobject-private-header
       Make a "fo-xxxx-private.h" file -->
  <xsl:template name="gobject-private-header">
    <xsl:param name="object"/>
    <xsl:param name="properties"/>
    <xsl:param name="uppercase-object"/>

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

    <xsl:variable name="noun-object">
      <xsl:call-template name="to-proper-noun">
        <xsl:with-param name="string">
          <xsl:call-template name="hyphen-colon-to-space">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Parent GObject type of the FO
    -->
    <xsl:variable name="parent-type">
      <xsl:choose>
        <xsl:when test="$allowed-fos[. = $object][../@parent-type]">
          <xsl:value-of select="$allowed-fos[. = $object]/../@parent-type"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>fo</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="camelcase-parent-type">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$parent-type"/>
      </xsl:call-template>
    </xsl:variable>

    <saxon:output href="./fo-{$object}-private.h"
      method="text">
      <xsl:text>/* Fo
 * fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>-private.h: Structures private to '</xsl:text><xsl:value-of select="$object"/><xsl:text>' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_PRIVATE_H__
#define __FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_PRIVATE_H__

#include "fo/fo-</xsl:text><xsl:value-of select="$parent-type"/><xsl:text>-private.h"
#include "fo/fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>.h"

G_BEGIN_DECLS

struct _Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>
{
  Fo</xsl:text><xsl:value-of select="$camelcase-parent-type"/><xsl:text> parent_instance;
</xsl:text>

  <xsl:if test="$properties">
    <xsl:text>&#10;</xsl:text>
  </xsl:if>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-instance-variable">
      <xsl:with-param name="property" select="."/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
        </xsl:call-template>
      </xsl:when>
      <!--
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-instance-variable">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-instance-variable">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      -->
    </xsl:choose>
  </xsl:for-each>

<xsl:text>};

struct _Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class
{
  Fo</xsl:text><xsl:value-of select="$camelcase-parent-type"/><xsl:text>Class parent_class;
};

G_END_DECLS

#endif /* !__FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text>_PRIVATE_H__ */
</xsl:text>
</saxon:output>
  </xsl:template>

  <!-- property-to-set-from-context
       Generate the calls to set the properties of the current
       object from the context -->
  <xsl:template name="property-to-set-from-context">
    <xsl:param name="property"/>
    <xsl:param name="object"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
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

    <xsl:variable name="uppercase-object">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text><xsl:value-of select="$lowercase-property"/><xsl:text> (fo,
			  fo_context_get_</xsl:text><xsl:value-of select="$lowercase-property"/><xsl:text> (context));
</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- gobject-c-file
       Make a "fo-xxxx.c" file -->
  <xsl:template name="gobject-c-file">
    <xsl:param name="object"/>
    <xsl:param name="properties"/>
    <xsl:param name="uppercase-object"/>

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

    <xsl:variable name="camelcase-object">
      <xsl:call-template name="to-camel">
        <xsl:with-param name="string" select="$object"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="noun-object">
      <xsl:call-template name="to-proper-noun">
        <xsl:with-param name="string">
          <xsl:call-template name="hyphen-colon-to-space">
            <xsl:with-param name="string" select="$object"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Parent GObject type of the FO
    -->
    <xsl:variable name="uppercase-parent-type">
      <xsl:choose>
        <xsl:when test="$allowed-fos[. = $object][../@parent-type]">
          <xsl:call-template name="hyphen-colon-to-underscore">
            <xsl:with-param name="string">
              <xsl:call-template name="to-upper">
                <xsl:with-param name="string" select="$allowed-fos[. = $object]/../@parent-type"/>
              </xsl:call-template>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>FO</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!-- Whether or not the FO generates an area.  Determined from the
         dump info.
    -->
    <xsl:variable name="generates-area"
      select="$allowed-fos[. = $object][../@area = 'yes']"/>

    <!-- Whether or not the FO should implement the 'fo-table-border-fo'
         GObject interface.  Determined by whether one of the
         properties in that interface is a property of the FO.
    -->
    <xsl:variable name="fo-table-border-fo-iface"
      select="$properties[. = 'border-after-precedence']"/>

    <!-- Whether or not the FO should implement the 'fo-inline-fo'
         GObject interface.  Determined from the dump info.
    -->
    <xsl:variable name="fo-inline-fo-iface"
      select="$allowed-fos[. = $object][../@inline = 'yes']"/>

    <!-- Whether or not the FO should implement the 'fo-block-fo'
         GObject interface.  Determined from the dump info.
    -->
    <xsl:variable name="fo-block-fo-iface"
      select="$allowed-fos[. = $object][../@block = 'yes']"/>

    <!-- 'validate' function, if any.
    -->
    <xsl:variable name="validate" select="$allowed-fos[. = $object]/../@validate"/>

    <!-- 'validate-content' function, if any.
    -->
    <xsl:variable name="validate-content" select="$allowed-fos[. = $object]/../@validate-content"/>

    <saxon:output href="./fo-{$object}.c"
      method="text">
    <!-- Start of generated text -->
  <xsl:text>/* Fo
 * fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>.c: '</xsl:text><xsl:value-of select="$object"/><xsl:text>' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

</xsl:text>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>#include "fo/fo-inline-fo.h"&#10;</xsl:text>
</xsl:if>

<xsl:if test="$fo-block-fo-iface">
  <xsl:text>#include "fo/fo-block-fo-private.h"&#10;</xsl:text>
</xsl:if>

<xsl:if test="$fo-table-border-fo-iface">
  <xsl:text>#include "fo/fo-table-border-fo-private.h"&#10;</xsl:text>
</xsl:if>

<xsl:text>#include "fo/fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>-private.h"&#10;</xsl:text>

<xsl:if test="$generates-area">
  <xsl:text>#include "fo/fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>-area.h"&#10;</xsl:text>
</xsl:if>

<xsl:if test="$properties[. = 'height']">
  <xsl:text>#include "fo-context-util.h"&#10;</xsl:text>
</xsl:if>

<xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:text>#include "property/fo-property-</xsl:text>
    <xsl:value-of select="."/>
    <xsl:text>.h"&#10;</xsl:text>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">

        <xsl:text>#include "property/fo-property-</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>-within-column.h"&#10;</xsl:text>

        <xsl:text>#include "property/fo-property-</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>-within-line.h"&#10;</xsl:text>

        <xsl:text>#include "property/fo-property-</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>-within-page.h"&#10;</xsl:text>
      </xsl:when>

      <!--
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">

        <xsl:text>#include "fo-property-</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>-minimum.h"&#10;</xsl:text>

        <xsl:text>#include "fo-property-</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>-optimum.h"&#10;</xsl:text>

        <xsl:text>#include "fo-property-</xsl:text>
        <xsl:value-of select="."/>
        <xsl:text>-maximum.h"&#10;</xsl:text>

        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']">

          <xsl:text>#include "fo-property-</xsl:text>
          <xsl:value-of select="."/>
          <xsl:text>-precedence.h"&#10;</xsl:text>

          <xsl:text>#include "fo-property-</xsl:text>
          <xsl:value-of select="."/>
          <xsl:text>-conditionality.h"&#10;</xsl:text>

        </xsl:if>
      </xsl:when>
      -->
    </xsl:choose>
  </xsl:for-each>

  <xsl:copy-of select="document($codegen-info)/codegen-info/fos/fo[@name = $object]/defines"/>

  <xsl:if test="document($codegen-info)/codegen-info/fos/fo[@name = $object]/errors">
    <xsl:variable
      name="errors"
      select="document($codegen-info)/codegen-info/fos/fo[@name = $object]/errors"/>

    <xsl:text>
const char *fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_error_messages[] = {
  N_("Failed"),
  N_("Warning")</xsl:text>
    <xsl:for-each select="$errors/error">
      <xsl:text>,&#10;  N_("</xsl:text>
      <xsl:value-of select="@message"/>
      <xsl:text>")</xsl:text>
    </xsl:for-each>
    <xsl:text>&#10;};
</xsl:text>
  </xsl:if>

  <xsl:if test="$properties">
    <xsl:text>
enum {
  PROP_0,&#10;</xsl:text>

      <xsl:for-each select="$properties">
        <xsl:sort/>
        <xsl:variable name="property" select="."/>

        <xsl:call-template name="property-to-prop-enum">
          <xsl:with-param name="property" select="."/>
        </xsl:call-template>

        <xsl:choose>
          <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
            <xsl:call-template name="property-to-prop-enum">
              <xsl:with-param name="property" select="concat(., '-within-column')"/>
            </xsl:call-template>
            <xsl:call-template name="property-to-prop-enum">
              <xsl:with-param name="property" select="concat(., '-within-line')"/>
            </xsl:call-template>
            <xsl:call-template name="property-to-prop-enum">
              <xsl:with-param name="property" select="concat(., '-within-page')"/>
            </xsl:call-template>
          </xsl:when>
          <!--
               <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
                 <xsl:call-template name="property-to-prop-enum">
                   <xsl:with-param name="property" select="concat(., '-minimum')"/>
                 </xsl:call-template>
                 <xsl:call-template name="property-to-prop-enum">
                   <xsl:with-param name="property" select="concat(., '-optimum')"/>
                 </xsl:call-template>
                 <xsl:call-template name="property-to-prop-enum">
                   <xsl:with-param name="property" select="concat(., '-maximum')"/>
                 </xsl:call-template>
                 <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
                   >
                   <xsl:call-template name="property-to-prop-enum">
                     <xsl:with-param name="property" select="concat(., '-precedence')"/>
                   </xsl:call-template>
                   <xsl:call-template name="property-to-prop-enum">
                     <xsl:with-param name="property" select="concat(., '-condity')"/>
                   </xsl:call-template>
                 </xsl:if>
               </xsl:when>
               -->
      </xsl:choose>
    </xsl:for-each>

    <xsl:text>};&#10;</xsl:text>
  </xsl:if>

  <xsl:text>
static void fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_class_init  (Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class *klass);
</xsl:text>

<xsl:if test="$fo-block-fo-iface">
  <xsl:text>static void fo_</xsl:text>
  <xsl:value-of select="$lowercase-object"/>
  <xsl:text>_block_fo_init (FoBlockFoIface *iface);&#10;</xsl:text>
</xsl:if>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>static void fo_</xsl:text>
  <xsl:value-of select="$lowercase-object"/>
  <xsl:text>_inline_fo_init (FoInlineFoIface *iface);&#10;</xsl:text>
</xsl:if>

<xsl:if test="$fo-table-border-fo-iface">
  <xsl:text>static void fo_</xsl:text>
  <xsl:value-of select="$lowercase-object"/>
  <xsl:text>_table_border_fo_init (FoTableBorderFoIface *iface);&#10;</xsl:text>
</xsl:if>

<xsl:if test="$properties">
<xsl:text>static void fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_get_property (GObject      *object,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               guint         prop_id,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               GValue       *value,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               GParamSpec   *pspec);
static void fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_set_property (GObject      *object,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               guint         prop_id,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               const GValue *value,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               GParamSpec   *pspec);
</xsl:text>
</xsl:if>

<xsl:text>static void fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_finalize    (GObject           *object);
</xsl:text>
<xsl:if test="not($validate-content)">
<xsl:text>static gboolean fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_validate_content (FoFo    *fo,
                   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>                   GError **error);
</xsl:text>
</xsl:if>
<xsl:if test="not($validate)">
<xsl:text>static void fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_validate (FoFo      *fo,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>           FoContext *current_context,
               </xsl:text>
               <xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>           FoContext *parent_context,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>           GError   **error);
</xsl:text></xsl:if>
<xsl:text>static void fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_update_from_context (FoFo      *fo,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>                      FoContext *context);
static void fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_debug_dump_properties (FoFo *fo,
               </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>                        gint  depth);
</xsl:text>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>static void fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_text_attr_list (FoFo *fo_inline_fo,
				       FoDoc   *fo_doc,
					     GString *text,
					     GList **attr_glist,
					     guint debug_level);
</xsl:text>
</xsl:if>

<xsl:text>
static gpointer parent_class;

/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_type:
 * 
 * Register the #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> object type.
 * 
 * Return value: #GType value of the #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> object type.
 **/
GType
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

</xsl:text>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_inline_fo_init, /* interface_init */
        NULL,
        NULL
      };

</xsl:text>
</xsl:if>

<xsl:if test="$fo-block-fo-iface">
  <xsl:text>      static const GInterfaceInfo fo_block_fo_info =
      {
	(GInterfaceInitFunc) fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_block_fo_init,	 /* interface_init */
        NULL,
        NULL
      };

</xsl:text>
</xsl:if>

<xsl:if test="$fo-table-border-fo-iface">
  <xsl:text>      static const GInterfaceInfo fo_table_border_fo_info =
      {
	(GInterfaceInitFunc) fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_table_border_fo_init, /* interface_init */
        NULL,
        NULL
      };

</xsl:text>
</xsl:if>

<xsl:text>      object_type = g_type_register_static (FO_TYPE_</xsl:text><xsl:value-of select="$uppercase-parent-type"/><xsl:text>,
                                            "</xsl:text><xsl:value-of select="$object"/><xsl:text>",
                                            &amp;object_info, 0);
</xsl:text>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &amp;fo_inline_fo_info);
</xsl:text>
</xsl:if>

<xsl:if test="$fo-block-fo-iface">
  <xsl:text>      g_type_add_interface_static (object_type,
                                   FO_TYPE_BLOCK_FO,
                                   &amp;fo_block_fo_info);
</xsl:text>
</xsl:if>

<xsl:if test="$fo-table-border-fo-iface">
  <xsl:text>      g_type_add_interface_static (object_type,
                                   FO_TYPE_TABLE_BORDER_FO,
                                   &amp;fo_table_border_fo_info);
</xsl:text>
</xsl:if>

<xsl:text>    }

  return object_type;
}

/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_class_init:
 * @klass: #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class object to initialise.
 * 
 * Implements #GClassInitFunc for #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_class_init (Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>Class *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_finalize;
</xsl:text>

<xsl:if test="$properties">
  <xsl:text>
  object_class->get_property = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_property;
  object_class->set_property = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_property;
</xsl:text>
</xsl:if>

<xsl:text>
  fofo_class->validate_content =
    </xsl:text>
<xsl:choose>
  <xsl:when test="$validate-content">
    <xsl:value-of select="$validate-content"/>
  </xsl:when>
  <xsl:otherwise>
    <xsl:text>fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_validate_content</xsl:text>
  </xsl:otherwise>
</xsl:choose>
<xsl:text>;
  fofo_class->validate2 =
    </xsl:text>
<xsl:choose>
  <xsl:when test="$validate">
    <xsl:value-of select="$validate"/>
  </xsl:when>
  <xsl:otherwise>
    <xsl:text>fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_validate</xsl:text>
  </xsl:otherwise>
</xsl:choose>
<xsl:text>;
  fofo_class->update_from_context = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_update_from_context;
  fofo_class->debug_dump_properties = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_debug_dump_properties;
</xsl:text>

<xsl:if test="$allowed-fos[. = $object][../@mixed = 'yes']">
  <xsl:text>  fofo_class->allow_mixed_content = TRUE;&#10;</xsl:text>
</xsl:if>

<xsl:if test="$allowed-fos[. = $object][../@reference = 'yes']">
  <xsl:text>  fofo_class->generate_reference_area = TRUE;&#10;</xsl:text>
</xsl:if>

<xsl:if test="$generates-area">
  <xsl:text>  fofo_class->area_new2 =
    fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_area_new2;&#10;</xsl:text>
</xsl:if>

<xsl:if test="$properties">
<xsl:text>&#10;</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-install-property">
      <xsl:with-param name="property" select="."/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
        </xsl:call-template>
      </xsl:when>
      <!--
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-install-property">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-install-property">
            <xsl:with-param name="property"
              select="concat(., '-conditionality')"/>
            <xsl:with-param name="property-abbrev"
              select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      -->
    </xsl:choose>
  </xsl:for-each>
</xsl:if>
  <xsl:text>}

</xsl:text>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_inline_fo_init:
 * @iface: #FoInlineFoIFace structure for this class.
 * 
 * Initialize #FoInlineFoIface interface for this class.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_text_attr_list;
}

</xsl:text>
</xsl:if>

<xsl:if test="$fo-block-fo-iface">
  <xsl:text>/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_block_fo_init:
 * @iface: #FoBlockFoIFace structure for this class.
 * 
 * Initialize #FoBlockFoIface interface for this class.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_block_fo_init (FoBlockFoIface *iface)
{
  iface->get_background_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_background_color;
  iface->get_border_after_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_color;
  iface->get_border_after_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_style;
  iface->get_border_after_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_width;
  iface->get_border_before_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_color;
  iface->get_border_before_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_style;
  iface->get_border_before_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_width;
  iface->get_border_end_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_color;
  iface->get_border_end_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_style;
  iface->get_border_end_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_width;
  iface->get_border_start_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_color;
  iface->get_border_start_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_style;
  iface->get_border_start_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_width;
  iface->get_keep_with_previous = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_keep_with_previous;
  iface->get_keep_with_next = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_keep_with_next;
  iface->get_keep_together = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_keep_together;
  iface->get_padding_after = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_padding_after;
  iface->get_padding_before = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_padding_before;
  iface->get_padding_end = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_padding_end;
  iface->get_padding_start = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_padding_start;
  iface->get_space_before = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_space_before;
  iface->get_space_after = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_space_after;
  iface->get_start_indent = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_start_indent;
  iface->get_end_indent = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_end_indent;
}

</xsl:text>
</xsl:if>

<xsl:if test="$fo-table-border-fo-iface">
  <xsl:text>/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_table_border_fo_init:
 * @iface: #FoTableBorderFoIFace structure for this class.
 * 
 * Initialize #FoTableBorderFoIface interface for this class.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_table_border_fo_init (FoTableBorderFoIface *iface)
{
  iface->get_background_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_background_color;
  iface->get_border_after_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_color;
  iface->get_border_after_precedence = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_precedence;
  iface->get_border_after_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_style;
  iface->get_border_after_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_after_width;
  iface->get_border_before_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_color;
  iface->get_border_before_precedence = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_precedence;
  iface->get_border_before_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_style;
  iface->get_border_before_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_before_width;
  iface->get_border_end_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_color;
  iface->get_border_end_precedence = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_precedence;
  iface->get_border_end_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_style;
  iface->get_border_end_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_end_width;
  iface->get_border_start_color = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_color;
  iface->get_border_start_precedence = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_precedence;
  iface->get_border_start_style = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_style;
  iface->get_border_start_width = fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_border_start_width;
}

</xsl:text>
</xsl:if>

<xsl:text>/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_finalize:
 * @object: #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
</xsl:text>
<xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <xsl:text>  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text> (fo, NULL);&#10;</xsl:text>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">

        <xsl:text>  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text>_within_column (fo, NULL);&#10;</xsl:text>
        <xsl:text>  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text>_within_line (fo, NULL);&#10;</xsl:text>
        <xsl:text>  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_</xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text>_within_page (fo, NULL);&#10;</xsl:text>
      </xsl:when>

      <!--
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">

       And for spaces and length ranges
            </xsl:when>
      -->
    </xsl:choose>
  </xsl:for-each>
<xsl:text>
  G_OBJECT_CLASS (parent_class)->finalize (object);
}
</xsl:text>

<xsl:if test="$properties">
  <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>.
 **/
void
fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_get_property (GObject    *object,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               guint       prop_id,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               GValue     *value,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
</xsl:text>
<xsl:for-each select="$properties">
  <xsl:sort/>
  <xsl:variable name="property" select="."/>

  <xsl:call-template name="property-to-get-property-case">
    <xsl:with-param name="property" select="."/>
    <xsl:with-param name="object" select="$object"/>
  </xsl:call-template>

  <xsl:choose>
    <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
      <xsl:call-template name="property-to-get-property-case">
        <xsl:with-param name="property" select="concat(., '-within-column')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-property-case">
        <xsl:with-param name="property" select="concat(., '-within-line')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-property-case">
        <xsl:with-param name="property" select="concat(., '-within-page')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
    </xsl:when>
    <!--
    <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
      <xsl:call-template name="property-to-get-property-case">
        <xsl:with-param name="property" select="concat(., '-minimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-property-case">
        <xsl:with-param name="property" select="concat(., '-optimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-property-case">
        <xsl:with-param name="property" select="concat(., '-maximum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-precedence')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
      </xsl:if>
    </xsl:when>
    -->
  </xsl:choose>
</xsl:for-each>
<xsl:text>    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>.
 **/
void
fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_set_property (GObject      *object,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               guint         prop_id,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               const GValue *value,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
</xsl:text>
<xsl:for-each select="$properties">
  <xsl:sort/>
  <xsl:variable name="property" select="."/>

  <xsl:call-template name="property-to-set-property-case">
    <xsl:with-param name="property" select="."/>
    <xsl:with-param name="object" select="$object"/>
  </xsl:call-template>

  <xsl:choose>
    <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
      <xsl:call-template name="property-to-set-property-case">
        <xsl:with-param name="property" select="concat(., '-within-column')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-set-property-case">
        <xsl:with-param name="property" select="concat(., '-within-line')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-set-property-case">
        <xsl:with-param name="property" select="concat(., '-within-page')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
    </xsl:when>
    <!--
    <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
      <xsl:call-template name="property-to-set-property-case">
        <xsl:with-param name="property" select="concat(., '-minimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-set-property-case">
        <xsl:with-param name="property" select="concat(., '-optimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-set-property-case">
        <xsl:with-param name="property" select="concat(., '-maximum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-precedence')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
      </xsl:if>
    </xsl:when>
    -->
  </xsl:choose>
</xsl:for-each>
<xsl:text>    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
</xsl:text>
</xsl:if>

<xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_new:
 * 
 * Creates a new #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> initialized to default value.
 * 
 * Return value: the new #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text>.
 **/
FoFo*
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_new (void)
{
  return FO_FO (g_object_new (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_type (),
                              NULL));
}
</xsl:text>

  <xsl:if test="document($codegen-info)/codegen-info/fos/fo[@name = $object]/errors">
    <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_error_quark:
 * 
 * Create and return the #GQuark for use as the error domain for
 * </xsl:text><xsl:value-of select="$object"/><xsl:text>.
 * 
 * Return value: Error domain #GQuark.
 **/
GQuark
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("fo-</xsl:text><xsl:value-of select="$object"/><xsl:text>-error");
  return quark;
}
</xsl:text>
  </xsl:if>

  <xsl:if test="not($validate-content)">
  <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_validate_content:
 * @fo:    #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_validate_content (FoFo    *fo,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>                   GError **error)
{
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  return FALSE;

/*
error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (fo));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
*/
}
</xsl:text>
</xsl:if>

<xsl:if test="not($validate)">
  <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_validate:
 * @fo:              #Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_validate (FoFo      *fo,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>           FoContext *current_context,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>           FoContext *parent_context,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>           GError   **error)
{
  Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> *fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text> = FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo);

</xsl:text>

  <xsl:if test="$properties[. = 'dominant-baseline']">
    <xsl:text>  fo_context_util_dominant_baseline_resolve (current_context, parent_context);&#10;</xsl:text>
  </xsl:if>

  <xsl:if test="$properties[. = 'height']">
    <xsl:text>  fo_context_util_height_width_resolve (current_context, parent_context);&#10;</xsl:text>
  </xsl:if>

  <xsl:text>  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
</xsl:text>

  <xsl:if test="$properties[. = 'line-height']">
    <xsl:text>  fo_</xsl:text>
    <xsl:value-of select="$lowercase-object"/>
    <xsl:text>_set_line_height (fo,
    fo_property_line_height_resolve (fo_</xsl:text>
    <xsl:value-of select="$lowercase-object"/>
    <xsl:text>->line_height,
				     fo_</xsl:text>
    <xsl:value-of select="$lowercase-object"/>
    <xsl:text>->font_size));&#10;</xsl:text>    
  </xsl:if>

  <xsl:if test="$properties[. = 'id']">
    <xsl:text>  fo_fo_register_id (fo,
                     fo_property_get_value (fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>->id));&#10;</xsl:text>
  </xsl:if>

  <xsl:text>}
</xsl:text>
</xsl:if>

<xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_</xsl:text>
<xsl:value-of select="$lowercase-object"/>
<xsl:text>_update_from_context (FoFo      *fo,
   </xsl:text>
<xsl:value-of select="$lowercase-object-spaces"/>
<xsl:text>                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

</xsl:text>

<xsl:for-each select="$properties">
  <xsl:sort/>
  <xsl:variable name="property" select="."/>

  <xsl:call-template name="property-to-set-from-context">
    <xsl:with-param name="property" select="."/>
    <xsl:with-param name="object" select="$object"/>
  </xsl:call-template>

  <xsl:choose>
    <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
      <xsl:call-template name="property-to-set-from-context">
        <xsl:with-param name="property" select="concat(., '-within-column')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-set-from-context">
        <xsl:with-param name="property" select="concat(., '-within-line')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-set-from-context">
        <xsl:with-param name="property" select="concat(., '-within-page')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
    </xsl:when>
  </xsl:choose>
</xsl:for-each>
<xsl:text>}

</xsl:text>

<xsl:call-template name="debug-dump-properties-function">
  <xsl:with-param name="properties" select="$properties"/>
  <xsl:with-param name="object" select="$object"/>
</xsl:call-template>

<xsl:if test="$fo-inline-fo-iface">
  <xsl:text>
/**
 * fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 **/
void
fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>_get_text_attr_list (FoFo *fo_inline_fo,
				 FoDoc   *fo_doc,
				 GString *text,
				 GList **attr_glist,
				 guint debug_level)
{
  FoNode *fo_child_node;
  Fo</xsl:text><xsl:value-of select="$camelcase-object"/><xsl:text> *fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text>;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo_inline_fo));

  fo_</xsl:text><xsl:value-of select="$lowercase-object"/><xsl:text> = FO_</xsl:text><xsl:value-of select="$uppercase-object"/><xsl:text> (fo_inline_fo);

  start_index = text->len;

  fo_child_node = fo_node_first_child (FO_NODE (fo_inline_fo));

  while (fo_child_node)
    {
      fo_inline_fo_get_text_attr_list (FO_FO (fo_child_node),
				       text,
				       &amp;my_attr_glist,
				       debug_level);
      fo_child_node = fo_node_next_sibling (fo_child_node);
    }

  end_index = text->len;

  if (start_index != end_index)
    {
      PangoAttribute *pango_attr;

    }

  *attr_glist = g_list_concat (my_attr_glist,
			       *attr_glist);
}
</xsl:text>
</xsl:if>

<xsl:for-each select="$properties">
  <xsl:sort/>
  <xsl:variable name="property" select="."/>

  <xsl:call-template name="property-to-get-set-functions">
    <xsl:with-param name="property" select="."/>
    <xsl:with-param name="object" select="$object"/>
  </xsl:call-template>

  <xsl:choose>
    <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
      <xsl:call-template name="property-to-get-set-functions">
        <xsl:with-param name="property" select="concat(., '-within-column')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-functions">
        <xsl:with-param name="property" select="concat(., '-within-line')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-functions">
        <xsl:with-param name="property" select="concat(., '-within-page')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
    </xsl:when>
    <!--
    <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
      <xsl:call-template name="property-to-get-set-functions">
        <xsl:with-param name="property" select="concat(., '-minimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-functions">
        <xsl:with-param name="property" select="concat(., '-optimum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:call-template name="property-to-get-set-functions">
        <xsl:with-param name="property" select="concat(., '-maximum')"/>
        <xsl:with-param name="object" select="$object"/>
      </xsl:call-template>
      <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-precedence')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property"
            select="concat(., '-conditionality')"/>
          <xsl:with-param name="property-abbrev"
            select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="$object"/>
        </xsl:call-template>
      </xsl:if>
    </xsl:when>
    -->
  </xsl:choose>
</xsl:for-each>
<!-- End of generated text -->

</saxon:output>
  </xsl:template>

  <xsl:template match="/">

    <xsl:if test="$debug >= 2">
      <xsl:message>Property groups:</xsl:message>
      <xsl:for-each select="/spec/body/div1[@id='pr-section']/div2[@id]">
        <xsl:sort select="@id"/>
        <xsl:message> - <xsl:value-of select="@id"/></xsl:message>
      </xsl:for-each>
      <xsl:message></xsl:message>

      <xsl:message>Allowed properties:</xsl:message>
      <xsl:for-each select="$allowed-properties">
        <xsl:sort/>
        <xsl:message> - <xsl:value-of select="."/></xsl:message>
      </xsl:for-each>
      <xsl:message></xsl:message>

      <xsl:message>Formatting objects:</xsl:message>
    </xsl:if>

    <xsl:for-each select="/spec/body/div1/div2/div3
                          [head[starts-with(., 'fo:')]]">

      <xsl:variable name="object"
        select="substring-after(head, 'fo:')"/>

      <xsl:variable name="object_in_macro">
        <xsl:call-template name="hyphen-colon-to-underscore">
          <xsl:with-param name="string">
            <xsl:call-template name="to-upper">
              <xsl:with-param name="string" select="$object"/>
            </xsl:call-template>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:variable>

      <xsl:variable name="properties"
        select="(key('property', slist/sitem/specref/@ref)/@id |
                key('property-group', slist/sitem/specref/@ref)/div3/@id)
                [not($allowed-properties) or $allowed-properties = .]"/>

      <xsl:if test="$debug">
        <xsl:message><xsl:value-of select="$object"/></xsl:message>
        <xsl:for-each select="$properties">
          <xsl:sort/>
          <xsl:message> - <xsl:value-of select="."/></xsl:message>
          <xsl:if test="document($codegen-info)/codegen-info/properties/property[@name = current()]/@is-datatype = 'yes'">
            <xsl:message>      It's a datatype</xsl:message>
          </xsl:if>
          <xsl:if test="document($codegen-info)/codegen-info/properties/property[@name = current()]/@type = 'keep'">
            <xsl:message>      It's a keep</xsl:message>
          </xsl:if>
        </xsl:for-each>

        <xsl:if test="$debug >= 2 and
                      key('property-group', slist/sitem/specref/@ref)">
          <xsl:message>...Property groups:</xsl:message>
          <xsl:for-each select="key('property-group', slist/sitem/specref/@ref)">
            <xsl:message>...<xsl:value-of select="@id"/></xsl:message>
            <xsl:for-each select="div3/@id">
              <xsl:message>......<xsl:value-of select="."/></xsl:message>
            </xsl:for-each>
          </xsl:for-each>
          <xsl:message>...</xsl:message>
        </xsl:if>
      </xsl:if>

      <!--<xsl:if test="not($codegen-info) or $properties">-->
        <xsl:call-template name="gobject-header">
          <xsl:with-param name="object" select="$object"/>
          <xsl:with-param name="uppercase-object" select="$object_in_macro"/>
          <xsl:with-param name="properties" select="$properties"/>
        </xsl:call-template>
        <xsl:call-template name="gobject-private-header">
          <xsl:with-param name="object" select="$object"/>
          <xsl:with-param name="uppercase-object" select="$object_in_macro"/>
          <xsl:with-param name="properties" select="$properties"/>
        </xsl:call-template>
        <xsl:call-template name="gobject-c-file">
          <xsl:with-param name="object" select="$object"/>
          <xsl:with-param name="uppercase-object" select="$object_in_macro"/>
          <xsl:with-param name="properties" select="$properties"/>
        </xsl:call-template>
        <!--</xsl:if>-->
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
