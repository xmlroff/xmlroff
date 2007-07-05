/* Fo
 * fo-list-item-area.h: Generate area for list-item formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-list-item.h>
#include <libfo/area/fo-area.h>

#ifndef __FO_LIST_ITEM_AREA_H__
#define __FO_LIST_ITEM_AREA_H__

G_BEGIN_DECLS

void fo_list_item_area_new (FoFo    *fo,
			    FoDoc   *fo_doc,
			    FoArea  *parent_area,
			    FoArea **new_area,
			    guint    debug_level);
void fo_list_item_area_new2 (FoFo                *fo_node,
			     FoFoAreaNew2Context *context,
			     GError             **error);

G_END_DECLS

#endif /* !__FO_LIST_ITEM_AREA_H__ */
