/* Fo
 * fo-pixbuf.h: Interface for getting GdkPixbuf contained by an object.
 *
 * Copyright (C) 2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PIXBUF_H__
#define __FO_PIXBUF_H__

#include <libfo/fo-utils.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <libfo/util/fo-image.h>

G_BEGIN_DECLS

#define FO_TYPE_PIXBUF            (fo_pixbuf_get_type ())
#define FO_PIXBUF(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_PIXBUF, FoPixbuf))
#define FO_PIXBUF_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_PIXBUF, FoPixbufIface))
#define FO_IS_PIXBUF(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_PIXBUF))
#define FO_PIXBUF_GET_IFACE(obj)  ((FoPixbufIface *)g_type_interface_peek (((GTypeInstance *) FO_PIXBUF (obj))->g_class, FO_TYPE_PIXBUF))

typedef struct _FoPixbuf      FoPixbuf; /* Dummy typedef */
typedef struct _FoPixbufIface FoPixbufIface;

struct _FoPixbufIface
{
  GTypeInterface g_iface;

  GdkPixbuf * (*get_pixbuf) (FoImage   *fo_image);
  void        (*set_pixbuf) (FoImage   *fo_image,
			     GdkPixbuf *pixbuf);
};


GType fo_pixbuf_get_type      (void) G_GNUC_CONST;

GdkPixbuf * fo_pixbuf_get_pixbuf (FoImage   *fo_image);
void        fo_pixbuf_set_pixbuf (FoImage   *fo_image,
				  GdkPixbuf *pixbuf);
G_END_DECLS

#endif /* !__FO_PIXBUF_H__ */
