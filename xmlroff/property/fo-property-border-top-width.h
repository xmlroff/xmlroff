/* Fo
 * fo-property-border-top-width.h: 'border-top-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-top-width.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_TOP_WIDTH_H__
#define __FO_PROPERTY_BORDER_TOP_WIDTH_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-top-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | inherit */
/* Initial value: medium */

#define FO_TYPE_PROPERTY_BORDER_TOP_WIDTH              (fo_property_border_top_width_get_type ())
#define FO_PROPERTY_BORDER_TOP_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_TOP_WIDTH, FoPropertyBorderTopWidth))
#define FO_PROPERTY_BORDER_TOP_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_TOP_WIDTH, FoPropertyBorderTopWidthClass))
#define FO_IS_PROPERTY_BORDER_TOP_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_TOP_WIDTH))
#define FO_IS_PROPERTY_BORDER_TOP_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_TOP_WIDTH))
#define FO_PROPERTY_BORDER_TOP_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_TOP_WIDTH, FoPropertyBorderTopWidthClass))


typedef struct _FoPropertyBorderTopWidth      FoPropertyBorderTopWidth;
typedef struct _FoPropertyBorderTopWidthClass FoPropertyBorderTopWidthClass;

GType        fo_property_border_top_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_top_width_new         (void);
FoProperty * fo_property_border_top_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_TOP_WIDTH_H__ */
