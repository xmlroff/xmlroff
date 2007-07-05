/* Fo
 * fo-area-table-body.c: Area object for 'table-body' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_BODY_H__
#define __FO_AREA_TABLE_BODY_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableBody      FoAreaTableBody;
typedef struct _FoAreaTableBodyClass FoAreaTableBodyClass;

#define FO_TYPE_AREA_TABLE_BODY              (fo_area_table_body_get_type ())
#define FO_AREA_TABLE_BODY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_BODY, FoAreaTableBody))
#define FO_AREA_TABLE_BODY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_BODY, FoAreaTableBodyClass))
#define FO_IS_AREA_TABLE_BODY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_BODY))
#define FO_IS_AREA_TABLE_BODY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_BODY))
#define FO_AREA_TABLE_BODY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_BODY, FoAreaTableBodyClass))


GType   fo_area_table_body_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_body_new (void);

G_END_DECLS

#endif /* !__FO_AREA_TABLE_BODY_H__ */
