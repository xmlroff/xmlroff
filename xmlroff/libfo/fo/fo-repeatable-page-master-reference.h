/* Fo
 * fo-repeatable-page-master-reference.h: 'repeatable-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REPEATABLE_PAGE_MASTER_REFERENCE_H__
#define __FO_REPEATABLE_PAGE_MASTER_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoRepeatablePageMasterReference      FoRepeatablePageMasterReference;
typedef struct _FoRepeatablePageMasterReferenceClass FoRepeatablePageMasterReferenceClass;

#define FO_TYPE_REPEATABLE_PAGE_MASTER_REFERENCE              (fo_repeatable_page_master_reference_get_type ())
#define FO_REPEATABLE_PAGE_MASTER_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REPEATABLE_PAGE_MASTER_REFERENCE, FoRepeatablePageMasterReference))
#define FO_REPEATABLE_PAGE_MASTER_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REPEATABLE_PAGE_MASTER_REFERENCE, FoRepeatablePageMasterReferenceClass))
#define FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REPEATABLE_PAGE_MASTER_REFERENCE))
#define FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REPEATABLE_PAGE_MASTER_REFERENCE))
#define FO_REPEATABLE_PAGE_MASTER_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REPEATABLE_PAGE_MASTER_REFERENCE, FoRepeatablePageMasterReferenceClass))


GType        fo_repeatable_page_master_reference_get_type (void) G_GNUC_CONST;
FoFo *       fo_repeatable_page_master_reference_new      (void);

FoProperty * fo_repeatable_page_master_reference_get_master_reference (FoFo       *fo_fo);
void         fo_repeatable_page_master_reference_set_master_reference (FoFo       *fo_fo,
                                                                       FoProperty *new_master_reference);

G_END_DECLS

#endif /* !__FO_REPEATABLE_PAGE_MASTER_REFERENCE_H__ */
