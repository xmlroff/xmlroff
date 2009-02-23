/* Fo
 * fo-table-body-area.c: Generate area for 'table-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-table-body.h"
#include "fo-table-body-private.h"

/**
 * fo_table_body_area_new2:
 * @fo:      #FoTableBody
 * @context: #FoFoAreaNew2Context
 * @error:   #GError
 * 
 * Create a new area for @fo and add it to the parent area.
 *
 * A pointer to the parent area is in @context.
 **/
void
fo_table_body_area_new2 (FoFo                *fo,
			 FoFoAreaNew2Context *context,
			 GError             **error)
{
  FoTableBody *table_body = (FoTableBody *) fo;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (table_body != NULL);
  g_return_if_fail (FO_IS_TABLE_BODY (table_body));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_table_body_new ();
  use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-body parent before new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end table-body parent");
#endif

  fo_area_set_generated_by (FO_AREA (new_area), fo);
  FO_FO (fo)->areas = g_list_append (FO_FO (fo)->areas, new_area);
  fo_area_add_child (use_parent_area, new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area, fo_area_get_available_width (new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-body parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end table-body parent");
#endif

  *(context->new_area) = new_area;
}
