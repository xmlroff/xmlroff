/* Fo
 * fo-table-private.h: Structures private to 'table' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TABLE_PRIVATE_H__
#define __FO_TABLE_PRIVATE_H__

#include <libfo/fo/fo-marker-parent-private.h>
#include <libfo/fo/fo-table.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _SpanInfo SpanInfo;

struct _SpanInfo
{
  gint rows_spanned;
  FoFo *table_cell;
};

struct _FoTable
{
  FoMarkerParent parent_instance;

  FoEnumTableLayoutMethod layout_method;
  GHashTable *column_hash;
  gint max_column_number;
  GArray *span_info;
  gint span_info_next_column;
  gfloat proportional_unit;

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
  FoProperty *border_collapse;
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
  FoProperty *border_separation;
  FoProperty *border_start_color;
  FoProperty *border_start_precedence;
  FoProperty *border_start_style;
  FoProperty *border_start_width;
  FoProperty *border_top_color;
  FoProperty *border_top_style;
  FoProperty *border_top_width;
  FoProperty *break_after;
  FoProperty *break_before;
  FoProperty *end_indent;
  FoProperty *height;
  FoProperty *id;
  FoProperty *inline_progression_dimension;
  FoProperty *keep_together;
  FoProperty *keep_together_within_column;
  FoProperty *keep_together_within_line;
  FoProperty *keep_together_within_page;
  FoProperty *keep_with_next;
  FoProperty *keep_with_next_within_column;
  FoProperty *keep_with_next_within_line;
  FoProperty *keep_with_next_within_page;
  FoProperty *keep_with_previous;
  FoProperty *keep_with_previous_within_column;
  FoProperty *keep_with_previous_within_line;
  FoProperty *keep_with_previous_within_page;
  FoProperty *margin_bottom;
  FoProperty *margin_left;
  FoProperty *margin_right;
  FoProperty *margin_top;
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
  FoProperty *space_after;
  FoProperty *space_before;
  FoProperty *start_indent;
  FoProperty *table_layout;
  FoProperty *width;
  FoProperty *writing_mode;
};

struct _FoTableClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_TABLE_PRIVATE_H__ */
