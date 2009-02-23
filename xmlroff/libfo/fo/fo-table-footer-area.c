/* Fo
 * fo-table-footer-area.c: Generate area for 'table-footer' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-table-footer.h"
#include "fo-table-footer-private.h"

/**
 * fo_table_footer_area_new2:
 * @fo:      #FoTableFooter
 * @context: #FoFoAreaNew2Context
 * @error:   #GError
 * 
 * Create a new area for @fo and add it to the parent area.
 *
 * A pointer to the parent area is in @context.
 **/
void
fo_table_footer_area_new2 (FoFo                *fo,
			   FoFoAreaNew2Context *context,
			   GError             **error)
{
  FoTableFooter *table_footer = (FoTableFooter *) fo;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (table_footer != NULL);
  g_return_if_fail (FO_IS_TABLE_FOOTER (table_footer));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_table_footer_new ();
  use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-footer parent before new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end table-footer parent");
#endif

  fo_area_set_generated_by (FO_AREA (new_area), fo);
  FO_FO (fo)->areas = g_list_append (FO_FO (fo)->areas, new_area);
  fo_area_add_child (use_parent_area, new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area, fo_area_get_available_width (new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-footer parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end table-footer parent");
#endif

  *(context->new_area) = new_area;
}
