/* Fo
 * fo-cbpbp-fo-private.h: Structures private to "Common Border, Padding, and Background Properties" FO interface
 *
 * Copyright (C) 2008-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CBPBP_FO_PRIVATE_H__
#define __FO_CBPBP_FO_PRIVATE_H__

#include <libfo/fo/fo-cbpbp-fo.h>
#include <libfo/fo-context.h>

G_BEGIN_DECLS

struct _FoCBPBPFoIface
{
  GTypeInterface g_iface;

  /*
  FoProperty * (* get_background_attachment)          (FoFo *fo_cbpbp_fo);
  */
  FoProperty * (* get_background_color)               (FoFo *fo_cbpbp_fo);
  void (* set_background_color) (FoFo *fo_cbpbp_fo,
				 FoProperty *new_background_color);
  /*
  FoProperty * (* get_background_image)               (FoFo *fo_cbpbp_fo);
  FoProperty * (* get_background_repeat)              (FoFo *fo_cbpbp_fo);
  FoProperty * (* get_background_position_horizontal) (FoFo *fo_cbpbp_fo);
  FoProperty * (* get_background_position_vertical)   (FoFo *fo_cbpbp_fo);
  */
  FoProperty * (* get_border_after_color)             (FoFo *fo_cbpbp_fo);
  void         (* set_border_after_color)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_after_color);
  FoProperty * (* get_border_after_style)             (FoFo *fo_cbpbp_fo);
  void         (* set_border_after_style)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_after_style);
  FoProperty * (* get_border_after_width)             (FoFo *fo_cbpbp_fo);
  void         (* set_border_after_width)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_after_width);
  FoProperty * (* get_border_before_color)            (FoFo *fo_cbpbp_fo);
  void         (* set_border_before_color)            (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_before_color);
  FoProperty * (* get_border_before_style)            (FoFo *fo_cbpbp_fo);
  void         (* set_border_before_style)            (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_before_style);
  FoProperty * (* get_border_before_width)            (FoFo *fo_cbpbp_fo);
  void         (* set_border_before_width)            (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_before_width);
  void         (* set_border_bottom_color)            (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_bottom_color);
  void         (* set_border_bottom_style)            (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_bottom_style);
  void         (* set_border_bottom_width)            (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_bottom_width);
  FoProperty * (* get_border_end_color)               (FoFo *fo_cbpbp_fo);
  void         (* set_border_end_color)               (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_end_color);
  FoProperty * (* get_border_end_style)               (FoFo *fo_cbpbp_fo);
  void         (* set_border_end_style)               (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_end_style);
  FoProperty * (* get_border_end_width)               (FoFo *fo_cbpbp_fo);
  void         (* set_border_end_width)               (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_end_width);
  void         (* set_border_left_color)              (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_left_color);
  void         (* set_border_left_style)              (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_left_style);
  void         (* set_border_left_width)              (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_left_width);
  void         (* set_border_right_color)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_right_color);
  void         (* set_border_right_style)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_right_style);
  void         (* set_border_right_width)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_right_width);
  FoProperty * (* get_border_start_color)             (FoFo *fo_cbpbp_fo);
  void         (* set_border_start_color)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_start_color);
  FoProperty * (* get_border_start_style)             (FoFo *fo_cbpbp_fo);
  void         (* set_border_start_style)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_start_style);
  FoProperty * (* get_border_start_width)             (FoFo *fo_cbpbp_fo);
  void         (* set_border_start_width)             (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_start_width);
  void         (* set_border_top_color)               (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_top_color);
  void         (* set_border_top_style)               (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_top_style);
  void         (* set_border_top_width)               (FoFo *fo_cbpbp_fo,
						       FoProperty *new_border_top_width);
  FoProperty * (* get_padding_after)                  (FoFo *fo_cbpbp_fo);
  void         (* set_padding_after)                  (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_after);
  FoProperty * (* get_padding_before)                 (FoFo *fo_cbpbp_fo);
  void         (* set_padding_before)                 (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_before);
  void         (* set_padding_bottom)                 (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_bottom);
  FoProperty * (* get_padding_end)                    (FoFo *fo_cbpbp_fo);
  void         (* set_padding_end)                    (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_end);
  void         (* set_padding_left)                   (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_left);
  void         (* set_padding_right)                  (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_right);
  FoProperty * (* get_padding_start)                  (FoFo *fo_cbpbp_fo);
  void         (* set_padding_start)                  (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_start);
  void         (* set_padding_top)                    (FoFo *fo_cbpbp_fo,
						       FoProperty *new_padding_top);
};

void fo_cbpbp_fo_finalize            (FoFo      *fo);
void fo_cbpbp_fo_update_from_context (FoFo      *fo,
				      FoContext *context);

G_END_DECLS

#endif /* !__FO_CBPBP_FO_PRIVATE_H__ */
