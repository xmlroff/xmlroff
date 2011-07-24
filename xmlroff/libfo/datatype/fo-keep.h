/* Fo
 * fo-keep.h: Keep datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_KEEP_H__
#define __FO_KEEP_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_KEEP              (fo_keep_get_type ())
#define FO_KEEP(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_KEEP, FoKeep))
#define FO_KEEP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_KEEP, FoKeepClass))
#define FO_IS_KEEP(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_KEEP))
#define FO_IS_KEEP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_KEEP))
#define FO_KEEP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_KEEP, FoKeepClass))


typedef struct _FoKeep      FoKeep;
typedef struct _FoKeepClass FoKeepClass;

GType        fo_keep_get_type          (void) G_GNUC_CONST;
FoDatatype * fo_keep_new               (void);
FoDatatype * fo_keep_new_with_value    (FoDatatype *value);
FoDatatype * fo_keep_get_keep_auto     (void);
FoDatatype * fo_keep_get_keep_always   (void);

FoDatatype * fo_keep_get_within_line   (FoDatatype *datatype);
FoDatatype * fo_keep_get_within_column (FoDatatype *datatype);
FoDatatype * fo_keep_get_within_page   (FoDatatype *datatype);
FoDatatype * fo_keep_resolve           (FoDatatype *shortform,
					FoDatatype *within_line,
					FoDatatype *within_column,
					FoDatatype *within_page,
					GError    **error);

FoDatatype * fo_keep_get_keep_auto     (void);
FoDatatype * fo_keep_get_keep_always   (void);

G_END_DECLS

#endif /* !__FO_KEEP_H__ */
