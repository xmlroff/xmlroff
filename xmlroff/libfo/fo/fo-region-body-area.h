/* Fo
 * fo-region-body-area.h: Generate area for region-body formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo-doc.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/area/fo-area.h>

#ifndef __FO_REGION_BODY_AREA_H__
#define __FO_REGION_BODY_AREA_H__

G_BEGIN_DECLS

void fo_region_body_area_new (FoFo    *fo,
			      FoDoc   *fo_doc,
			      FoArea  *parent_area,
			      FoArea **new_area,
			      guint    debug_level);

G_END_DECLS

#endif /* !__FO_REGION_BODY_AREA_H__ */
