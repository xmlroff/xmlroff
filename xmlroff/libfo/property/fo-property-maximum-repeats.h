/* Fo
 * fo-property-maximum-repeats.h: 'maximum-repeats' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_MAXIMUM_REPEATS_H__
#define __FO_PROPERTY_MAXIMUM_REPEATS_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* maximum-repeats */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <number> | no-limit | inherit */
/* Initial value: no-limit */

#define FO_TYPE_PROPERTY_MAXIMUM_REPEATS              (fo_property_maximum_repeats_get_type ())
#define FO_PROPERTY_MAXIMUM_REPEATS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MAXIMUM_REPEATS, FoPropertyMaximumRepeats))
#define FO_PROPERTY_MAXIMUM_REPEATS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MAXIMUM_REPEATS, FoPropertyMaximumRepeatsClass))
#define FO_IS_PROPERTY_MAXIMUM_REPEATS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MAXIMUM_REPEATS))
#define FO_IS_PROPERTY_MAXIMUM_REPEATS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MAXIMUM_REPEATS))
#define FO_PROPERTY_MAXIMUM_REPEATS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MAXIMUM_REPEATS, FoPropertyMaximumRepeatsClass))


/**
 * FoPropertyMaximumRepeats:
 *
 * Instance of the 'maximum-repeats' property.
 **/
typedef struct _FoPropertyMaximumRepeats      FoPropertyMaximumRepeats;

/**
 * FoPropertyMaximumRepeatsClass:
 *
 * Class structure for the 'maximum-repeats' property.
 **/
typedef struct _FoPropertyMaximumRepeatsClass FoPropertyMaximumRepeatsClass;

GType        fo_property_maximum_repeats_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_maximum_repeats_new         (void);
FoProperty * fo_property_maximum_repeats_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MAXIMUM_REPEATS_H__ */
