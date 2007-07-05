/* Fo
 * fo-string.h: String datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_STRING_H__
#define __FO_STRING_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_STRING              (fo_string_get_type ())
#define FO_STRING(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_STRING, FoString))
#define FO_STRING_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_STRING, FoStringClass))
#define FO_IS_STRING(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_STRING))
#define FO_IS_STRING_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_STRING))
#define FO_STRING_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_STRING, FoStringClass))


typedef struct _FoString      FoString;
typedef struct _FoStringClass FoStringClass;

GType        fo_string_get_type       (void) G_GNUC_CONST;
FoDatatype * fo_string_new            (void);
FoDatatype * fo_string_new_with_value (const gchar* value);

gchar*       fo_string_get_value      (FoDatatype   *string);

FoDatatype*  fo_string_get_string_one (void);

G_END_DECLS

#endif /* !__FO_STRING_H__ */
