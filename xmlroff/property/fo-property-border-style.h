/* Fo
 * fo-property-border-style.h: 'border-style' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-border-style.h,v 1.3 2005/03/10 11:46:36 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_STYLE_H__
#define __FO_PROPERTY_BORDER_STYLE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-style */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* <border-style>{1,4} | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER_STYLE              (fo_property_border_style_get_type ())
#define FO_PROPERTY_BORDER_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_STYLE, FoPropertyBorderStyle))
#define FO_PROPERTY_BORDER_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_STYLE, FoPropertyBorderStyleClass))
#define FO_IS_PROPERTY_BORDER_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_STYLE))
#define FO_IS_PROPERTY_BORDER_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_STYLE))
#define FO_PROPERTY_BORDER_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_STYLE, FoPropertyBorderStyleClass))


typedef struct _FoPropertyBorderStyle      FoPropertyBorderStyle;
typedef struct _FoPropertyBorderStyleClass FoPropertyBorderStyleClass;

GType        fo_property_border_style_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_style_new         (void);
FoProperty * fo_property_border_style_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_STYLE_H__ */
