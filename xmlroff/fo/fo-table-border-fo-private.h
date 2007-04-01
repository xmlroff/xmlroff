/* Fo
 * fo-table-border-private-fo.h: Structures private to the table
 *                               border properties formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-border-fo-private.h,v 1.3 2004/03/30 22:45:42 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_TABLE_BORDER_FO_PRIVATE_H__
#define __FO_TABLE_BORDER_FO_PRIVATE_H__

#include <fo-table-border-fo.h>

G_BEGIN_DECLS

struct _FoTableBorderFoIface
{
  GTypeInterface g_iface;

  FoProperty * (* get_background_color)         (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_after_color)       (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_after_precedence)  (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_after_style)       (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_after_width)       (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_before_color)      (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_before_precedence) (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_before_style)      (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_before_width)      (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_end_color)         (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_end_precedence)    (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_end_style)         (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_end_width)         (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_start_color)       (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_start_precedence)  (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_start_style)       (FoFo *fo_table_border_fo);
  FoProperty * (* get_border_start_width)       (FoFo *fo_table_border_fo);
};

G_END_DECLS

#endif /* !__FO_TABLE_BORDER_FO_PRIVATE_H__ */
