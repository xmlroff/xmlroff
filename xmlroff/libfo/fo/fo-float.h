/* Fo
 * fo-float.h: Float formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FLOAT_H__
#define __FO_FLOAT_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoFloat      FoFloat;
typedef struct _FoFloatClass FoFloatClass;

#define FO_TYPE_FLOAT              (fo_float_get_type ())
#define FO_FLOAT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FLOAT, FoFloat))
#define FO_FLOAT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FLOAT, FoFloatClass))
#define FO_IS_FLOAT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FLOAT))
#define FO_IS_FLOAT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FLOAT))
#define FO_FLOAT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FLOAT, FoFloatClass))


GType   fo_float_get_type (void) G_GNUC_CONST;
FoFo  * fo_float_new      (void);

G_END_DECLS

#endif /* !__FO_FLOAT_H__ */
