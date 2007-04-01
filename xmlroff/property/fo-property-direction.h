/* Fo
 * fo-property-direction.h: 'direction' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-direction.h,v 1.4 2004/03/24 11:56:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_DIRECTION_H__
#define __FO_PROPERTY_DIRECTION_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* direction */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* ltr | rtl | inherit */
/* Initial value: ltr */

#define FO_TYPE_PROPERTY_DIRECTION              (fo_property_direction_get_type ())
#define FO_PROPERTY_DIRECTION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_DIRECTION, FoPropertyDirection))
#define FO_PROPERTY_DIRECTION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_DIRECTION, FoPropertyDirectionClass))
#define FO_IS_PROPERTY_DIRECTION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_DIRECTION))
#define FO_IS_PROPERTY_DIRECTION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_DIRECTION))
#define FO_PROPERTY_DIRECTION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_DIRECTION, FoPropertyDirectionClass))


typedef struct _FoPropertyDirection      FoPropertyDirection;
typedef struct _FoPropertyDirectionClass FoPropertyDirectionClass;

GType        fo_property_direction_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_direction_new         (void);
FoProperty * fo_property_direction_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_DIRECTION_H__ */
