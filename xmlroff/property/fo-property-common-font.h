/* Fo
 * fo-property-common-font.h: Common font property functions
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-common-font.h,v 1.2 2003/03/21 14:41:28 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_PROPERTY_COMMON_FONT_H__
#define __FO_PROPERTY_COMMON_FONT_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

GList* fo_property_common_font_get_pango_attrs (FoProperty *font_family,
						/* No font-selection-family */
						FoProperty *font_size,
						FoProperty *font_stretch,
						/* No font-size-adjust */
						FoProperty *font_style,
						FoProperty *font_variant,
						FoProperty *font_weight,
						gint        start_index,
						gint        end_index);

G_END_DECLS

#endif /* !__FO_PROPERTY_COMMON_FONT_H__ */
