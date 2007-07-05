/* LibFO
 * libfo-pango.h: Extra PangoAttribute types needed by LibFO.
 *
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __LIBFO_PANGO_H__
#define __LIBFO_PANGO_H__

#include <pango/pango-attributes.h>

G_BEGIN_DECLS

typedef struct _LibfoPangoAttrPointer LibfoPangoAttrPointer;

struct _LibfoPangoAttrPointer
{
  PangoAttribute attr;
  gpointer pointer;
};

PangoAttrType    libfo_pango_attr_callback_get_type     (void);
PangoAttribute * libfo_pango_attr_callback_new          (gpointer callback);
gpointer         libfo_pango_attr_callback_get_callback (const PangoAttribute *attr);

G_END_DECLS

#endif /* __LIBFO_PANGO_H__ */
