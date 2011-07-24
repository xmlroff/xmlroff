/* Fo
 * fo-conditional-page-master-reference.h: 'conditional-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_H__
#define __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoConditionalPageMasterReference:
 *
 * Instance of the 'conditional-page-master-reference' formatting object.
 **/
typedef struct _FoConditionalPageMasterReference      FoConditionalPageMasterReference;

/**
 * FoConditionalPageMasterReferenceClass:
 *
 * Class structure for the 'conditional-page-master-reference' formatting object.
 **/
typedef struct _FoConditionalPageMasterReferenceClass FoConditionalPageMasterReferenceClass;

#define FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE              (fo_conditional_page_master_reference_get_type ())
#define FO_CONDITIONAL_PAGE_MASTER_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE, FoConditionalPageMasterReference))
#define FO_CONDITIONAL_PAGE_MASTER_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE, FoConditionalPageMasterReferenceClass))
#define FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE))
#define FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE))
#define FO_CONDITIONAL_PAGE_MASTER_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE, FoConditionalPageMasterReferenceClass))


GType        fo_conditional_page_master_reference_get_type (void) G_GNUC_CONST;
FoFo *       fo_conditional_page_master_reference_new      (void);

FoProperty * fo_conditional_page_master_reference_get_blank_or_not_blank (FoFo       *fo_fo);
void         fo_conditional_page_master_reference_set_blank_or_not_blank (FoFo       *fo_fo,
                                                                          FoProperty *new_blank_or_not_blank);
FoProperty * fo_conditional_page_master_reference_get_odd_or_even (FoFo       *fo_fo);
void         fo_conditional_page_master_reference_set_odd_or_even (FoFo       *fo_fo,
                                                                   FoProperty *new_odd_or_even);
FoProperty * fo_conditional_page_master_reference_get_page_position (FoFo       *fo_fo);
void         fo_conditional_page_master_reference_set_page_position (FoFo       *fo_fo,
                                                                     FoProperty *new_page_position);

G_END_DECLS

#endif /* !__FO_CONDITIONAL_PAGE_MASTER_REFERENCE_H__ */
