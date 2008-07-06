/* Fo
 * fo-property-font-style.h: 'font-style' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_STYLE_H__
#define __FO_PROPERTY_FONT_STYLE_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

/* font-style */
/* normal | italic | oblique | backslant | inherit */
/* Initial value: normal */

#define FO_TYPE_PROPERTY_FONT_STYLE              (fo_property_font_style_get_type ())
#define FO_PROPERTY_FONT_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FONT_STYLE, FoPropertyFontStyle))
#define FO_PROPERTY_FONT_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FONT_STYLE, FoPropertyFontStyleClass))
#define FO_IS_PROPERTY_FONT_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FONT_STYLE))
#define FO_IS_PROPERTY_FONT_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FONT_STYLE))
#define FO_PROPERTY_FONT_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FONT_STYLE, FoPropertyFontStyleClass))


typedef struct _FoPropertyFontStyle      FoPropertyFontStyle;
typedef struct _FoPropertyFontStyleClass FoPropertyFontStyleClass;

GType       fo_property_font_style_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_font_style_new         (void);
FoProperty* fo_property_font_style_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_STYLE_H__ */
