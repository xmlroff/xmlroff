/* Fo
 * fo-property-border-bottom-color.h: 'border-bottom-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-bottom-color.h,v 1.3 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BOTTOM_COLOR_H__
#define __FO_PROPERTY_BORDER_BOTTOM_COLOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-bottom-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: the value of the 'color' property */

#define FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR              (fo_property_border_bottom_color_get_type ())
#define FO_PROPERTY_BORDER_BOTTOM_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR, FoPropertyBorderBottomColor))
#define FO_PROPERTY_BORDER_BOTTOM_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR, FoPropertyBorderBottomColorClass))
#define FO_IS_PROPERTY_BORDER_BOTTOM_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR))
#define FO_IS_PROPERTY_BORDER_BOTTOM_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR))
#define FO_PROPERTY_BORDER_BOTTOM_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR, FoPropertyBorderBottomColorClass))


typedef struct _FoPropertyBorderBottomColor      FoPropertyBorderBottomColor;
typedef struct _FoPropertyBorderBottomColorClass FoPropertyBorderBottomColorClass;

GType        fo_property_border_bottom_color_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_bottom_color_new         (void);
FoProperty * fo_property_border_bottom_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BOTTOM_COLOR_H__ */
