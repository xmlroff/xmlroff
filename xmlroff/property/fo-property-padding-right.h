/* Fo
 * fo-property-padding-right.h: 'padding-right' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding-right.h,v 1.3 2003/05/16 10:40:07 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_RIGHT_H__
#define __FO_PROPERTY_PADDING_RIGHT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-right */
/* <padding-width> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_PADDING_RIGHT              (fo_property_padding_right_get_type ())
#define FO_PROPERTY_PADDING_RIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_RIGHT, FoPropertyPaddingRight))
#define FO_PROPERTY_PADDING_RIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_RIGHT, FoPropertyPaddingRightClass))
#define FO_IS_PROPERTY_PADDING_RIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_RIGHT))
#define FO_IS_PROPERTY_PADDING_RIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_RIGHT))
#define FO_PROPERTY_PADDING_RIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_RIGHT, FoPropertyPaddingRightClass))


typedef struct _FoPropertyPaddingRight      FoPropertyPaddingRight;
typedef struct _FoPropertyPaddingRightClass FoPropertyPaddingRightClass;

GType       fo_property_padding_right_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_padding_right_new         (void);
FoProperty* fo_property_padding_right_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_RIGHT_H__ */
