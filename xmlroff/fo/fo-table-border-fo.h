/* Fo
 * fo-table-border-fo.h: Block formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-border-fo.h,v 1.4 2004/03/30 22:45:42 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_TABLE_BORDER_FO_H__
#define __FO_TABLE_BORDER_FO_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>
#include <datatype/fo-datatype.h>

G_BEGIN_DECLS

#define FO_TYPE_TABLE_BORDER_FO            (fo_table_border_fo_get_type ())
#define FO_TABLE_BORDER_FO(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_TABLE_BORDER_FO, FoTableBorderFo))
#define FO_TABLE_BORDER_FO_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_TABLE_BORDER_FO, FoTableBorderFoIface))
#define FO_IS_TABLE_BORDER_FO(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_TABLE_BORDER_FO))
#define FO_TABLE_BORDER_FO_GET_IFACE(obj)  ((FoTableBorderFoIface *)g_type_interface_peek (((GTypeInstance *) FO_TABLE_BORDER_FO (obj))->g_class, FO_TYPE_TABLE_BORDER_FO))

typedef struct _FoTableBorderFo      FoTableBorderFo; /* Dummy typedef */
typedef struct _FoTableBorderFoIface FoTableBorderFoIface;

GType        fo_table_border_fo_get_type                     (void) G_GNUC_CONST;

FoProperty * fo_table_border_fo_get_background_color         (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_after_color       (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_after_precedence  (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_after_style       (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_after_width       (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_before_color      (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_before_precedence (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_before_style      (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_before_width      (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_end_color         (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_end_precedence    (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_end_style         (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_end_width         (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_start_color       (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_start_precedence  (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_start_style       (FoFo *fo_table_border_fo);
FoProperty * fo_table_border_fo_get_border_start_width       (FoFo *fo_table_border_fo);

G_END_DECLS

#endif /* !__FO_TABLE_BORDER_FO_H__ */
