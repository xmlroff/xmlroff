/* Fo
 * fo-property-provisional-label-separation.h: 'provisional-label-separation' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION_H__
#define __FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* provisional-label-separation */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <length> | <percentage> | inherit */
/* Initial value: 6.0pt */

#define FO_TYPE_PROPERTY_PROVISIONAL_LABEL_SEPARATION              (fo_property_provisional_label_separation_get_type ())
#define FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PROVISIONAL_LABEL_SEPARATION, FoPropertyProvisionalLabelSeparation))
#define FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PROVISIONAL_LABEL_SEPARATION, FoPropertyProvisionalLabelSeparationClass))
#define FO_IS_PROPERTY_PROVISIONAL_LABEL_SEPARATION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PROVISIONAL_LABEL_SEPARATION))
#define FO_IS_PROPERTY_PROVISIONAL_LABEL_SEPARATION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PROVISIONAL_LABEL_SEPARATION))
#define FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PROVISIONAL_LABEL_SEPARATION, FoPropertyProvisionalLabelSeparationClass))


typedef struct _FoPropertyProvisionalLabelSeparation      FoPropertyProvisionalLabelSeparation;
typedef struct _FoPropertyProvisionalLabelSeparationClass FoPropertyProvisionalLabelSeparationClass;

GType        fo_property_provisional_label_separation_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_provisional_label_separation_new         (void);
FoProperty * fo_property_provisional_label_separation_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION_H__ */
