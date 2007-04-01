/* Fo
 * fo-property-baseline-shift.h: 'baseline-shift' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-baseline-shift.h,v 1.3 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BASELINE_SHIFT_H__
#define __FO_PROPERTY_BASELINE_SHIFT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* baseline-shift */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* baseline | sub | super | <percentage> | <length> | inherit */
/* Initial value: baseline */

#define FO_TYPE_PROPERTY_BASELINE_SHIFT              (fo_property_baseline_shift_get_type ())
#define FO_PROPERTY_BASELINE_SHIFT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BASELINE_SHIFT, FoPropertyBaselineShift))
#define FO_PROPERTY_BASELINE_SHIFT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BASELINE_SHIFT, FoPropertyBaselineShiftClass))
#define FO_IS_PROPERTY_BASELINE_SHIFT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BASELINE_SHIFT))
#define FO_IS_PROPERTY_BASELINE_SHIFT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BASELINE_SHIFT))
#define FO_PROPERTY_BASELINE_SHIFT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BASELINE_SHIFT, FoPropertyBaselineShiftClass))


typedef struct _FoPropertyBaselineShift      FoPropertyBaselineShift;
typedef struct _FoPropertyBaselineShiftClass FoPropertyBaselineShiftClass;

GType       fo_property_baseline_shift_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_baseline_shift_new         (void);
FoProperty* fo_property_baseline_shift_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BASELINE_SHIFT_H__ */
