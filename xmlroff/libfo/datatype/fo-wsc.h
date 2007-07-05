/* Fo
 * fo-wsc.h: 'width-style-color' datatype
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WSC_H__
#define __FO_WSC_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_WSC              (fo_wsc_get_type ())
#define FO_WSC(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_WSC, FoWsc))
#define FO_WSC_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_WSC, FoWscClass))
#define FO_IS_WSC(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_WSC))
#define FO_IS_WSC_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_WSC))
#define FO_WSC_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_WSC, FoWscClass))


typedef struct _FoWsc      FoWsc;
typedef struct _FoWscClass FoWscClass;

GType        fo_wsc_get_type        (void) G_GNUC_CONST;
FoDatatype * fo_wsc_new             (void);
FoDatatype * fo_wsc_new_from_values (FoDatatype *width,
				     FoDatatype *style,
				     FoDatatype *color);

FoDatatype * fo_wsc_get_width       (FoDatatype *datatype);
FoDatatype * fo_wsc_get_style       (FoDatatype *datatype);
FoDatatype * fo_wsc_get_color       (FoDatatype *datatype);

G_END_DECLS

#endif /* !__FO_WSC_H__ */
