/* Fo
 * fo-table-row-area.c: Generate area for table-row formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-row-area.c,v 1.2 2003/04/15 12:12:08 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo-block-fo.h"
#include "fo-area.h"
#include <fo-area-table-row.h>
#include <fo-table-row-private.h>

void
fo_table_row_area_new2 (FoFo         *fo_node,
			 FoFoAreaNew2Context *context,
			 GError **error)
{
  FoTableRow *table_row = (FoTableRow *) fo_node;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (table_row != NULL);
  g_return_if_fail (FO_IS_TABLE_ROW (table_row));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_table_row_new ();
  use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-row parent before new area:");
  fo_object_debug_dump (use_parent_area, 0);
  g_warning ("*** end table-row parent");
#endif

  FO_AREA (new_area)->generated_by = fo_node;
  FO_FO (fo_node)->areas = g_list_append (FO_FO (fo_node)->areas, new_area);
  /*
    fo_block_fo_update_area (fo_node, new_area);
  */
  use_parent_area = fo_area_break_resolve (use_parent_area, new_area);
  fo_area_border_padding_space_resolve (use_parent_area, new_area);
  fo_area_add_child (use_parent_area, new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area, fo_area_get_available_width (new_area));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-row parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end table-row parent");
#endif

  *(context->new_area) = new_area;
}
