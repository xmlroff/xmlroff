/*
 * Fo
 * fo-root.h: 'root' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-root.h,v 1.4 2003/05/16 13:45:14 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_ROOT_H__
#define __FO_ROOT_H__

#include <libfo/fo-utils.h>
#include <fo-fo.h>
#include <fo-property.h>

G_BEGIN_DECLS

typedef struct _FoRoot      FoRoot;
typedef struct _FoRootClass FoRootClass;

#define FO_TYPE_ROOT              (fo_root_get_type ())
#define FO_ROOT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_ROOT, FoRoot))
#define FO_ROOT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_ROOT, FoRootClass))
#define FO_IS_ROOT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_ROOT))
#define FO_IS_ROOT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_ROOT))
#define FO_ROOT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_ROOT, FoRootClass))


GType        fo_root_get_type (void) G_GNUC_CONST;
FoFo *       fo_root_new      (void);

FoProperty * fo_root_get_media_usage (FoFo       *fo_fo);
void         fo_root_set_media_usage (FoFo       *fo_fo,
                                      FoProperty *new_media_usage);

G_END_DECLS

#endif /* !__FO_ROOT_H__ */
