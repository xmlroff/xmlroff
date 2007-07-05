/* Fo
 * fo-name.h: Name datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_NAME_H__
#define __FO_NAME_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_NAME              (fo_name_get_type ())
#define FO_NAME(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_NAME, FoName))
#define FO_NAME_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_NAME, FoNameClass))
#define FO_IS_NAME(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_NAME))
#define FO_IS_NAME_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_NAME))
#define FO_NAME_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_NAME, FoNameClass))


typedef struct _FoName      FoName;
typedef struct _FoNameClass FoNameClass;

GType        fo_name_get_type      (void) G_GNUC_CONST;
FoDatatype * fo_name_new           (void);
FoDatatype * fo_name_new_with_value (const gchar* value);

gchar* fo_name_get_value (FoDatatype  *name);

FoDatatype * fo_name_get_name_empty (void);

G_END_DECLS

#endif /* !__FO_NAME_H__ */
