<?xml version="1.0" encoding="utf-8"?>
<!-- libfo -->
<!-- fo-context-dump.xsl -->
<!-- Read the XSL spec and generate .c and .h files for FoContext object. -->

<!-- Copyright (C) 2001-2006 Sun Microsystems -->
<!-- Copyright (C) 2007-2010 Menteith Consulting Ltd -->
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

  <!-- property-to-unref-context-object
       Generate the function call to unref a class variable -->
  <xsl:template name="property-to-unref-context-object">
    <xsl:param name="property"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>  fo_context_set_</xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text> (context, NULL);&#10;</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- property-to-slist-foreach-if
       Generate the 'if' statement in fo_context_property_slist_foreach() -->
  <xsl:template name="property-to-slist-foreach-if">
    <xsl:param name="property"/>
    <xsl:param name="is-first"/>

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

    <xsl:variable name="property-macro">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-upper">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>  </xsl:text>
    <xsl:if test="not($is-first)">else </xsl:if>
    <xsl:choose>
      <xsl:when test="$is-datatype">
        <xsl:text>if (FO_IS_DATATYPE</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>if (FO_IS_PROPERTY_</xsl:text>
        <xsl:value-of select="$property-macro"/>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> (property))
    {
      fo_context_set_</xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text> (context, property);
    }&#10;</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- property-to-context-property-init
       Generate the assignment of context property value from property
       initial value -->
  <xsl:template name="property-to-context-property-init">
    <xsl:param name="property"/>
    <xsl:param name="null" select="false()"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>  context-></xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text> =</xsl:text>
    <xsl:choose>
      <xsl:when test="$null">
        <xsl:text> NULL</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>&#10;    g_object_ref (fo_property_</xsl:text>
          <xsl:value-of select="$lowercase-property"/>
          <xsl:text>_get_initial ())</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text>;&#10;</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- property-to-context-property-copy
       Generate the assignment of context property value from property
       value in source context -->
  <xsl:template name="property-to-context-property-copy">
    <xsl:param name="property"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->
    <xsl:text>  fo_context_set_</xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text> (context,
      fo_context_get_</xsl:text>
    <xsl:value-of select="$lowercase-property"/>
    <xsl:text> (src));&#10;</xsl:text>
    <!-- End of generated text -->
  </xsl:template>

  <!-- property-to-context-property-merge
       Generate the assignment of context property value from property
       value in source context -->
  <xsl:template name="property-to-context-property-merge">
    <xsl:param name="property"/>

    <xsl:variable name="inherited-string"
      select="normalize-space(/spec/back/div1[@id='property-index']/div2[@id = 'prtab1']/table/tbody/tr/td[@class = 'propindex'][specref/@ref = $property]/following-sibling::td[3])"/>
    <xsl:variable name="inherited"
      select="substring($inherited-string, 1, 3) = 'yes'"/>

    <xsl:variable name="lowercase-property">
      <xsl:call-template name="hyphen-colon-to-underscore">
        <xsl:with-param name="string">
          <xsl:call-template name="to-lower">
            <xsl:with-param name="string" select="$property"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:variable>

    <!-- Start of generated text -->

    <xsl:choose>
      <xsl:when test="$inherited">
        <xsl:text>  if (primary-></xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text> == NULL &amp;&amp;
      secondary-></xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text> != NULL)
    {
      primary-></xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text> =
        g_object_ref (secondary-></xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text>);
    }&#10;</xsl:text>
      </xsl:when>
      <xsl:otherwise>
        <xsl:text>  if (primary-></xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text> == NULL)
    {
      primary-></xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text> =
        g_object_ref (fo_property_</xsl:text>
        <xsl:value-of select="$lowercase-property"/>
        <xsl:text>_get_initial ());
    }&#10;</xsl:text>
      </xsl:otherwise>
    </xsl:choose>
    <!-- End of generated text -->
  </xsl:template>

  <!-- fo-context-h-file -->
  <!-- Generate the fo-context.h file -->
  <xsl:template name="fo-context-h-file">
    <xsl:param name="properties"/>

    <exsl:document href="./fo-context.h"
      method="text">
      <xsl:text>/* Fo
 * fo-context.h: Context formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONTEXT_H__
#define __FO_CONTEXT_H__

typedef struct _FoContext      FoContext;
typedef struct _FoContextClass FoContextClass;

#include &lt;libfo/fo-utils.h>
#include &lt;libfo/fo-object.h>
#include &lt;libfo/fo/fo-fo.h>
#include &lt;libfo/property/fo-property.h>

G_BEGIN_DECLS

#define FO_TYPE_CONTEXT              (fo_context_get_type ())
#define FO_CONTEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_CONTEXT, FoContext))
#define FO_CONTEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_CONTEXT, FoContextClass))
#define FO_IS_CONTEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_CONTEXT))
#define FO_IS_CONTEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_CONTEXT))
#define FO_CONTEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_CONTEXT, FoContextClass))


GType       fo_context_get_type      (void) G_GNUC_CONST;
FoContext * fo_context_new           (void);

void fo_context_initialize (FoContext *context);
void fo_context_merge (FoContext *primary,
		       FoContext *secondary);
void fo_context_update_from_slist (FoContext *context,
				   GSList *property_list);
void fo_context_debug_dump_properties (FoContext *fo_context,
                                       gint       depth);

</xsl:text>

<!-- Almost cheat by using the same 'property-to-get-set-prototypes'
     named template as is used in fo-object-dump.xsl.  Use 'context'
     as the object name and it comes out fine. -->
  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>
    <xsl:call-template name="property-to-get-set-prototypes">
      <xsl:with-param name="property" select="."/>
      <xsl:with-param name="object" select="'context'"/>
    </xsl:call-template>
    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']">
          <xsl:call-template name="property-to-get-set-prototypes">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-get-set-prototypes">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-length')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-prototypes">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>

G_END_DECLS

#endif /* __FO_CONTEXT_H__ */
</xsl:text>
</exsl:document>
  </xsl:template>

  <!-- fo-context-private-h-file -->
  <!-- Generate the fo-context-private.h file -->
  <xsl:template name="fo-context-private-h-file">
    <xsl:param name="properties"/>

    <exsl:document href="./fo-context-private.h"
      method="text">
      <xsl:text>/* Fo
 * fo-context-private.h: Structures private to the FoContext formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONTEXT_PRIVATE_H__
#define __FO_CONTEXT_PRIVATE_H__

#include "fo-object.h"
#include "property/fo-property.h"

G_BEGIN_DECLS

struct _FoContext
{
  FoObject parent_instance;

</xsl:text>

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
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']">
          <xsl:call-template name="property-to-instance-variable">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-instance-variable">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-length')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-instance-variable">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>};

struct _FoContextClass
{
  FoObjectClass parent_class;
};

G_END_DECLS

#endif /* __FO_CONTEXT_PRIVATE_H__ */
</xsl:text>
    </exsl:document>
  </xsl:template>

  <xsl:template name="fo-context-c-file">
    <xsl:param name="properties"/>

    <exsl:document href="./fo-context.c"
      method="text">
      <xsl:text>/* Fo
 * fo-context.c: Context formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-object.h"
#include "datatype/fo-all-datatype.h"
#include "property/fo-all-property.h"
#include "fo-context.h"
#include "fo-context-private.h"

enum {
  PROP_0,
</xsl:text>

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
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-prop-enum">
          <xsl:with-param name="property" select="concat(., '-length')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-prop-enum">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

  <xsl:text>};

static void fo_context_class_init   (FoContextClass *klass);
static void fo_context_set_property (GObject        *object,
				                             guint           prop_id,
				                             const GValue   *value,
				                             GParamSpec     *pspec);
static void fo_context_get_property (GObject        *object,
				                             guint           prop_id,
				                             GValue         *value,
				                             GParamSpec     *pspec);
static void fo_context_finalize     (GObject        *object);

static void fo_context_property_slist_foreach (gpointer   property,
					       gpointer   context);
static void fo_context_debug_dump             (FoObject  *object,
					       gint       depth);

static FoProperty* fo_context_get_space_before_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_precedence (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_precedence (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_precedence (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_precedence (FoContext *fo_context);

static gpointer parent_class;

/**
 * fo_context_get_type:
 * 
 * Register the #FoContext type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoContext.
 **/
GType
fo_context_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoContextClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_context_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoContext),
        0,              /* n_preallocs */
        NULL,           /* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoContext",
                                            &amp;object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_context_initialize:
 * @context: #FoContext to initialize.
 * 
 * Initialize @context with the initial/default value of every property.
 **/
void
fo_context_initialize (FoContext *context)
{
</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-context-property-init">
      <xsl:with-param name="property" select="."/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="null" select="true()"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="null" select="true()"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="null" select="true()"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']">
          <xsl:call-template name="property-to-context-property-init">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-context-property-init">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-length')"/>
          <xsl:with-param name="null" select="true()"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-init">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>}

/**
 * fo_context_init:
 * @klass: #FoContextClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoContextClass.
 **/
void
fo_context_class_init (FoContextClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_context_finalize;

  object_class->set_property = fo_context_set_property;
  object_class->get_property = fo_context_get_property;

  fo_object_class->debug_dump = fo_context_debug_dump;

</xsl:text>

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
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space']">
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="param-flags" select="'G_PARAM_WRITABLE'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="param-flags" select="'G_PARAM_WRITABLE'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="param-flags" select="'G_PARAM_WRITABLE'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-precedence')"/>
          <xsl:with-param name="param-flags" select="'G_PARAM_WRITABLE'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property"
            select="concat(., '-conditionality')"/>
          <xsl:with-param name="property-abbrev"
            select="concat(., '-condity')"/>
          <xsl:with-param name="param-flags" select="'G_PARAM_WRITABLE'"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-range']">
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-length')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-install-property">
          <xsl:with-param name="property" select="concat(., '-conditionality')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>}

/**
 * fo_context_finalize:
 * @object: #FoContext object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoContext.
 **/
void
fo_context_finalize (GObject *object)
{
  FoContext *context;

  context = FO_CONTEXT (object);

</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-unref-context-object">
      <xsl:with-param name="property" select="."/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-unref-context-object">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-unref-context-object">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-length')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-unref-context-object">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>
  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_context_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoContext.
 **/
void
fo_context_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoContext *fo_context;

  fo_context = FO_CONTEXT (object);

  switch (prop_id)
    {
</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-set-property-case">
      <xsl:with-param name="property" select="."/>
      <xsl:with-param name="object" select="'context'"/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-set-property-case">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-set-property-case">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-length')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-set-property-case">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_context_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoContext.
 **/
void
fo_context_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoContext *fo_context;

  fo_context = FO_CONTEXT (object);

  switch (prop_id)
    {
</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-get-property-case">
      <xsl:with-param name="property" select="."/>
      <xsl:with-param name="object" select="'context'"/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
      <!--
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        -->
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-range']">
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-get-property-case">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-get-property-case">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-length')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-property-case">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_context_new:
 * 
 * Creates a new #FoContext initialized to default value.
 * 
 * Return value: the new #FoContext.
 **/
FoContext *
fo_context_new (void)
{
  FoContext *context;

  context = FO_CONTEXT (g_object_new (fo_context_get_type (),
                        NULL));
  
  return context;
}
</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-get-set-functions">
      <xsl:with-param name="property" select="."/>
      <xsl:with-param name="object" select="'context'"/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']">
          <xsl:call-template name="property-to-get-set-functions">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-get-set-functions">
            <xsl:with-param name="property"
              select="concat(., '-conditionality')"/>
            <xsl:with-param name="property-abbrev"
              select="concat(., '-condity')"/>
            <xsl:with-param name="object" select="'context'"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property" select="concat(., '-length')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-get-set-functions">
          <xsl:with-param name="property"
            select="concat(., '-conditionality')"/>
          <xsl:with-param name="property-abbrev"
            select="concat(., '-condity')"/>
          <xsl:with-param name="object" select="'context'"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>
/**
 * fo_context_copy:
 * @src: #FoContext to be copied.
 * 
 * Make a copy of @src.
 * 
 * Return value: Copy of @src.
 **/
FoContext*
fo_context_copy (FoContext *src)
{
  FoContext *context;

  context = fo_context_new ();

</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-context-property-copy">
      <xsl:with-param name="property" select="."/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-context-property-copy">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-context-property-copy">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-length')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-copy">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>
  return context;
}

/**
 * fo_context_merge:
 * @primary:   Primary #FoContext.
 * @secondary: Secondary #FoContext.
 * 
 * Merge @primary and @secondary.
 *
 * When a property does not exist in @primary, if the property is
 * inherited, set the property value in @primary to that in
 * @secondary, otherwise set the property value in @primary to its
 * initial value.
 **/
void
fo_context_merge (FoContext *primary, FoContext *secondary)
{
  if (primary == NULL &amp;&amp; secondary != NULL)
    {
      primary = g_object_ref (secondary);
    }

</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-context-property-merge">
      <xsl:with-param name="property" select="."/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-context-property-merge">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-context-property-merge">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-length')"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-context-property-merge">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>}

/**
 * fo_context_property_slist_foreach:
 * @property: #FoProperty object.
 * @context:  #FoContext.
 * 
 * Add @property to @context.
 **/
void
fo_context_property_slist_foreach (gpointer property,
				   gpointer context)
{
</xsl:text>

  <xsl:for-each select="$properties">
    <xsl:sort/>
    <xsl:variable name="property" select="."/>

    <xsl:call-template name="property-to-slist-foreach-if">
      <xsl:with-param name="property" select="."/>
      <xsl:with-param name="is-first" select="position() = 1"/>
    </xsl:call-template>

    <xsl:choose>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'keep']">
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-within-column')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-within-line')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-within-page')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'space' or ../@type = 'length-range']">
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-minimum')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-optimum')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-maximum')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
        <xsl:if test="$allowed-properties[. = $property][../@type = 'space']"
>
          <xsl:call-template name="property-to-slist-foreach-if">
            <xsl:with-param name="property" select="concat(., '-precedence')"/>
            <xsl:with-param name="is-first" select="position() = 1"/>
          </xsl:call-template>
          <xsl:call-template name="property-to-slist-foreach-if">
            <xsl:with-param name="property" select="concat(., '-condity')"/>
            <xsl:with-param name="is-first" select="position() = 1"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:when>
      <xsl:when test="$allowed-properties[. = $property][../@type = 'length-conditional']">
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-length')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
        <xsl:call-template name="property-to-slist-foreach-if">
          <xsl:with-param name="property" select="concat(., '-condity')"/>
          <xsl:with-param name="is-first" select="position() = 1"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

<xsl:text>  else
    {
      gchar *property_dump = fo_object_debug_sprintf (property);

      g_warning (_("Unsupported property: %s"),
		 property_dump);

      g_free (property_dump);
    }
}

/**
 * fo_context_update_from_slist:
 * @context:       #FoContext to be updated.
 * @property_list: #GSList of #FoProperty objects.
 * 
 * Add each #FoProperty in @property_list to @context.
 **/
void
fo_context_update_from_slist (FoContext *context,
			      GSList *property_list)
{
  g_slist_foreach (property_list,
		   fo_context_property_slist_foreach,
		   (gpointer) context);
}

/**
 * fo_context_debug_dump:
 * @object: #FoContext instance to be dumped.
 * @depth:  Relative indent to apply to the output.
 * 
 * Dump information about @object and its properties.
 **/
void
fo_context_debug_dump (FoObject *object,
		       gint      depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_CONTEXT (object));

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);
  g_free (indent);

  fo_context_debug_dump_properties (FO_CONTEXT (object),
				    depth + 2);
}

</xsl:text>

<xsl:call-template name="debug-dump-properties-function">
  <xsl:with-param name="properties" select="$properties"/>
  <xsl:with-param name="object" select="'context'"/>
</xsl:call-template>

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
      <xsl:call-template name="fo-context-h-file">
        <xsl:with-param name="properties" select="$properties"/>
      </xsl:call-template>
      <xsl:call-template name="fo-context-private-h-file">
        <xsl:with-param name="properties" select="$properties"/>
      </xsl:call-template>
      <xsl:call-template name="fo-context-c-file">
        <xsl:with-param name="properties" select="$properties"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>
