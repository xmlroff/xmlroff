/* Fo
 * libfo-compat.h: LibFo compatibility processing
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting
 *
 * !See COPYING for the status of this software.
 */

#ifndef __LIBFO_COMPAT_H__
#define __LIBFO_COMPAT_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-xml-doc.h>

G_BEGIN_DECLS

#define LIBFO_COMPAT_ERROR libfo_compat_error_quark ()
GQuark libfo_compat_error_quark (void);

typedef enum
{
  LIBFO_COMPAT_ERROR_FAILED
} LibfoCompatError;

const gchar* libfo_compat_get_stylesheet  (void);
FoXmlDoc *   libfo_compat_make_compatible (FoXmlDoc       *result_tree,
					   FoLibfoContext *libfo_context,
					   GError        **error);

G_END_DECLS

#endif /* !__LIBFO_COMPAT_H__ */
