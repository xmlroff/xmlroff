/* Fo
 * fo-area-reference-private.h: Private information for reference area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_REFERENCE_PRIVATE_H__
#define __FO_AREA_REFERENCE_PRIVATE_H__

#include <libfo/area/fo-area-area-private.h>
#include <libfo/area/fo-area-reference.h>

G_BEGIN_DECLS

struct _FoAreaReference
{
  FoAreaArea parent_instance;

  guint bpd;	/* block progression direction */
  guint ipd;	/* inline progression direction */
  guint sd;	/* shift direction */
};

struct _FoAreaReferenceClass
{
  FoAreaAreaClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_REFERENCE_PRIVATE_H__ */
