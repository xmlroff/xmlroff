/* Fo
 * fo-bidi_override.h: Bidi Override formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BIDI_OVERRIDE_H__
#define __FO_BIDI_OVERRIDE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoBidiOverride      FoBidiOverride;
typedef struct _FoBidiOverrideClass FoBidiOverrideClass;

#define FO_TYPE_BIDI_OVERRIDE              (fo_bidi_override_get_type ())
#define FO_BIDI_OVERRIDE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BIDI_OVERRIDE, FoBidiOverride))
#define FO_BIDI_OVERRIDE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BIDI_OVERRIDE, FoBidiOverrideClass))
#define FO_IS_BIDI_OVERRIDE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BIDI_OVERRIDE))
#define FO_IS_BIDI_OVERRIDE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BIDI_OVERRIDE))
#define FO_BIDI_OVERRIDE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BIDI_OVERRIDE, FoBidiOverrideClass))


GType         fo_bidi_override_get_type      (void) G_GNUC_CONST;
FoFo *fo_bidi_override_new (void);

void fo_bidi_override_set_color (FoFo *fo_fo,
                                 FoProperty *new_color);
FoProperty *fo_bidi_override_get_color (FoFo *fo_fo);
void fo_bidi_override_set_direction (FoFo *fo_fo,
                                     FoProperty *new_direction);
FoProperty *fo_bidi_override_get_direction (FoFo *fo_fo);
void fo_bidi_override_set_font_family (FoFo *fo_fo,
                                       FoProperty *new_font_family);
FoProperty *fo_bidi_override_get_font_family (FoFo *fo_fo);
void fo_bidi_override_set_font_size (FoFo *fo_fo,
                                     FoProperty *new_font_size);
FoProperty *fo_bidi_override_get_font_size (FoFo *fo_fo);
void fo_bidi_override_set_font_stretch (FoFo *fo_fo,
                                        FoProperty *new_font_stretch);
FoProperty *fo_bidi_override_get_font_stretch (FoFo *fo_fo);
void fo_bidi_override_set_font_style (FoFo *fo_fo,
                                      FoProperty *new_font_style);
FoProperty *fo_bidi_override_get_font_style (FoFo *fo_fo);
void fo_bidi_override_set_font_variant (FoFo *fo_fo,
                                        FoProperty *new_font_variant);
FoProperty *fo_bidi_override_get_font_variant (FoFo *fo_fo);
void fo_bidi_override_set_font_weight (FoFo *fo_fo,
                                       FoProperty *new_font_weight);
FoProperty *fo_bidi_override_get_font_weight (FoFo *fo_fo);
void fo_bidi_override_set_id (FoFo *fo_fo,
                              FoProperty *new_id);
FoProperty *fo_bidi_override_get_id (FoFo *fo_fo);
void fo_bidi_override_set_line_height (FoFo *fo_fo,
                                       FoProperty *new_line_height);
FoProperty *fo_bidi_override_get_line_height (FoFo *fo_fo);
void fo_bidi_override_set_score_spaces (FoFo *fo_fo,
                                        FoProperty *new_score_spaces);
FoProperty *fo_bidi_override_get_score_spaces (FoFo *fo_fo);
void fo_bidi_override_set_unicode_bidi (FoFo *fo_fo,
                                        FoProperty *new_unicode_bidi);
FoProperty *fo_bidi_override_get_unicode_bidi (FoFo *fo_fo);

G_END_DECLS

#endif /* !__FO_BIDI_OVERRIDE_H__ */
