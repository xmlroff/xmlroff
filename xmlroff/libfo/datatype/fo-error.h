/* Fo
 * fo-error.h: Error datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ERROR_H__
#define __FO_ERROR_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_ERROR              (fo_error_get_type ())
#define FO_ERROR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_ERROR, FoError))
#define FO_ERROR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_ERROR, FoErrorClass))
#define FO_IS_ERROR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_ERROR))
#define FO_IS_ERROR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_ERROR))
#define FO_ERROR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_ERROR, FoErrorClass))


typedef struct _FoError      FoError;
typedef struct _FoErrorClass FoErrorClass;

GType       fo_error_get_type       (void) G_GNUC_CONST;
FoDatatype* fo_error_new            (void);
FoDatatype* fo_error_new_with_value (GError *value);

GError* fo_error_get_value (FoDatatype *error);

G_END_DECLS

#endif /* !__FO_ERROR_H__ */
