/* Fo
 * fo-property-font-stretch.h: 'font-stretch' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_STRETCH_H__
#define __FO_PROPERTY_FONT_STRETCH_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* font-stretch */
/* normal | wider | narrower | ultra-condensed | extra-condensed | condensed | semi-condensed | semi-expanded | expanded | extra-expanded | ultra-expanded | inherit */
/* Initial value: normal */

#define FO_TYPE_PROPERTY_FONT_STRETCH              (fo_property_font_stretch_get_type ())
#define FO_PROPERTY_FONT_STRETCH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FONT_STRETCH, FoPropertyFontStretch))
#define FO_PROPERTY_FONT_STRETCH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FONT_STRETCH, FoPropertyFontStretchClass))
#define FO_IS_PROPERTY_FONT_STRETCH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FONT_STRETCH))
#define FO_IS_PROPERTY_FONT_STRETCH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FONT_STRETCH))
#define FO_PROPERTY_FONT_STRETCH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FONT_STRETCH, FoPropertyFontStretchClass))


typedef struct _FoPropertyFontStretch      FoPropertyFontStretch;
typedef struct _FoPropertyFontStretchClass FoPropertyFontStretchClass;

GType       fo_property_font_stretch_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_font_stretch_new         (void);
FoProperty* fo_property_font_stretch_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_STRETCH_H__ */
