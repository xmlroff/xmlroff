/* Fo
 * fo-property-keep-together-within-page.h: 'keep-together-within-page' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE_H__
#define __FO_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* keep-together-within-page */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

#define FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE              (fo_property_keep_together_within_page_get_type ())
#define FO_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE, FoPropertyKeepTogetherWithinPage))
#define FO_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE, FoPropertyKeepTogetherWithinPageClass))
#define FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE))
#define FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE))
#define FO_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE, FoPropertyKeepTogetherWithinPageClass))


typedef struct _FoPropertyKeepTogetherWithinPage      FoPropertyKeepTogetherWithinPage;
typedef struct _FoPropertyKeepTogetherWithinPageClass FoPropertyKeepTogetherWithinPageClass;

GType       fo_property_keep_together_within_page_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_keep_together_within_page_new         (void);
FoProperty* fo_property_keep_together_within_page_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE_H__ */
