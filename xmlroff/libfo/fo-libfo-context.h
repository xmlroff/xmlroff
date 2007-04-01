/* Fo
 * fo-libfo-context.h: 'FoLibfoContext' object type
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-libfo-context.h,v 1.14 2006/04/16 20:35:13 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LIBFO_CONTEXT_H__
#define __FO_LIBFO_CONTEXT_H__

#include <libfo/fo-utils.h>
#include "libfo/fo-libfo-basic.h"

G_BEGIN_DECLS

typedef enum
{
  FO_ENUM_FORMAT_UNKNOWN,
  FO_ENUM_FORMAT_AUTO,
  FO_ENUM_FORMAT_PDF,
  FO_ENUM_FORMAT_POSTSCRIPT,
  FO_ENUM_FORMAT_SVG
} FoEnumFormat;

GType fo_enum_format_get_type (void);
#define FO_TYPE_ENUM_FORMAT fo_enum_format_get_type ()

typedef enum {
  FO_ENUM_FONT_EMBED_INVALID,
  FO_ENUM_FONT_EMBED_ALL,
  FO_ENUM_FONT_EMBED_NONBASE,
  FO_ENUM_FONT_EMBED_NONE
} FoEnumFontEmbed;

GType fo_enum_font_embed_get_type (void);
#define FO_TYPE_ENUM_FONT_EMBED fo_enum_font_embed_get_type ()

#define FO_TYPE_LIBFO_CONTEXT              (fo_libfo_context_get_type ())
#define FO_LIBFO_CONTEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LIBFO_CONTEXT, FoLibfoContext))
#define FO_LIBFO_CONTEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LIBFO_CONTEXT, FoLibfoContextClass))
#define FO_IS_LIBFO_CONTEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LIBFO_CONTEXT))
#define FO_IS_LIBFO_CONTEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LIBFO_CONTEXT))
#define FO_LIBFO_CONTEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LIBFO_CONTEXT, FoLibfoContextClass))


/* typedef struct _FoLibfoContext      FoLibfoContext; */
typedef struct _FoLibfoContextClass FoLibfoContextClass;

GType            fo_libfo_context_get_type (void) G_GNUC_CONST;
/* fo_libfo_context_new() prototype is in fo-libfo-basic.h */
/* FoLibfoContext * fo_libfo_context_new      (void); */

FoEnumFormat    fo_libfo_context_get_format               (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_format               (FoLibfoContext *libfo_context,
							   FoEnumFormat    format);
FoEnumFontEmbed fo_libfo_context_get_font_embed           (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_font_embed           (FoLibfoContext *libfo_context,
							   FoEnumFontEmbed font_embed);
gboolean        fo_libfo_context_get_validation           (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_validation           (FoLibfoContext *libfo_context,
							   gboolean        validation);
gboolean        fo_libfo_context_get_continue_after_error (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_continue_after_error (FoLibfoContext *libfo_context,
							   gboolean        continue_after_error);
FoDebugFlag     fo_libfo_context_get_debug_mode           (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_debug_mode           (FoLibfoContext *libfo_context,
							   FoDebugFlag     debug_mode);
FoWarningFlag   fo_libfo_context_get_warning_mode         (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_warning_mode         (FoLibfoContext *libfo_context,
							   FoWarningFlag   warning_mode);

G_END_DECLS

#endif /* !__FO_LIBFO_CONTEXT_H__ */
