/* Fo
 * fo-block-fo.h: Block formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-fo.h,v 1.3 2004/03/30 22:45:40 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_BLOCK_FO_H__
#define __FO_BLOCK_FO_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>

G_BEGIN_DECLS

#define FO_TYPE_BLOCK_FO            (fo_block_fo_get_type ())
#define FO_BLOCK_FO(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_BLOCK_FO, FoBlockFo))
#define FO_BLOCK_FO_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_BLOCK_FO, FoBlockFoIface))
#define FO_IS_BLOCK_FO(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_BLOCK_FO))
#define FO_BLOCK_FO_GET_IFACE(obj)  ((FoBlockFoIface *)g_type_interface_peek (((GTypeInstance *) FO_BLOCK_FO (obj))->g_class, FO_TYPE_BLOCK_FO))

typedef struct _FoBlockFo      FoBlockFo; /* Dummy typedef */
typedef struct _FoBlockFoIface FoBlockFoIface;

GType fo_block_fo_get_type      (void) G_GNUC_CONST;

void fo_block_fo_update_area (FoFo *fo,
			      FoArea *area);

FoProperty * fo_block_fo_get_background_color    (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_after_color  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_after_style  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_after_width  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_before_color (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_before_style (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_before_width (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_end_color    (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_end_style    (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_end_width    (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_start_color  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_start_style  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_border_start_width  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_keep_together       (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_keep_with_next      (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_keep_with_previous  (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_padding_after       (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_padding_before      (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_padding_end         (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_padding_start       (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_space_before        (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_space_after         (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_start_indent        (FoFo *fo_block_fo);
FoProperty * fo_block_fo_get_end_indent          (FoFo *fo_block_fo);

G_END_DECLS

#endif /* !__FO_BLOCK_FO_H__ */
