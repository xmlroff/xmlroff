/* Fo
 * fo-numeric.h: Numeric datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-numeric-private.h,v 1.2 2003/03/19 21:13:34 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_NUMERIC_PRIVATE_H__
#define __FO_NUMERIC_PRIVATE_H__

#include "fo-datatype.h"
#include "fo-datatype-private.h"

G_BEGIN_DECLS

struct _FoNumeric
{
  FoDatatype parent_instance;
};

struct _FoNumericClass
{
  FoDatatypeClass parent_class;

};

G_END_DECLS

#endif /* !__FO_NUMERIC_PRIVATE_H__ */
