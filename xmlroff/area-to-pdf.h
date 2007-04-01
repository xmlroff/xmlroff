/* Fo
 * area-to-pdf.h: Convert area tree to pdf
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: area-to-pdf.h,v 1.5 2003/07/22 13:02:36 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_TO_PDF_H__
#define __FO_AREA_TO_PDF_H__

#include <area/fo-area.h>
#include <libfo/fo-doc-commands.h>

G_BEGIN_DECLS

typedef struct _FoAreaToPDFData
{
  FoDoc *fo_doc;
  FoDebugFlag debug_level;
} FoAreaToPDFData;

void fo_area_tree_to_pdf (FoArea *area_node,
			  gpointer data);

G_END_DECLS

#endif /* !__FO_AREA_TO_PDF_H__ */
