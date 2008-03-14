/* Fo
 * fo-property-inline-progression-dimension-optimum.h: 'inline-progression-dimension-optimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM_H__
#define __FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* inline-progression-dimension-optimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> | <percentage> | <length-range> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM              (fo_property_inline_progression_dimension_optimum_get_type ())
#define FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM, FoPropertyInlineProgressionDimensionOptimum))
#define FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM, FoPropertyInlineProgressionDimensionOptimumClass))
#define FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM))
#define FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM))
#define FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM, FoPropertyInlineProgressionDimensionOptimumClass))


typedef struct _FoPropertyInlineProgressionDimensionOptimum      FoPropertyInlineProgressionDimensionOptimum;
typedef struct _FoPropertyInlineProgressionDimensionOptimumClass FoPropertyInlineProgressionDimensionOptimumClass;

GType        fo_property_inline_progression_dimension_optimum_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_inline_progression_dimension_optimum_new         (void);
FoProperty * fo_property_inline_progression_dimension_optimum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM_H__ */
