/* Fo
 * fo-wrapper-inline-empty.h: Empty inline-level wrapper formatting object.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-wrapper-inline-empty.h,v 1.1 2006/03/21 23:29:29 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_INLINE_EMPTY_H__
#define __FO_WRAPPER_INLINE_EMPTY_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoWrapperInlineEmpty      FoWrapperInlineEmpty;
typedef struct _FoWrapperInlineEmptyClass FoWrapperInlineEmptyClass;

#define FO_TYPE_WRAPPER_INLINE_EMPTY              (fo_wrapper_inline_empty_get_type ())
#define FO_WRAPPER_INLINE_EMPTY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_WRAPPER_INLINE_EMPTY, FoWrapperInlineEmpty))
#define FO_WRAPPER_INLINE_EMPTY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_WRAPPER_INLINE_EMPTY, FoWrapperInlineEmptyClass))
#define FO_IS_WRAPPER_INLINE_EMPTY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_WRAPPER_INLINE_EMPTY))
#define FO_IS_WRAPPER_INLINE_EMPTY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_WRAPPER_INLINE_EMPTY))
#define FO_WRAPPER_INLINE_EMPTY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_WRAPPER_INLINE_EMPTY, FoWrapperInlineEmptyClass))


GType  fo_wrapper_inline_empty_get_type (void) G_GNUC_CONST;
FoFo * fo_wrapper_inline_empty_new      (void);

G_END_DECLS

#endif /* !__FO_WRAPPER_INLINE_EMPTY_H__ */
