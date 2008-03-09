/* Fo
 * fo-area-layout-private.h: Private information for layout area objects
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_AREA_LAYOUT_PRIVATE_H__
#define __FO_AREA_LAYOUT_PRIVATE_H__

#include <pango/pango.h>
#include <libfo/area/fo-area-area-private.h>

G_BEGIN_DECLS

struct _FoAreaLayout
{
  FoAreaArea parent_instance;

  FoLayout      *layout;
  gchar         *text;
  PangoAttrList *attr_list;
  guint          line_first;
  guint          line_last;
  FoAreaLayout  *prev_portion;
  FoAreaLayout  *next_portion;
  GSList        *line_heights;
};

struct _FoAreaLayoutClass
{
  FoAreaAreaClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_LAYOUT_PRIVATE_H__ */
