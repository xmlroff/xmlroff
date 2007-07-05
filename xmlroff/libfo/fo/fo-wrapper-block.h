/* Fo
 * fo-wrapper-block.h: Block-level wrapper formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_BLOCK_H__
#define __FO_WRAPPER_BLOCK_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoWrapperBlock      FoWrapperBlock;
typedef struct _FoWrapperBlockClass FoWrapperBlockClass;

#define FO_TYPE_WRAPPER_BLOCK              (fo_wrapper_block_get_type ())
#define FO_WRAPPER_BLOCK(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_WRAPPER_BLOCK, FoWrapperBlock))
#define FO_WRAPPER_BLOCK_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_WRAPPER_BLOCK, FoWrapperBlockClass))
#define FO_IS_WRAPPER_BLOCK(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_WRAPPER_BLOCK))
#define FO_IS_WRAPPER_BLOCK_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_WRAPPER_BLOCK))
#define FO_WRAPPER_BLOCK_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_WRAPPER_BLOCK, FoWrapperBlockClass))


GType         fo_wrapper_block_get_type      (void) G_GNUC_CONST;
FoFo *fo_wrapper_block_new (void);

void fo_wrapper_block_update_from_context (FoFo *fo,
				   FoContext *context);

G_END_DECLS

#endif /* !__FO_WRAPPER_BLOCK_H__ */
