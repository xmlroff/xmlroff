/* Fo
 * fo-property-widows.h: 'widows' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-widows.h,v 1.3 2003/07/02 10:39:38 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_WIDOWS_H__
#define __FO_PROPERTY_WIDOWS_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* widows */
/* <integer> | inherit */
/* Initial value: 2 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_WIDOWS              (fo_property_widows_get_type ())
#define FO_PROPERTY_WIDOWS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_WIDOWS, FoPropertyWidows))
#define FO_PROPERTY_WIDOWS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_WIDOWS, FoPropertyWidowsClass))
#define FO_IS_PROPERTY_WIDOWS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_WIDOWS))
#define FO_IS_PROPERTY_WIDOWS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_WIDOWS))
#define FO_PROPERTY_WIDOWS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_WIDOWS, FoPropertyWidowsClass))


typedef struct _FoPropertyWidows      FoPropertyWidows;
typedef struct _FoPropertyWidowsClass FoPropertyWidowsClass;

GType       fo_property_widows_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_widows_new         (void);
FoProperty* fo_property_widows_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_WIDOWS_H__ */
