/* Fo
 * fo-property-color.h: 'color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_COLOR_H__
#define __FO_PROPERTY_COLOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* color */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: depends on user agent */

#define FO_TYPE_PROPERTY_COLOR              (fo_property_color_get_type ())
#define FO_PROPERTY_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_COLOR, FoPropertyColor))
#define FO_PROPERTY_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_COLOR, FoPropertyColorClass))
#define FO_IS_PROPERTY_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_COLOR))
#define FO_IS_PROPERTY_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_COLOR))
#define FO_PROPERTY_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_COLOR, FoPropertyColorClass))


typedef struct _FoPropertyColor      FoPropertyColor;
typedef struct _FoPropertyColorClass FoPropertyColorClass;

GType        fo_property_color_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_color_new         (void);
FoProperty * fo_property_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_COLOR_H__ */
