/* Fo
 * fo-property-font-size.h: 'font-size' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_SIZE_H__
#define __FO_PROPERTY_FONT_SIZE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* font-size */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <absolute-size> | <relative-size> | <length> | <percentage> | inherit */
/* Initial value: medium */

#define FO_TYPE_PROPERTY_FONT_SIZE              (fo_property_font_size_get_type ())
#define FO_PROPERTY_FONT_SIZE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FONT_SIZE, FoPropertyFontSize))
#define FO_PROPERTY_FONT_SIZE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FONT_SIZE, FoPropertyFontSizeClass))
#define FO_IS_PROPERTY_FONT_SIZE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FONT_SIZE))
#define FO_IS_PROPERTY_FONT_SIZE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FONT_SIZE))
#define FO_PROPERTY_FONT_SIZE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FONT_SIZE, FoPropertyFontSizeClass))


typedef struct _FoPropertyFontSize      FoPropertyFontSize;
typedef struct _FoPropertyFontSizeClass FoPropertyFontSizeClass;

GType        fo_property_font_size_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_font_size_new         (void);
FoProperty * fo_property_font_size_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_SIZE_H__ */
