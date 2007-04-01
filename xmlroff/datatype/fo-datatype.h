/* Fo
 * fo-datatype.h: Datatype datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-datatype.h,v 1.4 2004/06/01 16:53:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_DATATYPE_H__
#define __FO_DATATYPE_H__

#include <libfo/fo-utils.h>
#include "fo-object.h"

G_BEGIN_DECLS

#define FO_TYPE_DATATYPE              (fo_datatype_get_type ())
#define FO_DATATYPE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_DATATYPE, FoDatatype))
#define FO_DATATYPE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_DATATYPE, FoDatatypeClass))
#define FO_IS_DATATYPE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_DATATYPE))
#define FO_IS_DATATYPE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_DATATYPE))
#define FO_DATATYPE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_DATATYPE, FoDatatypeClass))

typedef struct _FoDatatype      FoDatatype;
typedef struct _FoDatatypeClass FoDatatypeClass;

#define FO_DATATYPE_ERROR fo_datatype_error_quark ()
GQuark fo_datatype_error_quark (void);

typedef enum
{
  FO_DATATYPE_ERROR_WRONG_DATATYPE, /* Wrong datatype for context */
  FO_DATATYPE_ERROR_ADD,	    /* Cannot add datatype types */
  FO_DATATYPE_ERROR_SUB,	    /* Cannot subtract datatype types */
  FO_DATATYPE_ERROR_MUL,	    /* Cannot multiply datatype types */
  FO_DATATYPE_ERROR_DIV,	    /* Cannot divide datatype types */
  FO_DATATYPE_ERROR_MOD,	    /* Cannot get mod of datatype types */
  FO_DATATYPE_ERROR_MAX,	    /* max() error */
  FO_DATATYPE_ERROR_MIN,	    /* min() error */
  FO_DATATYPE_ERROR_FLOOR,	    /* floor() error */
  FO_DATATYPE_ERROR_ROUND,	    /* round() error */
  FO_DATATYPE_ERROR_CEILING,	    /* ceiling() error */
  FO_DATATYPE_ERROR_ABS,	    /* abs() error */
  FO_DATATYPE_ERROR_NEGATE	    /* negation error */
} FoDatatypeError;


GType       fo_datatype_get_type  (void) G_GNUC_CONST;
FoDatatype* fo_datatype_new       (void);
FoDatatype* fo_datatype_copy      (FoDatatype *datatype);

FoDatatype* fo_datatype_get_condity_discard (void);
FoDatatype* fo_datatype_get_condity_retain (void);

FoDatatype* fo_datatype_add	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_sub	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_mul	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_div	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_mod	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_max	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_min	(FoDatatype *arg1,
				 FoDatatype *arg2);
FoDatatype* fo_datatype_floor	(FoDatatype *arg);
FoDatatype* fo_datatype_ceiling (FoDatatype *arg);
FoDatatype* fo_datatype_abs	(FoDatatype *arg);
FoDatatype* fo_datatype_round	(FoDatatype *arg);
FoDatatype* fo_datatype_negate	(FoDatatype *arg);

G_END_DECLS

#endif /* !__FO_DATATYPE_H__ */
