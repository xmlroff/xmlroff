/* Fo
 * fo-region-end-area.c: Generate area for 'region-end' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-region.h"
#include "fo-region-end-private.h"
#include "fo-cbpbp-fo.h"
#include "property/fo-property-writing-mode.h"

void
fo_region_end_area_new (FoFo                *fo,
			FoFoAreaNew2Context *context,
			GError             **error)
{
  FoProperty *writing_mode;

  FoDoc *fo_doc = context->fo_doc;
  FoArea *parent_area = context->parent_area;
  FoArea **new_area = context->new_area;
  guint debug_level = context->debug_level;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_END (fo));

  *new_area = g_object_ref_sink (fo_area_region_new ());

  fo_area_region_set_region_name (*new_area,
    fo_name_get_value (fo_property_get_value (fo_region_get_region_name (fo))));

  fo_area_area_set_border_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_end_width (fo))));
  fo_area_area_set_border_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_end_width (fo))));
  fo_area_area_set_border_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_end_width (fo))));
  fo_area_area_set_border_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_end_width (fo))));

  fo_area_area_set_padding_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_end (fo))));
  fo_area_area_set_padding_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_end (fo))));
  fo_area_area_set_padding_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_end (fo))));
  fo_area_area_set_padding_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_end (fo))));

  fo_area_area_set_height (*new_area,
			   fo_area_area_get_border_end (*new_area) +
			   fo_area_area_get_padding_end (*new_area) +
			   fo_area_area_get_padding_end (*new_area) +
			   fo_area_area_get_border_end (*new_area));
  fo_area_area_set_width (*new_area,
			  fo_area_area_get_border_end (*new_area) +
			  fo_area_area_get_padding_end (*new_area) +
			  fo_area_area_get_padding_end (*new_area) +
			  fo_area_area_get_border_end (*new_area));

  fo_area_set_available_width (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (fo))));
  writing_mode = fo_region_get_writing_mode (fo);

  fo_area_reference_set_bpd (*new_area,
			     fo_property_writing_mode_to_bpd (writing_mode,
							      NULL));
  fo_area_reference_set_ipd (*new_area,
			     fo_property_writing_mode_to_ipd (writing_mode,
							      NULL));
  fo_area_reference_set_sd (*new_area,
			    fo_property_writing_mode_to_sd (writing_mode,
							    NULL));
  fo_area_set_generated_by (*new_area,
			    fo);
}
