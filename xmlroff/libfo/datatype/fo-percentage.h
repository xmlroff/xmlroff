/* Fo
 * fo-percentage.h: Percentage datatype
 *
 * Copyright (C) 2001 Sun Microsystems
  * Copyright (C) 2007 Menteith Consulting Ltd
*
 * See COPYING for the status of this software.
 */

#ifndef __FO_PERCENTAGE_H__
#define __FO_PERCENTAGE_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_PERCENTAGE              (fo_percentage_get_type ())
#define FO_PERCENTAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PERCENTAGE, FoPercentage))
#define FO_PERCENTAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PERCENTAGE, FoPercentageClass))
#define FO_IS_PERCENTAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PERCENTAGE))
#define FO_IS_PERCENTAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PERCENTAGE))
#define FO_PERCENTAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PERCENTAGE, FoPercentageClass))


typedef struct _FoPercentage      FoPercentage;
typedef struct _FoPercentageClass FoPercentageClass;

GType        fo_percentage_get_type               (void) G_GNUC_CONST;
FoDatatype * fo_percentage_new                    (void);
FoDatatype * fo_percentage_new_with_value         (gdouble     value);

gdouble      fo_percentage_get_value              (FoDatatype *percentage);
void         fo_percentage_set_value              (FoDatatype *percentage,
						   gdouble     new_value);
FoDatatype * fo_percentage_get_percentage_hundred (void);

G_END_DECLS

#endif /* !__FO_PERCENTAGE_H__ */
