/* Fo
 * fo-table.h: 'table' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TABLE_H__
#define __FO_TABLE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef enum {
  FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN,
  FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC,
  FO_ENUM_TABLE_LAYOUT_METHOD_FIXED
} FoEnumTableLayoutMethod;

GType fo_enum_table_layout_method_get_type (void);
#define FO_TYPE_ENUM_TABLE_LAYOUT_METHOD fo_enum_table_layout_method_get_type ()

#define FO_TABLE_ERROR fo_table_error_quark ()

GQuark fo_table_error_quark (void);

typedef enum
{
  FO_TABLE_ERROR_FAILED,          /* Generic error code */
  FO_TABLE_ERROR_WARNING,         /* Non-fatal error */
  FO_TABLE_ERROR_LAYOUT_METHOD_UNKNOWN,
  FO_TABLE_ERROR_FIXED_NO_COLUMN,
  FO_TABLE_ERROR_MISSING_COLUMN,
  FO_TABLE_ERROR_WIDTH_NOT_LENGTH,
  FO_TABLE_ERROR_NO_AREA,
  FO_TABLE_ERROR_FIXED_BUT_AUTO,
  FO_TABLE_ERROR_AUTOMATIC_NOT_SUPPORTED,
  FO_TABLE_ERROR_SPANNING_CELLS_FILL_ROW,
  FO_TABLE_ERROR_LAST
} FoTableError;

extern const char *fo_table_error_messages[FO_TABLE_ERROR_LAST];

typedef struct _FoTable      FoTable;
typedef struct _FoTableClass FoTableClass;

#define FO_TYPE_TABLE              (fo_table_get_type ())
#define FO_TABLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TABLE, FoTable))
#define FO_TABLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TABLE, FoTableClass))
#define FO_IS_TABLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TABLE))
#define FO_IS_TABLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TABLE))
#define FO_TABLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TABLE, FoTableClass))


GType        fo_table_get_type      (void) G_GNUC_CONST;
FoFo *       fo_table_new (void);

gboolean fo_table_validate_content_table_row_table_cell (FoFo *fo,
							 GError **error);
void fo_table_resolve_columns (FoFo    *fo,
			       GError **error);
void fo_table_span_info_start_row (FoFo    *fo,
				   GError **error);
gint fo_table_span_info_resolve_column_number (FoFo    *fo,
					       FoFo    *table_cell,
					       gint     column_number,
					       gint     columns_spanned,
					       gint     rows_spanned,
					       GError **error);
void fo_table_span_info_debug_dump (FoFo *fo,
				    gint depth);

void fo_table_add_column (FoFo *fo,
			  gint column_number,
			  gint number_columns_spanned,
			  FoFo *column);
FoFo* fo_table_get_column (FoFo *fo,
			   gint column_number,
			   gint number_columns_spanned);
gint fo_table_get_max_column_number (FoFo *fo);
FoEnumTableLayoutMethod fo_table_get_layout_method (FoFo *fo_fo);
gdouble fo_table_get_proportional_unit (FoFo *fo);

FoProperty * fo_table_get_background_color (FoFo       *fo_fo);
void         fo_table_set_background_color (FoFo       *fo_fo,
					    FoProperty *new_background_color);
FoProperty * fo_table_get_background_image (FoFo       *fo_fo);
void         fo_table_set_background_image (FoFo       *fo_fo,
                                            FoProperty *new_background_image);
FoProperty * fo_table_get_block_progression_dimension (FoFo       *fo_fo);
void         fo_table_set_block_progression_dimension (FoFo       *fo_fo,
                                                       FoProperty *new_block_progression_dimension);
FoProperty * fo_table_get_border_after_color (FoFo       *fo_fo);
void         fo_table_set_border_after_color (FoFo       *fo_fo,
                                              FoProperty *new_border_after_color);
FoProperty * fo_table_get_border_after_precedence (FoFo       *fo_fo);
void         fo_table_set_border_after_precedence (FoFo       *fo_fo,
                                                   FoProperty *new_border_after_precedence);
FoProperty * fo_table_get_border_after_style (FoFo       *fo_fo);
void         fo_table_set_border_after_style (FoFo       *fo_fo,
                                              FoProperty *new_border_after_style);
FoProperty * fo_table_get_border_after_width (FoFo       *fo_fo);
void         fo_table_set_border_after_width (FoFo       *fo_fo,
                                              FoProperty *new_border_after_width);
FoProperty * fo_table_get_border_before_color (FoFo       *fo_fo);
void         fo_table_set_border_before_color (FoFo       *fo_fo,
                                               FoProperty *new_border_before_color);
FoProperty * fo_table_get_border_before_precedence (FoFo       *fo_fo);
void         fo_table_set_border_before_precedence (FoFo       *fo_fo,
                                                    FoProperty *new_border_before_precedence);
FoProperty * fo_table_get_border_before_style (FoFo       *fo_fo);
void         fo_table_set_border_before_style (FoFo       *fo_fo,
                                               FoProperty *new_border_before_style);
FoProperty * fo_table_get_border_before_width (FoFo       *fo_fo);
void         fo_table_set_border_before_width (FoFo       *fo_fo,
                                               FoProperty *new_border_before_width);
FoProperty * fo_table_get_border_bottom_color (FoFo       *fo_fo);
void         fo_table_set_border_bottom_color (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_color);
FoProperty * fo_table_get_border_bottom_style (FoFo       *fo_fo);
void         fo_table_set_border_bottom_style (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_style);
FoProperty * fo_table_get_border_bottom_width (FoFo       *fo_fo);
void         fo_table_set_border_bottom_width (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_width);
FoProperty * fo_table_get_border_collapse (FoFo       *fo_fo);
void         fo_table_set_border_collapse (FoFo       *fo_fo,
                                           FoProperty *new_border_collapse);
FoProperty * fo_table_get_border_end_color (FoFo       *fo_fo);
void         fo_table_set_border_end_color (FoFo       *fo_fo,
                                            FoProperty *new_border_end_color);
FoProperty * fo_table_get_border_end_precedence (FoFo       *fo_fo);
void         fo_table_set_border_end_precedence (FoFo       *fo_fo,
                                                 FoProperty *new_border_end_precedence);
FoProperty * fo_table_get_border_end_style (FoFo       *fo_fo);
void         fo_table_set_border_end_style (FoFo       *fo_fo,
                                            FoProperty *new_border_end_style);
FoProperty * fo_table_get_border_end_width (FoFo       *fo_fo);
void         fo_table_set_border_end_width (FoFo       *fo_fo,
                                            FoProperty *new_border_end_width);
FoProperty * fo_table_get_border_left_color (FoFo       *fo_fo);
void         fo_table_set_border_left_color (FoFo       *fo_fo,
                                             FoProperty *new_border_left_color);
FoProperty * fo_table_get_border_left_style (FoFo       *fo_fo);
void         fo_table_set_border_left_style (FoFo       *fo_fo,
                                             FoProperty *new_border_left_style);
FoProperty * fo_table_get_border_left_width (FoFo       *fo_fo);
void         fo_table_set_border_left_width (FoFo       *fo_fo,
                                             FoProperty *new_border_left_width);
FoProperty * fo_table_get_border_right_color (FoFo       *fo_fo);
void         fo_table_set_border_right_color (FoFo       *fo_fo,
                                              FoProperty *new_border_right_color);
FoProperty * fo_table_get_border_right_style (FoFo       *fo_fo);
void         fo_table_set_border_right_style (FoFo       *fo_fo,
                                              FoProperty *new_border_right_style);
FoProperty * fo_table_get_border_right_width (FoFo       *fo_fo);
void         fo_table_set_border_right_width (FoFo       *fo_fo,
                                              FoProperty *new_border_right_width);
FoProperty * fo_table_get_border_separation (FoFo       *fo_fo);
void         fo_table_set_border_separation (FoFo       *fo_fo,
                                             FoProperty *new_border_separation);
FoProperty * fo_table_get_border_start_color (FoFo       *fo_fo);
void         fo_table_set_border_start_color (FoFo       *fo_fo,
                                              FoProperty *new_border_start_color);
FoProperty * fo_table_get_border_start_precedence (FoFo       *fo_fo);
void         fo_table_set_border_start_precedence (FoFo       *fo_fo,
                                                   FoProperty *new_border_start_precedence);
FoProperty * fo_table_get_border_start_style (FoFo       *fo_fo);
void         fo_table_set_border_start_style (FoFo       *fo_fo,
                                              FoProperty *new_border_start_style);
FoProperty * fo_table_get_border_start_width (FoFo       *fo_fo);
void         fo_table_set_border_start_width (FoFo       *fo_fo,
                                              FoProperty *new_border_start_width);
FoProperty * fo_table_get_border_top_color (FoFo       *fo_fo);
void         fo_table_set_border_top_color (FoFo       *fo_fo,
                                            FoProperty *new_border_top_color);
FoProperty * fo_table_get_border_top_style (FoFo       *fo_fo);
void         fo_table_set_border_top_style (FoFo       *fo_fo,
                                            FoProperty *new_border_top_style);
FoProperty * fo_table_get_border_top_width (FoFo       *fo_fo);
void         fo_table_set_border_top_width (FoFo       *fo_fo,
                                            FoProperty *new_border_top_width);
FoProperty * fo_table_get_break_after (FoFo       *fo_fo);
void         fo_table_set_break_after (FoFo       *fo_fo,
                                       FoProperty *new_break_after);
FoProperty * fo_table_get_break_before (FoFo       *fo_fo);
void         fo_table_set_break_before (FoFo       *fo_fo,
                                        FoProperty *new_break_before);
FoProperty * fo_table_get_end_indent (FoFo       *fo_fo);
void         fo_table_set_end_indent (FoFo       *fo_fo,
                                      FoProperty *new_end_indent);
FoProperty * fo_table_get_height (FoFo       *fo_fo);
void         fo_table_set_height (FoFo       *fo_fo,
                                  FoProperty *new_height);
FoProperty * fo_table_get_id (FoFo       *fo_fo);
void         fo_table_set_id (FoFo       *fo_fo,
                              FoProperty *new_id);
FoProperty * fo_table_get_inline_progression_dimension (FoFo       *fo_fo);
void         fo_table_set_inline_progression_dimension (FoFo       *fo_fo,
                                                        FoProperty *new_inline_progression_dimension);
FoProperty * fo_table_get_keep_together (FoFo       *fo_fo);
void         fo_table_set_keep_together (FoFo       *fo_fo,
                                         FoProperty *new_keep_together);
FoProperty * fo_table_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_table_set_keep_together_within_column (FoFo       *fo_fo,
                                                       FoProperty *new_keep_together_within_column);
FoProperty * fo_table_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_table_set_keep_together_within_line (FoFo       *fo_fo,
                                                     FoProperty *new_keep_together_within_line);
FoProperty * fo_table_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_table_set_keep_together_within_page (FoFo       *fo_fo,
                                                     FoProperty *new_keep_together_within_page);
FoProperty * fo_table_get_keep_with_next (FoFo       *fo_fo);
void         fo_table_set_keep_with_next (FoFo       *fo_fo,
                                          FoProperty *new_keep_with_next);
FoProperty * fo_table_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_table_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                        FoProperty *new_keep_with_next_within_column);
FoProperty * fo_table_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_table_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                      FoProperty *new_keep_with_next_within_line);
FoProperty * fo_table_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_table_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                      FoProperty *new_keep_with_next_within_page);
FoProperty * fo_table_get_keep_with_previous (FoFo       *fo_fo);
void         fo_table_set_keep_with_previous (FoFo       *fo_fo,
                                              FoProperty *new_keep_with_previous);
FoProperty * fo_table_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_table_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                            FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_table_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_table_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_table_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_table_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_table_get_margin_bottom (FoFo       *fo_fo);
void         fo_table_set_margin_bottom (FoFo       *fo_fo,
                                         FoProperty *new_margin_bottom);
FoProperty * fo_table_get_margin_left (FoFo       *fo_fo);
void         fo_table_set_margin_left (FoFo       *fo_fo,
                                       FoProperty *new_margin_left);
FoProperty * fo_table_get_margin_right (FoFo       *fo_fo);
void         fo_table_set_margin_right (FoFo       *fo_fo,
                                        FoProperty *new_margin_right);
FoProperty * fo_table_get_margin_top (FoFo       *fo_fo);
void         fo_table_set_margin_top (FoFo       *fo_fo,
                                      FoProperty *new_margin_top);
FoProperty * fo_table_get_padding_after (FoFo       *fo_fo);
void         fo_table_set_padding_after (FoFo       *fo_fo,
                                         FoProperty *new_padding_after);
FoProperty * fo_table_get_padding_before (FoFo       *fo_fo);
void         fo_table_set_padding_before (FoFo       *fo_fo,
                                          FoProperty *new_padding_before);
FoProperty * fo_table_get_padding_bottom (FoFo       *fo_fo);
void         fo_table_set_padding_bottom (FoFo       *fo_fo,
                                          FoProperty *new_padding_bottom);
FoProperty * fo_table_get_padding_end (FoFo       *fo_fo);
void         fo_table_set_padding_end (FoFo       *fo_fo,
                                       FoProperty *new_padding_end);
FoProperty * fo_table_get_padding_left (FoFo       *fo_fo);
void         fo_table_set_padding_left (FoFo       *fo_fo,
                                        FoProperty *new_padding_left);
FoProperty * fo_table_get_padding_right (FoFo       *fo_fo);
void         fo_table_set_padding_right (FoFo       *fo_fo,
                                         FoProperty *new_padding_right);
FoProperty * fo_table_get_padding_start (FoFo       *fo_fo);
void         fo_table_set_padding_start (FoFo       *fo_fo,
                                         FoProperty *new_padding_start);
FoProperty * fo_table_get_padding_top (FoFo       *fo_fo);
void         fo_table_set_padding_top (FoFo       *fo_fo,
                                       FoProperty *new_padding_top);
FoProperty * fo_table_get_role (FoFo       *fo_fo);
void         fo_table_set_role (FoFo       *fo_fo,
                                FoProperty *new_role);
FoProperty * fo_table_get_source_document (FoFo       *fo_fo);
void         fo_table_set_source_document (FoFo       *fo_fo,
                                           FoProperty *new_source_document);
FoProperty * fo_table_get_space_after (FoFo       *fo_fo);
void         fo_table_set_space_after (FoFo       *fo_fo,
                                       FoProperty *new_space_after);
FoProperty * fo_table_get_space_before (FoFo       *fo_fo);
void         fo_table_set_space_before (FoFo       *fo_fo,
                                        FoProperty *new_space_before);
FoProperty * fo_table_get_start_indent (FoFo       *fo_fo);
void         fo_table_set_start_indent (FoFo       *fo_fo,
                                        FoProperty *new_start_indent);
FoProperty * fo_table_get_table_layout (FoFo       *fo_fo);
void         fo_table_set_table_layout (FoFo       *fo_fo,
                                        FoProperty *new_table_layout);
FoProperty * fo_table_get_width (FoFo       *fo_fo);
void         fo_table_set_width (FoFo       *fo_fo,
                                 FoProperty *new_width);
FoProperty * fo_table_get_writing_mode (FoFo       *fo_fo);
void         fo_table_set_writing_mode (FoFo       *fo_fo,
                                        FoProperty *new_writing_mode);

G_END_DECLS

#endif /* !__FO_TABLE_H__ */
