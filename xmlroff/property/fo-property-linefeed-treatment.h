/* Fo
 * fo-property-linefeed-treatment.h: 'linefeed-treatment' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-property-linefeed-treatment.h,v 1.3 2006/03/22 23:31:29 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_LINEFEED_TREATMENT_H__
#define __FO_PROPERTY_LINEFEED_TREATMENT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* linefeed-treatment */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* ignore | preserve | treat-as-space | treat-as-zero-width-space | inherit */
/* Initial value: treat-as-space */

#define FO_TYPE_PROPERTY_LINEFEED_TREATMENT              (fo_property_linefeed_treatment_get_type ())
#define FO_PROPERTY_LINEFEED_TREATMENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_LINEFEED_TREATMENT, FoPropertyLinefeedTreatment))
#define FO_PROPERTY_LINEFEED_TREATMENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_LINEFEED_TREATMENT, FoPropertyLinefeedTreatmentClass))
#define FO_IS_PROPERTY_LINEFEED_TREATMENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_LINEFEED_TREATMENT))
#define FO_IS_PROPERTY_LINEFEED_TREATMENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_LINEFEED_TREATMENT))
#define FO_PROPERTY_LINEFEED_TREATMENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_LINEFEED_TREATMENT, FoPropertyLinefeedTreatmentClass))


/**
 * FoPropertyLinefeedTreatment:
 *
 * Instance of the 'linefeed-treatment' property.
 **/
typedef struct _FoPropertyLinefeedTreatment      FoPropertyLinefeedTreatment;

/**
 * FoPropertyLinefeedTreatmentClass:
 *
 * Class structure for the 'linefeed-treatment' property.
 **/
typedef struct _FoPropertyLinefeedTreatmentClass FoPropertyLinefeedTreatmentClass;

GType        fo_property_linefeed_treatment_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_linefeed_treatment_new         (void);
FoProperty * fo_property_linefeed_treatment_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_LINEFEED_TREATMENT_H__ */
