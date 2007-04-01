/* Fo
 * fo-property-number-columns-repeated.h: 'number-columns-repeated' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-number-columns-repeated.h,v 1.2 2003/03/21 14:41:38 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_NUMBER_COLUMNS_REPEATED_H__
#define __FO_PROPERTY_NUMBER_COLUMNS_REPEATED_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

/* number-columns-repeated */
/* <number> */
/* Initial value: 1 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_NUMBER_COLUMNS_REPEATED              (fo_property_number_columns_repeated_get_type ())
#define FO_PROPERTY_NUMBER_COLUMNS_REPEATED(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_NUMBER_COLUMNS_REPEATED, FoPropertyNumberColumnsRepeated))
#define FO_PROPERTY_NUMBER_COLUMNS_REPEATED_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_NUMBER_COLUMNS_REPEATED, FoPropertyNumberColumnsRepeatedClass))
#define FO_IS_PROPERTY_NUMBER_COLUMNS_REPEATED(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_NUMBER_COLUMNS_REPEATED))
#define FO_IS_PROPERTY_NUMBER_COLUMNS_REPEATED_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_NUMBER_COLUMNS_REPEATED))
#define FO_PROPERTY_NUMBER_COLUMNS_REPEATED_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_NUMBER_COLUMNS_REPEATED, FoPropertyNumberColumnsRepeatedClass))


typedef struct _FoPropertyNumberColumnsRepeated      FoPropertyNumberColumnsRepeated;
typedef struct _FoPropertyNumberColumnsRepeatedClass FoPropertyNumberColumnsRepeatedClass;

GType       fo_property_number_columns_repeated_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_number_columns_repeated_new         (void);
FoProperty* fo_property_number_columns_repeated_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_NUMBER_COLUMNS_REPEATED_H__ */
