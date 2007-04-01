/* Fo
 * fo-property-font-size.h: 'font-size' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-font-size.h,v 1.4 2004/03/31 21:12:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_FONT_SIZE_H__
#define __FO_PROPERTY_FONT_SIZE_H__

#include <libfo/fo-utils.h>

typedef struct _FoPropertyFontSize      FoPropertyFontSize;
typedef struct _FoPropertyFontSizeClass FoPropertyFontSizeClass;

#include <property/fo-property.h>

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


GType        fo_property_font_size_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_font_size_new         (void);
FoProperty * fo_property_font_size_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FONT_SIZE_H__ */
