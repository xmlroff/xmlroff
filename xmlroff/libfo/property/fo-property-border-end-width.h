/* Fo
 * fo-property-border-end-width.h: 'border-end-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_END_WIDTH_H__
#define __FO_PROPERTY_BORDER_END_WIDTH_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-end-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | <length-conditional> | inherit */
/* Initial value: medium */

#define FO_TYPE_PROPERTY_BORDER_END_WIDTH              (fo_property_border_end_width_get_type ())
#define FO_PROPERTY_BORDER_END_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_END_WIDTH, FoPropertyBorderEndWidth))
#define FO_PROPERTY_BORDER_END_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_END_WIDTH, FoPropertyBorderEndWidthClass))
#define FO_IS_PROPERTY_BORDER_END_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_END_WIDTH))
#define FO_IS_PROPERTY_BORDER_END_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_END_WIDTH))
#define FO_PROPERTY_BORDER_END_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_END_WIDTH, FoPropertyBorderEndWidthClass))


typedef struct _FoPropertyBorderEndWidth      FoPropertyBorderEndWidth;
typedef struct _FoPropertyBorderEndWidthClass FoPropertyBorderEndWidthClass;

GType        fo_property_border_end_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_end_width_new         (void);
FoProperty * fo_property_border_end_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_END_WIDTH_H__ */
