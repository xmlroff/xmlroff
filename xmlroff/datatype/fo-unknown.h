/* Fo
 * fo-unknown.h: Unknown datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-unknown.h,v 1.3 2003/07/02 10:43:35 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_UNKNOWN_H__
#define __FO_UNKNOWN_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_UNKNOWN              (fo_unknown_get_type ())
#define FO_UNKNOWN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_UNKNOWN, FoUnknown))
#define FO_UNKNOWN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_UNKNOWN, FoUnknownClass))
#define FO_IS_UNKNOWN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_UNKNOWN))
#define FO_IS_UNKNOWN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_UNKNOWN))
#define FO_UNKNOWN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_UNKNOWN, FoUnknownClass))


typedef struct _FoUnknown      FoUnknown;
typedef struct _FoUnknownClass FoUnknownClass;

GType        fo_unknown_get_type      (void) G_GNUC_CONST;
FoDatatype * fo_unknown_new           (void);

gchar* fo_unknown_get_value (FoDatatype  *unknown);
void   fo_unknown_set_value (FoDatatype  *unknown,
			     const gchar *new_value);

G_END_DECLS

#endif /* !__FO_UNKNOWN_H__ */
