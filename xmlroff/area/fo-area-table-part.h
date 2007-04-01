/* Fo
 * fo-area-table-part.c: Area object for table-part formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-part.h,v 1.2 2003/03/19 21:12:55 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_TABLE_PART_H__
#define __FO_AREA_TABLE_PART_H__

#include <libfo/fo-utils.h>
#include <fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTablePart      FoAreaTablePart;
typedef struct _FoAreaTablePartClass FoAreaTablePartClass;

#define FO_TYPE_AREA_TABLE_PART              (fo_area_table_part_get_type ())
#define FO_AREA_TABLE_PART(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_PART, FoAreaTablePart))
#define FO_AREA_TABLE_PART_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_PART, FoAreaTablePartClass))
#define FO_IS_AREA_TABLE_PART(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_PART))
#define FO_IS_AREA_TABLE_PART_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_PART))
#define FO_AREA_TABLE_PART_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_PART, FoAreaTablePartClass))


GType   fo_area_table_part_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_part_new (void);

G_END_DECLS

#endif /* !__FO_AREA_TABLE_PART_H__ */
