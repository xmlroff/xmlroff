/* Fo
 * fo-list-item-label-private.h: Structures private to 'list-item-label' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-list-item-label-private.h,v 1.3 2003/03/11 00:04:07 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LIST_ITEM_LABEL_PRIVATE_H__
#define __FO_LIST_ITEM_LABEL_PRIVATE_H__

#include "fo/fo-fo.h"
#include "fo/fo-marker-parent-private.h"
#include "fo-list-item-label.h"

G_BEGIN_DECLS

struct _FoListItemLabel
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

struct _FoListItemLabelClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_LIST_ITEM_LABEL_PRIVATE_H__ */
