/* Fo
 * fo-property-odd-or-even.h: 'odd-or-even' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_ODD_OR_EVEN_H__
#define __FO_PROPERTY_ODD_OR_EVEN_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* odd-or-even */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* odd | even | any | inherit */
/* Initial value: any */

#define FO_TYPE_PROPERTY_ODD_OR_EVEN              (fo_property_odd_or_even_get_type ())
#define FO_PROPERTY_ODD_OR_EVEN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_ODD_OR_EVEN, FoPropertyOddOrEven))
#define FO_PROPERTY_ODD_OR_EVEN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_ODD_OR_EVEN, FoPropertyOddOrEvenClass))
#define FO_IS_PROPERTY_ODD_OR_EVEN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_ODD_OR_EVEN))
#define FO_IS_PROPERTY_ODD_OR_EVEN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_ODD_OR_EVEN))
#define FO_PROPERTY_ODD_OR_EVEN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_ODD_OR_EVEN, FoPropertyOddOrEvenClass))


/**
 * FoPropertyOddOrEven:
 *
 * Instance of the 'odd-or-even' property.
 **/
typedef struct _FoPropertyOddOrEven      FoPropertyOddOrEven;

/**
 * FoPropertyOddOrEvenClass:
 *
 * Class structure for the 'odd-or-even' property.
 **/
typedef struct _FoPropertyOddOrEvenClass FoPropertyOddOrEvenClass;

GType        fo_property_odd_or_even_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_odd_or_even_new         (void);
FoProperty * fo_property_odd_or_even_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_ODD_OR_EVEN_H__ */
