/* Fo
 * fo-list_item_label.h: 'list-item-label' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-list-item-label.h,v 1.3 2003/03/19 21:11:39 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LIST_ITEM_LABEL_H__
#define __FO_LIST_ITEM_LABEL_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

typedef struct _FoListItemLabel      FoListItemLabel;
typedef struct _FoListItemLabelClass FoListItemLabelClass;

#define FO_TYPE_LIST_ITEM_LABEL              (fo_list_item_label_get_type ())
#define FO_LIST_ITEM_LABEL(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LIST_ITEM_LABEL, FoListItemLabel))
#define FO_LIST_ITEM_LABEL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LIST_ITEM_LABEL, FoListItemLabelClass))
#define FO_IS_LIST_ITEM_LABEL(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LIST_ITEM_LABEL))
#define FO_IS_LIST_ITEM_LABEL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LIST_ITEM_LABEL))
#define FO_LIST_ITEM_LABEL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LIST_ITEM_LABEL, FoListItemLabelClass))


GType        fo_list_item_label_get_type      (void) G_GNUC_CONST;
FoFo *       fo_list_item_label_new (void);

FoProperty * fo_list_item_label_get_id (FoFo       *fo_fo);
void         fo_list_item_label_set_id (FoFo       *fo_fo,
                                        FoProperty *new_id);
FoProperty * fo_list_item_label_get_keep_together (FoFo       *fo_fo);
void         fo_list_item_label_set_keep_together (FoFo       *fo_fo,
                                                   FoProperty *new_keep_together);
FoProperty * fo_list_item_label_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_list_item_label_set_keep_together_within_column (FoFo       *fo_fo,
                                                                 FoProperty *new_keep_together_within_column);
FoProperty * fo_list_item_label_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_list_item_label_set_keep_together_within_line (FoFo       *fo_fo,
                                                               FoProperty *new_keep_together_within_line);
FoProperty * fo_list_item_label_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_list_item_label_set_keep_together_within_page (FoFo       *fo_fo,
                                                               FoProperty *new_keep_together_within_page);
FoProperty * fo_list_item_label_get_role (FoFo       *fo_fo);
void         fo_list_item_label_set_role (FoFo       *fo_fo,
                                          FoProperty *new_role);
FoProperty * fo_list_item_label_get_source_document (FoFo       *fo_fo);
void         fo_list_item_label_set_source_document (FoFo       *fo_fo,
                                                     FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_LIST_ITEM_LABEL_H__ */
