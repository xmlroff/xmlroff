/* Fo
 * fo-flow-area.h: Generate area for flow formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-flow-area.h,v 1.5 2003/05/23 16:36:48 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include <pango/pango.h>
#include <libfo/fo-utils.h>
#include <libfo/fo-doc.h>
#include <fo-flow.h>
#include <fo-area.h>

#ifndef __FO_FLOW_AREA_H__
#define __FO_FLOW_AREA_H__

G_BEGIN_DECLS

void fo_flow_area_new (FoFo    *fo,
		       FoDoc   *fo_doc,
		       FoArea  *parent_area,
		       FoArea **new_area,
		       guint    debug_level);
void fo_flow_area_new2 (FoFo                *fo,
			FoFoAreaNew2Context *context,
			GError             **error);

G_END_DECLS

#endif /* !__FO_FLOW_AREA_H__ */
