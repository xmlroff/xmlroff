/* Fo
 * fo-number.h: Number datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-number.h,v 1.4 2004/02/24 10:31:39 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_NUMBER_H__
#define __FO_NUMBER_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_NUMBER              (fo_number_get_type ())
#define FO_NUMBER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_NUMBER, FoNumber))
#define FO_NUMBER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_NUMBER, FoNumberClass))
#define FO_IS_NUMBER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_NUMBER))
#define FO_IS_NUMBER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_NUMBER))
#define FO_NUMBER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_NUMBER, FoNumberClass))


typedef struct _FoNumber      FoNumber;
typedef struct _FoNumberClass FoNumberClass;

GType        fo_number_get_type       (void) G_GNUC_CONST;
FoDatatype * fo_number_new            (void);
FoDatatype * fo_number_new_with_value (gdouble     value);
gdouble      fo_number_get_value      (FoDatatype *number);

FoDatatype* fo_number_get_number_one (void);

G_END_DECLS

#endif /* !__FO_NUMBER_H__ */
