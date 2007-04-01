/* Fo
 * fo-table_column.h: 'table-column' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-column.h,v 1.4 2004/03/30 22:45:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_TABLE_COLUMN_H__
#define __FO_TABLE_COLUMN_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

#define FO_TABLE_COLUMN_ERROR fo_table_column_error_quark ()

GQuark fo_table_column_error_quark (void);

typedef enum
{
  FO_TABLE_COLUMN_ERROR_FAILED,          /* Generic error code */
  FO_TABLE_COLUMN_ERROR_WARNING,         /* Non-fatal error */
  FO_TABLE_COLUMN_ERROR_FIXED_NO_WIDTH,  /* column-width required when fixed */
  FO_TABLE_COLUMN_ERROR_LAST
} FoTableColumnError;

extern const char *fo_table_column_error_messages[FO_TABLE_COLUMN_ERROR_LAST];

typedef struct _FoTableColumn      FoTableColumn;
typedef struct _FoTableColumnClass FoTableColumnClass;

#define FO_TYPE_TABLE_COLUMN              (fo_table_column_get_type ())
#define FO_TABLE_COLUMN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TABLE_COLUMN, FoTableColumn))
#define FO_TABLE_COLUMN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TABLE_COLUMN, FoTableColumnClass))
#define FO_IS_TABLE_COLUMN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TABLE_COLUMN))
#define FO_IS_TABLE_COLUMN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TABLE_COLUMN))
#define FO_TABLE_COLUMN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TABLE_COLUMN, FoTableColumnClass))


GType        fo_table_column_get_type      (void) G_GNUC_CONST;
FoFo *       fo_table_column_new (void);

gfloat       fo_table_column_get_offset (FoFo   *fo_fo);
void         fo_table_column_set_offset (FoFo   *fo_fo,
					 gfloat new_offset);

FoProperty * fo_table_column_get_background_color (FoFo       *fo_fo);
void         fo_table_column_set_background_color (FoFo       *fo_fo,
						   FoProperty *new_background_color);
FoProperty * fo_table_column_get_background_image (FoFo       *fo_fo);
void         fo_table_column_set_background_image (FoFo       *fo_fo,
                                                   FoProperty *new_background_image);
FoProperty * fo_table_column_get_border_after_color (FoFo       *fo_fo);
void         fo_table_column_set_border_after_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_after_color);
FoProperty * fo_table_column_get_border_after_precedence (FoFo       *fo_fo);
void         fo_table_column_set_border_after_precedence (FoFo       *fo_fo,
                                                          FoProperty *new_border_after_precedence);
FoProperty * fo_table_column_get_border_after_style (FoFo       *fo_fo);
void         fo_table_column_set_border_after_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_after_style);
FoProperty * fo_table_column_get_border_after_width (FoFo       *fo_fo);
void         fo_table_column_set_border_after_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_after_width);
FoProperty * fo_table_column_get_border_before_color (FoFo       *fo_fo);
void         fo_table_column_set_border_before_color (FoFo       *fo_fo,
                                                      FoProperty *new_border_before_color);
FoProperty * fo_table_column_get_border_before_precedence (FoFo       *fo_fo);
void         fo_table_column_set_border_before_precedence (FoFo       *fo_fo,
                                                           FoProperty *new_border_before_precedence);
FoProperty * fo_table_column_get_border_before_style (FoFo       *fo_fo);
void         fo_table_column_set_border_before_style (FoFo       *fo_fo,
                                                      FoProperty *new_border_before_style);
FoProperty * fo_table_column_get_border_before_width (FoFo       *fo_fo);
void         fo_table_column_set_border_before_width (FoFo       *fo_fo,
                                                      FoProperty *new_border_before_width);
FoProperty * fo_table_column_get_border_bottom_color (FoFo       *fo_fo);
void         fo_table_column_set_border_bottom_color (FoFo       *fo_fo,
                                                      FoProperty *new_border_bottom_color);
FoProperty * fo_table_column_get_border_bottom_style (FoFo       *fo_fo);
void         fo_table_column_set_border_bottom_style (FoFo       *fo_fo,
                                                      FoProperty *new_border_bottom_style);
FoProperty * fo_table_column_get_border_bottom_width (FoFo       *fo_fo);
void         fo_table_column_set_border_bottom_width (FoFo       *fo_fo,
                                                      FoProperty *new_border_bottom_width);
FoProperty * fo_table_column_get_border_end_color (FoFo       *fo_fo);
void         fo_table_column_set_border_end_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_end_color);
FoProperty * fo_table_column_get_border_end_precedence (FoFo       *fo_fo);
void         fo_table_column_set_border_end_precedence (FoFo       *fo_fo,
                                                        FoProperty *new_border_end_precedence);
FoProperty * fo_table_column_get_border_end_style (FoFo       *fo_fo);
void         fo_table_column_set_border_end_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_end_style);
FoProperty * fo_table_column_get_border_end_width (FoFo       *fo_fo);
void         fo_table_column_set_border_end_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_end_width);
FoProperty * fo_table_column_get_border_left_color (FoFo       *fo_fo);
void         fo_table_column_set_border_left_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_left_color);
FoProperty * fo_table_column_get_border_left_style (FoFo       *fo_fo);
void         fo_table_column_set_border_left_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_left_style);
FoProperty * fo_table_column_get_border_left_width (FoFo       *fo_fo);
void         fo_table_column_set_border_left_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_left_width);
FoProperty * fo_table_column_get_border_right_color (FoFo       *fo_fo);
void         fo_table_column_set_border_right_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_right_color);
FoProperty * fo_table_column_get_border_right_style (FoFo       *fo_fo);
void         fo_table_column_set_border_right_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_right_style);
FoProperty * fo_table_column_get_border_right_width (FoFo       *fo_fo);
void         fo_table_column_set_border_right_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_right_width);
FoProperty * fo_table_column_get_border_start_color (FoFo       *fo_fo);
void         fo_table_column_set_border_start_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_start_color);
FoProperty * fo_table_column_get_border_start_precedence (FoFo       *fo_fo);
void         fo_table_column_set_border_start_precedence (FoFo       *fo_fo,
                                                          FoProperty *new_border_start_precedence);
FoProperty * fo_table_column_get_border_start_style (FoFo       *fo_fo);
void         fo_table_column_set_border_start_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_start_style);
FoProperty * fo_table_column_get_border_start_width (FoFo       *fo_fo);
void         fo_table_column_set_border_start_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_start_width);
FoProperty * fo_table_column_get_border_top_color (FoFo       *fo_fo);
void         fo_table_column_set_border_top_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_top_color);
FoProperty * fo_table_column_get_border_top_style (FoFo       *fo_fo);
void         fo_table_column_set_border_top_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_top_style);
FoProperty * fo_table_column_get_border_top_width (FoFo       *fo_fo);
void         fo_table_column_set_border_top_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_top_width);
FoProperty * fo_table_column_get_column_number (FoFo       *fo_fo);
void         fo_table_column_set_column_number (FoFo       *fo_fo,
                                                FoProperty *new_column_number);
FoProperty * fo_table_column_get_column_width (FoFo       *fo_fo);
void         fo_table_column_set_column_width (FoFo       *fo_fo,
                                               FoProperty *new_column_width);
FoProperty * fo_table_column_get_number_columns_repeated (FoFo       *fo_fo);
void         fo_table_column_set_number_columns_repeated (FoFo       *fo_fo,
                                                          FoProperty *new_number_columns_repeated);
FoProperty * fo_table_column_get_number_columns_spanned (FoFo       *fo_fo);
void         fo_table_column_set_number_columns_spanned (FoFo       *fo_fo,
                                                         FoProperty *new_number_columns_spanned);
FoProperty * fo_table_column_get_padding_after (FoFo       *fo_fo);
void         fo_table_column_set_padding_after (FoFo       *fo_fo,
                                                FoProperty *new_padding_after);
FoProperty * fo_table_column_get_padding_before (FoFo       *fo_fo);
void         fo_table_column_set_padding_before (FoFo       *fo_fo,
                                                 FoProperty *new_padding_before);
FoProperty * fo_table_column_get_padding_bottom (FoFo       *fo_fo);
void         fo_table_column_set_padding_bottom (FoFo       *fo_fo,
                                                 FoProperty *new_padding_bottom);
FoProperty * fo_table_column_get_padding_end (FoFo       *fo_fo);
void         fo_table_column_set_padding_end (FoFo       *fo_fo,
                                              FoProperty *new_padding_end);
FoProperty * fo_table_column_get_padding_left (FoFo       *fo_fo);
void         fo_table_column_set_padding_left (FoFo       *fo_fo,
                                               FoProperty *new_padding_left);
FoProperty * fo_table_column_get_padding_right (FoFo       *fo_fo);
void         fo_table_column_set_padding_right (FoFo       *fo_fo,
                                                FoProperty *new_padding_right);
FoProperty * fo_table_column_get_padding_start (FoFo       *fo_fo);
void         fo_table_column_set_padding_start (FoFo       *fo_fo,
                                                FoProperty *new_padding_start);
FoProperty * fo_table_column_get_padding_top (FoFo       *fo_fo);
void         fo_table_column_set_padding_top (FoFo       *fo_fo,
                                              FoProperty *new_padding_top);

G_END_DECLS

#endif /* !__FO_TABLE_COLUMN_H__ */
