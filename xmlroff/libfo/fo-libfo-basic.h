/* Fo
 * fo-libfo-basic.h: 'Basic' (i.e., simple) high-level interface to libfo
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 * Copyright (C) 2013 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LIBFO_BASIC_H__
#define __FO_LIBFO_BASIC_H__

#include <stdio.h>
#include <glib.h>

G_BEGIN_DECLS

typedef enum
{
  FO_LIBFO_BASIC_ERROR_FAILED,		/* Generic error code */
  FO_LIBFO_BASIC_ERROR_UNKNOWN_FORMAT,
  FO_LIBFO_BASIC_ERROR_WARNING,	/* Non-fatal error */
  FO_LIBFO_BASIC_ERROR_LAST
} FoLibfoBasicError;

#define FO_LIBFO_BASIC_ERROR (fo_libfo_basic_error_quark ())
GQuark fo_libfo_basic_error_quark (void) G_GNUC_CONST;

extern const gchar *fo_libfo_basic_error_messages[FO_LIBFO_BASIC_ERROR_LAST];

gboolean         fo_libfo_init (void);

typedef  gpointer (*FoMalloc)      (gsize    n_bytes);
typedef  gpointer (*FoRealloc)     (gpointer mem,
				    gsize    n_bytes);
typedef  void     (*FoFree)        (gpointer mem);

gboolean         fo_libfo_init2 (FoMalloc  fo_malloc,
				 FoRealloc fo_realloc,
				 FoFree    fo_free);

gboolean         fo_libfo_shutdown (void);

gboolean         fo_libfo_format (const gchar    *xml,
				  const gchar    *xslt,
				  const gchar    *out,
				  GError        **error);

G_END_DECLS

#endif /* __FO_LIBFO_BASIC_H__ */
