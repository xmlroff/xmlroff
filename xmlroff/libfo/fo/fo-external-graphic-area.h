/* Fo
 * fo-external-graphic-area.h: Generate area for external-graphic formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/fo-doc.h>

#ifndef __FO_EXTERNAL_GRAPHIC_AREA_H__
#define __FO_EXTERNAL_GRAPHIC_AREA_H__

G_BEGIN_DECLS

void fo_external_graphic_get_text_attr_list (FoFo    *fo_inline_fo,
					     FoDoc   *fo_doc,
					     GString *text,
					     GList  **attr_glist,
					     guint    debug_level);

G_END_DECLS

#endif /* !__FO_EXTERNAL_GRAPHIC_AREA_H__ */
