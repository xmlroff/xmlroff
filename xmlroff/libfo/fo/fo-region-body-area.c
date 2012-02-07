/* Fo
 * fo-region-body-area.c: Generate area for 'region-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-region.h"
#include "fo-region-body-private.h"
#include "fo-cbpbp-fo.h"
#include "property/fo-property-writing-mode.h"

void
fo_region_body_area_new (FoFo    *fo,
			 FoFoAreaNew2Context *context,
			 GError **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  /* FoDoc *fo_doc = context->fo_doc; */
  /* FoArea *use_parent_area = context->parent_area; */
  FoArea **new_area = context->new_area;
  /* guint debug_level = context->debug_level; */

  *new_area = g_object_ref_sink (fo_area_region_new ());

  gchar *name =
    fo_name_get_value (fo_property_get_value (fo_region_get_region_name (fo)));
  fo_area_region_set_region_name (*new_area,
				  name);
  g_free (name);

  fo_area_area_set_border_start (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_start_width (fo))));
  fo_area_area_set_border_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_end_width (fo))));
  fo_area_area_set_border_before (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_before_width (fo))));
  fo_area_area_set_border_after (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_border_after_width (fo))));

  fo_area_area_set_padding_start (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_start (fo))));
  fo_area_area_set_padding_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_end (fo))));
  fo_area_area_set_padding_before (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_before (fo))));
  fo_area_area_set_padding_after (*new_area,
    fo_length_get_value (fo_property_get_value (fo_cbpbp_fo_get_padding_after (fo))));

  fo_area_area_set_space_before (*new_area,
    fo_length_get_value (fo_property_get_value (FO_REGION_BODY (fo)->margin_top)));
  fo_area_area_set_space_after (*new_area,
    fo_length_get_value (fo_property_get_value (FO_REGION_BODY (fo)->margin_bottom)));
  fo_area_area_set_start_indent (*new_area,
    fo_length_get_value (fo_property_get_value (FO_REGION_BODY (fo)->margin_left)));
  fo_area_area_set_end_indent (*new_area,
    fo_length_get_value (fo_property_get_value (FO_REGION_BODY (fo)->margin_right)));

  fo_area_area_set_height (*new_area,
			   fo_area_area_get_space_before (*new_area) +
			   fo_area_area_get_border_before (*new_area) +
			   fo_area_area_get_padding_before (*new_area) +
			   fo_area_area_get_padding_after (*new_area) +
			   fo_area_area_get_border_after (*new_area) +
			   fo_area_area_get_space_after (*new_area));
  fo_area_area_set_width (*new_area,
			  fo_area_area_get_border_start (*new_area) +
			  fo_area_area_get_padding_start (*new_area) +
			  fo_area_area_get_padding_end (*new_area) +
			  fo_area_area_get_border_end (*new_area));

  fo_area_set_next_x (*new_area,
		      fo_area_area_get_start_indent (*new_area));
  fo_area_set_next_y (*new_area,
		      -fo_area_area_get_space_before (*new_area));

  FoProperty *writing_mode = fo_region_get_writing_mode (fo);

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
