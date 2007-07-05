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

  gfloat x;
  gfloat y;
  gfloat height;
  gfloat width;

  gfloat border_before;
  gfloat border_after;
  gfloat border_start;
  gfloat border_end;

  gfloat padding_before;
  gfloat padding_after;
  gfloat padding_start;
  gfloat padding_end;

  gfloat start_indent;
  gfloat end_indent;

  gfloat space_before;
  gfloat space_after;

};

struct _FoAreaAreaClass
{
  FoAreaClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_AREA_PRIVATE_H__ */
