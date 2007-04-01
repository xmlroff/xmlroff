/* Fo
 * fo-property-font-weight.h: 'font-weight' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-font-weight.h,v 1.4 2005/08/18 09:46:05 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_WEIGHT_H__
#define __FO_PROPERTY_FONT_WEIGHT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* font-weight */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* normal | bold | bolder | lighter | 100 | 200 | 300 | 400 | 500 | 600 | 700 | 800 | 900 | inherit */
/* Initial value: normal */

#define FO_TYPE_PROPERTY_FONT_WEIGHT              (fo_property_font_weight_get_type ())
#define FO_PROPERTY_FONT_WEIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FONT_WEIGHT, FoPropertyFontWeight))
#define FO_PROPERTY_FONT_WEIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FONT_WEIGHT, FoPropertyFontWeightClass))
#define FO_IS_PROPERTY_FONT_WEIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FONT_WEIGHT))
#define FO_IS_PROPERTY_FONT_WEIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FONT_WEIGHT))
#define FO_PROPERTY_FONT_WEIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FONT_WEIGHT, FoPropertyFontWeightClass))


typedef struct _FoPropertyFontWeight      FoPropertyFontWeight;
typedef struct _FoPropertyFontWeightClass FoPropertyFontWeightClass;

GType        fo_property_font_weight_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_font_weight_new         (void);
FoProperty * fo_property_font_weight_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_WEIGHT_H__ */
