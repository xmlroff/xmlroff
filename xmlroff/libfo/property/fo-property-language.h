/* Fo
 * fo-property-language.h: 'language' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_LANGUAGE_H__
#define __FO_PROPERTY_LANGUAGE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* language */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* none | <language> | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_LANGUAGE              (fo_property_language_get_type ())
#define FO_PROPERTY_LANGUAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_LANGUAGE, FoPropertyLanguage))
#define FO_PROPERTY_LANGUAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_LANGUAGE, FoPropertyLanguageClass))
#define FO_IS_PROPERTY_LANGUAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_LANGUAGE))
#define FO_IS_PROPERTY_LANGUAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_LANGUAGE))
#define FO_PROPERTY_LANGUAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_LANGUAGE, FoPropertyLanguageClass))


/**
 * FoPropertyLanguage:
 *
 * Instance of the 'language' property.
 **/
typedef struct _FoPropertyLanguage      FoPropertyLanguage;

/**
 * FoPropertyLanguageClass:
 *
 * Class structure for the 'language' property.
 **/
typedef struct _FoPropertyLanguageClass FoPropertyLanguageClass;

GType        fo_property_language_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_language_new         (void);
FoProperty * fo_property_language_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_LANGUAGE_H__ */
