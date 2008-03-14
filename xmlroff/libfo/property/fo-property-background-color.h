/* Fo
 * fo-property-background-color.h: 'background-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
  * Copyright (C) 2007 Menteith Consulting Ltd
*
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BACKGROUND_COLOR_H__
#define __FO_PROPERTY_BACKGROUND_COLOR_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* background-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | transparent | inherit */
/* Initial value: transparent */

#define FO_TYPE_PROPERTY_BACKGROUND_COLOR              (fo_property_background_color_get_type ())
#define FO_PROPERTY_BACKGROUND_COLOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BACKGROUND_COLOR, FoPropertyBackgroundColor))
#define FO_PROPERTY_BACKGROUND_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BACKGROUND_COLOR, FoPropertyBackgroundColorClass))
#define FO_IS_PROPERTY_BACKGROUND_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BACKGROUND_COLOR))
#define FO_IS_PROPERTY_BACKGROUND_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BACKGROUND_COLOR))
#define FO_PROPERTY_BACKGROUND_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BACKGROUND_COLOR, FoPropertyBackgroundColorClass))


typedef struct _FoPropertyBackgroundColor      FoPropertyBackgroundColor;
typedef struct _FoPropertyBackgroundColorClass FoPropertyBackgroundColorClass;

GType        fo_property_background_color_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_background_color_new         (void);
FoProperty * fo_property_background_color_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BACKGROUND_COLOR_H__ */
