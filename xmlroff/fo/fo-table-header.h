/* Fo
 * fo-table_header.h: 'table-header' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-header.h,v 1.4 2004/03/30 22:45:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_TABLE_HEADER_H__
#define __FO_TABLE_HEADER_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

typedef struct _FoTableHeader      FoTableHeader;
typedef struct _FoTableHeaderClass FoTableHeaderClass;

#define FO_TYPE_TABLE_HEADER              (fo_table_header_get_type ())
#define FO_TABLE_HEADER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TABLE_HEADER, FoTableHeader))
#define FO_TABLE_HEADER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TABLE_HEADER, FoTableHeaderClass))
#define FO_IS_TABLE_HEADER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TABLE_HEADER))
#define FO_IS_TABLE_HEADER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TABLE_HEADER))
#define FO_TABLE_HEADER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TABLE_HEADER, FoTableHeaderClass))


GType        fo_table_header_get_type      (void) G_GNUC_CONST;
FoFo *       fo_table_header_new (void);

FoProperty * fo_table_header_get_background_color (FoFo       *fo_fo);
void         fo_table_header_set_background_color (FoFo       *fo_fo,
                                                   FoProperty *new_background_color);
FoProperty * fo_table_header_get_background_image (FoFo       *fo_fo);
void         fo_table_header_set_background_image (FoFo       *fo_fo,
                                                   FoProperty *new_background_image);
FoProperty * fo_table_header_get_border_after_color (FoFo       *fo_fo);
void         fo_table_header_set_border_after_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_after_color);
FoProperty * fo_table_header_get_border_after_precedence (FoFo       *fo_fo);
void         fo_table_header_set_border_after_precedence (FoFo       *fo_fo,
                                                          FoProperty *new_border_after_precedence);
FoProperty * fo_table_header_get_border_after_style (FoFo       *fo_fo);
void         fo_table_header_set_border_after_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_after_style);
FoProperty * fo_table_header_get_border_after_width (FoFo       *fo_fo);
void         fo_table_header_set_border_after_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_after_width);
FoProperty * fo_table_header_get_border_before_color (FoFo       *fo_fo);
void         fo_table_header_set_border_before_color (FoFo       *fo_fo,
                                                      FoProperty *new_border_before_color);
FoProperty * fo_table_header_get_border_before_precedence (FoFo       *fo_fo);
void         fo_table_header_set_border_before_precedence (FoFo       *fo_fo,
                                                           FoProperty *new_border_before_precedence);
FoProperty * fo_table_header_get_border_before_style (FoFo       *fo_fo);
void         fo_table_header_set_border_before_style (FoFo       *fo_fo,
                                                      FoProperty *new_border_before_style);
FoProperty * fo_table_header_get_border_before_width (FoFo       *fo_fo);
void         fo_table_header_set_border_before_width (FoFo       *fo_fo,
                                                      FoProperty *new_border_before_width);
FoProperty * fo_table_header_get_border_bottom_color (FoFo       *fo_fo);
void         fo_table_header_set_border_bottom_color (FoFo       *fo_fo,
                                                      FoProperty *new_border_bottom_color);
FoProperty * fo_table_header_get_border_bottom_style (FoFo       *fo_fo);
void         fo_table_header_set_border_bottom_style (FoFo       *fo_fo,
                                                      FoProperty *new_border_bottom_style);
FoProperty * fo_table_header_get_border_bottom_width (FoFo       *fo_fo);
void         fo_table_header_set_border_bottom_width (FoFo       *fo_fo,
                                                      FoProperty *new_border_bottom_width);
FoProperty * fo_table_header_get_border_end_color (FoFo       *fo_fo);
void         fo_table_header_set_border_end_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_end_color);
FoProperty * fo_table_header_get_border_end_precedence (FoFo       *fo_fo);
void         fo_table_header_set_border_end_precedence (FoFo       *fo_fo,
                                                        FoProperty *new_border_end_precedence);
FoProperty * fo_table_header_get_border_end_style (FoFo       *fo_fo);
void         fo_table_header_set_border_end_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_end_style);
FoProperty * fo_table_header_get_border_end_width (FoFo       *fo_fo);
void         fo_table_header_set_border_end_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_end_width);
FoProperty * fo_table_header_get_border_left_color (FoFo       *fo_fo);
void         fo_table_header_set_border_left_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_left_color);
FoProperty * fo_table_header_get_border_left_style (FoFo       *fo_fo);
void         fo_table_header_set_border_left_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_left_style);
FoProperty * fo_table_header_get_border_left_width (FoFo       *fo_fo);
void         fo_table_header_set_border_left_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_left_width);
FoProperty * fo_table_header_get_border_right_color (FoFo       *fo_fo);
void         fo_table_header_set_border_right_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_right_color);
FoProperty * fo_table_header_get_border_right_style (FoFo       *fo_fo);
void         fo_table_header_set_border_right_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_right_style);
FoProperty * fo_table_header_get_border_right_width (FoFo       *fo_fo);
void         fo_table_header_set_border_right_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_right_width);
FoProperty * fo_table_header_get_border_start_color (FoFo       *fo_fo);
void         fo_table_header_set_border_start_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_start_color);
FoProperty * fo_table_header_get_border_start_precedence (FoFo       *fo_fo);
void         fo_table_header_set_border_start_precedence (FoFo       *fo_fo,
                                                          FoProperty *new_border_start_precedence);
FoProperty * fo_table_header_get_border_start_style (FoFo       *fo_fo);
void         fo_table_header_set_border_start_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_start_style);
FoProperty * fo_table_header_get_border_start_width (FoFo       *fo_fo);
void         fo_table_header_set_border_start_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_start_width);
FoProperty * fo_table_header_get_border_top_color (FoFo       *fo_fo);
void         fo_table_header_set_border_top_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_top_color);
FoProperty * fo_table_header_get_border_top_style (FoFo       *fo_fo);
void         fo_table_header_set_border_top_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_top_style);
FoProperty * fo_table_header_get_border_top_width (FoFo       *fo_fo);
void         fo_table_header_set_border_top_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_top_width);
FoProperty * fo_table_header_get_id (FoFo       *fo_fo);
void         fo_table_header_set_id (FoFo       *fo_fo,
                                     FoProperty *new_id);
FoProperty * fo_table_header_get_padding_after (FoFo       *fo_fo);
void         fo_table_header_set_padding_after (FoFo       *fo_fo,
                                                FoProperty *new_padding_after);
FoProperty * fo_table_header_get_padding_before (FoFo       *fo_fo);
void         fo_table_header_set_padding_before (FoFo       *fo_fo,
                                                 FoProperty *new_padding_before);
FoProperty * fo_table_header_get_padding_bottom (FoFo       *fo_fo);
void         fo_table_header_set_padding_bottom (FoFo       *fo_fo,
                                                 FoProperty *new_padding_bottom);
FoProperty * fo_table_header_get_padding_end (FoFo       *fo_fo);
void         fo_table_header_set_padding_end (FoFo       *fo_fo,
                                              FoProperty *new_padding_end);
FoProperty * fo_table_header_get_padding_left (FoFo       *fo_fo);
void         fo_table_header_set_padding_left (FoFo       *fo_fo,
                                               FoProperty *new_padding_left);
FoProperty * fo_table_header_get_padding_right (FoFo       *fo_fo);
void         fo_table_header_set_padding_right (FoFo       *fo_fo,
                                                FoProperty *new_padding_right);
FoProperty * fo_table_header_get_padding_start (FoFo       *fo_fo);
void         fo_table_header_set_padding_start (FoFo       *fo_fo,
                                                FoProperty *new_padding_start);
FoProperty * fo_table_header_get_padding_top (FoFo       *fo_fo);
void         fo_table_header_set_padding_top (FoFo       *fo_fo,
                                              FoProperty *new_padding_top);
FoProperty * fo_table_header_get_role (FoFo       *fo_fo);
void         fo_table_header_set_role (FoFo       *fo_fo,
                                       FoProperty *new_role);
FoProperty * fo_table_header_get_source_document (FoFo       *fo_fo);
void         fo_table_header_set_source_document (FoFo       *fo_fo,
                                                  FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_TABLE_HEADER_H__ */
