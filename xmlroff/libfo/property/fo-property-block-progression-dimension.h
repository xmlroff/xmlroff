/* Fo
 * fo-property-block-progression-dimension.h: 'block-progression-dimension' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_H__
#define __FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* block-progression-dimension */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> | <percentage> | <length-range> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION              (fo_property_block_progression_dimension_get_type ())
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION, FoPropertyBlockProgressionDimension))
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION, FoPropertyBlockProgressionDimensionClass))
#define FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION))
#define FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION))
#define FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION, FoPropertyBlockProgressionDimensionClass))


typedef struct _FoPropertyBlockProgressionDimension      FoPropertyBlockProgressionDimension;
typedef struct _FoPropertyBlockProgressionDimensionClass FoPropertyBlockProgressionDimensionClass;

GType        fo_property_block_progression_dimension_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_block_progression_dimension_new         (void);
FoProperty * fo_property_block_progression_dimension_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_H__ */
