/* Fo
 * fo-property-orphans.h: 'orphans' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_ORPHANS_H__
#define __FO_PROPERTY_ORPHANS_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* orphans */
/* <integer> | inherit */
/* Initial value: 2 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_ORPHANS              (fo_property_orphans_get_type ())
#define FO_PROPERTY_ORPHANS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_ORPHANS, FoPropertyOrphans))
#define FO_PROPERTY_ORPHANS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_ORPHANS, FoPropertyOrphansClass))
#define FO_IS_PROPERTY_ORPHANS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_ORPHANS))
#define FO_IS_PROPERTY_ORPHANS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_ORPHANS))
#define FO_PROPERTY_ORPHANS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_ORPHANS, FoPropertyOrphansClass))


typedef struct _FoPropertyOrphans      FoPropertyOrphans;
typedef struct _FoPropertyOrphansClass FoPropertyOrphansClass;

GType       fo_property_orphans_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_orphans_new         (void);
FoProperty* fo_property_orphans_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_ORPHANS_H__ */
