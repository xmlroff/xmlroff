/* Fo
 * fo-property-country.h: 'country' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_COUNTRY_H__
#define __FO_PROPERTY_COUNTRY_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* country */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* none | <country> | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_COUNTRY              (fo_property_country_get_type ())
#define FO_PROPERTY_COUNTRY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_COUNTRY, FoPropertyCountry))
#define FO_PROPERTY_COUNTRY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_COUNTRY, FoPropertyCountryClass))
#define FO_IS_PROPERTY_COUNTRY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_COUNTRY))
#define FO_IS_PROPERTY_COUNTRY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_COUNTRY))
#define FO_PROPERTY_COUNTRY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_COUNTRY, FoPropertyCountryClass))


/**
 * FoPropertyCountry:
 *
 * Instance of the 'country' property.
 **/
typedef struct _FoPropertyCountry      FoPropertyCountry;

/**
 * FoPropertyCountryClass:
 *
 * Class structure for the 'country' property.
 **/
typedef struct _FoPropertyCountryClass FoPropertyCountryClass;

GType        fo_property_country_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_country_new         (void);
FoProperty * fo_property_country_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_COUNTRY_H__ */
