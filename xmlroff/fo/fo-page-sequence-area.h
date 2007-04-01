/* Fo
 * fo-page-sequence-area.h: Generate area for page-sequence formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-page-sequence-area.h,v 1.4 2003/05/23 16:36:48 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <fo-page-sequence.h>
#include <fo-area.h>

#ifndef __FO_PAGE_SEQUENCE_AREA_H__
#define __FO_PAGE_SEQUENCE_AREA_H__

G_BEGIN_DECLS

void fo_page_sequence_area_new (FoFo    *fo_node,
				FoDoc   *fo_doc,
				FoArea  *parent_area,
				FoArea **new_area,
				guint    debug_level);
void fo_page_sequence_area_new2 (FoFo                *fo_node,
				 FoFoAreaNew2Context *context,
				 GError             **error);

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_AREA_H__ */
