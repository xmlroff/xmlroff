/* Fo
 * fo-datatype-private.h: Structures private to the 'FoDatatype' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-datatype-private.h,v 1.2 2003/03/19 21:13:16 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_DATATYPE_PRIVATE_H__
#define __FO_DATATYPE_PRIVATE_H__

#include "fo-object.h"
#include "fo-datatype.h"
#include "fo-enum.h"

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
