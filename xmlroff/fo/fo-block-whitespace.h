/* Fo
 * fo-block-whitespace.h: Whitespace-only block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-whitespace.h,v 1.2 2003/03/19 21:10:42 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_BLOCK_WHITESPACE_H__
#define __FO_BLOCK_WHITESPACE_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoBlockWhitespace      FoBlockWhitespace;
typedef struct _FoBlockWhitespaceClass FoBlockWhitespaceClass;

#define FO_TYPE_BLOCK_WHITESPACE              (fo_block_whitespace_get_type ())
#define FO_BLOCK_WHITESPACE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BLOCK_WHITESPACE, FoBlockWhitespace))
#define FO_BLOCK_WHITESPACE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BLOCK_WHITESPACE, FoBlockWhitespaceClass))
#define FO_IS_BLOCK_WHITESPACE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BLOCK_WHITESPACE))
#define FO_IS_BLOCK_WHITESPACE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BLOCK_WHITESPACE))
#define FO_BLOCK_WHITESPACE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BLOCK_WHITESPACE, FoBlockWhitespaceClass))


GType         fo_block_whitespace_get_type      (void) G_GNUC_CONST;
FoFo *fo_block_whitespace_new (void);

void fo_block_whitespace_update_from_context (FoFo *fo,
				   FoContext *context);

G_END_DECLS

#endif /* !__FO_BLOCK_WHITESPACE_H__ */
