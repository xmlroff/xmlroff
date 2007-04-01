/* Fo
 * fo-list-block-area.h: Generate area for list-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-list-block-area.h,v 1.4 2003/05/23 16:36:48 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <fo-list-block.h>
#include <fo-area.h>

#ifndef __FO_LIST_BLOCK_AREA_H__
#define __FO_LIST_BLOCK_AREA_H__

G_BEGIN_DECLS

void fo_list_block_area_new (FoFo    *fo,
			     FoDoc   *fo_doc,
			     FoArea  *parent_area,
			     FoArea **new_area,
			     guint    debug_level);
void fo_list_block_area_new2 (FoFo                *fo_node,
			      FoFoAreaNew2Context *context,
			      GError             **error);

G_END_DECLS

#endif /* !__FO_LIST_BLOCK_AREA_H__ */
