/* Fo
 * fo-repeatable-page-master-alternatives.h: 'repeatable-page-master-alternatives' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_H__
#define __FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRepeatablePageMasterAlternatives:
 *
 * Instance of the 'repeatable-page-master-alternatives' formatting object.
 **/
typedef struct _FoRepeatablePageMasterAlternatives      FoRepeatablePageMasterAlternatives;

/**
 * FoRepeatablePageMasterAlternativesClass:
 *
 * Class structure for the 'repeatable-page-master-alternatives' formatting object.
 **/
typedef struct _FoRepeatablePageMasterAlternativesClass FoRepeatablePageMasterAlternativesClass;

#define FO_TYPE_REPEATABLE_PAGE_MASTER_ALTERNATIVES              (fo_repeatable_page_master_alternatives_get_type ())
#define FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REPEATABLE_PAGE_MASTER_ALTERNATIVES, FoRepeatablePageMasterAlternatives))
#define FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REPEATABLE_PAGE_MASTER_ALTERNATIVES, FoRepeatablePageMasterAlternativesClass))
#define FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REPEATABLE_PAGE_MASTER_ALTERNATIVES))
#define FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REPEATABLE_PAGE_MASTER_ALTERNATIVES))
#define FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REPEATABLE_PAGE_MASTER_ALTERNATIVES, FoRepeatablePageMasterAlternativesClass))


GType        fo_repeatable_page_master_alternatives_get_type (void) G_GNUC_CONST;
FoFo *       fo_repeatable_page_master_alternatives_new      (void);

FoProperty * fo_repeatable_page_master_alternatives_get_maximum_repeats (FoFo       *fo_fo);
void         fo_repeatable_page_master_alternatives_set_maximum_repeats (FoFo       *fo_fo,
                                                                         FoProperty *new_maximum_repeats);

G_END_DECLS

#endif /* !__FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_H__ */
