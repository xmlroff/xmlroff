/* Fo
 * fo-text.h: Unofficial text formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TEXT_H__
#define __FO_TEXT_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoText      FoText;
typedef struct _FoTextClass FoTextClass;

#define FO_TYPE_TEXT              (fo_text_get_type ())
#define FO_TEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TEXT, FoText))
#define FO_TEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TEXT, FoTextClass))
#define FO_IS_TEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TEXT))
#define FO_IS_TEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TEXT))
#define FO_TEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TEXT, FoTextClass))


GType        fo_text_get_type      (void) G_GNUC_CONST;
FoFo       * fo_text_new (void);

FoProperty * fo_text_get_color        (FoFo        *fo_fo);
void         fo_text_set_color        (FoFo        *fo_fo,
				       FoProperty  *new_color);
FoProperty * fo_text_get_font_family  (FoFo        *fo_fo);
void         fo_text_set_font_family  (FoFo        *fo_fo,
				       FoProperty  *new_font_family);
FoProperty * fo_text_get_font_size    (FoFo        *fo_fo);
void         fo_text_set_font_size    (FoFo        *fo_fo,
				       FoProperty  *new_font_size);
FoProperty * fo_text_get_font_stretch (FoFo        *fo_fo);
void         fo_text_set_font_stretch (FoFo        *fo_fo,
				       FoProperty  *new_font_stretch);
FoProperty * fo_text_get_font_style   (FoFo        *fo_fo);
void         fo_text_set_font_style   (FoFo        *fo_fo,
				       FoProperty  *new_font_style);
FoProperty * fo_text_get_font_variant (FoFo        *fo_fo);
void         fo_text_set_font_variant (FoFo        *fo_fo,
				       FoProperty  *new_font_variant);
FoProperty * fo_text_get_font_weight  (FoFo        *fo_fo);
void         fo_text_set_font_weight  (FoFo        *fo_fo,
				       FoProperty  *new_font_weight);
FoProperty * fo_text_get_score_spaces (FoFo        *fo_fo);
void         fo_text_set_score_spaces (FoFo        *fo_fo,
				       FoProperty  *new_score_spaces);
const gchar* fo_text_get_value        (FoFo        *fo_fo);
void         fo_text_set_value        (FoFo        *fo_fo,
				       const gchar *new_value);
gboolean fo_text_get_whitespace_only (FoFo *fo_fo);


G_END_DECLS

#endif /* !__FO_TEXT_H__ */
