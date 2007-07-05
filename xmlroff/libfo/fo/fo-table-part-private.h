/* Fo
 * fo-table-part-private.h: Part-level table formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-marker-parent-private.h>
#include <libfo/fo/fo-table-part.h>

struct _FoTablePart
{
  FoMarkerParent parent_instance;
};

struct _FoTablePartClass
{
  FoMarkerParentClass parent_class;
};
