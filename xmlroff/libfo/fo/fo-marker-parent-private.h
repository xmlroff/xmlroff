/* Fo
 * fo-marker-parent-private.h: Abstract formatting object that is parent of possible fo:marker
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-marker-parent.h>

struct _FoMarkerParent
{
  FoFo parent_instance;

  GList *marker_list;
};

struct _FoMarkerParentClass
{
  FoFoClass parent_class;
};
