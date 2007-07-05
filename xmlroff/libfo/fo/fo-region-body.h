/* Fo
 * fo-region_body.h: 'region-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_BODY_H__
#define __FO_REGION_BODY_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoRegionBody      FoRegionBody;
typedef struct _FoRegionBodyClass FoRegionBodyClass;

#define FO_TYPE_REGION_BODY              (fo_region_body_get_type ())
#define FO_REGION_BODY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_BODY, FoRegionBody))
#define FO_REGION_BODY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_BODY, FoRegionBodyClass))
#define FO_IS_REGION_BODY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_BODY))
#define FO_IS_REGION_BODY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_BODY))
#define FO_REGION_BODY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_BODY, FoRegionBodyClass))


GType        fo_region_body_get_type      (void) G_GNUC_CONST;
FoFo *       fo_region_body_new (void);

FoProperty * fo_region_body_get_background_color (FoFo       *fo_fo);
void         fo_region_body_set_background_color (FoFo       *fo_fo,
						  FoProperty *new_background_color);
FoProperty * fo_region_body_get_background_image (FoFo       *fo_fo);
void         fo_region_body_set_background_image (FoFo       *fo_fo,
                                                  FoProperty *new_background_image);
FoProperty * fo_region_body_get_border_after_color (FoFo       *fo_fo);
void         fo_region_body_set_border_after_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_after_color);
FoProperty * fo_region_body_get_border_after_style (FoFo       *fo_fo);
void         fo_region_body_set_border_after_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_after_style);
FoProperty * fo_region_body_get_border_after_width (FoFo       *fo_fo);
void         fo_region_body_set_border_after_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_after_width);
FoProperty * fo_region_body_get_border_before_color (FoFo       *fo_fo);
void         fo_region_body_set_border_before_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_before_color);
FoProperty * fo_region_body_get_border_before_style (FoFo       *fo_fo);
void         fo_region_body_set_border_before_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_before_style);
FoProperty * fo_region_body_get_border_before_width (FoFo       *fo_fo);
void         fo_region_body_set_border_before_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_before_width);
FoProperty * fo_region_body_get_border_bottom_color (FoFo       *fo_fo);
void         fo_region_body_set_border_bottom_color (FoFo       *fo_fo,
                                                     FoProperty *new_border_bottom_color);
FoProperty * fo_region_body_get_border_bottom_style (FoFo       *fo_fo);
void         fo_region_body_set_border_bottom_style (FoFo       *fo_fo,
                                                     FoProperty *new_border_bottom_style);
FoProperty * fo_region_body_get_border_bottom_width (FoFo       *fo_fo);
void         fo_region_body_set_border_bottom_width (FoFo       *fo_fo,
                                                     FoProperty *new_border_bottom_width);
FoProperty * fo_region_body_get_border_end_color (FoFo       *fo_fo);
void         fo_region_body_set_border_end_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_end_color);
FoProperty * fo_region_body_get_border_end_style (FoFo       *fo_fo);
void         fo_region_body_set_border_end_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_end_style);
FoProperty * fo_region_body_get_border_end_width (FoFo       *fo_fo);
void         fo_region_body_set_border_end_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_end_width);
FoProperty * fo_region_body_get_border_left_color (FoFo       *fo_fo);
void         fo_region_body_set_border_left_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_left_color);
FoProperty * fo_region_body_get_border_left_style (FoFo       *fo_fo);
void         fo_region_body_set_border_left_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_left_style);
FoProperty * fo_region_body_get_border_left_width (FoFo       *fo_fo);
void         fo_region_body_set_border_left_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_left_width);
FoProperty * fo_region_body_get_border_right_color (FoFo       *fo_fo);
void         fo_region_body_set_border_right_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_right_color);
FoProperty * fo_region_body_get_border_right_style (FoFo       *fo_fo);
void         fo_region_body_set_border_right_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_right_style);
FoProperty * fo_region_body_get_border_right_width (FoFo       *fo_fo);
void         fo_region_body_set_border_right_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_right_width);
FoProperty * fo_region_body_get_border_start_color (FoFo       *fo_fo);
void         fo_region_body_set_border_start_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_start_color);
FoProperty * fo_region_body_get_border_start_style (FoFo       *fo_fo);
void         fo_region_body_set_border_start_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_start_style);
FoProperty * fo_region_body_get_border_start_width (FoFo       *fo_fo);
void         fo_region_body_set_border_start_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_start_width);
FoProperty * fo_region_body_get_border_top_color (FoFo       *fo_fo);
void         fo_region_body_set_border_top_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_top_color);
FoProperty * fo_region_body_get_border_top_style (FoFo       *fo_fo);
void         fo_region_body_set_border_top_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_top_style);
FoProperty * fo_region_body_get_border_top_width (FoFo       *fo_fo);
void         fo_region_body_set_border_top_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_top_width);
FoProperty * fo_region_body_get_clip (FoFo       *fo_fo);
void         fo_region_body_set_clip (FoFo       *fo_fo,
                                      FoProperty *new_clip);
FoProperty * fo_region_body_get_display_align (FoFo       *fo_fo);
void         fo_region_body_set_display_align (FoFo       *fo_fo,
                                               FoProperty *new_display_align);
FoProperty * fo_region_body_get_end_indent (FoFo       *fo_fo);
void         fo_region_body_set_end_indent (FoFo       *fo_fo,
                                            FoProperty *new_end_indent);
FoProperty * fo_region_body_get_margin_bottom (FoFo       *fo_fo);
void         fo_region_body_set_margin_bottom (FoFo       *fo_fo,
                                               FoProperty *new_margin_bottom);
FoProperty * fo_region_body_get_margin_left (FoFo       *fo_fo);
void         fo_region_body_set_margin_left (FoFo       *fo_fo,
                                             FoProperty *new_margin_left);
FoProperty * fo_region_body_get_margin_right (FoFo       *fo_fo);
void         fo_region_body_set_margin_right (FoFo       *fo_fo,
                                              FoProperty *new_margin_right);
FoProperty * fo_region_body_get_margin_top (FoFo       *fo_fo);
void         fo_region_body_set_margin_top (FoFo       *fo_fo,
                                            FoProperty *new_margin_top);
FoProperty * fo_region_body_get_overflow (FoFo       *fo_fo);
void         fo_region_body_set_overflow (FoFo       *fo_fo,
                                          FoProperty *new_overflow);
FoProperty * fo_region_body_get_padding_after (FoFo       *fo_fo);
void         fo_region_body_set_padding_after (FoFo       *fo_fo,
                                               FoProperty *new_padding_after);
FoProperty * fo_region_body_get_padding_before (FoFo       *fo_fo);
void         fo_region_body_set_padding_before (FoFo       *fo_fo,
                                                FoProperty *new_padding_before);
FoProperty * fo_region_body_get_padding_bottom (FoFo       *fo_fo);
void         fo_region_body_set_padding_bottom (FoFo       *fo_fo,
                                                FoProperty *new_padding_bottom);
FoProperty * fo_region_body_get_padding_end (FoFo       *fo_fo);
void         fo_region_body_set_padding_end (FoFo       *fo_fo,
                                             FoProperty *new_padding_end);
FoProperty * fo_region_body_get_padding_left (FoFo       *fo_fo);
void         fo_region_body_set_padding_left (FoFo       *fo_fo,
                                              FoProperty *new_padding_left);
FoProperty * fo_region_body_get_padding_right (FoFo       *fo_fo);
void         fo_region_body_set_padding_right (FoFo       *fo_fo,
                                               FoProperty *new_padding_right);
FoProperty * fo_region_body_get_padding_start (FoFo       *fo_fo);
void         fo_region_body_set_padding_start (FoFo       *fo_fo,
                                               FoProperty *new_padding_start);
FoProperty * fo_region_body_get_padding_top (FoFo       *fo_fo);
void         fo_region_body_set_padding_top (FoFo       *fo_fo,
                                             FoProperty *new_padding_top);
FoProperty * fo_region_body_get_region_name (FoFo       *fo_fo);
void         fo_region_body_set_region_name (FoFo       *fo_fo,
                                             FoProperty *new_region_name);
FoProperty * fo_region_body_get_space_after (FoFo       *fo_fo);
void         fo_region_body_set_space_after (FoFo       *fo_fo,
                                             FoProperty *new_space_after);
FoProperty * fo_region_body_get_space_before (FoFo       *fo_fo);
void         fo_region_body_set_space_before (FoFo       *fo_fo,
                                              FoProperty *new_space_before);
FoProperty * fo_region_body_get_start_indent (FoFo       *fo_fo);
void         fo_region_body_set_start_indent (FoFo       *fo_fo,
                                              FoProperty *new_start_indent);
FoProperty * fo_region_body_get_writing_mode (FoFo       *fo_fo);
void         fo_region_body_set_writing_mode (FoFo       *fo_fo,
                                              FoProperty *new_writing_mode);

G_END_DECLS

#endif /* !__FO_REGION_BODY_H__ */
