/* Fo
 * fo-enum.h: Enum datatype
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ENUM_H__
#define __FO_ENUM_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-datatype.h>
#include <libfo/datatype/fo-enum-factory.h>

G_BEGIN_DECLS

#define FO_TYPE_ENUM              (fo_enum_get_type ())
#define FO_ENUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_ENUM, FoEnum))
#define FO_ENUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_ENUM, FoEnumClass))
#define FO_IS_ENUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_ENUM))
#define FO_IS_ENUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_ENUM))
#define FO_ENUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_ENUM, FoEnumClass))


/**
 * FoEnum:
 *
 * Instance of the 'enum' datatype.
 **/
typedef struct _FoEnum      FoEnum;

/**
 * FoEnumClass:
 *
 * Class structure for the 'enum' datatype.
 **/
typedef struct _FoEnumClass FoEnumClass;

GType        fo_enum_get_type       (void) G_GNUC_CONST;

GEnumClass * fo_enum_get_enum_class (FoDatatype *fo_enum);
FoEnumEnum   fo_enum_get_value      (FoDatatype *fo_enum);
const gchar* fo_enum_get_nick       (FoDatatype *fo_enum);

G_END_DECLS

#endif /* !__FO_ENUM_H__ */
