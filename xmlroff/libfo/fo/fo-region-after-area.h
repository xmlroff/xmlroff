/* Fo
 * fo-region-after-area.h: Generate area for 'region-after' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

#ifndef __FO_REGION_AFTER_AREA_H__
#define __FO_REGION_AFTER_AREA_H__

G_BEGIN_DECLS

void fo_region_after_area_new (FoFo                *fo,
			       FoFoAreaNew2Context *context,
			       GError             **error);

G_END_DECLS

#endif /* !__FO_REGION_AFTER_AREA_H__ */
