/* Fo
 * fo-property-white-space-treatment.h: 'white-space-treatment' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_WHITE_SPACE_TREATMENT_H__
#define __FO_PROPERTY_WHITE_SPACE_TREATMENT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* white-space-treatment */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* ignore | preserve | ignore-if-before-linefeed | ignore-if-after-linefeed | ignore-if-surrounding-linefeed | inherit */
/* Initial value: ignore-if-surrounding-linefeed */

#define FO_TYPE_PROPERTY_WHITE_SPACE_TREATMENT              (fo_property_white_space_treatment_get_type ())
#define FO_PROPERTY_WHITE_SPACE_TREATMENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_WHITE_SPACE_TREATMENT, FoPropertyWhiteSpaceTreatment))
#define FO_PROPERTY_WHITE_SPACE_TREATMENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_WHITE_SPACE_TREATMENT, FoPropertyWhiteSpaceTreatmentClass))
#define FO_IS_PROPERTY_WHITE_SPACE_TREATMENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_WHITE_SPACE_TREATMENT))
#define FO_IS_PROPERTY_WHITE_SPACE_TREATMENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_WHITE_SPACE_TREATMENT))
#define FO_PROPERTY_WHITE_SPACE_TREATMENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_WHITE_SPACE_TREATMENT, FoPropertyWhiteSpaceTreatmentClass))


/**
 * FoPropertyWhiteSpaceTreatment:
 *
 * Instance of the 'white-space-treatment' property.
 **/
typedef struct _FoPropertyWhiteSpaceTreatment      FoPropertyWhiteSpaceTreatment;

/**
 * FoPropertyWhiteSpaceTreatmentClass:
 *
 * Class structure for the 'white-space-treatment' property.
 **/
typedef struct _FoPropertyWhiteSpaceTreatmentClass FoPropertyWhiteSpaceTreatmentClass;

GType        fo_property_white_space_treatment_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_white_space_treatment_new         (void);
FoProperty * fo_property_white_space_treatment_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_WHITE_SPACE_TREATMENT_H__ */
