/* Fo
 * fo-property-font-variant.h: 'font-variant' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-font-variant.h,v 1.4 2003/05/16 11:01:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_VARIANT_H__
#define __FO_PROPERTY_FONT_VARIANT_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

/* font-variant */
/* normal | small-caps | inherit */
/* Initial value: normal */
/* FoEnumFontVariant typedef moved to fo-utils.h */

GType fo_enum_font_variant_get_type (void);
#define FO_TYPE_ENUM_FONT_VARIANT fo_enum_font_variant_get_type ()

#define FO_TYPE_PROPERTY_FONT_VARIANT              (fo_property_font_variant_get_type ())
#define FO_PROPERTY_FONT_VARIANT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FONT_VARIANT, FoPropertyFontVariant))
#define FO_PROPERTY_FONT_VARIANT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FONT_VARIANT, FoPropertyFontVariantClass))
#define FO_IS_PROPERTY_FONT_VARIANT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FONT_VARIANT))
#define FO_IS_PROPERTY_FONT_VARIANT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FONT_VARIANT))
#define FO_PROPERTY_FONT_VARIANT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FONT_VARIANT, FoPropertyFontVariantClass))


typedef struct _FoPropertyFontVariant      FoPropertyFontVariant;
typedef struct _FoPropertyFontVariantClass FoPropertyFontVariantClass;

GType       fo_property_font_variant_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_font_variant_new         (void);
FoProperty* fo_property_font_variant_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_VARIANT_H__ */
