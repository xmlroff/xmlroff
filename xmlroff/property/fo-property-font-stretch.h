/* Fo
 * fo-property-font-stretch.h: 'font-stretch' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-font-stretch.h,v 1.4 2003/05/16 11:01:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_STRETCH_H__
#define __FO_PROPERTY_FONT_STRETCH_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

/* font-stretch */
/* normal | wider | narrower | ultra-condensed | extra-condensed | condensed | semi-condensed | semi-expanded | expanded | extra-expanded | ultra-expanded | inherit */
/* Initial value: normal */
/* FoEnumFontStretch typedef moved to fo-utils.h */

GType fo_enum_font_stretch_get_type (void);
#define FO_TYPE_ENUM_FONT_STRETCH fo_enum_font_stretch_get_type ()

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
