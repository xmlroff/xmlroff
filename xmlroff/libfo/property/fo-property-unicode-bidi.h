/* Fo
 * fo-property-unicode-bidi.h: 'unicode-bidi' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
  * Copyright (C) 2007 Menteith Consulting Ltd
*
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_UNICODE_BIDI_H__
#define __FO_PROPERTY_UNICODE_BIDI_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* unicode-bidi */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* normal | embed | bidi-override | inherit */
/* Initial value: normal */

#define FO_TYPE_PROPERTY_UNICODE_BIDI              (fo_property_unicode_bidi_get_type ())
#define FO_PROPERTY_UNICODE_BIDI(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_UNICODE_BIDI, FoPropertyUnicodeBidi))
#define FO_PROPERTY_UNICODE_BIDI_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_UNICODE_BIDI, FoPropertyUnicodeBidiClass))
#define FO_IS_PROPERTY_UNICODE_BIDI(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_UNICODE_BIDI))
#define FO_IS_PROPERTY_UNICODE_BIDI_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_UNICODE_BIDI))
#define FO_PROPERTY_UNICODE_BIDI_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_UNICODE_BIDI, FoPropertyUnicodeBidiClass))


typedef struct _FoPropertyUnicodeBidi      FoPropertyUnicodeBidi;
typedef struct _FoPropertyUnicodeBidiClass FoPropertyUnicodeBidiClass;

GType        fo_property_unicode_bidi_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_unicode_bidi_new         (void);
FoProperty * fo_property_unicode_bidi_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_UNICODE_BIDI_H__ */
