/* Fo
 * fo-doc-gp-private.h: Wrapper for libfo output document
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DOC_GP_PRIVATE_H__
#define __FO_DOC_GP_PRIVATE_H__

#include <libgnomeprint/gnome-print.h>
#include <libgnomeprint/gnome-print-job.h>
#include <libfo/fo-doc-gp.h>
#include <libfo/fo-doc-private.h>

G_BEGIN_DECLS

struct _FoDocGP
{
  FoDoc  parent_instance;

  GnomePrintJob     *job;
  GnomePrintContext *context;
  GnomePrintConfig  *config;

  gchar             *base_filename;
  FoEnumFormat       format;
  gint               output_sequence;

  gchar             *current_filename;

  gfloat	     page_width;
  gfloat	     page_height;
};

struct _FoDocGPClass
{
  FoDocClass  parent_class;
};

GnomePrintContext * fo_doc_gp_get_context (FoDoc *fo_doc);

#endif /* !__FO_DOC_GP_PRIVATE_H__ */
