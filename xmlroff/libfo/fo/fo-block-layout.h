/* Fo
 * fo-block-layout.h: Layout-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BLOCK_LAYOUT_H__
#define __FO_BLOCK_LAYOUT_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoBlockLayout      FoBlockLayout;
typedef struct _FoBlockLayoutClass FoBlockLayoutClass;

#define FO_TYPE_BLOCK_LAYOUT              (fo_block_layout_get_type ())
#define FO_BLOCK_LAYOUT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BLOCK_LAYOUT, FoBlockLayout))
#define FO_BLOCK_LAYOUT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BLOCK_LAYOUT, FoBlockLayoutClass))
#define FO_IS_BLOCK_LAYOUT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BLOCK_LAYOUT))
#define FO_IS_BLOCK_LAYOUT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BLOCK_LAYOUT))
#define FO_BLOCK_LAYOUT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BLOCK_LAYOUT, FoBlockLayoutClass))


GType         fo_block_layout_get_type      (void) G_GNUC_CONST;
FoFo *fo_block_layout_new (void);

void fo_block_layout_update_from_context (FoFo *fo,
				   FoContext *context);

G_END_DECLS

#endif /* !__FO_BLOCK_LAYOUT_H__ */
