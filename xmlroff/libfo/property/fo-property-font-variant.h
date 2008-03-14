/* Fo
 * fo-property-font-variant.h: 'font-variant' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_VARIANT_H__
#define __FO_PROPERTY_FONT_VARIANT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* font-variant */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* normal | small-caps | inherit */
/* Initial value: normal */

#define FO_TYPE_PROPERTY_FONT_VARIANT              (fo_property_font_variant_get_type ())
#define FO_PROPERTY_FONT_VARIANT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FONT_VARIANT, FoPropertyFontVariant))
#define FO_PROPERTY_FONT_VARIANT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FONT_VARIANT, FoPropertyFontVariantClass))
#define FO_IS_PROPERTY_FONT_VARIANT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FONT_VARIANT))
#define FO_IS_PROPERTY_FONT_VARIANT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FONT_VARIANT))
#define FO_PROPERTY_FONT_VARIANT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FONT_VARIANT, FoPropertyFontVariantClass))


/**
 * FoPropertyFontVariant:
 *
 * Instance of the 'font-variant' property.
 **/
typedef struct _FoPropertyFontVariant      FoPropertyFontVariant;

/**
 * FoPropertyFontVariantClass:
 *
 * Class structure for the 'font-variant' property.
 **/
typedef struct _FoPropertyFontVariantClass FoPropertyFontVariantClass;

GType        fo_property_font_variant_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_font_variant_new         (void);
FoProperty * fo_property_font_variant_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_VARIANT_H__ */
