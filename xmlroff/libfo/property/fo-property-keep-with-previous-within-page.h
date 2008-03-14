/* Fo
 * fo-property-keep-with-previous-within-page.h: 'keep-with-previous-within-page' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE_H__
#define __FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* keep-with-previous-within-page */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

#define FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE              (fo_property_keep_with_previous_within_page_get_type ())
#define FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE, FoPropertyKeepWithPreviousWithinPage))
#define FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE, FoPropertyKeepWithPreviousWithinPageClass))
#define FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE))
#define FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE))
#define FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE, FoPropertyKeepWithPreviousWithinPageClass))


typedef struct _FoPropertyKeepWithPreviousWithinPage      FoPropertyKeepWithPreviousWithinPage;
typedef struct _FoPropertyKeepWithPreviousWithinPageClass FoPropertyKeepWithPreviousWithinPageClass;

GType       fo_property_keep_with_previous_within_page_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_keep_with_previous_within_page_new         (void);
FoProperty* fo_property_keep_with_previous_within_page_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE_H__ */
