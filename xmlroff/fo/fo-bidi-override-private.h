/* Fo
 * fo-bidi-override-private.h: Structures private to Bidi Override formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-bidi-override-private.h,v 1.2 2003/03/07 17:54:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_BIDI_OVERRIDE_PRIVATE_H__
#define __FO_BIDI_OVERRIDE_PRIVATE_H__

#include "fo/fo-fo.h"
#include "fo/fo-marker-parent-private.h"
#include "fo-bidi-override.h"

struct _FoBidiOverride
{
  FoMarkerParent parent_instance;

  FoProperty *color;
  FoProperty *direction;
  FoProperty *font_family;
  FoProperty *font_size;
  FoProperty *font_stretch;
  FoProperty *font_style;
  FoProperty *font_variant;
  FoProperty *font_weight;
  FoProperty *id;
  FoProperty *line_height;
  FoProperty *score_spaces;
  FoProperty *unicode_bidi;
};

struct _FoBidiOverrideClass
{
  FoMarkerParentClass parent_class;
};

#endif /* !__FO_BIDI_OVERRIDE_PRIVATE_H__ */
