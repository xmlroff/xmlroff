/* Fo
 * fo-list-block-area.c: Generate area for list-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area.h"
#include "area/fo-area-normal.h"
#include "fo-list-block-private.h"
#include "fo-block-fo.h"

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
