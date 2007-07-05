/* Fo
 * fo-property-border-width.h: 'border-width' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_WIDTH_H__
#define __FO_PROPERTY_BORDER_WIDTH_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-width */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* <border-width>{1,4} | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER_WIDTH              (fo_property_border_width_get_type ())
#define FO_PROPERTY_BORDER_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_WIDTH, FoPropertyBorderWidth))
#define FO_PROPERTY_BORDER_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_WIDTH, FoPropertyBorderWidthClass))
#define FO_IS_PROPERTY_BORDER_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_WIDTH))
#define FO_IS_PROPERTY_BORDER_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_WIDTH))
#define FO_PROPERTY_BORDER_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_WIDTH, FoPropertyBorderWidthClass))


typedef struct _FoPropertyBorderWidth      FoPropertyBorderWidth;
typedef struct _FoPropertyBorderWidthClass FoPropertyBorderWidthClass;

GType        fo_property_border_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_width_new         (void);
FoProperty * fo_property_border_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_WIDTH_H__ */
