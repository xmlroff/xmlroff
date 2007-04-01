/* Fo
 * fo-property-keep-with-next-within-page.h: 'keep-with-next-within-page' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-keep-with-next-within-page.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE_H__
#define __FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* keep-with-next-within-page */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

#define FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE              (fo_property_keep_with_next_within_page_get_type ())
#define FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE, FoPropertyKeepWithNextWithinPage))
#define FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE, FoPropertyKeepWithNextWithinPageClass))
#define FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE))
#define FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE))
#define FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE, FoPropertyKeepWithNextWithinPageClass))


typedef struct _FoPropertyKeepWithNextWithinPage      FoPropertyKeepWithNextWithinPage;
typedef struct _FoPropertyKeepWithNextWithinPageClass FoPropertyKeepWithNextWithinPageClass;

GType       fo_property_keep_with_next_within_page_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_keep_with_next_within_page_new         (void);
FoProperty* fo_property_keep_with_next_within_page_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE_H__ */
