/* Fo
 * fo-property-margin-right.h: 'margin-right' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-margin-right.h,v 1.3 2004/02/24 10:21:11 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_MARGIN_RIGHT_H__
#define __FO_PROPERTY_MARGIN_RIGHT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* margin-right */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <margin-width> | inherit */
/* Initial value: 0pt */

#define FO_TYPE_PROPERTY_MARGIN_RIGHT              (fo_property_margin_right_get_type ())
#define FO_PROPERTY_MARGIN_RIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MARGIN_RIGHT, FoPropertyMarginRight))
#define FO_PROPERTY_MARGIN_RIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MARGIN_RIGHT, FoPropertyMarginRightClass))
#define FO_IS_PROPERTY_MARGIN_RIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MARGIN_RIGHT))
#define FO_IS_PROPERTY_MARGIN_RIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MARGIN_RIGHT))
#define FO_PROPERTY_MARGIN_RIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MARGIN_RIGHT, FoPropertyMarginRightClass))


typedef struct _FoPropertyMarginRight      FoPropertyMarginRight;
typedef struct _FoPropertyMarginRightClass FoPropertyMarginRightClass;

GType       fo_property_margin_right_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_margin_right_new         (void);
FoProperty* fo_property_margin_right_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MARGIN_RIGHT_H__ */
