/* Fo
 * fo-idable.h: Formatting object that has an Id
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_IDABLE_H__
#define __FO_IDABLE_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoIdable      FoIdable;
typedef struct _FoIdableClass FoIdableClass;

#define FO_TYPE_IDABLE              (fo_idable_get_type ())
#define FO_IDABLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_IDABLE, FoIdable))
#define FO_IDABLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_IDABLE, FoIdableClass))
#define FO_IS_IDABLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_IDABLE))
#define FO_IS_IDABLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_IDABLE))
#define FO_IDABLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_IDABLE, FoIdableClass))


GType  fo_idable_get_type  (void) G_GNUC_CONST;
FoFo  *fo_idable_new       (void);

G_END_DECLS

#endif /* !__FO_IDABLE_H__ */
