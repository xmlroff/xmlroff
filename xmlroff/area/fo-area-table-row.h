/* Fo
 * fo-area-table-row.c: Area object for table-row formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-row.h,v 1.2 2003/03/19 21:12:57 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_TABLE_ROW_H__
#define __FO_AREA_TABLE_ROW_H__

#include <libfo/fo-utils.h>
#include <fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableRow      FoAreaTableRow;
typedef struct _FoAreaTableRowClass FoAreaTableRowClass;

#define FO_TYPE_AREA_TABLE_ROW              (fo_area_table_row_get_type ())
#define FO_AREA_TABLE_ROW(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_ROW, FoAreaTableRow))
#define FO_AREA_TABLE_ROW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_ROW, FoAreaTableRowClass))
#define FO_IS_AREA_TABLE_ROW(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_ROW))
#define FO_IS_AREA_TABLE_ROW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_ROW))
#define FO_AREA_TABLE_ROW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_ROW, FoAreaTableRowClass))


GType   fo_area_table_row_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_row_new (void);

G_END_DECLS

#endif /* !__FO_AREA_TABLE_ROW_H__ */
