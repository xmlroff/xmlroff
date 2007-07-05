/* Fo
 * fo-area-page.h: Page area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_PAGE_H__
#define __FO_AREA_PAGE_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_AREA_PAGE_ERROR (fo_area_page_error_quark ())

GQuark fo_area_page_error_quark (void) G_GNUC_CONST;

typedef enum
{
  FO_AREA_PAGE_ERROR_FAILED,            /* Generic error code */
  FO_AREA_PAGE_ERROR_WARNING,	        /* Non-fatal error */
  FO_AREA_PAGE_ERROR_OVERFLOW	        /* An area is too large for the region */
} FoAreaPageError;

typedef struct _FoAreaPage      FoAreaPage;
typedef struct _FoAreaPageClass FoAreaPageClass;

#define FO_TYPE_AREA_PAGE              (fo_area_page_get_type ())
#define FO_AREA_PAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_PAGE, FoAreaPage))
#define FO_AREA_PAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_PAGE, FoAreaPageClass))
#define FO_IS_AREA_PAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_PAGE))
#define FO_IS_AREA_PAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_PAGE))
#define FO_AREA_PAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_PAGE, FoAreaPageClass))


GType         fo_area_page_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_page_new (void);

void fo_area_page_set_page_number (FoArea *fo_area_page,
		      gint new_page_number);
gint fo_area_page_get_page_number (FoArea *fo_area_page);
void fo_area_page_set_page_width (FoArea *fo_area_page,
		      gfloat new_page_width);
gfloat fo_area_page_get_page_width (FoArea *fo_area_page);
void fo_area_page_set_page_height (FoArea *fo_area_page,
		      gfloat new_page_height);
gfloat fo_area_page_get_page_height (FoArea *fo_area_page);
void fo_area_page_set_margin_top (FoArea *fo_area_page,
		      gfloat new_margin_top);
gfloat fo_area_page_get_margin_top (FoArea *fo_area_page);
void fo_area_page_set_margin_bottom (FoArea *fo_area_page,
		      gfloat new_margin_bottom);
gfloat fo_area_page_get_margin_bottom (FoArea *fo_area_page);
void fo_area_page_set_margin_left (FoArea *fo_area_page,
		      gfloat new_margin_left);
gfloat fo_area_page_get_margin_left (FoArea *fo_area_page);
void fo_area_page_set_margin_right (FoArea *fo_area_page,
		      gfloat new_margin_right);
gfloat fo_area_page_get_margin_right (FoArea *fo_area_page);

G_END_DECLS

#endif /* !__FO_AREA_PAGE_H__ */
