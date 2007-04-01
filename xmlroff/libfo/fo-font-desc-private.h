/* Fo
 * fo-font-desc-private.h: Boxed object type for FontDesc
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-font-desc-private.h,v 1.2 2004/03/30 22:38:26 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_FONT_DESC_PRIVATE_H__
#define __FO_FONT_DESC_PRIVATE_H__

#include <pango/pango.h>
#include <pango/pango-font.h>
#include "fo-font-desc.h"

G_BEGIN_DECLS

PangoFontDescription * fo_font_desc_get_font_description (const FoFontDesc *fo_font_desc);
void fo_font_desc_set_font_description (FoFontDesc *fo_font_desc,
					const PangoFontDescription *desc);

#endif /* !__FO_FONT_DESC_PRIVATE_H__ */
