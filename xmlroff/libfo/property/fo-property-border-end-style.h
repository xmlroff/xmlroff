/* Fo
 * fo-property-border-end-style.h: 'border-end-style' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_END_STYLE_H__
#define __FO_PROPERTY_BORDER_END_STYLE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border-end-style */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-style> | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_BORDER_END_STYLE              (fo_property_border_end_style_get_type ())
#define FO_PROPERTY_BORDER_END_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_END_STYLE, FoPropertyBorderEndStyle))
#define FO_PROPERTY_BORDER_END_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_END_STYLE, FoPropertyBorderEndStyleClass))
#define FO_IS_PROPERTY_BORDER_END_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_END_STYLE))
#define FO_IS_PROPERTY_BORDER_END_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_END_STYLE))
#define FO_PROPERTY_BORDER_END_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_END_STYLE, FoPropertyBorderEndStyleClass))


typedef struct _FoPropertyBorderEndStyle      FoPropertyBorderEndStyle;
typedef struct _FoPropertyBorderEndStyleClass FoPropertyBorderEndStyleClass;

GType        fo_property_border_end_style_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_end_style_new         (void);
FoProperty * fo_property_border_end_style_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_END_STYLE_H__ */
