/* Fo
 * fo-property-border-after-color.h: 'border-after-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_AFTER_COLOR_H__
#define __FO_PROPERTY_BORDER_AFTER_COLOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-after-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: the value of the 'color' property */

#define FO_TYPE_PROPERTY_BORDER_AFTER_COLOR              (fo_property_border_after_color_get_type ())
#define FO_PROPERTY_BORDER_AFTER_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_AFTER_COLOR, FoPropertyBorderAfterColor))
#define FO_PROPERTY_BORDER_AFTER_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_AFTER_COLOR, FoPropertyBorderAfterColorClass))
#define FO_IS_PROPERTY_BORDER_AFTER_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_AFTER_COLOR))
#define FO_IS_PROPERTY_BORDER_AFTER_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_AFTER_COLOR))
#define FO_PROPERTY_BORDER_AFTER_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_AFTER_COLOR, FoPropertyBorderAfterColorClass))


typedef struct _FoPropertyBorderAfterColor      FoPropertyBorderAfterColor;
typedef struct _FoPropertyBorderAfterColorClass FoPropertyBorderAfterColorClass;

GType       fo_property_border_after_color_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_border_after_color_new         (void);
FoProperty* fo_property_border_after_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_AFTER_COLOR_H__ */
