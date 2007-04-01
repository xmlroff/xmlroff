/* Fo
 * fo-space.h: Space datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-space.h,v 1.3 2003/12/16 17:26:44 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_SPACE_H__
#define __FO_SPACE_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_SPACE              (fo_space_get_type ())
#define FO_SPACE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_SPACE, FoSpace))
#define FO_SPACE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_SPACE, FoSpaceClass))
#define FO_IS_SPACE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_SPACE))
#define FO_IS_SPACE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_SPACE))
#define FO_SPACE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_SPACE, FoSpaceClass))


typedef struct _FoSpace      FoSpace;
typedef struct _FoSpaceClass FoSpaceClass;

GType        fo_space_get_type        (void) G_GNUC_CONST;
FoDatatype * fo_space_new             (void);
FoDatatype * fo_space_new_from_length (FoDatatype *length);

void         fo_space_set_minimum     (FoDatatype *datatype,
				       gfloat      new_minimum);
gfloat       fo_space_get_minimum     (FoDatatype *datatype);
void         fo_space_set_optimum     (FoDatatype *datatype,
				       gfloat      new_optimum);
gfloat       fo_space_get_optimum     (FoDatatype *datatype);
void         fo_space_set_maximum     (FoDatatype *datatype,
				       gfloat      new_maximum);
gfloat       fo_space_get_maximum     (FoDatatype *datatype);
void         fo_space_set_precedence  (FoDatatype *datatype,
				       gint        new_precedence);
gint         fo_space_get_precedence  (FoDatatype *datatype);
void         fo_space_set_condity     (FoDatatype *datatype,
				       gboolean    new_condity);
gboolean     fo_space_get_condity     (FoDatatype *datatype);

FoDatatype * fo_space_get_space_0pt   (void);

FoDatatype* fo_space_resolve (FoDatatype *shortform,
			      FoDatatype *minimum,
			      FoDatatype *optimum,
			      FoDatatype *maximum,
			      FoDatatype *precedence,
			      FoDatatype *condity,
			      gfloat hundred_percent,
			      GError **error);
G_END_DECLS

#endif /* !__FO_SPACE_H__ */
