/* Fo
 * fo-list-item-label-area.c: Generate area for list-item-label formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area.h"
#include "area/fo-area-area.h"
#include "fo-list-item-label-private.h"

void
fo_list_item_label_area_new2 (FoFo                *fo,
			      FoFoAreaNew2Context *context,
			      GError             **error)
{
  FoListItemLabel *list_item_label = (FoListItemLabel *) fo;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (list_item_label != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_LABEL (list_item_label));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_area_new ();
  use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-item-label parent before new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end list-item-label parent");
#endif

  fo_area_set_generated_by (new_area,
			    fo);
  fo_fo_area_list_append (fo,
			  new_area);
  fo_area_add_child (use_parent_area,
		     new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area,
			  fo_area_get_available_width (new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** list-item-label parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end list-item-label parent");
#endif

  *(context->new_area) = new_area;
}
