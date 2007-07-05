/* Fo
 * fo-area-list-item.h: Area object for 'list-item' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_LIST_ITEM_H__
#define __FO_AREA_LIST_ITEM_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaListItem      FoAreaListItem;
typedef struct _FoAreaListItemClass FoAreaListItemClass;

#define FO_TYPE_AREA_LIST_ITEM              (fo_area_list_item_get_type ())
#define FO_AREA_LIST_ITEM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_LIST_ITEM, FoAreaListItem))
#define FO_AREA_LIST_ITEM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_LIST_ITEM, FoAreaListItemClass))
#define FO_IS_AREA_LIST_ITEM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_LIST_ITEM))
#define FO_IS_AREA_LIST_ITEM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_LIST_ITEM))
#define FO_AREA_LIST_ITEM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_LIST_ITEM, FoAreaListItemClass))


GType   fo_area_list_item_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_list_item_new (void);

G_END_DECLS

#endif /* !__FO_AREA_LIST_ITEM_H__ */
