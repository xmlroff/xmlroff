/* Fo
 * fo-property-border-bottom.h: 'border-bottom' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-border-bottom.h,v 1.3 2005/04/07 17:58:57 jrosse1 Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BOTTOM_H__
#define __FO_PROPERTY_BORDER_BOTTOM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-bottom */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER_BOTTOM              (fo_property_border_bottom_get_type ())
#define FO_PROPERTY_BORDER_BOTTOM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM, FoPropertyBorderBottom))
#define FO_PROPERTY_BORDER_BOTTOM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM, FoPropertyBorderBottomClass))
#define FO_IS_PROPERTY_BORDER_BOTTOM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BOTTOM))
#define FO_IS_PROPERTY_BORDER_BOTTOM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BOTTOM))
#define FO_PROPERTY_BORDER_BOTTOM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BOTTOM, FoPropertyBorderBottomClass))


typedef struct _FoPropertyBorderBottom      FoPropertyBorderBottom;
typedef struct _FoPropertyBorderBottomClass FoPropertyBorderBottomClass;

GType        fo_property_border_bottom_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_bottom_new         (void);
FoProperty * fo_property_border_bottom_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BOTTOM_H__ */
