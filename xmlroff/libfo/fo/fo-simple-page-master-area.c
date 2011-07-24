/* Fo
 * fo-simple-page-master-area.c: Generate area for 'simple-page-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-simple-page-master-private.h"
#include "fo-simple-page-master-area.h"
#include "property/fo-property-page-width.h"
#include "property/fo-property-page-height.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-writing-mode.h"
#include "area/fo-area-page.h"
#include "area/fo-area-tree.h"
#include "datatype/fo-length.h"

void
fo_simple_page_master_area_new (FoFo                *fo,
				FoFoAreaNew2Context *context,
				GError             **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  FoDoc *fo_doc = context->fo_doc;
  FoArea *use_parent_area = context->parent_area;
  FoArea **new_area = context->new_area;
  guint debug_level = context->debug_level;

  *new_area = NULL;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FO (fo));
  /*g_return_if_fail (use_parent_area != NULL);
    g_return_if_fail (FO_IS_AREA (use_parent_area));*/
  /*g_return_if_fail (FO_IS_DOC (fo_doc));*/

  gdouble page_width =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_page_width (fo)));
  gdouble page_height =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_page_height (fo)));
  gdouble margin_left =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_left (fo)));
  gdouble margin_right =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_right (fo)));
  gdouble margin_top =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_top (fo)));
  gdouble margin_bottom =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_bottom (fo)));
  FoProperty *writing_mode
    = fo_simple_page_master_get_writing_mode (fo);

  /*
  g_message ("Writing mode: %d", writing_mode);
  */
  *new_area = g_object_ref_sink (fo_area_page_new ());

  fo_fo_area_list_append (fo,
			  *new_area);
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("simple_page_master_area_new:: fo: %s; areas: %p; *new_area: %p"),
	 fo_object_debug_sprintf (fo),
	 fo->areas, *new_area);
#endif
  fo_area_set_generated_by (*new_area,
			    fo);
  fo_area_set_page (*new_area,
		    *new_area);
  fo_area_set_reference (*new_area,
			 *new_area);

  fo_area_page_set_page_number (*new_area,
				0);
  fo_area_set_is_first (FO_AREA (*new_area),
			FALSE);
  fo_area_page_set_page_width (*new_area,
			       page_width);
  fo_area_page_set_page_height (*new_area,
				page_height);
  fo_area_page_set_margin_left (*new_area,
				margin_left);
  fo_area_page_set_margin_right (*new_area,
				 margin_right);
  fo_area_page_set_margin_top (*new_area,
			       margin_top);
  fo_area_page_set_margin_bottom (*new_area,
				  margin_bottom);

  fo_area_set_next_x (*new_area,
		      margin_left);
  fo_area_set_next_y (*new_area,
		      page_height - margin_top);

  /*fo_area_add_child (use_parent_area, *new_area);*/

  fo_area_reference_set_bpd (*new_area,
			     fo_property_writing_mode_to_bpd (writing_mode,
							      NULL));
  FoEnumAreaDirection ipd =
    fo_property_writing_mode_to_ipd (writing_mode,
				     NULL);

  fo_area_reference_set_ipd (*new_area,
			     ipd);

  if (fo_doc != NULL)
    {
      if ((ipd == FO_ENUM_AREA_DIRECTION_LR) ||
	  (ipd == FO_ENUM_AREA_DIRECTION_RL) ||
	  (ipd == FO_ENUM_AREA_DIRECTION_TB))
	{
	  fo_doc_set_base_dir (fo_doc,
			       ipd);
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  fo_area_reference_set_sd (*new_area,
			    fo_property_writing_mode_to_sd (writing_mode,
							    NULL));
}
