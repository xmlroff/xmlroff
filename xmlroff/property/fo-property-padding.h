/* Fo
 * fo-property-padding.h: 'padding' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_H__
#define __FO_PROPERTY_PADDING_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding */
/* <padding-width>{1,4} | inherit */
/* Initial value: not defined for shorthand properties */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_PADDING              (fo_property_padding_get_type ())
#define FO_PROPERTY_PADDING(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING, FoPropertyPadding))
#define FO_PROPERTY_PADDING_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING, FoPropertyPaddingClass))
#define FO_IS_PROPERTY_PADDING(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING))
#define FO_IS_PROPERTY_PADDING_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING))
#define FO_PROPERTY_PADDING_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING, FoPropertyPaddingClass))


typedef struct _FoPropertyPadding      FoPropertyPadding;
typedef struct _FoPropertyPaddingClass FoPropertyPaddingClass;

GType       fo_property_padding_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_padding_new         (void);
FoProperty* fo_property_padding_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_H__ */
