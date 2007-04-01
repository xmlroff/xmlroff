/* Fo
 * fo-property-block-progression-dimension-minimum.h: 'block-progression-dimension-minimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-block-progression-dimension-minimum.h,v 1.4 2004/05/02 22:52:19 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM_H__
#define __FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* block-progression-dimension-minimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> | <percentage> | <length-range> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM              (fo_property_block_progression_dimension_minimum_get_type ())
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM, FoPropertyBlockProgressionDimensionMinimum))
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM, FoPropertyBlockProgressionDimensionMinimumClass))
#define FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM))
#define FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM))
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM, FoPropertyBlockProgressionDimensionMinimumClass))


typedef struct _FoPropertyBlockProgressionDimensionMinimum      FoPropertyBlockProgressionDimensionMinimum;
typedef struct _FoPropertyBlockProgressionDimensionMinimumClass FoPropertyBlockProgressionDimensionMinimumClass;

GType        fo_property_block_progression_dimension_minimum_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_block_progression_dimension_minimum_new         (void);
FoProperty * fo_property_block_progression_dimension_minimum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM_H__ */
