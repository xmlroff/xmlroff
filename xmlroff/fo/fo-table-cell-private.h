/* Fo
 * fo-table-cell-private.h: Structures private to 'table-cell' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-cell-private.h,v 1.4 2004/03/30 22:45:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_TABLE_CELL_PRIVATE_H__
#define __FO_TABLE_CELL_PRIVATE_H__

#include "fo/fo-marker-parent-private.h"
#include "fo/fo-table-cell.h"

G_BEGIN_DECLS

struct _FoTableCell
{
  FoMarkerParent parent_instance;

  FoFo *column;

  FoProperty *background_color;
  FoProperty *background_image;
  FoProperty *block_progression_dimension;
  FoProperty *border_after_color;
  FoProperty *border_after_precedence;
  FoProperty *border_after_style;
  FoProperty *border_after_width;
  FoProperty *border_before_color;
  FoProperty *border_before_precedence;
  FoProperty *border_before_style;
  FoProperty *border_before_width;
  FoProperty *border_bottom_color;
  FoProperty *border_bottom_style;
  FoProperty *border_bottom_width;
  FoProperty *border_end_color;
  FoProperty *border_end_precedence;
  FoProperty *border_end_style;
  FoProperty *border_end_width;
  FoProperty *border_left_color;
  FoProperty *border_left_style;
  FoProperty *border_left_width;
  FoProperty *border_right_color;
  FoProperty *border_right_style;
  FoProperty *border_right_width;
  FoProperty *border_start_color;
  FoProperty *border_start_precedence;
  FoProperty *border_start_style;
  FoProperty *border_start_width;
  FoProperty *border_top_color;
  FoProperty *border_top_style;
  FoProperty *border_top_width;
  FoProperty *column_number;
  FoProperty *display_align;
  FoProperty *height;
  FoProperty *id;
  FoProperty *inline_progression_dimension;
  FoProperty *number_columns_spanned;
  FoProperty *number_rows_spanned;
  FoProperty *padding_after;
  FoProperty *padding_before;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_top;
  FoProperty *role;
  FoProperty *source_document;
  FoProperty *width;
};

struct _FoTableCellClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_TABLE_CELL_PRIVATE_H__ */
