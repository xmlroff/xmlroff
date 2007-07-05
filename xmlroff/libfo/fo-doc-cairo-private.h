/* Fo
 * fo-doc-cairo-private.h: Wrapper for libfo output document
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DOC_CAIRO_PRIVATE_H__
#define __FO_DOC_CAIRO_PRIVATE_H__

#include <pango/pangocairo.h>
#include "libfo/fo-doc-cairo.h"
#include "libfo/fo-doc-private.h"

G_BEGIN_DECLS

typedef cairo_surface_t* (*FoDocCairoSurfaceCreate)   (const char *filename,
						       double      width_in_points,
						       double      height_in_points);

struct _FoDocCairo
{
  FoDoc  parent_instance;

  cairo_t *cr;

  FoDocCairoSurfaceCreate  surface_create;
  gchar                   *base_filename;
  FoEnumFormat             format;
  gint                     output_sequence;

  gchar                   *current_filename;

  gdouble	           page_width;
  gdouble	           page_height;
};

struct _FoDocCairoClass
{
  FoDocClass  parent_class;
};

#endif /* !__FO_DOC_CAIRO_PRIVATE_H__ */
