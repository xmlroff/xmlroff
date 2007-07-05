/* Fo
 * fo-property-scaling.h: 'scaling' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SCALING_H__
#define __FO_PROPERTY_SCALING_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* scaling */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* uniform | non-uniform | inherit */
/* Initial value: uniform */

#define FO_TYPE_PROPERTY_SCALING              (fo_property_scaling_get_type ())
#define FO_PROPERTY_SCALING(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SCALING, FoPropertyScaling))
#define FO_PROPERTY_SCALING_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SCALING, FoPropertyScalingClass))
#define FO_IS_PROPERTY_SCALING(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SCALING))
#define FO_IS_PROPERTY_SCALING_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SCALING))
#define FO_PROPERTY_SCALING_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SCALING, FoPropertyScalingClass))


typedef struct _FoPropertyScaling      FoPropertyScaling;
typedef struct _FoPropertyScalingClass FoPropertyScalingClass;

GType       fo_property_scaling_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_scaling_new         (void);
FoProperty* fo_property_scaling_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SCALING_H__ */
