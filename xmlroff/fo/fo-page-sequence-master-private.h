/* Fo
 * fo-page-sequence-master-private.h: Structures private to Page Sequence Master formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-page-sequence-master-private.h,v 1.1.1.1 2003/02/13 00:51:17 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-page-sequence-master.h"

struct _FoPageSequenceMaster
{
  FoFo parent_instance;
  FoProperty *master_name;
};

struct _FoPageSequenceMasterClass
{
  FoFoClass parent_class;
};
