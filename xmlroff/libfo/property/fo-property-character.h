/* Fo
 * fo-property-character.h: 'character' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_CHARACTER_H__
#define __FO_PROPERTY_CHARACTER_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* character */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <character> */
/* Initial value: N/A, value is required */

#define FO_TYPE_PROPERTY_CHARACTER              (fo_property_character_get_type ())
#define FO_PROPERTY_CHARACTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_CHARACTER, FoPropertyCharacter))
#define FO_PROPERTY_CHARACTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_CHARACTER, FoPropertyCharacterClass))
#define FO_IS_PROPERTY_CHARACTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_CHARACTER))
#define FO_IS_PROPERTY_CHARACTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_CHARACTER))
#define FO_PROPERTY_CHARACTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_CHARACTER, FoPropertyCharacterClass))


typedef struct _FoPropertyCharacter      FoPropertyCharacter;
typedef struct _FoPropertyCharacterClass FoPropertyCharacterClass;

GType        fo_property_character_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_character_new         (void);
FoProperty * fo_property_character_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_CHARACTER_H__ */
