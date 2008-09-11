/* Fo
 * fo-page-sequence-area.c: Generate area for page-sequence formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#include "fo-page-sequence-private.h"
#include "fo-page-sequence-area.h"
#include "fo-simple-page-master.h"
#include "property/fo-property-page-width.h"
#include "property/fo-property-page-height.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-writing-mode.h"
#include "area/fo-area.h"
#include "area/fo-all-area.h"
#include "datatype/fo-length.h"

void
fo_page_sequence_area_new (FoFo                *fo_node,
			   FoFoAreaNew2Context *context,
			   GError             **error)
{
  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_node));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  FoDoc *fo_doc = context->fo_doc;
  FoArea *use_parent_area = context->parent_area;
  FoArea **new_area = context->new_area;

  *new_area = NULL;

  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_FO (fo_node));
  g_return_if_fail (use_parent_area != NULL);
  g_return_if_fail (FO_IS_AREA (use_parent_area));
  /*g_return_if_fail (FO_IS_DOC (fo_doc));*/

  while (! FO_IS_PAGE_SEQUENCE (fo_node))
    {
      fo_node = FO_FO (fo_node_parent (FO_NODE (fo_node)));
    }

  FoFo *page_master = FO_PAGE_SEQUENCE (fo_node)->page_master;

  gdouble page_width =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_page_width (page_master)));
  gdouble page_height =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_page_height (page_master)));
  gdouble margin_left =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_left (page_master)));
  gdouble margin_right =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_right (page_master)));
  gdouble margin_top =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_top (page_master)));
  gdouble margin_bottom =
    fo_length_get_value (fo_property_get_value (fo_simple_page_master_get_margin_bottom (page_master)));
  FoProperty *writing_mode
    = fo_simple_page_master_get_writing_mode (page_master);

  /*
  g_message ("Writing mode: %d", writing_mode);
  */
  *new_area = fo_area_page_new ();

  FO_FO (fo_node)->areas = g_list_append (FO_FO (fo_node)->areas, *new_area);
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("page_sequence_area_new:: fo: %s; areas: %p; *new_area: %p"),
	 fo_object_debug_sprintf (fo_node),
	 fo_node->areas, *new_area);
#endif
  fo_area_set_generated_by (*new_area, g_object_ref (fo_node));
  fo_area_set_page (*new_area, g_object_ref (*new_area));

  gint page_number = 0;
  while (! FO_IS_AREA_TREE (use_parent_area))
    {
      if (FO_IS_AREA_PAGE (use_parent_area))
	{
	  page_number =
	    fo_area_page_get_page_number (use_parent_area);
	  fo_area_set_is_last (use_parent_area, FALSE);
	}
      use_parent_area = fo_area_parent (use_parent_area);
    }

  fo_area_page_set_page_number (*new_area, page_number + 1);
  fo_area_set_is_first (FO_AREA (*new_area), FALSE);
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

  fo_area_add_child (use_parent_area, *new_area);

  fo_area_reference_set_bpd (*new_area,
			     fo_property_writing_mode_to_bpd (writing_mode,
							      NULL));
  FoEnumAreaDirection ipd
    = fo_property_writing_mode_to_ipd (writing_mode,
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
