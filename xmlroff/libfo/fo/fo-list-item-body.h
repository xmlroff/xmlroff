/* Fo
 * fo-list_item_body.h: 'list-item-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LIST_ITEM_BODY_H__
#define __FO_LIST_ITEM_BODY_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoListItemBody      FoListItemBody;
typedef struct _FoListItemBodyClass FoListItemBodyClass;

#define FO_TYPE_LIST_ITEM_BODY              (fo_list_item_body_get_type ())
#define FO_LIST_ITEM_BODY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LIST_ITEM_BODY, FoListItemBody))
#define FO_LIST_ITEM_BODY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LIST_ITEM_BODY, FoListItemBodyClass))
#define FO_IS_LIST_ITEM_BODY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LIST_ITEM_BODY))
#define FO_IS_LIST_ITEM_BODY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LIST_ITEM_BODY))
#define FO_LIST_ITEM_BODY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LIST_ITEM_BODY, FoListItemBodyClass))


GType        fo_list_item_body_get_type      (void) G_GNUC_CONST;
FoFo *       fo_list_item_body_new (void);

FoProperty * fo_list_item_body_get_id (FoFo       *fo_fo);
void         fo_list_item_body_set_id (FoFo       *fo_fo,
                                       FoProperty *new_id);
FoProperty * fo_list_item_body_get_keep_together (FoFo       *fo_fo);
void         fo_list_item_body_set_keep_together (FoFo       *fo_fo,
                                                  FoProperty *new_keep_together);
FoProperty * fo_list_item_body_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_list_item_body_set_keep_together_within_column (FoFo       *fo_fo,
                                                                FoProperty *new_keep_together_within_column);
FoProperty * fo_list_item_body_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_list_item_body_set_keep_together_within_line (FoFo       *fo_fo,
                                                              FoProperty *new_keep_together_within_line);
FoProperty * fo_list_item_body_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_list_item_body_set_keep_together_within_page (FoFo       *fo_fo,
                                                              FoProperty *new_keep_together_within_page);
FoProperty * fo_list_item_body_get_role (FoFo       *fo_fo);
void         fo_list_item_body_set_role (FoFo       *fo_fo,
                                         FoProperty *new_role);
FoProperty * fo_list_item_body_get_source_document (FoFo       *fo_fo);
void         fo_list_item_body_set_source_document (FoFo       *fo_fo,
                                                    FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_LIST_ITEM_BODY_H__ */
