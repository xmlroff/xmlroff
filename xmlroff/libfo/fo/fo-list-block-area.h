/* Fo
 * fo-list-block-area.h: Generate area for list-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-list-block.h>
#include <libfo/area/fo-area.h>

#ifndef __FO_LIST_BLOCK_AREA_H__
#define __FO_LIST_BLOCK_AREA_H__

G_BEGIN_DECLS

void fo_list_block_area_new2 (FoFo                *fo_node,
			      FoFoAreaNew2Context *context,
			      GError             **error);

G_END_DECLS

#endif /* !__FO_LIST_BLOCK_AREA_H__ */
