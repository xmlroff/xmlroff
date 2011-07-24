/* Fo
 * fo-flow-area.c: Generate area for flow formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-region-body-area.h"
#include "area/fo-area-region.h"
#include "fo-flow-private.h"

void
fo_flow_area_new2 (FoFo *fo,
		   FoFoAreaNew2Context *context,
		   GError **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FLOW (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  gchar *name =
    fo_name_get_value (fo_property_get_value (fo_flow_get_flow_name (fo)));

  FoAreaRegionNameAndArea name_and_area =
    {
      name,
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
      fo_area_set_generated_by (name_and_area.area,
				fo);
      fo_fo_area_list_append (fo,
			      name_and_area.area);
      *(context->new_area) = fo_area_size_request (name_and_area.area); 
    }
  else
    {
      *(context->new_area) = NULL;
      context->truncate = TRUE;
    }

  g_free (name);
}
