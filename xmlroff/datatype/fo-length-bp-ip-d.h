/* Fo
 * fo-length-bp-ip-d.h: 'length-bp-ip-direction' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-length-bp-ip-d.h,v 1.3 2006/02/22 12:17:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LENGTH_BP_IP_D_H__
#define __FO_LENGTH_BP_IP_D_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_LENGTH_BP_IP_D              (fo_length_bp_ip_d_get_type ())
#define FO_LENGTH_BP_IP_D(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LENGTH_BP_IP_D, FoLengthBpIpD))
#define FO_LENGTH_BP_IP_D_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LENGTH_BP_IP_D, FoLengthBpIpDClass))
#define FO_IS_LENGTH_BP_IP_D(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LENGTH_BP_IP_D))
#define FO_IS_LENGTH_BP_IP_D_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LENGTH_BP_IP_D))
#define FO_LENGTH_BP_IP_D_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LENGTH_BP_IP_D, FoLengthBpIpDClass))


typedef struct _FoLengthBpIpD      FoLengthBpIpD;
typedef struct _FoLengthBpIpDClass FoLengthBpIpDClass;

GType        fo_length_bp_ip_d_get_type       (void) G_GNUC_CONST;
FoDatatype * fo_length_bp_ip_d_new            (void);
FoDatatype * fo_length_bp_ip_d_new_with_value (FoDatatype *length_bpd,
					       FoDatatype *length_ipd);
FoDatatype * fo_length_bp_ip_d_get_length_bpd (FoDatatype *datatype);
FoDatatype * fo_length_bp_ip_d_get_length_ipd (FoDatatype *datatype);

G_END_DECLS

#endif /* !__FO_LENGTH_BPD_IP_D_H__ */
