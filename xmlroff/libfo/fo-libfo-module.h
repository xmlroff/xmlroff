/* Fo
 * fo-libfo-module.h: Formatting object that is module of possible fo:libfo
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LIBFO_MODULE_H__
#define __FO_LIBFO_MODULE_H__

#include <libfo/fo-utils.h>
#include <libfo/libfo-version.h>

G_BEGIN_DECLS

typedef struct _FoLibfoModule      FoLibfoModule;
typedef struct _FoLibfoModuleClass FoLibfoModuleClass;

#define FO_TYPE_LIBFO_MODULE              (fo_libfo_module_get_type ())
#define FO_LIBFO_MODULE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LIBFO_MODULE, FoLibfoModule))
#define FO_LIBFO_MODULE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LIBFO_MODULE, FoLibfoModuleClass))
#define FO_IS_LIBFO_MODULE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LIBFO_MODULE))
#define FO_IS_LIBFO_MODULE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LIBFO_MODULE))
#define FO_LIBFO_MODULE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LIBFO_MODULE, FoLibfoModuleClass))


GType  fo_libfo_module_get_type  (void) G_GNUC_CONST;

gint          fo_libfo_module_version_from_name (const gchar *name);
const gchar*  fo_libfo_module_version_string_from_name (const gchar *name);
const LibfoVersionInfo * fo_libfo_module_version_info_from_name (const gchar *name);

G_END_DECLS

#endif /* !__FO_LIBFO_MODULE_H__ */
