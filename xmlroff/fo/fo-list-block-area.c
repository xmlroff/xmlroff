/* Fo
 * fo-list-block-area.c: Generate area for list-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-list-block-area.c,v 1.3 2003/05/23 16:36:48 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo-area.h"
#include "fo-area-normal.h"
#include "fo-list-block-private.h"
#include "fo-block-fo.h"

void
fo_list_block_area_new (FoFo    *fo,
			FoDoc   *fo_doc,
			FoArea  *parent_area,
			FoArea **new_area,
			guint    debug_level)
{
  FoListBlock *list_block = (FoListBlock *) fo;
  FoFo *fo_node;
  FoArea *use_parent_area;
  FoArea *child_area;
  FoArea *child_area_parent;

  g_return_if_fail (list_block != NULL);
  g_return_if_fail (FO_IS_LIST_BLOCK (list_block));
  g_return_if_fail (FO_IS_DOC (fo_doc));

  *new_area = fo_area_normal_new ();

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-block parent before new area:");
  fo_object_debug_dump (use_parent_area, 0);
  g_warning ("*** end list-block parent");
#endif

  fo_area_set_generated_by (*new_area, fo);
  fo_block_fo_update_area (fo, *new_area);
  use_parent_area = fo_area_break_resolve (parent_area, *new_area);
  fo_area_border_padding_space_resolve (use_parent_area, *new_area);
  fo_area_add_child (use_parent_area, *new_area);
  *new_area = fo_area_size_request (*new_area);
  fo_area_area_set_width (*new_area, fo_area_get_available_width (*new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-block parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end list-block parent");
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
  g_warning ("*** list-block parent after adding children:");
  fo_object_debug_dump (use_parent_area, 0);
  g_warning ("*** end list-block parent");
#endif
}

void
fo_list_block_area_new2 (FoFo *fo,
			 FoFoAreaNew2Context *context,
			 GError **error)
{
  FoListBlock *list_block = (FoListBlock *) fo;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (list_block != NULL);
  g_return_if_fail (FO_IS_LIST_BLOCK (list_block));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_normal_new ();
  use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-block parent before new area:");
  fo_object_debug_dump (use_parent_area, 0);
  g_warning ("*** end list-block parent");
#endif

  FO_AREA (new_area)->generated_by = fo;
  FO_FO (fo)->areas = g_list_append (FO_FO (fo)->areas, new_area);
  fo_block_fo_update_area (fo, new_area);
  use_parent_area = fo_area_break_resolve (use_parent_area, new_area);
  fo_area_border_padding_space_resolve (use_parent_area, new_area);
  fo_area_add_child (use_parent_area, new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area, fo_area_get_available_width (new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-block parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end list-block parent");
#endif

  *(context->new_area) = new_area;
}
