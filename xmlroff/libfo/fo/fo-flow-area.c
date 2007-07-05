/* Fo
 * fo-flow-area.c: Generate area for flow formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-region-body-area.h"
#include "area/fo-area.h"
#include "area/fo-area-area.h"
#include "fo-flow-private.h"

void
fo_flow_area_new (FoFo    *fo,
		  FoDoc   *fo_doc,
		  FoArea  *parent_area,
		  FoArea **new_area,
		  guint    debug_level)
{
  FoFlow *flow = (FoFlow *) fo;
  FoFo *fo_node;
  FoArea *use_parent_area;
  FoArea *child_area;
  FoArea *child_area_parent;

  g_return_if_fail (flow != NULL);
  g_return_if_fail (FO_IS_FLOW (flow));
  g_return_if_fail (FO_IS_DOC (fo_doc));

  /* FIXME: Should be separate function, not _new().  Properties should be
     CONSTRUCT_ONLY */
  fo_region_body_area_new (fo_flow_get_region_master (fo),
			   fo_doc,
			   parent_area,
			   new_area,
			   debug_level);
  /*
  *new_area = fo_region_body_area_new ();
  */
#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** flow parent before new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end flow parent");
#endif

  fo_area_set_generated_by (*new_area, fo);
  fo_area_add_child (parent_area, *new_area);
  *new_area = fo_area_size_request (*new_area);
#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** flow parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end flow parent");
#endif

  fo_node = FO_FO (fo_node_first_child (FO_NODE (fo)));
  /*
  fo_node = fo->children;
  */

  child_area_parent = *new_area;

  while (fo_node)
    {
      fo_fo_area_new (fo_node,
		      fo_doc,
		      child_area_parent,
		      &child_area,
		      debug_level);
      fo_node = FO_FO (fo_node_next_sibling (FO_NODE (fo_node)));
      child_area_parent = fo_area_parent (child_area);
    }

  /* The last child may be on a different page, which means it has a
     different parent that was cloned from the new area created within
     this function. */
  *new_area = child_area_parent;
  use_parent_area = fo_area_parent (*new_area);

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** flow parent after adding children:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end flow parent");
#endif
}

void
fo_flow_area_new2 (FoFo *fo,
		   FoFoAreaNew2Context *context,
		   GError **error)
{
  FoFlow *flow = (FoFlow *) fo;

  g_return_if_fail (flow != NULL);
  g_return_if_fail (FO_IS_FLOW (flow));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  fo_region_body_area_new (fo_flow_get_region_master (fo),
			   context->fo_doc,
			   context->parent_area,
			   context->new_area,
			   context->debug_level);

  fo_area_set_generated_by (*(context->new_area), fo);
  FO_FO (fo)->areas = g_list_append (FO_FO (fo)->areas, *(context->new_area));
  fo_area_add_child (context->parent_area, *(context->new_area));
  *(context->new_area) = fo_area_size_request (*(context->new_area));
}
