/* Fo
 * fo-property-letter-value.h: 'letter-value' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_LETTER_VALUE_H__
#define __FO_PROPERTY_LETTER_VALUE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* letter-value */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | alphabetic | traditional */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_LETTER_VALUE              (fo_property_letter_value_get_type ())
#define FO_PROPERTY_LETTER_VALUE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_LETTER_VALUE, FoPropertyLetterValue))
#define FO_PROPERTY_LETTER_VALUE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_LETTER_VALUE, FoPropertyLetterValueClass))
#define FO_IS_PROPERTY_LETTER_VALUE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_LETTER_VALUE))
#define FO_IS_PROPERTY_LETTER_VALUE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_LETTER_VALUE))
#define FO_PROPERTY_LETTER_VALUE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_LETTER_VALUE, FoPropertyLetterValueClass))


typedef struct _FoPropertyLetterValue      FoPropertyLetterValue;
typedef struct _FoPropertyLetterValueClass FoPropertyLetterValueClass;

GType       fo_property_letter_value_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_letter_value_new         (void);
FoProperty* fo_property_letter_value_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_LETTER_VALUE_H__ */
