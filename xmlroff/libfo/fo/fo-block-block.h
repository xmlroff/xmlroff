/* Fo
 * fo-block-block.h: Block-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BLOCK_BLOCK_H__
#define __FO_BLOCK_BLOCK_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoBlockBlock      FoBlockBlock;
typedef struct _FoBlockBlockClass FoBlockBlockClass;

#define FO_TYPE_BLOCK_BLOCK              (fo_block_block_get_type ())
#define FO_BLOCK_BLOCK(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BLOCK_BLOCK, FoBlockBlock))
#define FO_BLOCK_BLOCK_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BLOCK_BLOCK, FoBlockBlockClass))
#define FO_IS_BLOCK_BLOCK(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BLOCK_BLOCK))
#define FO_IS_BLOCK_BLOCK_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BLOCK_BLOCK))
#define FO_BLOCK_BLOCK_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BLOCK_BLOCK, FoBlockBlockClass))


GType         fo_block_block_get_type      (void) G_GNUC_CONST;
FoFo *fo_block_block_new (void);

G_END_DECLS

#endif /* !__FO_BLOCK_BLOCK_H__ */
