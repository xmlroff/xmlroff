/* Fo
 * fo-area-table.c: Area object for 'table' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table.h,v 1.2 2003/03/19 21:13:00 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_TABLE_H__
#define __FO_AREA_TABLE_H__

#include <libfo/fo-utils.h>
#include <fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTable      FoAreaTable;
typedef struct _FoAreaTableClass FoAreaTableClass;

#define FO_TYPE_AREA_TABLE              (fo_area_table_get_type ())
#define FO_AREA_TABLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE, FoAreaTable))
#define FO_AREA_TABLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE, FoAreaTableClass))
#define FO_IS_AREA_TABLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE))
#define FO_IS_AREA_TABLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE))
#define FO_AREA_TABLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE, FoAreaTableClass))


GType   fo_area_table_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_new (void);
G_END_DECLS

#endif /* !__FO_AREA_TABLE_H__ */
