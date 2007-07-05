/* Fo
 * fo-numeric.h: Numeric datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_NUMERIC_PRIVATE_H__
#define __FO_NUMERIC_PRIVATE_H__

#include <libfo/datatype/fo-datatype.h>
#include <libfo/datatype/fo-datatype-private.h>

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
