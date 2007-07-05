/* Fo
 * fo-page-sequence-master-private.h: Structures private to Page Sequence Master formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-fo.h>
#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-page-sequence-master.h>

struct _FoPageSequenceMaster
{
  FoFo parent_instance;
  FoProperty *master_name;
};

struct _FoPageSequenceMasterClass
{
  FoFoClass parent_class;
};
