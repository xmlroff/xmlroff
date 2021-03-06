/* Fo
 * fo-property-util.h: Utility functions for properties.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_UTIL_H__
#define __FO_PROPERTY_UTIL_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-datatype.h>
#include <libfo/fo-context.h>

G_BEGIN_DECLS

FoDatatype * fo_property_util_get_color_initial        (void);
FoDatatype * fo_property_util_resolve_no_enum          (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_resolve_color_enum       (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_resolve_color_transparent_enum (const gchar *token,
							      FoContext   *context,
							      GError     **error);
FoDatatype * fo_property_util_resolve_auto_enum        (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_resolve_auto_always_enum (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_resolve_condity_enum     (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_resolve_force_enum       (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_resolve_true_false_enum  (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_validate_boolean         (FoDatatype *datatype,
							FoContext  *context,
							GError    **error);
FoDatatype * fo_property_util_validate_color           (FoDatatype  *datatype,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_validate_color_transparent (FoDatatype *datatype,
							  FoContext  *context,
							  GError    **error);
FoDatatype * fo_property_util_resolve_ipdim_percent    (gdouble           percentage,
							const FoDatatype *font_size,
							const FoFo       *fo_node,
							const FoContext  *context,
							GError          **error);
FoDatatype * fo_property_util_resolve_width_enum       (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_validate_width           (FoDatatype *datatype,
							FoContext  *context,
							GError    **error);
FoDatatype * fo_property_util_get_width_initial        (void);

FoDatatype * fo_property_util_resolve_style_enum       (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_validate_style           (FoDatatype *datatype,
							FoContext  *context,
							GError    **error);
FoDatatype * fo_property_util_resolve_wsc_enum         (const gchar *token,
							FoContext   *context,
							GError     **error);
FoDatatype * fo_property_util_validate_wsc             (FoDatatype *datatype,
							FoContext  *context,
							GError    **error);
FoDatatype * fo_property_util_get_style_initial        (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_UTIL_H__ */
