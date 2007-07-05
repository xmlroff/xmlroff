/* Fo
 * fo-property-border-color.h: 'border-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_COLOR_H__
#define __FO_PROPERTY_BORDER_COLOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-color */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <color> | transparent ]{1,4} | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER_COLOR              (fo_property_border_color_get_type ())
#define FO_PROPERTY_BORDER_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_COLOR, FoPropertyBorderColor))
#define FO_PROPERTY_BORDER_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_COLOR, FoPropertyBorderColorClass))
#define FO_IS_PROPERTY_BORDER_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_COLOR))
#define FO_IS_PROPERTY_BORDER_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_COLOR))
#define FO_PROPERTY_BORDER_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_COLOR, FoPropertyBorderColorClass))


typedef struct _FoPropertyBorderColor      FoPropertyBorderColor;
typedef struct _FoPropertyBorderColorClass FoPropertyBorderColorClass;

GType        fo_property_border_color_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_color_new         (void);
FoProperty * fo_property_border_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_COLOR_H__ */
