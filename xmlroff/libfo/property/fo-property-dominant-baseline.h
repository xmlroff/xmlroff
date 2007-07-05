/* Fo
 * fo-property-dominant-baseline.h: 'dominant-baseline' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_DOMINANT_BASELINE_H__
#define __FO_PROPERTY_DOMINANT_BASELINE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* dominant-baseline */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | use-script | no-change | reset-size | ideographic | alphabetic | hanging | mathematical | central | middle | text-after-edge | text-before-edge | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_DOMINANT_BASELINE              (fo_property_dominant_baseline_get_type ())
#define FO_PROPERTY_DOMINANT_BASELINE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_DOMINANT_BASELINE, FoPropertyDominantBaseline))
#define FO_PROPERTY_DOMINANT_BASELINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_DOMINANT_BASELINE, FoPropertyDominantBaselineClass))
#define FO_IS_PROPERTY_DOMINANT_BASELINE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_DOMINANT_BASELINE))
#define FO_IS_PROPERTY_DOMINANT_BASELINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_DOMINANT_BASELINE))
#define FO_PROPERTY_DOMINANT_BASELINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_DOMINANT_BASELINE, FoPropertyDominantBaselineClass))


typedef struct _FoPropertyDominantBaseline      FoPropertyDominantBaseline;
typedef struct _FoPropertyDominantBaselineClass FoPropertyDominantBaselineClass;

GType        fo_property_dominant_baseline_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_dominant_baseline_new         (void);
FoProperty * fo_property_dominant_baseline_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_DOMINANT_BASELINE_H__ */
