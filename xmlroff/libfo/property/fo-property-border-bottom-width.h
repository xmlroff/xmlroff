/* Fo
 * fo-property-border-bottom-width.h: 'border-bottom-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BOTTOM_WIDTH_H__
#define __FO_PROPERTY_BORDER_BOTTOM_WIDTH_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border-bottom-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | inherit */
/* Initial value: medium */

#define FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH              (fo_property_border_bottom_width_get_type ())
#define FO_PROPERTY_BORDER_BOTTOM_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH, FoPropertyBorderBottomWidth))
#define FO_PROPERTY_BORDER_BOTTOM_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH, FoPropertyBorderBottomWidthClass))
#define FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH))
#define FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH))
#define FO_PROPERTY_BORDER_BOTTOM_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH, FoPropertyBorderBottomWidthClass))


typedef struct _FoPropertyBorderBottomWidth      FoPropertyBorderBottomWidth;
typedef struct _FoPropertyBorderBottomWidthClass FoPropertyBorderBottomWidthClass;

GType        fo_property_border_bottom_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_bottom_width_new         (void);
FoProperty * fo_property_border_bottom_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BOTTOM_WIDTH_H__ */
