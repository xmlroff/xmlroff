/* Fo
 * fo-layout.h: Object type for PangoLayout
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-layout-gp.h,v 1.1 2003/05/23 15:29:28 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LAYOUT_GP_H__
#define __FO_LAYOUT_GP_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-font-desc.h>
#include <libfo/fo-layout.h>

typedef struct _FoLayoutGP      FoLayoutGP;
typedef struct _FoLayoutGPClass FoLayoutGPClass;

#include <libfo/fo-doc.h>

G_BEGIN_DECLS

#define FO_TYPE_LAYOUT_GP              (fo_layout_gp_get_type ())
#define FO_LAYOUT_GP(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LAYOUT_GP, FoLayoutGP))
#define FO_LAYOUT_GP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LAYOUT_GP, FoLayoutGPClass))
#define FO_IS_LAYOUT_GP(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LAYOUT_GP))
#define FO_IS_LAYOUT_GP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LAYOUT_GP))
#define FO_LAYOUT_GP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LAYOUT, FoLayoutGPClass))

GType      fo_layout_gp_get_type  (void);
FoLayout * fo_layout_gp_new       (void);
FoLayout * fo_layout_gp_new_from_fo_doc      (FoDoc   *fo_doc);

G_END_DECLS


#endif /* !__FO_LAYOUT_H__ */
