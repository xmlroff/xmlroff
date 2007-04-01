/* Fo
 * fo-property-scaling-method.h: 'scaling-method' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-scaling-method.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SCALING_METHOD_H__
#define __FO_PROPERTY_SCALING_METHOD_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* scaling-method */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | integer-pixels | resample-any-method | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_SCALING_METHOD              (fo_property_scaling_method_get_type ())
#define FO_PROPERTY_SCALING_METHOD(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SCALING_METHOD, FoPropertyScalingMethod))
#define FO_PROPERTY_SCALING_METHOD_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SCALING_METHOD, FoPropertyScalingMethodClass))
#define FO_IS_PROPERTY_SCALING_METHOD(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SCALING_METHOD))
#define FO_IS_PROPERTY_SCALING_METHOD_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SCALING_METHOD))
#define FO_PROPERTY_SCALING_METHOD_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SCALING_METHOD, FoPropertyScalingMethodClass))


typedef struct _FoPropertyScalingMethod      FoPropertyScalingMethod;
typedef struct _FoPropertyScalingMethodClass FoPropertyScalingMethodClass;

GType       fo_property_scaling_method_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_scaling_method_new         (void);
FoProperty* fo_property_scaling_method_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SCALING_METHOD_H__ */
