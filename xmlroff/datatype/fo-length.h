/* Fo
 * fo-length.h: Length datatype
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-length.h,v 1.9 2006/07/25 20:55:44 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LENGTH_H__
#define __FO_LENGTH_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_LENGTH              (fo_length_get_type ())
#define FO_LENGTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LENGTH, FoLength))
#define FO_LENGTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LENGTH, FoLengthClass))
#define FO_IS_LENGTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LENGTH))
#define FO_IS_LENGTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LENGTH))
#define FO_LENGTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LENGTH, FoLengthClass))


typedef struct _FoLength      FoLength;
typedef struct _FoLengthClass FoLengthClass;

GType        fo_length_get_type        (void) G_GNUC_CONST;
FoDatatype * fo_length_new             (void);
FoDatatype * fo_length_new_with_value  (gdouble     value);
FoDatatype * fo_length_new_from_pixels (gint        count);
gdouble      fo_length_get_value       (FoDatatype *length);

FoDatatype * fo_length_get_length_minus_3pt  (void);
FoDatatype * fo_length_get_length_zero       (void);
FoDatatype * fo_length_get_length_3pt        (void);
FoDatatype * fo_length_get_length_6pt        (void);
FoDatatype * fo_length_get_length_12         (void);
FoDatatype * fo_length_get_length_24         (void);
FoDatatype * fo_length_get_length_A4_width   (void);
FoDatatype * fo_length_get_length_A4_height  (void);

FoDatatype * fo_length_get_width_thin   (void);
FoDatatype * fo_length_get_width_medium (void);
FoDatatype * fo_length_get_width_thick  (void);

G_END_DECLS

#endif /* !__FO_LENGTH_H__ */
