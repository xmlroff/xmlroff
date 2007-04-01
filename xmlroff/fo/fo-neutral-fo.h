/* Fo
 * fo-neutral-fo.h: Neutral formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-neutral-fo.h,v 1.2 2003/03/19 21:11:51 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_NEUTRAL_FO_H__
#define __FO_NEUTRAL_FO_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_NEUTRAL_FO            (fo_neutral_fo_get_type ())
#define FO_NEUTRAL_FO(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_NEUTRAL_FO, FoNeutralFo))
#define FO_NEUTRAL_FO_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_NEUTRAL_FO, FoNeutralFoIface))
#define FO_IS_NEUTRAL_FO(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_NEUTRAL_FO))
#define FO_NEUTRAL_FO_GET_IFACE(obj)  ((FoNeutralFoIface *)g_type_interface_peek (((GTypeInstance *) FO_NEUTRAL_FO (obj))->g_class, FO_TYPE_NEUTRAL_FO))

typedef struct _FoNeutralFo      FoNeutralFo; /* Dummy typedef */
typedef struct _FoNeutralFoIface FoNeutralFoIface;

struct _FoNeutralFoIface
{
  GTypeInterface g_iface;
};


GType fo_neutral_fo_get_type      (void) G_GNUC_CONST;

G_END_DECLS

#endif /* !__FO_NEUTRAL_FO_H__ */
