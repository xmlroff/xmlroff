/* Fo
 * fo-simple-page-master.h: 'simple-page-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SIMPLE_PAGE_MASTER_H__
#define __FO_SIMPLE_PAGE_MASTER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/area/fo-area.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoSimplePageMaster:
 *
 * Instance of the 'simple-page-master' formatting object.
 **/
typedef struct _FoSimplePageMaster      FoSimplePageMaster;

/**
 * FoSimplePageMasterClass:
 *
 * Class structure for the 'simple-page-master' formatting object.
 **/
typedef struct _FoSimplePageMasterClass FoSimplePageMasterClass;

#define FO_TYPE_SIMPLE_PAGE_MASTER              (fo_simple_page_master_get_type ())
#define FO_SIMPLE_PAGE_MASTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_SIMPLE_PAGE_MASTER, FoSimplePageMaster))
#define FO_SIMPLE_PAGE_MASTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_SIMPLE_PAGE_MASTER, FoSimplePageMasterClass))
#define FO_IS_SIMPLE_PAGE_MASTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_SIMPLE_PAGE_MASTER))
#define FO_IS_SIMPLE_PAGE_MASTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_SIMPLE_PAGE_MASTER))
#define FO_SIMPLE_PAGE_MASTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_SIMPLE_PAGE_MASTER, FoSimplePageMasterClass))


GType        fo_simple_page_master_get_type (void) G_GNUC_CONST;
FoFo *       fo_simple_page_master_new      (void);

FoArea *     fo_simple_page_master_get_area (FoFo       *fo_fo);

FoFo       * fo_simple_page_master_get_region_body   (FoFo        *fo_fo);
void         fo_simple_page_master_set_region_body   (FoFo        *fo_fo,
						      FoFo        *new_region_body);
FoFo       * fo_simple_page_master_get_region_before (FoFo        *fo_fo);
void         fo_simple_page_master_set_region_before (FoFo        *fo_fo,
						      FoFo        *new_region_before);
FoFo       * fo_simple_page_master_get_region_after  (FoFo        *fo_fo);
void         fo_simple_page_master_set_region_after  (FoFo        *fo_fo,
						      FoFo        *new_region_after);
FoFo       * fo_simple_page_master_get_region_start  (FoFo        *fo_fo);
void         fo_simple_page_master_set_region_start  (FoFo        *fo_fo,
						      FoFo        *new_region_start);
FoFo       * fo_simple_page_master_get_region_end    (FoFo        *fo_fo);
void         fo_simple_page_master_set_region_end    (FoFo        *fo_fo,
						      FoFo        *new_region_end);
FoFo *       fo_simple_page_master_region_name_get   (FoFo        *simple_page_master,
						      const gchar *name);

FoProperty * fo_simple_page_master_get_end_indent (FoFo       *fo_fo);
void         fo_simple_page_master_set_end_indent (FoFo       *fo_fo,
                                                   FoProperty *new_end_indent);
FoProperty * fo_simple_page_master_get_margin_bottom (FoFo       *fo_fo);
void         fo_simple_page_master_set_margin_bottom (FoFo       *fo_fo,
                                                      FoProperty *new_margin_bottom);
FoProperty * fo_simple_page_master_get_margin_left (FoFo       *fo_fo);
void         fo_simple_page_master_set_margin_left (FoFo       *fo_fo,
                                                    FoProperty *new_margin_left);
FoProperty * fo_simple_page_master_get_margin_right (FoFo       *fo_fo);
void         fo_simple_page_master_set_margin_right (FoFo       *fo_fo,
                                                     FoProperty *new_margin_right);
FoProperty * fo_simple_page_master_get_margin_top (FoFo       *fo_fo);
void         fo_simple_page_master_set_margin_top (FoFo       *fo_fo,
                                                   FoProperty *new_margin_top);
FoProperty * fo_simple_page_master_get_page_height (FoFo       *fo_fo);
void         fo_simple_page_master_set_page_height (FoFo       *fo_fo,
                                                    FoProperty *new_page_height);
FoProperty * fo_simple_page_master_get_page_width (FoFo       *fo_fo);
void         fo_simple_page_master_set_page_width (FoFo       *fo_fo,
                                                   FoProperty *new_page_width);
FoProperty * fo_simple_page_master_get_reference_orientation (FoFo       *fo_fo);
void         fo_simple_page_master_set_reference_orientation (FoFo       *fo_fo,
                                                              FoProperty *new_reference_orientation);
FoProperty * fo_simple_page_master_get_space_after (FoFo       *fo_fo);
void         fo_simple_page_master_set_space_after (FoFo       *fo_fo,
                                                    FoProperty *new_space_after);
FoProperty * fo_simple_page_master_get_space_before (FoFo       *fo_fo);
void         fo_simple_page_master_set_space_before (FoFo       *fo_fo,
                                                     FoProperty *new_space_before);
FoProperty * fo_simple_page_master_get_start_indent (FoFo       *fo_fo);
void         fo_simple_page_master_set_start_indent (FoFo       *fo_fo,
                                                     FoProperty *new_start_indent);
FoProperty * fo_simple_page_master_get_writing_mode (FoFo       *fo_fo);
void         fo_simple_page_master_set_writing_mode (FoFo       *fo_fo,
                                                     FoProperty *new_writing_mode);

G_END_DECLS

#endif /* !__FO_SIMPLE_PAGE_MASTER_H__ */
