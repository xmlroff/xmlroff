/* Fo
 * fo-list-item-area.c: Generate area for list-item formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-block-fo.h"
#include "area/fo-area.h"
#include "area/fo-area-list-item.h"
#include "fo-list-item-private.h"

void
fo_list_item_area_new2 (FoFo                *fo,
			FoFoAreaNew2Context *context,
			GError             **error)
{
  FoListItem *list_item = (FoListItem *) fo;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (list_item != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM (list_item));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_list_item_new ();
  use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-item parent before new area:");
  fo_object_debug_dump (use_parent_area, 0);
  g_warning ("*** end list-item parent");
#endif

  fo_area_set_generated_by (new_area,
			    fo);
  fo_fo_area_list_append (fo,
			  new_area);
  fo_block_fo_update_area (fo,
			   new_area);
  use_parent_area = fo_area_break_resolve (use_parent_area,
					   new_area);
  fo_area_border_padding_space_resolve (use_parent_area,
					new_area);
  fo_area_add_child (use_parent_area,
		     new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area,
			  fo_area_get_available_width (new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-item parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end list-item parent");
#endif

  *(context->new_area) = new_area;
}
