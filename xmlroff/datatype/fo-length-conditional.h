/* Fo
 * fo-length-cond.h: 'length-conditional' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-length-conditional.h,v 1.6 2004/06/01 16:17:11 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LENGTH_COND_H__
#define __FO_LENGTH_COND_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_LENGTH_COND              (fo_length_cond_get_type ())
#define FO_LENGTH_COND(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LENGTH_COND, FoLengthCond))
#define FO_LENGTH_COND_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LENGTH_COND, FoLengthCondClass))
#define FO_IS_LENGTH_COND(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LENGTH_COND))
#define FO_IS_LENGTH_COND_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LENGTH_COND))
#define FO_LENGTH_COND_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LENGTH_COND, FoLengthCondClass))


typedef struct _FoLengthCond      FoLengthCond;
typedef struct _FoLengthCondClass FoLengthCondClass;

GType        fo_length_cond_get_type      (void) G_GNUC_CONST;
FoDatatype * fo_length_cond_new           (void);
FoDatatype * fo_length_cond_new_with_value  (gdouble     length,
					     gboolean    condity);
FoDatatype * fo_length_cond_new_from_length (FoDatatype *length);

gdouble      fo_length_cond_get_length      (FoDatatype *datatype);
void         fo_length_cond_set_length      (FoDatatype *datatype,
					     gdouble     new_length);
gboolean     fo_length_cond_get_condity     (FoDatatype *datatype);
void         fo_length_cond_set_condity     (FoDatatype *datatype,
					     gboolean    new_condity);

FoDatatype * fo_length_cond_get_length_cond_zero (void);

FoDatatype * fo_length_cond_resolve (FoDatatype *shortform,
				     FoDatatype *length,
				     FoDatatype *condity,
				     GError    **error);

G_END_DECLS

#endif /* !__FO_LENGTH_COND_H__ */
