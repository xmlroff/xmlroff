/* Fo
 * fo-static-content-area.h: Generate area for static-content formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2008-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

#ifndef __FO_STATIC_CONTENT_AREA_H__
#define __FO_STATIC_CONTENT_AREA_H__

G_BEGIN_DECLS

void fo_static_content_area_new (FoFo                *fo,
				 FoFoAreaNew2Context *context,
				 GError             **error);

G_END_DECLS

#endif /* !__FO_STATIC_CONTENT_AREA_H__ */
