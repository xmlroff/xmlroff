/* Fo
 * fo-libfo-context.h: 'FoLibfoContext' object type
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LIBFO_CONTEXT_H__
#define __FO_LIBFO_CONTEXT_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

/**
 * FoFlagsFormat:
 * @FO_FLAG_FORMAT_UNKNOWN:    Invalid format
 * @FO_FLAG_FORMAT_AUTO:       Choose based on output file name or other heuristic
 * @FO_FLAG_FORMAT_PDF:        PDF
 * @FO_FLAG_FORMAT_POSTSCRIPT: PostScript
 * @FO_FLAG_FORMAT_SVG:        SVG
 *
 * Output file format.  Used both for specifying which format to use
 * and to identify formats supported by a particular backend.
 */
typedef enum {
  FO_FLAG_FORMAT_UNKNOWN = 0,
  FO_FLAG_FORMAT_AUTO = 1 << 0,
  FO_FLAG_FORMAT_PDF = 1 << 1,
  FO_FLAG_FORMAT_POSTSCRIPT = 1 << 2,
  FO_FLAG_FORMAT_SVG = 1 << 3
} FoFlagsFormat;

GType fo_flags_format_get_type (void);
#define FO_TYPE_FLAGS_FORMAT fo_flags_format_get_type ()

/**
 * FoEnumFontEmbed:
 * @FO_ENUM_FONT_EMBED_INVALID: Invalid category
 * @FO_ENUM_FONT_EMBED_ALL:     Embed all fonts
 * @FO_ENUM_FONT_EMBED_NONBASE: Embed all fonts except the PostScript base fonts
 * @FO_ENUM_FONT_EMBED_NONE:    Do not embed any fonts
 *
 * Which categories of fonts to embed in the output file, useful only
 * where the output format and the backend both support control of
 * embedding or not embedding those fonts.
 */
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


typedef struct _FoLibfoContext FoLibfoContext;
typedef struct _FoLibfoContextClass FoLibfoContextClass;

GType            fo_libfo_context_get_type (void) G_GNUC_CONST;
FoLibfoContext * fo_libfo_context_new (void);

FoFlagsFormat   fo_libfo_context_get_format               (FoLibfoContext *libfo_context);
void            fo_libfo_context_set_format               (FoLibfoContext *libfo_context,
							   FoFlagsFormat   format);
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
