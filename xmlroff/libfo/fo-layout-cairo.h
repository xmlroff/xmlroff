/* Fo
 * fo-layout.h: Object type for PangoLayout
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-layout-cairo.h,v 1.1 2006/03/07 23:35:29 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LAYOUT_CAIRO_H__
#define __FO_LAYOUT_CAIRO_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-font-desc.h>
#include <libfo/fo-layout.h>

typedef struct _FoLayoutCairo      FoLayoutCairo;
typedef struct _FoLayoutCairoClass FoLayoutCairoClass;

#include <libfo/fo-doc.h>

G_BEGIN_DECLS

#define FO_TYPE_LAYOUT_CAIRO              (fo_layout_cairo_get_type ())
#define FO_LAYOUT_CAIRO(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LAYOUT_CAIRO, FoLayoutCairo))
#define FO_LAYOUT_CAIRO_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LAYOUT_CAIRO, FoLayoutCairoClass))
#define FO_IS_LAYOUT_CAIRO(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LAYOUT_CAIRO))
#define FO_IS_LAYOUT_CAIRO_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LAYOUT_CAIRO))
#define FO_LAYOUT_CAIRO_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LAYOUT, FoLayoutCairoClass))

GType      fo_layout_cairo_get_type  (void);
FoLayout * fo_layout_cairo_new       (void);
FoLayout * fo_layout_cairo_new_from_fo_doc      (FoDoc   *fo_doc);

G_END_DECLS


#endif /* !__FO_LAYOUT_H__ */
