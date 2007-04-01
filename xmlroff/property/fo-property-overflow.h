/* Fo
 * fo-property-overflow.h: 'overflow' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-overflow.h,v 1.4 2005/11/04 13:54:11 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_OVERFLOW_H__
#define __FO_PROPERTY_OVERFLOW_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* overflow */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* visible | hidden | scroll | error-if-overflow | auto | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_OVERFLOW              (fo_property_overflow_get_type ())
#define FO_PROPERTY_OVERFLOW(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_OVERFLOW, FoPropertyOverflow))
#define FO_PROPERTY_OVERFLOW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_OVERFLOW, FoPropertyOverflowClass))
#define FO_IS_PROPERTY_OVERFLOW(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_OVERFLOW))
#define FO_IS_PROPERTY_OVERFLOW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_OVERFLOW))
#define FO_PROPERTY_OVERFLOW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_OVERFLOW, FoPropertyOverflowClass))


/**
 * FoPropertyOverflow:
 *
 * Instance of the 'overflow' property.
 **/
typedef struct _FoPropertyOverflow      FoPropertyOverflow;

/**
 * FoPropertyOverflowClass:
 *
 * Class structure for the 'overflow' property.
 **/
typedef struct _FoPropertyOverflowClass FoPropertyOverflowClass;

GType        fo_property_overflow_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_overflow_new         (void);
FoProperty * fo_property_overflow_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_OVERFLOW_H__ */
