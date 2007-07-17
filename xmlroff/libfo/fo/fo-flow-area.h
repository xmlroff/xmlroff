/* Fo
 * fo-flow-area.h: Generate area for flow formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo-doc.h>
#include <libfo/fo/fo-flow.h>
#include <libfo/area/fo-area.h>

#ifndef __FO_FLOW_AREA_H__
#define __FO_FLOW_AREA_H__

G_BEGIN_DECLS

void fo_flow_area_new2 (FoFo                *fo,
			FoFoAreaNew2Context *context,
			GError             **error);

G_END_DECLS

#endif /* !__FO_FLOW_AREA_H__ */
