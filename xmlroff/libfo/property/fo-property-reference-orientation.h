/* Fo
 * fo-property-reference-orientation.h: 'reference-orientation' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_REFERENCE_ORIENTATION_H__
#define __FO_PROPERTY_REFERENCE_ORIENTATION_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* reference-orientation */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* 0 | 90 | 180 | 270 | -90 | -180 | -270 | inherit */
/* Initial value: 0 */

#define FO_TYPE_PROPERTY_REFERENCE_ORIENTATION              (fo_property_reference_orientation_get_type ())
#define FO_PROPERTY_REFERENCE_ORIENTATION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_REFERENCE_ORIENTATION, FoPropertyReferenceOrientation))
#define FO_PROPERTY_REFERENCE_ORIENTATION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_REFERENCE_ORIENTATION, FoPropertyReferenceOrientationClass))
#define FO_IS_PROPERTY_REFERENCE_ORIENTATION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_REFERENCE_ORIENTATION))
#define FO_IS_PROPERTY_REFERENCE_ORIENTATION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_REFERENCE_ORIENTATION))
#define FO_PROPERTY_REFERENCE_ORIENTATION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_REFERENCE_ORIENTATION, FoPropertyReferenceOrientationClass))


/**
 * FoPropertyReferenceOrientation:
 *
 * Instance of the 'reference-orientation' property.
 **/
typedef struct _FoPropertyReferenceOrientation      FoPropertyReferenceOrientation;

/**
 * FoPropertyReferenceOrientationClass:
 *
 * Class structure for the 'reference-orientation' property.
 **/
typedef struct _FoPropertyReferenceOrientationClass FoPropertyReferenceOrientationClass;

GType        fo_property_reference_orientation_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_reference_orientation_new         (void);
FoProperty * fo_property_reference_orientation_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_REFERENCE_ORIENTATION_H__ */
