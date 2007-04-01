/* Fo
 * fo-wrapper-whitespace.h: Whitespace-only wrapper formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-wrapper-whitespace.h,v 1.2 2003/03/19 21:12:33 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_WRAPPER_WHITESPACE_H__
#define __FO_WRAPPER_WHITESPACE_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoWrapperWhitespace      FoWrapperWhitespace;
typedef struct _FoWrapperWhitespaceClass FoWrapperWhitespaceClass;

#define FO_TYPE_WRAPPER_WHITESPACE              (fo_wrapper_whitespace_get_type ())
#define FO_WRAPPER_WHITESPACE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_WRAPPER_WHITESPACE, FoWrapperWhitespace))
#define FO_WRAPPER_WHITESPACE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_WRAPPER_WHITESPACE, FoWrapperWhitespaceClass))
#define FO_IS_WRAPPER_WHITESPACE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_WRAPPER_WHITESPACE))
#define FO_IS_WRAPPER_WHITESPACE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_WRAPPER_WHITESPACE))
#define FO_WRAPPER_WHITESPACE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_WRAPPER_WHITESPACE, FoWrapperWhitespaceClass))


GType         fo_wrapper_whitespace_get_type      (void) G_GNUC_CONST;
FoFo *fo_wrapper_whitespace_new (void);

void fo_wrapper_whitespace_update_from_context (FoFo *fo,
				   FoContext *context);

G_END_DECLS

#endif /* !__FO_WRAPPER_WHITESPACE_H__ */
