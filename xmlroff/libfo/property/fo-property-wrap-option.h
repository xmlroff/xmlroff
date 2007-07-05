/* Fo
 * fo-property-wrap-option.h: 'wrap-option' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_WRAP_OPTION_H__
#define __FO_PROPERTY_WRAP_OPTION_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* wrap-option */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* no-wrap | wrap | inherit */
/* Initial value: wrap */

#define FO_TYPE_PROPERTY_WRAP_OPTION              (fo_property_wrap_option_get_type ())
#define FO_PROPERTY_WRAP_OPTION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_WRAP_OPTION, FoPropertyWrapOption))
#define FO_PROPERTY_WRAP_OPTION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_WRAP_OPTION, FoPropertyWrapOptionClass))
#define FO_IS_PROPERTY_WRAP_OPTION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_WRAP_OPTION))
#define FO_IS_PROPERTY_WRAP_OPTION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_WRAP_OPTION))
#define FO_PROPERTY_WRAP_OPTION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_WRAP_OPTION, FoPropertyWrapOptionClass))


/**
 * FoPropertyWrapOption:
 *
 * Instance of the 'wrap-option' property.
 **/
typedef struct _FoPropertyWrapOption      FoPropertyWrapOption;

/**
 * FoPropertyWrapOptionClass:
 *
 * Class structure for the 'wrap-option' property.
 **/
typedef struct _FoPropertyWrapOptionClass FoPropertyWrapOptionClass;

GType        fo_property_wrap_option_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_wrap_option_new         (void);
FoProperty * fo_property_wrap_option_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_WRAP_OPTION_H__ */
