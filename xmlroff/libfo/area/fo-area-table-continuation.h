/* Fo
 * fo-area-table-continuation.c: Area object for table-continuation formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_CONTINUATION_H__
#define __FO_AREA_TABLE_CONTINUATION_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableContinuation      FoAreaTableContinuation;
typedef struct _FoAreaTableContinuationClass FoAreaTableContinuationClass;

#define FO_TYPE_AREA_TABLE_CONTINUATION              (fo_area_table_continuation_get_type ())
#define FO_AREA_TABLE_CONTINUATION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_CONTINUATION, FoAreaTableContinuation))
#define FO_AREA_TABLE_CONTINUATION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_CONTINUATION, FoAreaTableContinuationClass))
#define FO_IS_AREA_TABLE_CONTINUATION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_CONTINUATION))
#define FO_IS_AREA_TABLE_CONTINUATION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_CONTINUATION))
#define FO_AREA_TABLE_CONTINUATION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_CONTINUATION, FoAreaTableContinuationClass))


GType   fo_area_table_continuation_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_continuation_new (void);
G_END_DECLS

#endif /* !__FO_AREA_TABLE_CONTINUATION_H__ */
