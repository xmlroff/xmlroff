/* Fo
 * fo-marker-parent-private.h: Part-level table formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-marker-parent-private.h,v 1.1 2003/03/07 17:54:52 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-fo-private.h"
#include "fo-marker-parent.h"

struct _FoMarkerParent
{
  FoFo parent_instance;

  GList *marker_list;
};

struct _FoMarkerParentClass
{
  FoFoClass parent_class;
};
