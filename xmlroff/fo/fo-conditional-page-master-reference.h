/* Fo
 * fo-conditional_page_master_reference.h: 'conditional-page-master-reference' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-conditional-page-master-reference.h,v 1.3 2003/05/16 11:44:27 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_H__
#define __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoConditionalPageMasterReference      FoConditionalPageMasterReference;
typedef struct _FoConditionalPageMasterReferenceClass FoConditionalPageMasterReferenceClass;

#define FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE              (fo_conditional_page_master_reference_get_type ())
#define FO_CONDITIONAL_PAGE_MASTER_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE, FoConditionalPageMasterReference))
#define FO_CONDITIONAL_PAGE_MASTER_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE, FoConditionalPageMasterReferenceClass))
#define FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE))
#define FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE))
#define FO_CONDITIONAL_PAGE_MASTER_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_CONDITIONAL_PAGE_MASTER_REFERENCE, FoConditionalPageMasterReferenceClass))


GType        fo_conditional_page_master_reference_get_type (void) G_GNUC_CONST;
FoFo *       fo_conditional_page_master_reference_new      (void);

FoProperty * fo_conditional_page_master_reference_get_master_reference (FoFo       *fo_fo);
void         fo_conditional_page_master_reference_set_master_reference (FoFo       *fo_fo,
                                                                        FoProperty *new_master_reference);

G_END_DECLS

#endif /* !__FO_CONDITIONAL_PAGE_MASTER_REFERENCE_H__ */
