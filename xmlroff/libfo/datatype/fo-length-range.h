/* Fo
 * fo-length-range.h: length-range datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LENGTH_RANGE_H__
#define __FO_LENGTH_RANGE_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-datatype.h>

G_BEGIN_DECLS

#define FO_TYPE_LENGTH_RANGE              (fo_length_range_get_type ())
#define FO_LENGTH_RANGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LENGTH_RANGE, FoLengthRange))
#define FO_LENGTH_RANGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LENGTH_RANGE, FoLengthRangeClass))
#define FO_IS_LENGTH_RANGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LENGTH_RANGE))
#define FO_IS_LENGTH_RANGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LENGTH_RANGE))
#define FO_LENGTH_RANGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LENGTH_RANGE, FoLengthRangeClass))


typedef struct _FoLengthRange      FoLengthRange;
typedef struct _FoLengthRangeClass FoLengthRangeClass;

GType        fo_length_range_get_type           (void) G_GNUC_CONST;
FoDatatype * fo_length_range_new_auto           (void);
FoDatatype * fo_length_range_new_with_value     (FoDatatype *datatype);

FoDatatype * fo_length_range_get_minimum        (FoDatatype *datatype);
FoDatatype * fo_length_range_get_optimum        (FoDatatype *datatype);
FoDatatype * fo_length_range_get_maximum        (FoDatatype *datatype);

FoDatatype * fo_length_range_resolve            (FoDatatype *shortform,
						 FoDatatype *minimum,
						 FoDatatype *optimum,
						 FoDatatype *maximum,
						 gfloat      hundred_percent,
						 GError    **error);
FoDatatype * fo_length_range_resolve_allow_auto (FoDatatype *shortform,
						 FoDatatype *minimum,
						 FoDatatype *optimum,
						 FoDatatype *maximum,
						 gfloat      hundred_percent,
						 GError    **error);

FoDatatype * fo_length_range_get_length_range_hundred_percent (void);

G_END_DECLS

#endif /* !__FO_LENGTH_RANGE_H__ */
