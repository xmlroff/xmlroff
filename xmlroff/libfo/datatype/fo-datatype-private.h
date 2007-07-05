/* Fo
 * fo-datatype-private.h: Structures private to the 'FoDatatype' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DATATYPE_PRIVATE_H__
#define __FO_DATATYPE_PRIVATE_H__

#include <libfo/fo-object.h>
#include <libfo/datatype/fo-datatype.h>

G_BEGIN_DECLS

struct _FoDatatype
{
  FoObject parent_instance;
};

struct _FoDatatypeClass
{
  FoObjectClass parent_class;

  FoDatatype* (*copy)      (FoDatatype *datatype);
};

G_END_DECLS

#endif /* !__FO_DATATYPE_PRIVATE_H__ */
