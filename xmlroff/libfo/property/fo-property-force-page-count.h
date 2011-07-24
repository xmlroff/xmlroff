/* Fo
 * fo-property-force-page-count.h: 'force-page-count' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_FORCE_PAGE_COUNT_H__
#define __FO_PROPERTY_FORCE_PAGE_COUNT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* force-page-count */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | even | odd | end-on-even | end-on-odd | no-force | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_FORCE_PAGE_COUNT              (fo_property_force_page_count_get_type ())
#define FO_PROPERTY_FORCE_PAGE_COUNT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FORCE_PAGE_COUNT, FoPropertyForcePageCount))
#define FO_PROPERTY_FORCE_PAGE_COUNT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FORCE_PAGE_COUNT, FoPropertyForcePageCountClass))
#define FO_IS_PROPERTY_FORCE_PAGE_COUNT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FORCE_PAGE_COUNT))
#define FO_IS_PROPERTY_FORCE_PAGE_COUNT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FORCE_PAGE_COUNT))
#define FO_PROPERTY_FORCE_PAGE_COUNT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FORCE_PAGE_COUNT, FoPropertyForcePageCountClass))


/**
 * FoPropertyForcePageCount:
 *
 * Instance of the 'force-page-count' property.
 **/
typedef struct _FoPropertyForcePageCount      FoPropertyForcePageCount;

/**
 * FoPropertyForcePageCountClass:
 *
 * Class structure for the 'force-page-count' property.
 **/
typedef struct _FoPropertyForcePageCountClass FoPropertyForcePageCountClass;

GType        fo_property_force_page_count_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_force_page_count_new         (void);
FoProperty * fo_property_force_page_count_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FORCE_PAGE_COUNT_H__ */
