/* Fo
 * fo-area-inline.h: Inline block-area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_INLINE_H__
#define __FO_AREA_INLINE_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoAreaInline      FoAreaInline;
typedef struct _FoAreaInlineClass FoAreaInlineClass;

#define FO_TYPE_AREA_INLINE              (fo_area_inline_get_type ())
#define FO_AREA_INLINE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_INLINE, FoAreaInline))
#define FO_AREA_INLINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_INLINE, FoAreaInlineClass))
#define FO_IS_AREA_INLINE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_INLINE))
#define FO_IS_AREA_INLINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_INLINE))
#define FO_AREA_INLINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_INLINE, FoAreaInlineClass))


GType    fo_area_inline_get_type (void) G_GNUC_CONST;
FoArea * fo_area_inline_new      (void);

G_END_DECLS

#endif /* !__FO_AREA_INLINE_H__ */
