/* Fo
 * fo-wrapper-block-area.c: Generate area for wrapper-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#include "area/fo-area-area.h"
#include "fo-wrapper-block.h"
#include "fo-wrapper-block-private.h"

/**
 * fo_wrapper_block_area_new2:
 * @fo_node: #FoWrapperBlock formatting object
 * @context: Extra information necessary
 * @error:   #GError
 * 
 * 
 **/
void
fo_wrapper_block_area_new2 (FoFo                *fo_node,
			    FoFoAreaNew2Context *context,
			    GError             **error)
{
  FoWrapperBlock *wrapper_block = (FoWrapperBlock *) fo_node;
  FoArea *use_parent_area;
  FoArea *new_area;

  g_return_if_fail (wrapper_block != NULL);
  g_return_if_fail (FO_IS_WRAPPER_BLOCK (wrapper_block));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  new_area = fo_area_area_new ();
  use_parent_area = context->parent_area;

  fo_area_set_generated_by (FO_AREA (new_area), fo_node);
  FO_FO (fo_node)->areas = g_list_append (FO_FO (fo_node)->areas, new_area);
  fo_area_add_child (use_parent_area, new_area);
  new_area = fo_area_size_request (new_area);
  fo_area_area_set_width (new_area, fo_area_get_available_width (new_area));

  *(context->new_area) = new_area;
}
