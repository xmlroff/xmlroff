/* Fo
 * fo-region-body.h: 'region-body' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_BODY_H__
#define __FO_REGION_BODY_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRegionBody:
 *
 * Instance of the 'region-body' formatting object.
 **/
typedef struct _FoRegionBody      FoRegionBody;

/**
 * FoRegionBodyClass:
 *
 * Class structure for the 'region-body' formatting object.
 **/
typedef struct _FoRegionBodyClass FoRegionBodyClass;

#define FO_TYPE_REGION_BODY              (fo_region_body_get_type ())
#define FO_REGION_BODY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_BODY, FoRegionBody))
#define FO_REGION_BODY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_BODY, FoRegionBodyClass))
#define FO_IS_REGION_BODY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_BODY))
#define FO_IS_REGION_BODY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_BODY))
#define FO_REGION_BODY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_BODY, FoRegionBodyClass))


GType        fo_region_body_get_type (void) G_GNUC_CONST;
FoFo *       fo_region_body_new      (void);

FoProperty * fo_region_body_get_display_align (FoFo       *fo_fo);
void         fo_region_body_set_display_align (FoFo       *fo_fo,
                                               FoProperty *new_display_align);
FoProperty * fo_region_body_get_end_indent (FoFo       *fo_fo);
void         fo_region_body_set_end_indent (FoFo       *fo_fo,
                                            FoProperty *new_end_indent);
FoProperty * fo_region_body_get_margin_bottom (FoFo       *fo_fo);
void         fo_region_body_set_margin_bottom (FoFo       *fo_fo,
                                               FoProperty *new_margin_bottom);
FoProperty * fo_region_body_get_margin_left (FoFo       *fo_fo);
void         fo_region_body_set_margin_left (FoFo       *fo_fo,
                                             FoProperty *new_margin_left);
FoProperty * fo_region_body_get_margin_right (FoFo       *fo_fo);
void         fo_region_body_set_margin_right (FoFo       *fo_fo,
                                              FoProperty *new_margin_right);
FoProperty * fo_region_body_get_margin_top (FoFo       *fo_fo);
void         fo_region_body_set_margin_top (FoFo       *fo_fo,
                                            FoProperty *new_margin_top);
FoProperty * fo_region_body_get_space_after (FoFo       *fo_fo);
void         fo_region_body_set_space_after (FoFo       *fo_fo,
                                             FoProperty *new_space_after);
FoProperty * fo_region_body_get_space_before (FoFo       *fo_fo);
void         fo_region_body_set_space_before (FoFo       *fo_fo,
                                              FoProperty *new_space_before);
FoProperty * fo_region_body_get_start_indent (FoFo       *fo_fo);
void         fo_region_body_set_start_indent (FoFo       *fo_fo,
                                              FoProperty *new_start_indent);

G_END_DECLS

#endif /* !__FO_REGION_BODY_H__ */
