/* Fo
 * fo-table-part-private.h: Part-level table formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-part-private.h,v 1.2 2003/03/07 17:54:56 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-marker-parent-private.h"
#include "fo-table-part.h"

struct _FoTablePart
{
  FoMarkerParent parent_instance;
};

struct _FoTablePartClass
{
  FoMarkerParentClass parent_class;
};
