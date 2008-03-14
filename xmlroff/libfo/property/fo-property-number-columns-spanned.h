/* Fo
 * fo-property-number-columns-spanned.h: 'number-columns-spanned' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_NUMBER_COLUMNS_SPANNED_H__
#define __FO_PROPERTY_NUMBER_COLUMNS_SPANNED_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* number-columns-spanned */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <number> */
/* Initial value: 1 */

#define FO_TYPE_PROPERTY_NUMBER_COLUMNS_SPANNED              (fo_property_number_columns_spanned_get_type ())
#define FO_PROPERTY_NUMBER_COLUMNS_SPANNED(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_NUMBER_COLUMNS_SPANNED, FoPropertyNumberColumnsSpanned))
#define FO_PROPERTY_NUMBER_COLUMNS_SPANNED_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_NUMBER_COLUMNS_SPANNED, FoPropertyNumberColumnsSpannedClass))
#define FO_IS_PROPERTY_NUMBER_COLUMNS_SPANNED(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_NUMBER_COLUMNS_SPANNED))
#define FO_IS_PROPERTY_NUMBER_COLUMNS_SPANNED_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_NUMBER_COLUMNS_SPANNED))
#define FO_PROPERTY_NUMBER_COLUMNS_SPANNED_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_NUMBER_COLUMNS_SPANNED, FoPropertyNumberColumnsSpannedClass))


typedef struct _FoPropertyNumberColumnsSpanned      FoPropertyNumberColumnsSpanned;
typedef struct _FoPropertyNumberColumnsSpannedClass FoPropertyNumberColumnsSpannedClass;

GType        fo_property_number_columns_spanned_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_number_columns_spanned_new         (void);
FoProperty * fo_property_number_columns_spanned_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_NUMBER_COLUMNS_SPANNED_H__ */
