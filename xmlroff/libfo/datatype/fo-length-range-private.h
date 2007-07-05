/* Fo
 * fo-length-range-private.h: Structures private to length-range datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LENGTH_RANGE_PRIVATE_H__
#define __FO_LENGTH_RANGE_PRIVATE_H__

#include <libfo/datatype/fo-datatype.h>
#include <libfo/datatype/fo-datatype-private.h>

G_BEGIN_DECLS

struct _FoLengthRange
{
  FoDatatype parent_instance;

  FoDatatype *minimum;
  FoDatatype *optimum;
  FoDatatype *maximum;
};

struct _FoLengthRangeClass
{
  FoDatatypeClass parent_class;
  FoDatatype* (*resolve) (FoDatatype *shortform,
			  FoDatatype *minimum,
			  FoDatatype *optimum,
			  FoDatatype *maximum,
			  FoDatatype *hundred_percent,
			  GError **error);
};

G_END_DECLS

#endif /* !__FO_LENGTH_RANGE_PRIVATE_H__ */
