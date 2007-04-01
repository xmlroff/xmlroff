/* Fo
 * fo-wrapper-inline.h: Inline-level wrapper formatting object.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-wrapper-inline.h,v 1.3 2006/03/21 23:21:38 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_INLINE_H__
#define __FO_WRAPPER_INLINE_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoWrapperInline      FoWrapperInline;
typedef struct _FoWrapperInlineClass FoWrapperInlineClass;

#define FO_TYPE_WRAPPER_INLINE              (fo_wrapper_inline_get_type ())
#define FO_WRAPPER_INLINE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_WRAPPER_INLINE, FoWrapperInline))
#define FO_WRAPPER_INLINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_WRAPPER_INLINE, FoWrapperInlineClass))
#define FO_IS_WRAPPER_INLINE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_WRAPPER_INLINE))
#define FO_IS_WRAPPER_INLINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_WRAPPER_INLINE))
#define FO_WRAPPER_INLINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_WRAPPER_INLINE, FoWrapperInlineClass))


GType  fo_wrapper_inline_get_type (void) G_GNUC_CONST;
FoFo * fo_wrapper_inline_new      (void);

G_END_DECLS

#endif /* !__FO_WRAPPER_INLINE_H__ */
