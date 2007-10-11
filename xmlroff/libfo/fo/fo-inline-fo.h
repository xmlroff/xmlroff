/* Fo
 * fo-inline-fo.h: Inline formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_INLINE_FO_H__
#define __FO_INLINE_FO_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-doc.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

#define FO_TYPE_INLINE_FO            (fo_inline_fo_get_type ())
#define FO_INLINE_FO(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_INLINE_FO, FoInlineFo))
#define FO_INLINE_FO_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_INLINE_FO, FoInlineFoIface))
#define FO_IS_INLINE_FO(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_INLINE_FO))
#define FO_INLINE_FO_GET_IFACE(obj)  ((FoInlineFoIface *)g_type_interface_peek (((GTypeInstance *) FO_INLINE_FO (obj))->g_class, FO_TYPE_INLINE_FO))

typedef struct _FoInlineFo      FoInlineFo; /* Dummy typedef */
typedef struct _FoInlineFoIface FoInlineFoIface;

struct _FoInlineFoIface
{
  GTypeInterface g_iface;

  void (*get_text_attr_list) (FoFo    *fo_inline_fo,
			      FoDoc   *fo_doc,
			      GString *text,
			      GList **attr_glist,
			      guint   debug_level);
};


GType fo_inline_fo_get_type      (void) G_GNUC_CONST;

void fo_inline_fo_get_text_attr_list (FoFo    *fo_inline_fo,
				      FoDoc   *fo_doc,
				      GString *text,
				      GList  **attr_glist,
				      guint    debug_level);
gboolean fo_inline_fo_is_white_space              (const gchar *string);
gboolean fo_inline_fo_is_non_linefeed_white_space (const gchar *string);
gboolean fo_inline_fo_is_linefeed                 (const gchar *string);

G_END_DECLS

#endif /* !__FO_INLINE_FO_H__ */
