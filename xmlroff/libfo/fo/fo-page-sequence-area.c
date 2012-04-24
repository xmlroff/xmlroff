/* Fo
 * fo-page-sequence-area.c: Generate area for 'page-sequence' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011-2012 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo-page-sequence-private.h"
#include "fo-page-sequence-area.h"
#include "fo-simple-page-master.h"
#include "area/fo-area-page.h"
#include "area/fo-area-tree.h"

static void
_clone_region (FoArea  *region,
	       gpointer data)
{
  FoArea *clone_region = g_object_ref_sink (fo_area_clone (region));
  fo_fo_area_list_remove (fo_area_get_generated_by (clone_region),
			  clone_region);
  fo_area_set_is_last (region,
		       FALSE);
  fo_area_set_is_first (clone_region,
			TRUE);
  fo_area_unlink (clone_region);
  fo_area_add_child ((FoArea *) data,
		     clone_region);
}

/**
 * fo_page_sequence_area_new:
 * @fo_node: 
 * @context: 
 * @error: 
 *
 * 
 **/
void
fo_page_sequence_area_new (FoFo                *fo_node,
			   FoFoAreaNew2Context *context,
			   GError             **error)
{
  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_node) ||
		    FO_IS_SIMPLE_PAGE_MASTER (fo_node));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  /*FoDoc *fo_doc = context->fo_doc;*/
  FoArea *use_parent_area = context->parent_area;
  FoArea **new_area = context->new_area;
  /*guint debug_level = context->debug_level;*/

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

  FoFo *page_master =
    fo_page_sequence_walker_next_page_master (FO_PAGE_SEQUENCE (fo_node)->walker,
					      NULL);

  FO_PAGE_SEQUENCE (fo_node)->page_master = page_master;

  *new_area =
    g_object_ref_sink (fo_area_clone (fo_simple_page_master_get_area (page_master)));
  fo_fo_area_list_remove (fo_area_get_generated_by (*new_area),
			  *new_area);
  fo_area_set_generated_by (*new_area,
			    fo_node);
  fo_area_children_foreach (fo_simple_page_master_get_area (page_master),
			    G_TRAVERSE_ALL,
			    &_clone_region,
			    *new_area);


  fo_fo_area_list_append (fo_node,
			  *new_area);

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("page_sequence_area_new:: fo: %s; areas: %p; *new_area: %p"),
	 fo_object_debug_sprintf (fo_node),
	 fo_node->areas, *new_area);
#endif
  fo_area_set_generated_by (*new_area,
			    fo_node);
  fo_area_set_page (*new_area,
		    *new_area);

  /* Find the tree and the ancestor page in one go. */
  gint page_number = 0;
  while (! FO_IS_AREA_TREE (use_parent_area))
    {
      if (FO_IS_AREA_PAGE (use_parent_area))
	{
	  page_number =
	    fo_area_page_get_page_number (use_parent_area);
	  fo_area_set_is_last (use_parent_area,
			       FALSE);
	  /* Don't break here because still want to find tree. */
	}
      use_parent_area = fo_area_parent (use_parent_area);
    }

  fo_area_set_is_first (FO_AREA (*new_area),
			page_number == 0 ? TRUE : FALSE);
  fo_area_page_set_page_number (*new_area,
				page_number + 1);

  fo_area_set_next_x (*new_area,
		      fo_area_page_get_margin_left (*new_area));
  fo_area_set_next_y (*new_area,
		      fo_area_page_get_page_height (*new_area) -
		      fo_area_page_get_margin_top (*new_area));

  fo_area_add_child (use_parent_area, *new_area);
}
