/* Fo
 * fo-boolean.h: Boolean datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BOOLEAN_H__
#define __FO_BOOLEAN_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_BOOLEAN              (fo_boolean_get_type ())
#define FO_BOOLEAN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BOOLEAN, FoBoolean))
#define FO_BOOLEAN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BOOLEAN, FoBooleanClass))
#define FO_IS_BOOLEAN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BOOLEAN))
#define FO_IS_BOOLEAN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BOOLEAN))
#define FO_BOOLEAN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BOOLEAN, FoBooleanClass))


typedef struct _FoBoolean      FoBoolean;
typedef struct _FoBooleanClass FoBooleanClass;

GType        fo_boolean_get_type       (void) G_GNUC_CONST;
FoDatatype * fo_boolean_new            (void);
FoDatatype * fo_boolean_new_with_value (gboolean value);

gboolean     fo_boolean_get_value      (FoDatatype *boolean);

FoDatatype * fo_boolean_get_true       (void);
FoDatatype * fo_boolean_get_false      (void);

G_END_DECLS

#endif /* !__FO_BOOLEAN_H__ */
