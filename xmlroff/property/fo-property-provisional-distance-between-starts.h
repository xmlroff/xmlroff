/* Fo
 * fo-property-provisional-distance-between-starts.h: 'provisional-distance-between-starts' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-provisional-distance-between-starts.h,v 1.4 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS_H__
#define __FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* provisional-distance-between-starts */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <length> | <percentage> | inherit */
/* Initial value: 24.0pt */

#define FO_TYPE_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS              (fo_property_provisional_distance_between_starts_get_type ())
#define FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS, FoPropertyProvisionalDistanceBetweenStarts))
#define FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS, FoPropertyProvisionalDistanceBetweenStartsClass))
#define FO_IS_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS))
#define FO_IS_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS))
#define FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS, FoPropertyProvisionalDistanceBetweenStartsClass))


typedef struct _FoPropertyProvisionalDistanceBetweenStarts      FoPropertyProvisionalDistanceBetweenStarts;
typedef struct _FoPropertyProvisionalDistanceBetweenStartsClass FoPropertyProvisionalDistanceBetweenStartsClass;

GType       fo_property_provisional_distance_between_starts_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_provisional_distance_between_starts_new         (void);
FoProperty* fo_property_provisional_distance_between_starts_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS_H__ */
