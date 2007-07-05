/* Fo
 * fo-title.h: 'title' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TITLE_H__
#define __FO_TITLE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoTitle      FoTitle;
typedef struct _FoTitleClass FoTitleClass;

#define FO_TYPE_TITLE              (fo_title_get_type ())
#define FO_TITLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TITLE, FoTitle))
#define FO_TITLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TITLE, FoTitleClass))
#define FO_IS_TITLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TITLE))
#define FO_IS_TITLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TITLE))
#define FO_TITLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TITLE, FoTitleClass))


GType        fo_title_get_type      (void) G_GNUC_CONST;
FoFo *       fo_title_new (void);

FoProperty * fo_title_get_background_color (FoFo       *fo_fo);
void         fo_title_set_background_color (FoFo       *fo_fo,
					    FoProperty *new_background_color);
FoProperty * fo_title_get_background_image (FoFo       *fo_fo);
void         fo_title_set_background_image (FoFo       *fo_fo,
                                            FoProperty *new_background_image);
FoProperty * fo_title_get_border_after_color (FoFo       *fo_fo);
void         fo_title_set_border_after_color (FoFo       *fo_fo,
                                              FoProperty *new_border_after_color);
FoProperty * fo_title_get_border_after_style (FoFo       *fo_fo);
void         fo_title_set_border_after_style (FoFo       *fo_fo,
                                              FoProperty *new_border_after_style);
FoProperty * fo_title_get_border_after_width (FoFo       *fo_fo);
void         fo_title_set_border_after_width (FoFo       *fo_fo,
                                              FoProperty *new_border_after_width);
FoProperty * fo_title_get_border_before_color (FoFo       *fo_fo);
void         fo_title_set_border_before_color (FoFo       *fo_fo,
                                               FoProperty *new_border_before_color);
FoProperty * fo_title_get_border_before_style (FoFo       *fo_fo);
void         fo_title_set_border_before_style (FoFo       *fo_fo,
                                               FoProperty *new_border_before_style);
FoProperty * fo_title_get_border_before_width (FoFo       *fo_fo);
void         fo_title_set_border_before_width (FoFo       *fo_fo,
                                               FoProperty *new_border_before_width);
FoProperty * fo_title_get_border_bottom_color (FoFo       *fo_fo);
void         fo_title_set_border_bottom_color (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_color);
FoProperty * fo_title_get_border_bottom_style (FoFo       *fo_fo);
void         fo_title_set_border_bottom_style (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_style);
FoProperty * fo_title_get_border_bottom_width (FoFo       *fo_fo);
void         fo_title_set_border_bottom_width (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_width);
FoProperty * fo_title_get_border_end_color (FoFo       *fo_fo);
void         fo_title_set_border_end_color (FoFo       *fo_fo,
                                            FoProperty *new_border_end_color);
FoProperty * fo_title_get_border_end_style (FoFo       *fo_fo);
void         fo_title_set_border_end_style (FoFo       *fo_fo,
                                            FoProperty *new_border_end_style);
FoProperty * fo_title_get_border_end_width (FoFo       *fo_fo);
void         fo_title_set_border_end_width (FoFo       *fo_fo,
                                            FoProperty *new_border_end_width);
FoProperty * fo_title_get_border_left_color (FoFo       *fo_fo);
void         fo_title_set_border_left_color (FoFo       *fo_fo,
                                             FoProperty *new_border_left_color);
FoProperty * fo_title_get_border_left_style (FoFo       *fo_fo);
void         fo_title_set_border_left_style (FoFo       *fo_fo,
                                             FoProperty *new_border_left_style);
FoProperty * fo_title_get_border_left_width (FoFo       *fo_fo);
void         fo_title_set_border_left_width (FoFo       *fo_fo,
                                             FoProperty *new_border_left_width);
FoProperty * fo_title_get_border_right_color (FoFo       *fo_fo);
void         fo_title_set_border_right_color (FoFo       *fo_fo,
                                              FoProperty *new_border_right_color);
FoProperty * fo_title_get_border_right_style (FoFo       *fo_fo);
void         fo_title_set_border_right_style (FoFo       *fo_fo,
                                              FoProperty *new_border_right_style);
FoProperty * fo_title_get_border_right_width (FoFo       *fo_fo);
void         fo_title_set_border_right_width (FoFo       *fo_fo,
                                              FoProperty *new_border_right_width);
FoProperty * fo_title_get_border_start_color (FoFo       *fo_fo);
void         fo_title_set_border_start_color (FoFo       *fo_fo,
                                              FoProperty *new_border_start_color);
FoProperty * fo_title_get_border_start_style (FoFo       *fo_fo);
void         fo_title_set_border_start_style (FoFo       *fo_fo,
                                              FoProperty *new_border_start_style);
FoProperty * fo_title_get_border_start_width (FoFo       *fo_fo);
void         fo_title_set_border_start_width (FoFo       *fo_fo,
                                              FoProperty *new_border_start_width);
FoProperty * fo_title_get_border_top_color (FoFo       *fo_fo);
void         fo_title_set_border_top_color (FoFo       *fo_fo,
                                            FoProperty *new_border_top_color);
FoProperty * fo_title_get_border_top_style (FoFo       *fo_fo);
void         fo_title_set_border_top_style (FoFo       *fo_fo,
                                            FoProperty *new_border_top_style);
FoProperty * fo_title_get_border_top_width (FoFo       *fo_fo);
void         fo_title_set_border_top_width (FoFo       *fo_fo,
                                            FoProperty *new_border_top_width);
FoProperty * fo_title_get_color (FoFo       *fo_fo);
void         fo_title_set_color (FoFo       *fo_fo,
                                 FoProperty *new_color);
FoProperty * fo_title_get_font_family (FoFo       *fo_fo);
void         fo_title_set_font_family (FoFo       *fo_fo,
                                       FoProperty *new_font_family);
FoProperty * fo_title_get_font_size (FoFo       *fo_fo);
void         fo_title_set_font_size (FoFo       *fo_fo,
                                     FoProperty *new_font_size);
FoProperty * fo_title_get_font_stretch (FoFo       *fo_fo);
void         fo_title_set_font_stretch (FoFo       *fo_fo,
                                        FoProperty *new_font_stretch);
FoProperty * fo_title_get_font_style (FoFo       *fo_fo);
void         fo_title_set_font_style (FoFo       *fo_fo,
                                      FoProperty *new_font_style);
FoProperty * fo_title_get_font_variant (FoFo       *fo_fo);
void         fo_title_set_font_variant (FoFo       *fo_fo,
                                        FoProperty *new_font_variant);
FoProperty * fo_title_get_font_weight (FoFo       *fo_fo);
void         fo_title_set_font_weight (FoFo       *fo_fo,
                                       FoProperty *new_font_weight);
FoProperty * fo_title_get_line_height (FoFo       *fo_fo);
void         fo_title_set_line_height (FoFo       *fo_fo,
                                       FoProperty *new_line_height);
FoProperty * fo_title_get_padding_after (FoFo       *fo_fo);
void         fo_title_set_padding_after (FoFo       *fo_fo,
                                         FoProperty *new_padding_after);
FoProperty * fo_title_get_padding_before (FoFo       *fo_fo);
void         fo_title_set_padding_before (FoFo       *fo_fo,
                                          FoProperty *new_padding_before);
FoProperty * fo_title_get_padding_bottom (FoFo       *fo_fo);
void         fo_title_set_padding_bottom (FoFo       *fo_fo,
                                          FoProperty *new_padding_bottom);
FoProperty * fo_title_get_padding_end (FoFo       *fo_fo);
void         fo_title_set_padding_end (FoFo       *fo_fo,
                                       FoProperty *new_padding_end);
FoProperty * fo_title_get_padding_left (FoFo       *fo_fo);
void         fo_title_set_padding_left (FoFo       *fo_fo,
                                        FoProperty *new_padding_left);
FoProperty * fo_title_get_padding_right (FoFo       *fo_fo);
void         fo_title_set_padding_right (FoFo       *fo_fo,
                                         FoProperty *new_padding_right);
FoProperty * fo_title_get_padding_start (FoFo       *fo_fo);
void         fo_title_set_padding_start (FoFo       *fo_fo,
                                         FoProperty *new_padding_start);
FoProperty * fo_title_get_padding_top (FoFo       *fo_fo);
void         fo_title_set_padding_top (FoFo       *fo_fo,
                                       FoProperty *new_padding_top);
FoProperty * fo_title_get_role (FoFo       *fo_fo);
void         fo_title_set_role (FoFo       *fo_fo,
                                FoProperty *new_role);
FoProperty * fo_title_get_source_document (FoFo       *fo_fo);
void         fo_title_set_source_document (FoFo       *fo_fo,
                                           FoProperty *new_source_document);
FoProperty * fo_title_get_space_end (FoFo       *fo_fo);
void         fo_title_set_space_end (FoFo       *fo_fo,
                                     FoProperty *new_space_end);
FoProperty * fo_title_get_space_start (FoFo       *fo_fo);
void         fo_title_set_space_start (FoFo       *fo_fo,
                                       FoProperty *new_space_start);

G_END_DECLS

#endif /* !__FO_TITLE_H__ */
