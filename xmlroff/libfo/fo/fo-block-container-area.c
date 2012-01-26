/* Fo
 * fo-block-container-area.c: Generate area for block-container formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011-2012 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-viewport-reference.h"
#include "fo-block-container-private.h"

void
fo_block_container_area_new2 (FoFo         *fo,
			      FoFoAreaNew2Context *context,
			      GError **error)
{
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK_CONTAINER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_viewport_reference_new ();
  use_parent_area = context->parent_area;

  fo_area_set_generated_by (new_area, fo);
  fo_fo_area_list_append (fo,
			  new_area);
  fo_area_add_child (use_parent_area,
		     new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area,
			  fo_area_get_available_width (new_area));

  *(context->new_area) = new_area;
}
