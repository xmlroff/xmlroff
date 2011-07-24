/* Fo
 * fo-static-content-area.c: Generate area for 'static-content' formatting object
 *
 * Copyright (C) 2008-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "area/fo-area-region.h"
#include "fo-static-content-private.h"

void
fo_static_content_area_new (FoFo                *fo,
			    FoFoAreaNew2Context *context,
			    GError             **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  FoAreaRegionNameAndArea name_and_area =
    {
      fo_name_get_value (fo_property_get_value (fo_static_content_get_flow_name (fo))),
      NULL
    };

  fo_area_traverse (context->parent_area,
		    G_POST_ORDER,
		    G_TRAVERSE_LEAVES,
		    2,
		    fo_area_region_is_named_region,
		    &name_and_area);

  if (name_and_area.area != NULL)
    {
      *(context->new_area) = fo_area_size_request (name_and_area.area); 
    }
  else
    {
      *(context->new_area) = NULL;
      context->truncate = TRUE;
    }
}
