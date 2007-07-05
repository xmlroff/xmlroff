/* Fo
 * fo-area-table-footer.c: Area object for 'table-footer' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_FOOTER_H__
#define __FO_AREA_TABLE_FOOTER_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableFooter      FoAreaTableFooter;
typedef struct _FoAreaTableFooterClass FoAreaTableFooterClass;

#define FO_TYPE_AREA_TABLE_FOOTER              (fo_area_table_footer_get_type ())
#define FO_AREA_TABLE_FOOTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_FOOTER, FoAreaTableFooter))
#define FO_AREA_TABLE_FOOTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_FOOTER, FoAreaTableFooterClass))
#define FO_IS_AREA_TABLE_FOOTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_FOOTER))
#define FO_IS_AREA_TABLE_FOOTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_FOOTER))
#define FO_AREA_TABLE_FOOTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_FOOTER, FoAreaTableFooterClass))


GType   fo_area_table_footer_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_footer_new (void);

G_END_DECLS

#endif /* !__FO_AREA_TABLE_FOOTER_H__ */
