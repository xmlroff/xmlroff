/* Fo
 * fo-property-border-bottom-style.h: 'border-bottom-style' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-bottom-style.h,v 1.3 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BOTTOM_STYLE_H__
#define __FO_PROPERTY_BORDER_BOTTOM_STYLE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-bottom-style */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-style> | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_BORDER_BOTTOM_STYLE              (fo_property_border_bottom_style_get_type ())
#define FO_PROPERTY_BORDER_BOTTOM_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM_STYLE, FoPropertyBorderBottomStyle))
#define FO_PROPERTY_BORDER_BOTTOM_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM_STYLE, FoPropertyBorderBottomStyleClass))
#define FO_IS_PROPERTY_BORDER_BOTTOM_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM_STYLE))
#define FO_IS_PROPERTY_BORDER_BOTTOM_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM_STYLE))
#define FO_PROPERTY_BORDER_BOTTOM_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BOTTOM_STYLE, FoPropertyBorderBottomStyleClass))


typedef struct _FoPropertyBorderBottomStyle      FoPropertyBorderBottomStyle;
typedef struct _FoPropertyBorderBottomStyleClass FoPropertyBorderBottomStyleClass;

GType        fo_property_border_bottom_style_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_bottom_style_new         (void);
FoProperty * fo_property_border_bottom_style_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BOTTOM_STYLE_H__ */
