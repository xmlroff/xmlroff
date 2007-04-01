/* Fo
 * fo-multi-toggle.h: 'multi-toggle' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-multi-toggle.h,v 1.4 2005/08/23 11:00:32 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_TOGGLE_H__
#define __FO_MULTI_TOGGLE_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoMultiToggle      FoMultiToggle;
typedef struct _FoMultiToggleClass FoMultiToggleClass;

#define FO_TYPE_MULTI_TOGGLE              (fo_multi_toggle_get_type ())
#define FO_MULTI_TOGGLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_MULTI_TOGGLE, FoMultiToggle))
#define FO_MULTI_TOGGLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_MULTI_TOGGLE, FoMultiToggleClass))
#define FO_IS_MULTI_TOGGLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_MULTI_TOGGLE))
#define FO_IS_MULTI_TOGGLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_MULTI_TOGGLE))
#define FO_MULTI_TOGGLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_MULTI_TOGGLE, FoMultiToggleClass))


GType        fo_multi_toggle_get_type (void) G_GNUC_CONST;
FoFo *       fo_multi_toggle_new      (void);

FoProperty * fo_multi_toggle_get_id (FoFo       *fo_fo);
void         fo_multi_toggle_set_id (FoFo       *fo_fo,
                                     FoProperty *new_id);
FoProperty * fo_multi_toggle_get_role (FoFo       *fo_fo);
void         fo_multi_toggle_set_role (FoFo       *fo_fo,
                                       FoProperty *new_role);
FoProperty * fo_multi_toggle_get_source_document (FoFo       *fo_fo);
void         fo_multi_toggle_set_source_document (FoFo       *fo_fo,
                                                  FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_MULTI_TOGGLE_H__ */
