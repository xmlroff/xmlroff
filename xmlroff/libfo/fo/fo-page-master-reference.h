/* Fo
 * fo-page-master-reference.h: Abstract 'page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_MASTER_REFERENCE_H__
#define __FO_PAGE_MASTER_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoPageMasterReference:
 *
 * Instance of the 'page-master-reference' formatting object.
 **/
typedef struct _FoPageMasterReference      FoPageMasterReference;

/**
 * FoPageMasterReferenceClass:
 *
 * Class structure for the 'page-master-reference' formatting object.
 **/
typedef struct _FoPageMasterReferenceClass FoPageMasterReferenceClass;

#define FO_TYPE_PAGE_MASTER_REFERENCE              (fo_page_master_reference_get_type ())
#define FO_PAGE_MASTER_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_MASTER_REFERENCE, FoPageMasterReference))
#define FO_PAGE_MASTER_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_MASTER_REFERENCE, FoPageMasterReferenceClass))
#define FO_IS_PAGE_MASTER_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_MASTER_REFERENCE))
#define FO_IS_PAGE_MASTER_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_MASTER_REFERENCE))
#define FO_PAGE_MASTER_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_MASTER_REFERENCE, FoPageMasterReferenceClass))


GType        fo_page_master_reference_get_type (void) G_GNUC_CONST;
FoFo *       fo_page_master_reference_new      (void);

FoProperty * fo_page_master_reference_get_master_reference (FoFo       *fo_fo);
void         fo_page_master_reference_set_master_reference (FoFo       *fo_fo,
                                                                        FoProperty *new_master_reference);

G_END_DECLS

#endif /* !__FO_PAGE_MASTER_REFERENCE_H__ */
