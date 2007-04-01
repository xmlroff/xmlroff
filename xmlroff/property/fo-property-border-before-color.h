/* Fo
 * fo-property-border-before-color.h: 'border-before-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-before-color.h,v 1.3 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BEFORE_COLOR_H__
#define __FO_PROPERTY_BORDER_BEFORE_COLOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-before-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: the value of the 'color' property */

#define FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR              (fo_property_border_before_color_get_type ())
#define FO_PROPERTY_BORDER_BEFORE_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR, FoPropertyBorderBeforeColor))
#define FO_PROPERTY_BORDER_BEFORE_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR, FoPropertyBorderBeforeColorClass))
#define FO_IS_PROPERTY_BORDER_BEFORE_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR))
#define FO_IS_PROPERTY_BORDER_BEFORE_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR))
#define FO_PROPERTY_BORDER_BEFORE_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR, FoPropertyBorderBeforeColorClass))


typedef struct _FoPropertyBorderBeforeColor      FoPropertyBorderBeforeColor;
typedef struct _FoPropertyBorderBeforeColorClass FoPropertyBorderBeforeColorClass;

GType        fo_property_border_before_color_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_before_color_new         (void);
FoProperty * fo_property_border_before_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BEFORE_COLOR_H__ */
