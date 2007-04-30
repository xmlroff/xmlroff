/* Fo
 * fo-layout-private.h: Object type for PangoLayout
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-layout-private.h,v 1.4 2006/03/08 00:21:52 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LAYOUT_PRIVATE_H__
#define __FO_LAYOUT_PRIVATE_H__

#include "fo-layout.h"
#include <pango/pango.h>

G_BEGIN_DECLS

struct _FoLayout
{
  FoObject     parent_instance;

  FoDoc       *fo_doc;

  PangoLayout *pango_layout;
};

struct _FoLayoutClass
{
  FoObjectClass parent_class;

  void (* set_line_height) (FoLayout *fo_layout,
			    gfloat    line_height);

  void (* set_line_stacking_strategy) (FoLayout  *fo_layout,
				       FoEnumEnum line_stacking_strategy);

};

PangoLayout * fo_layout_get_pango_layout (FoLayout *fo_layout);
/*
PangoLineStackingStrategy fo_layout_line_stacking_strategy_to_pango_line_stacking_strategy (FoEnumEnum line_stacking_strategy);
*/
G_END_DECLS

#endif /* !__FO_LAYOUT_PRIVATE_H__ */
