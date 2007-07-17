/* Fo
 * fo-flow-area.c: Generate area for flow formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-region-body-area.h"
#include "area/fo-area.h"
#include "area/fo-area-area.h"
#include "fo-flow-private.h"

void
fo_flow_area_new2 (FoFo *fo,
		   FoFoAreaNew2Context *context,
		   GError **error)
{
  FoFlow *flow = (FoFlow *) fo;

  g_return_if_fail (flow != NULL);
  g_return_if_fail (FO_IS_FLOW (flow));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  fo_region_body_area_new (fo_flow_get_region_master (fo),
			   context->fo_doc,
			   context->parent_area,
			   context->new_area,
			   context->debug_level);

  fo_area_set_generated_by (*(context->new_area), fo);
  FO_FO (fo)->areas = g_list_append (FO_FO (fo)->areas, *(context->new_area));
  fo_area_add_child (context->parent_area, *(context->new_area));
  *(context->new_area) = fo_area_size_request (*(context->new_area));
}
