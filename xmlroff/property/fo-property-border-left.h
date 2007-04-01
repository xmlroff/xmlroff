/* Fo
 * fo-property-border-left.h: 'border-left' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-border-left.h,v 1.3 2005/04/07 17:56:42 jrosse1 Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_LEFT_H__
#define __FO_PROPERTY_BORDER_LEFT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-left */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER_LEFT              (fo_property_border_left_get_type ())
#define FO_PROPERTY_BORDER_LEFT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_LEFT, FoPropertyBorderLeft))
#define FO_PROPERTY_BORDER_LEFT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_LEFT, FoPropertyBorderLeftClass))
#define FO_IS_PROPERTY_BORDER_LEFT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_LEFT))
#define FO_IS_PROPERTY_BORDER_LEFT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_LEFT))
#define FO_PROPERTY_BORDER_LEFT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_LEFT, FoPropertyBorderLeftClass))


typedef struct _FoPropertyBorderLeft      FoPropertyBorderLeft;
typedef struct _FoPropertyBorderLeftClass FoPropertyBorderLeftClass;

GType        fo_property_border_left_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_left_new         (void);
FoProperty * fo_property_border_left_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_LEFT_H__ */
