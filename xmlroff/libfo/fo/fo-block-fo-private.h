/* Fo
 * fo-block-fo-private.h: Structures private to block formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BLOCK_FO_PRIVATE_H__
#define __FO_BLOCK_FO_PRIVATE_H__

#include <libfo/fo/fo-block-fo.h>

G_BEGIN_DECLS

struct _FoBlockFoIface
{
  GTypeInterface g_iface;

  FoProperty * (* get_background_color)    (FoFo *fo_block_fo);
  FoProperty * (* get_border_after_color)  (FoFo *fo_block_fo);
  FoProperty * (* get_border_after_style)  (FoFo *fo_block_fo);
  FoProperty * (* get_border_after_width)  (FoFo *fo_block_fo);
  FoProperty * (* get_border_before_color) (FoFo *fo_block_fo);
  FoProperty * (* get_border_before_style) (FoFo *fo_block_fo);
  FoProperty * (* get_border_before_width) (FoFo *fo_block_fo);
  FoProperty * (* get_border_end_color)    (FoFo *fo_block_fo);
  FoProperty * (* get_border_end_style)    (FoFo *fo_block_fo);
  FoProperty * (* get_border_end_width)    (FoFo *fo_block_fo);
  FoProperty * (* get_border_start_color)  (FoFo *fo_block_fo);
  FoProperty * (* get_border_start_style)  (FoFo *fo_block_fo);
  FoProperty * (* get_border_start_width)  (FoFo *fo_block_fo);
  FoProperty * (* get_keep_together)       (FoFo *fo_block_fo);
  FoProperty * (* get_keep_with_next)      (FoFo *fo_block_fo);
  FoProperty * (* get_keep_with_previous)  (FoFo *fo_block_fo);
  FoProperty * (* get_padding_after)       (FoFo *fo_block_fo);
  FoProperty * (* get_padding_before)      (FoFo *fo_block_fo);
  FoProperty * (* get_padding_end)         (FoFo *fo_block_fo);
  FoProperty * (* get_padding_start)       (FoFo *fo_block_fo);
  FoProperty * (* get_space_before)        (FoFo *fo_block_fo);
  FoProperty * (* get_space_after)         (FoFo *fo_block_fo);
  FoProperty * (* get_start_indent)        (FoFo *fo_block_fo);
  FoProperty * (* get_end_indent)          (FoFo *fo_block_fo);
};

G_END_DECLS

#endif /* !__FO_BLOCK_FO_PRIVATE_H__ */
