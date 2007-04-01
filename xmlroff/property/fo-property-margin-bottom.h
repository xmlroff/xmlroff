/* Fo
 * fo-property-margin-bottom.h: 'margin-bottom' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-margin-bottom.h,v 1.3 2004/02/24 10:21:11 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_MARGIN_BOTTOM_H__
#define __FO_PROPERTY_MARGIN_BOTTOM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* margin-bottom */
/* <margin-width> | inherit */
/* Initial value: 0pt */

#define FO_TYPE_PROPERTY_MARGIN_BOTTOM              (fo_property_margin_bottom_get_type ())
#define FO_PROPERTY_MARGIN_BOTTOM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MARGIN_BOTTOM, FoPropertyMarginBottom))
#define FO_PROPERTY_MARGIN_BOTTOM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MARGIN_BOTTOM, FoPropertyMarginBottomClass))
#define FO_IS_PROPERTY_MARGIN_BOTTOM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MARGIN_BOTTOM))
#define FO_IS_PROPERTY_MARGIN_BOTTOM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MARGIN_BOTTOM))
#define FO_PROPERTY_MARGIN_BOTTOM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MARGIN_BOTTOM, FoPropertyMarginBottomClass))


typedef struct _FoPropertyMarginBottom      FoPropertyMarginBottom;
typedef struct _FoPropertyMarginBottomClass FoPropertyMarginBottomClass;

GType       fo_property_margin_bottom_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_margin_bottom_new         (void);
FoProperty* fo_property_margin_bottom_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MARGIN_BOTTOM_H__ */
