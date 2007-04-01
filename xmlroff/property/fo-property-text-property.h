/* Fo
 * fo-property-text-property.h: Inline formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-text-property.h,v 1.2 2003/03/21 14:41:46 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_PROPERTY_TEXT_PROPERTY_H__
#define __FO_PROPERTY_TEXT_PROPERTY_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>
#include <fo-context.h>
#include <pango/pango.h>

G_BEGIN_DECLS

#define FO_TYPE_PROPERTY_TEXT_PROPERTY            (fo_property_text_property_get_type ())
#define FO_PROPERTY_TEXT_PROPERTY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_PROPERTY_TEXT_PROPERTY, FoPropertyTextProperty))
#define FO_PROPERTY_TEXT_PROPERTY_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_PROPERTY_TEXT_PROPERTY, FoPropertyTextPropertyIface))
#define FO_IS_PROPERTY_TEXT_PROPERTY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_PROPERTY_TEXT_PROPERTY))
#define FO_PROPERTY_TEXT_PROPERTY_GET_IFACE(obj)  ((FoPropertyTextPropertyIface *)g_type_interface_peek (((GTypeInstance *) FO_PROPERTY_TEXT_PROPERTY (obj))->g_class, FO_TYPE_PROPERTY_TEXT_PROPERTY))

typedef struct _FoPropertyTextProperty      FoPropertyTextProperty; /* Dummy typedef */
typedef struct _FoPropertyTextPropertyIface FoPropertyTextPropertyIface;

struct _FoPropertyTextPropertyIface
{
  GTypeInterface g_iface;

  PangoAttribute* (*new_attr) (FoProperty *property);
  PangoAttribute* (*new_attr_from_context) (FoProperty *property,
					    FoContext  *context);
};


GType fo_property_text_property_get_type      (void) G_GNUC_CONST;

PangoAttribute * fo_property_text_property_new_attr (FoProperty *property);
PangoAttribute * fo_property_text_property_new_attr_from_context (FoProperty *property,
								  FoContext  *context);

G_END_DECLS

#endif /* !__FO_PROPERTY_TEXT_PROPERTY_H__ */
