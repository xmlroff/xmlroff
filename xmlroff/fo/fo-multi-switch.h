/* Fo
 * fo-multi-switch.h: 'multi-switch' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-multi-switch.h,v 1.4 2005/09/08 21:36:12 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_SWITCH_H__
#define __FO_MULTI_SWITCH_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoMultiSwitch      FoMultiSwitch;
typedef struct _FoMultiSwitchClass FoMultiSwitchClass;

#define FO_TYPE_MULTI_SWITCH              (fo_multi_switch_get_type ())
#define FO_MULTI_SWITCH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_MULTI_SWITCH, FoMultiSwitch))
#define FO_MULTI_SWITCH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_MULTI_SWITCH, FoMultiSwitchClass))
#define FO_IS_MULTI_SWITCH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_MULTI_SWITCH))
#define FO_IS_MULTI_SWITCH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_MULTI_SWITCH))
#define FO_MULTI_SWITCH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_MULTI_SWITCH, FoMultiSwitchClass))


GType        fo_multi_switch_get_type (void) G_GNUC_CONST;
FoFo *       fo_multi_switch_new      (void);

FoProperty * fo_multi_switch_get_id (FoFo       *fo_fo);
void         fo_multi_switch_set_id (FoFo       *fo_fo,
                                     FoProperty *new_id);
FoProperty * fo_multi_switch_get_role (FoFo       *fo_fo);
void         fo_multi_switch_set_role (FoFo       *fo_fo,
                                       FoProperty *new_role);
FoProperty * fo_multi_switch_get_source_document (FoFo       *fo_fo);
void         fo_multi_switch_set_source_document (FoFo       *fo_fo,
                                                  FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_MULTI_SWITCH_H__ */
