/* Fo
 * fo-single-page-master-reference.h: 'single-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SINGLE_PAGE_MASTER_REFERENCE_H__
#define __FO_SINGLE_PAGE_MASTER_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoSinglePageMasterReference:
 *
 * Instance of the 'single-page-master-reference' formatting object.
 **/
typedef struct _FoSinglePageMasterReference      FoSinglePageMasterReference;

/**
 * FoSinglePageMasterReferenceClass:
 *
 * Class structure for the 'single-page-master-reference' formatting object.
 **/
typedef struct _FoSinglePageMasterReferenceClass FoSinglePageMasterReferenceClass;

#define FO_TYPE_SINGLE_PAGE_MASTER_REFERENCE              (fo_single_page_master_reference_get_type ())
#define FO_SINGLE_PAGE_MASTER_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_SINGLE_PAGE_MASTER_REFERENCE, FoSinglePageMasterReference))
#define FO_SINGLE_PAGE_MASTER_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_SINGLE_PAGE_MASTER_REFERENCE, FoSinglePageMasterReferenceClass))
#define FO_IS_SINGLE_PAGE_MASTER_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_SINGLE_PAGE_MASTER_REFERENCE))
#define FO_IS_SINGLE_PAGE_MASTER_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_SINGLE_PAGE_MASTER_REFERENCE))
#define FO_SINGLE_PAGE_MASTER_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_SINGLE_PAGE_MASTER_REFERENCE, FoSinglePageMasterReferenceClass))


GType        fo_single_page_master_reference_get_type (void) G_GNUC_CONST;
FoFo *       fo_single_page_master_reference_new      (void);

G_END_DECLS

#endif /* !__FO_SINGLE_PAGE_MASTER_REFERENCE_H__ */
