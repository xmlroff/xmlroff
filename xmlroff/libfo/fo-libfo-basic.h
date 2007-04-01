/* Fo
 * fo-libfo-basic.h: 'Basic' (i.e., simple) high-level interface to libfo
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-libfo-basic.h,v 1.3 2003/05/16 11:00:15 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LIBFO_BASIC_H__
#define __FO_LIBFO_BASIC_H__

#include <stdio.h>
#include <glib/gtypes.h>
#include <glib/gerror.h>

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

typedef enum {
    FO_ENUM_TYPE_CHAR,
    FO_ENUM_TYPE_INT,
    FO_ENUM_TYPE_FILE
} FoEnumType;

typedef struct _FoValue {
  FoEnumType	type;
  union {
    const gchar	*s;
    gint         i;
    const FILE  *fp;
  } u;
} FoValue;

typedef struct _FoLibfoContext FoLibfoContext;

gboolean         fo_libfo_init (void);

typedef  gpointer (*FoMalloc)      (gsize    n_bytes);
typedef  gpointer (*FoRealloc)     (gpointer mem,
				    gsize    n_bytes);
typedef  void     (*FoFree)        (gpointer mem);

gboolean         fo_libfo_init2 (FoMalloc  fo_malloc,
				 FoRealloc fo_realloc,
				 FoFree    fo_free);

gboolean         fo_libfo_shutdown (void);

FoLibfoContext * fo_libfo_context_new (void);

void             fo_libfo_context_close (FoLibfoContext *libfo_context);

gboolean         fo_libfo_format (FoLibfoContext *libfo_context,
				  const gchar    *xml,
				  const gchar    *xslt,
				  const gchar    *out,
				  GError        **error);

G_END_DECLS

#endif /* __FO_LIBFO_BASIC_H__ */
