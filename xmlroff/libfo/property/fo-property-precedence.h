/* Fo
 * fo-property-precedence.h: 'precedence' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PRECEDENCE_H__
#define __FO_PROPERTY_PRECEDENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* true | false | inherit */
/* Initial value: false */

#define FO_TYPE_PROPERTY_PRECEDENCE              (fo_property_precedence_get_type ())
#define FO_PROPERTY_PRECEDENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PRECEDENCE, FoPropertyPrecedence))
#define FO_PROPERTY_PRECEDENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PRECEDENCE, FoPropertyPrecedenceClass))
#define FO_IS_PROPERTY_PRECEDENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PRECEDENCE))
#define FO_IS_PROPERTY_PRECEDENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PRECEDENCE))
#define FO_PROPERTY_PRECEDENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PRECEDENCE, FoPropertyPrecedenceClass))


/**
 * FoPropertyPrecedence:
 *
 * Instance of the 'precedence' property.
 **/
typedef struct _FoPropertyPrecedence      FoPropertyPrecedence;

/**
 * FoPropertyPrecedenceClass:
 *
 * Class structure for the 'precedence' property.
 **/
typedef struct _FoPropertyPrecedenceClass FoPropertyPrecedenceClass;

GType        fo_property_precedence_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_precedence_new         (void);
FoProperty * fo_property_precedence_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PRECEDENCE_H__ */
