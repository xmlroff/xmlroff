/* Fo
 * fo-pcw.h: Proportional-column-width datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-pcw.h,v 1.3 2005/03/03 11:49:27 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PCW_H__
#define __FO_PCW_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_PCW              (fo_pcw_get_type ())
#define FO_PCW(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PCW, FoPcw))
#define FO_PCW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PCW, FoPcwClass))
#define FO_IS_PCW(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PCW))
#define FO_IS_PCW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PCW))
#define FO_PCW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PCW, FoPcwClass))


typedef struct _FoPcw      FoPcw;
typedef struct _FoPcwClass FoPcwClass;

GType       fo_pcw_get_type          (void) G_GNUC_CONST;
FoDatatype* fo_pcw_new               (void);
FoDatatype* fo_pcw_new_with_value    (gdouble value);

gdouble     fo_pcw_get_value         (FoDatatype *pcw);

FoDatatype* fo_pcw_get_pcw_zero (void);

G_END_DECLS

#endif /* !__FO_PCW_H__ */
