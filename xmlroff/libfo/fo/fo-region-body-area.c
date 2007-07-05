/* Fo
 * fo-region-body-area.c: Generate area for region-body formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-area.h"
#include "area/fo-area-reference.h"
#include "area/fo-area-viewport-reference.h"
#include "fo-region-body-private.h"

void
fo_region_body_area_new (FoFo    *fo,
			 FoDoc   *fo_doc,
			 FoArea  *parent_area,
			 FoArea **new_area,
			 guint    debug_level)
{
  FoProperty *writing_mode;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo));

  *new_area = fo_area_viewport_reference_new ();

  fo_area_area_set_border_start (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_border_start_width (fo))));
  fo_area_area_set_border_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_border_end_width (fo))));
  fo_area_area_set_border_before (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_border_before_width (fo))));
  fo_area_area_set_border_after (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_border_after_width (fo))));

  fo_area_area_set_padding_start (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_padding_start (fo))));
  fo_area_area_set_padding_end (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_padding_end (fo))));
  fo_area_area_set_padding_before (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_padding_before (fo))));
  fo_area_area_set_padding_after (*new_area,
    fo_length_get_value (fo_property_get_value (fo_region_body_get_padding_after (fo))));

  fo_area_area_set_height (*new_area,
			   fo_area_area_get_border_before (*new_area) +
			   fo_area_area_get_padding_before (*new_area) +
			   fo_area_area_get_padding_after (*new_area) +
			   fo_area_area_get_border_after (*new_area));
  fo_area_area_set_width (*new_area,
			  fo_area_area_get_border_start (*new_area) +
			  fo_area_area_get_padding_start (*new_area) +
			  fo_area_area_get_padding_end (*new_area) +
			  fo_area_area_get_border_end (*new_area));

  writing_mode = fo_region_body_get_writing_mode (fo);

  fo_area_reference_set_bpd (*new_area,
			     fo_property_writing_mode_to_bpd (writing_mode,
							      NULL));
  fo_area_reference_set_ipd (*new_area,
			     fo_property_writing_mode_to_ipd (writing_mode,
							      NULL));
  fo_area_reference_set_sd (*new_area,
			    fo_property_writing_mode_to_sd (writing_mode,
							    NULL));
}
