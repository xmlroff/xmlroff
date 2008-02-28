/* Fo
 * fo-property-common-font.c: Common font property functions
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "property/fo-property-common-font.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-font-variant.h"
#include "property/fo-property-font-weight.h"

GList*
fo_property_common_font_get_pango_attrs (FoProperty *font_family,
					 /* No font-selection-strategy */
					 FoProperty *font_size,
					 FoProperty *font_stretch,
					 /* No font-size-adjust */
					 FoProperty *font_style,
					 FoProperty *font_variant,
					 FoProperty *font_weight,
					 gint        start_index,
					 gint        end_index)
{
  PangoAttribute *pango_attr;
  GList *pango_attr_glist = NULL;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_FAMILY (font_family), NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_SIZE (font_size), NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_STRETCH (font_stretch), NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_STYLE (font_style), NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_VARIANT (font_variant), NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_WEIGHT (font_weight), NULL);

  pango_attr = fo_property_text_property_new_attr (font_family);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;

  pango_attr_glist = g_list_prepend (pango_attr_glist,
				     pango_attr);

  pango_attr = fo_property_text_property_new_attr (font_size);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;

  pango_attr_glist = g_list_prepend (pango_attr_glist,
				     pango_attr);

  pango_attr = fo_property_text_property_new_attr (font_stretch);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;

  pango_attr_glist = g_list_prepend (pango_attr_glist,
				     pango_attr);

  pango_attr = fo_property_text_property_new_attr (font_style);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;

  pango_attr_glist = g_list_prepend (pango_attr_glist,
				     pango_attr);

  pango_attr = fo_property_text_property_new_attr (font_variant);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;

  pango_attr_glist = g_list_prepend (pango_attr_glist,
				     pango_attr);

  pango_attr = fo_property_text_property_new_attr (font_weight);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;

  return g_list_prepend (pango_attr_glist,
			 pango_attr);
}

