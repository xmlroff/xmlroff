/* Fo
 * fo-property-border-collapse.h: 'border-collapse' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_COLLAPSE_H__
#define __FO_PROPERTY_BORDER_COLLAPSE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-collapse */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* collapse | collapse-with-precedence | separate | inherit */
/* Initial value: collapse */

#define FO_TYPE_PROPERTY_BORDER_COLLAPSE              (fo_property_border_collapse_get_type ())
#define FO_PROPERTY_BORDER_COLLAPSE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_COLLAPSE, FoPropertyBorderCollapse))
#define FO_PROPERTY_BORDER_COLLAPSE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_COLLAPSE, FoPropertyBorderCollapseClass))
#define FO_IS_PROPERTY_BORDER_COLLAPSE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_COLLAPSE))
#define FO_IS_PROPERTY_BORDER_COLLAPSE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_COLLAPSE))
#define FO_PROPERTY_BORDER_COLLAPSE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_COLLAPSE, FoPropertyBorderCollapseClass))


typedef struct _FoPropertyBorderCollapse      FoPropertyBorderCollapse;
typedef struct _FoPropertyBorderCollapseClass FoPropertyBorderCollapseClass;

GType        fo_property_border_collapse_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_collapse_new         (void);
FoProperty * fo_property_border_collapse_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_COLLAPSE_H__ */
