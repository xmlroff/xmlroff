/* Fo
 * fo-property-white-space-collapse.h: 'white-space-collapse' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_WHITE_SPACE_COLLAPSE_H__
#define __FO_PROPERTY_WHITE_SPACE_COLLAPSE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* white-space-collapse */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* false | true | inherit */
/* Initial value: true */

#define FO_TYPE_PROPERTY_WHITE_SPACE_COLLAPSE              (fo_property_white_space_collapse_get_type ())
#define FO_PROPERTY_WHITE_SPACE_COLLAPSE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_WHITE_SPACE_COLLAPSE, FoPropertyWhiteSpaceCollapse))
#define FO_PROPERTY_WHITE_SPACE_COLLAPSE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_WHITE_SPACE_COLLAPSE, FoPropertyWhiteSpaceCollapseClass))
#define FO_IS_PROPERTY_WHITE_SPACE_COLLAPSE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_WHITE_SPACE_COLLAPSE))
#define FO_IS_PROPERTY_WHITE_SPACE_COLLAPSE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_WHITE_SPACE_COLLAPSE))
#define FO_PROPERTY_WHITE_SPACE_COLLAPSE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_WHITE_SPACE_COLLAPSE, FoPropertyWhiteSpaceCollapseClass))


/**
 * FoPropertyWhiteSpaceCollapse:
 *
 * Instance of the 'white-space-collapse' property.
 **/
typedef struct _FoPropertyWhiteSpaceCollapse      FoPropertyWhiteSpaceCollapse;

/**
 * FoPropertyWhiteSpaceCollapseClass:
 *
 * Class structure for the 'white-space-collapse' property.
 **/
typedef struct _FoPropertyWhiteSpaceCollapseClass FoPropertyWhiteSpaceCollapseClass;

GType        fo_property_white_space_collapse_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_white_space_collapse_new         (void);
FoProperty * fo_property_white_space_collapse_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_WHITE_SPACE_COLLAPSE_H__ */
