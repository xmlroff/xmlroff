/* Fo
 * fo-property-number-rows-spanned.h: 'number-rows-spanned' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_NUMBER_ROWS_SPANNED_H__
#define __FO_PROPERTY_NUMBER_ROWS_SPANNED_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* number-rows-spanned */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <number> */
/* Initial value: 1 */

#define FO_TYPE_PROPERTY_NUMBER_ROWS_SPANNED              (fo_property_number_rows_spanned_get_type ())
#define FO_PROPERTY_NUMBER_ROWS_SPANNED(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_NUMBER_ROWS_SPANNED, FoPropertyNumberRowsSpanned))
#define FO_PROPERTY_NUMBER_ROWS_SPANNED_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_NUMBER_ROWS_SPANNED, FoPropertyNumberRowsSpannedClass))
#define FO_IS_PROPERTY_NUMBER_ROWS_SPANNED(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_NUMBER_ROWS_SPANNED))
#define FO_IS_PROPERTY_NUMBER_ROWS_SPANNED_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_NUMBER_ROWS_SPANNED))
#define FO_PROPERTY_NUMBER_ROWS_SPANNED_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_NUMBER_ROWS_SPANNED, FoPropertyNumberRowsSpannedClass))


typedef struct _FoPropertyNumberRowsSpanned      FoPropertyNumberRowsSpanned;
typedef struct _FoPropertyNumberRowsSpannedClass FoPropertyNumberRowsSpannedClass;

GType       fo_property_number_rows_spanned_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_number_rows_spanned_new         (void);
FoProperty* fo_property_number_rows_spanned_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_NUMBER_ROWS_SPANNED_H__ */
