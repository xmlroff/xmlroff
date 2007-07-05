/* Fo
 * fo-block-block-area.c: Generate area for block-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-area.h"
#include "fo-block-block-private.h"

void
fo_block_block_area_new2 (FoFo         *fo,
			  FoFoAreaNew2Context *context,
			  GError **error)
{
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK_BLOCK (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_area_new ();
  use_parent_area = context->parent_area;

  fo_area_set_generated_by (new_area, fo);
  fo->areas = g_list_append (fo->areas, new_area);
  fo_area_add_child (use_parent_area, new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area, fo_area_get_available_width (new_area));

  *(context->new_area) = new_area;
}
