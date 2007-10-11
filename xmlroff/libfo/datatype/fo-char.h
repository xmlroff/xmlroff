/* Fo
 * fo-char.h: Character datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CHAR_H__
#define __FO_CHAR_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_CHAR              (fo_char_get_type ())
#define FO_CHAR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_CHAR, FoChar))
#define FO_CHAR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_CHAR, FoCharClass))
#define FO_IS_CHAR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_CHAR))
#define FO_IS_CHAR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_CHAR))
#define FO_CHAR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_CHAR, FoCharClass))


typedef struct _FoChar      FoChar;
typedef struct _FoCharClass FoCharClass;

GType        fo_char_get_type       (void) G_GNUC_CONST;
FoDatatype * fo_char_new_with_value (const gchar *value);

const gchar *fo_char_get_value      (FoDatatype  *fo_char);

FoDatatype * fo_char_get_char_space (void);
FoDatatype * fo_char_get_char_zws   (void);
G_END_DECLS

#endif /* !__FO_CHAR_H__ */
