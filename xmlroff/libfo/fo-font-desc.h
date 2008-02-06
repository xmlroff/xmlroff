/* Fo
 * fo-font-desc.c: Boxed object type for Pango font description.
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FONT_DESC_H__
#define __FO_FONT_DESC_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-enum.h>

typedef struct _FoFontDesc      FoFontDesc;
typedef struct _FoFontDescClass FoFontDescClass;

#include <libfo/fo-doc.h>

G_BEGIN_DECLS

#define FO_FONT_DESC_ERROR fo_font_desc_error_quark ()
GQuark fo_font_desc_error_quark (void);

typedef enum
{
  FO_FONT_DESC_ERROR_FAILED
} FoFontDescError;

#define FO_TYPE_FONT_DESC              (fo_font_desc_get_type ())
#define FO_FONT_DESC(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FONT_DESC, FoFontDesc))
#define FO_FONT_DESC_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FONT_DESC, FoFontDescClass))
#define FO_IS_FONT_DESC(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FONT_DESC))
#define FO_IS_FONT_DESC_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FONT_DESC))
#define FO_FONT_DESC_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FONT_DESC, FoFontDescClass))

GType        fo_font_desc_get_type  (void);
FoFontDesc * fo_font_desc_new       (void);

FoFontDesc * fo_font_desc_copy (const FoFontDesc *font_desc);

void         fo_font_desc_set_family  (FoFontDesc        *font_desc,
				       const char        *family);
void         fo_font_desc_set_size    (FoFontDesc        *font_desc,
				       gfloat             size);
void         fo_font_desc_set_style   (FoFontDesc        *font_desc,
				       FoEnumFontStyle    style);
void         fo_font_desc_set_stretch (FoFontDesc        *font_desc,
				       FoEnumFontStretch  stretch);
void         fo_font_desc_set_variant (FoFontDesc        *font_desc,
				       FoEnumEnum         variant);
void         fo_font_desc_set_weight  (FoFontDesc        *font_desc,
				       gint               weight);


G_END_DECLS

#endif /* !__FO_FONT_DESC_H__ */
