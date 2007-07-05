/* Fo
 * fo-property-border-left-color.h: 'border-left-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_LEFT_COLOR_H__
#define __FO_PROPERTY_BORDER_LEFT_COLOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-left-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: the value of the 'color' property */

#define FO_TYPE_PROPERTY_BORDER_LEFT_COLOR              (fo_property_border_left_color_get_type ())
#define FO_PROPERTY_BORDER_LEFT_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_LEFT_COLOR, FoPropertyBorderLeftColor))
#define FO_PROPERTY_BORDER_LEFT_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_LEFT_COLOR, FoPropertyBorderLeftColorClass))
#define FO_IS_PROPERTY_BORDER_LEFT_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_LEFT_COLOR))
#define FO_IS_PROPERTY_BORDER_LEFT_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_LEFT_COLOR))
#define FO_PROPERTY_BORDER_LEFT_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_LEFT_COLOR, FoPropertyBorderLeftColorClass))


typedef struct _FoPropertyBorderLeftColor      FoPropertyBorderLeftColor;
typedef struct _FoPropertyBorderLeftColorClass FoPropertyBorderLeftColorClass;

GType        fo_property_border_left_color_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_left_color_new         (void);
FoProperty * fo_property_border_left_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_LEFT_COLOR_H__ */
