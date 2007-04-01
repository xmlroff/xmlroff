/* Fo
 * fo-tblr.h: 'Top-bottom-left-right' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-tblr.h,v 1.2 2005/03/03 11:49:27 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_TBLR_H__
#define __FO_TBLR_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_TBLR              (fo_tblr_get_type ())
#define FO_TBLR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TBLR, FoTblr))
#define FO_TBLR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TBLR, FoTblrClass))
#define FO_IS_TBLR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TBLR))
#define FO_IS_TBLR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TBLR))
#define FO_TBLR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TBLR, FoTblrClass))


typedef struct _FoTblr      FoTblr;
typedef struct _FoTblrClass FoTblrClass;

GType        fo_tblr_get_type        (void) G_GNUC_CONST;
FoDatatype * fo_tblr_new             (void);
FoDatatype * fo_tblr_new_from_values (FoDatatype *top,
				      FoDatatype *bottom,
				      FoDatatype *left,
				      FoDatatype *right);

FoDatatype * fo_tblr_get_top         (FoDatatype *datatype);
FoDatatype * fo_tblr_get_bottom      (FoDatatype *datatype);
FoDatatype * fo_tblr_get_left        (FoDatatype *datatype);
FoDatatype * fo_tblr_get_right       (FoDatatype *datatype);

G_END_DECLS

#endif /* !__FO_TBLR_H__ */
