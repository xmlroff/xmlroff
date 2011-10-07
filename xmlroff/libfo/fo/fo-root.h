/* Fo
 * fo-root.h: 'root' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ROOT_H__
#define __FO_ROOT_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRoot:
 *
 * Instance of the 'root' formatting object.
 **/
typedef struct _FoRoot      FoRoot;

/**
 * FoRootClass:
 *
 * Class structure for the 'root' formatting object.
 **/
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
