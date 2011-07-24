/* Fo
 * fo-cbpbp-fo.h: "Common Border, Padding, and Background Properties" FO interface
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CBPBP_FO_H__
#define __FO_CBPBP_FO_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

#define FO_TYPE_CBPBP_FO            (fo_cbpbp_fo_get_type ())
#define FO_CBPBP_FO(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), FO_TYPE_CBPBP_FO, FoCBPBPFo))
#define FO_CBPBP_FO_IFACE(obj)      (G_TYPE_CHECK_CLASS_CAST ((obj), FO_TYPE_CBPBP_FO, FoCBPBPFoIface))
#define FO_IS_CBPBP_FO(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FO_TYPE_CBPBP_FO))
#define FO_CBPBP_FO_GET_IFACE(obj)  ((FoCBPBPFoIface *)g_type_interface_peek (((GTypeInstance *) FO_CBPBP_FO (obj))->g_class, FO_TYPE_CBPBP_FO))

typedef struct _FoCBPBPFo      FoCBPBPFo; /* Dummy typedef */
typedef struct _FoCBPBPFoIface FoCBPBPFoIface;

GType fo_cbpbp_fo_get_type      (void) G_GNUC_CONST;

void fo_cbpbp_fo_update_area (FoFo *fo,
			      FoArea *area);

FoProperty * fo_cbpbp_fo_get_background_color    (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_after_color  (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_after_style  (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_after_width  (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_before_color (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_before_style (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_before_width (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_end_color    (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_end_style    (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_end_width    (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_start_color  (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_start_style  (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_border_start_width  (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_padding_after       (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_padding_before      (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_padding_end         (FoFo *fo_cbpbp_fo);
FoProperty * fo_cbpbp_fo_get_padding_start       (FoFo *fo_cbpbp_fo);

G_END_DECLS

#endif /* !__FO_CBPBP_FO_H__ */
