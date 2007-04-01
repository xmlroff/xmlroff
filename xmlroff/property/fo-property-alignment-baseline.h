/* Fo
 * fo-property-alignment-baseline.h: 'alignment-baseline' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-alignment-baseline.h,v 1.4 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_ALIGNMENT_BASELINE_H__
#define __FO_PROPERTY_ALIGNMENT_BASELINE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* alignment-baseline */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | baseline | before-edge | text-before-edge | middle | central | after-edge | text-after-edge | ideographic | alphabetic | hanging | mathematical | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_ALIGNMENT_BASELINE              (fo_property_alignment_baseline_get_type ())
#define FO_PROPERTY_ALIGNMENT_BASELINE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_ALIGNMENT_BASELINE, FoPropertyAlignmentBaseline))
#define FO_PROPERTY_ALIGNMENT_BASELINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_ALIGNMENT_BASELINE, FoPropertyAlignmentBaselineClass))
#define FO_IS_PROPERTY_ALIGNMENT_BASELINE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_ALIGNMENT_BASELINE))
#define FO_IS_PROPERTY_ALIGNMENT_BASELINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_ALIGNMENT_BASELINE))
#define FO_PROPERTY_ALIGNMENT_BASELINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_ALIGNMENT_BASELINE, FoPropertyAlignmentBaselineClass))


typedef struct _FoPropertyAlignmentBaseline      FoPropertyAlignmentBaseline;
typedef struct _FoPropertyAlignmentBaselineClass FoPropertyAlignmentBaselineClass;

GType       fo_property_alignment_baseline_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_alignment_baseline_new         (void);
FoProperty* fo_property_alignment_baseline_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_ALIGNMENT_BASELINE_H__ */
