/* Fo
 * fo-area-area-private.h: Structures private to FoAreaArea object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_AREA_PRIVATE_H__
#define __FO_AREA_AREA_PRIVATE_H__

#include <libfo/area/fo-area-private.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

struct _FoAreaArea
{
  FoArea parent_instance;

  gdouble x;
  gdouble y;
  gdouble height;
  gdouble width;

  gdouble border_before;
  gdouble border_after;
  gdouble border_start;
  gdouble border_end;

  gdouble padding_before;
  gdouble padding_after;
  gdouble padding_start;
  gdouble padding_end;

  gdouble start_indent;
  gdouble end_indent;

  gdouble space_before;
  gdouble space_after;

};

struct _FoAreaAreaClass
{
  FoAreaClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_AREA_PRIVATE_H__ */
