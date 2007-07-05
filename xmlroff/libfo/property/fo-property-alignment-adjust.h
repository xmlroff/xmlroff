/* Fo
 * fo-property-alignment-adjust.h: 'alignment-adjust' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_ALIGNMENT_ADJUST_H__
#define __FO_PROPERTY_ALIGNMENT_ADJUST_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* alignment-adjust */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | baseline | before-edge | text-before-edge | middle | central | after-edge | text-after-edge | ideographic | alphabetic | hanging | mathematical | <percentage> | <length> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_ALIGNMENT_ADJUST              (fo_property_alignment_adjust_get_type ())
#define FO_PROPERTY_ALIGNMENT_ADJUST(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_ALIGNMENT_ADJUST, FoPropertyAlignmentAdjust))
#define FO_PROPERTY_ALIGNMENT_ADJUST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_ALIGNMENT_ADJUST, FoPropertyAlignmentAdjustClass))
#define FO_IS_PROPERTY_ALIGNMENT_ADJUST(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_ALIGNMENT_ADJUST))
#define FO_IS_PROPERTY_ALIGNMENT_ADJUST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_ALIGNMENT_ADJUST))
#define FO_PROPERTY_ALIGNMENT_ADJUST_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_ALIGNMENT_ADJUST, FoPropertyAlignmentAdjustClass))


typedef struct _FoPropertyAlignmentAdjust      FoPropertyAlignmentAdjust;
typedef struct _FoPropertyAlignmentAdjustClass FoPropertyAlignmentAdjustClass;

GType       fo_property_alignment_adjust_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_alignment_adjust_new         (void);
FoProperty* fo_property_alignment_adjust_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_ALIGNMENT_ADJUST_H__ */
