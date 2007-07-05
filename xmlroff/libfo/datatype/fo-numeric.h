/* Fo
 * fo-numeric.h: Numeric datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-numeric.h,v 1.2 2003/03/19 21:13:35 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_NUMERIC_H__
#define __FO_NUMERIC_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_NUMERIC              (fo_numeric_get_type ())
#define FO_NUMERIC(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_NUMERIC, FoNumeric))
#define FO_NUMERIC_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_NUMERIC, FoNumericClass))
#define FO_IS_NUMERIC(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_NUMERIC))
#define FO_IS_NUMERIC_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_NUMERIC))
#define FO_NUMERIC_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_NUMERIC, FoNumericClass))


typedef struct _FoNumeric      FoNumeric;
typedef struct _FoNumericClass FoNumericClass;

GType       fo_numeric_get_type      (void) G_GNUC_CONST;
FoDatatype *fo_numeric_new           (void);

G_END_DECLS

#endif /* !__FO_NUMERIC_H__ */
