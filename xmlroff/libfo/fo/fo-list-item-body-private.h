/* Fo
 * fo-list-item-body-private.h: Structures private to 'list-item-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LIST_ITEM_BODY_PRIVATE_H__
#define __FO_LIST_ITEM_BODY_PRIVATE_H__

#include <libfo/fo/fo-fo.h>
#include <libfo/fo/fo-marker-parent-private.h>
#include <libfo/fo/fo-list-item-body.h>

G_BEGIN_DECLS

struct _FoListItemBody
{
  FoMarkerParent parent_instance;

  FoProperty *id;
  FoProperty *keep_together;
  FoProperty *keep_together_within_column;
  FoProperty *keep_together_within_line;
  FoProperty *keep_together_within_page;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoListItemBodyClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_LIST_ITEM_BODY_PRIVATE_H__ */
