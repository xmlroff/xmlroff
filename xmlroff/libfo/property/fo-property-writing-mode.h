/* Fo
 * fo-property-writing-mode.h: 'writing-mode' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_WRITING_MODE_H__
#define __FO_PROPERTY_WRITING_MODE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* writing-mode */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* lr-tb | rl-tb | tb-rl | lr | rl | tb | inherit */
/* Initial value: lr-tb */

#define FO_TYPE_PROPERTY_WRITING_MODE              (fo_property_writing_mode_get_type ())
#define FO_PROPERTY_WRITING_MODE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_WRITING_MODE, FoPropertyWritingMode))
#define FO_PROPERTY_WRITING_MODE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_WRITING_MODE, FoPropertyWritingModeClass))
#define FO_IS_PROPERTY_WRITING_MODE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_WRITING_MODE))
#define FO_IS_PROPERTY_WRITING_MODE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_WRITING_MODE))
#define FO_PROPERTY_WRITING_MODE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_WRITING_MODE, FoPropertyWritingModeClass))


typedef struct _FoPropertyWritingMode      FoPropertyWritingMode;
typedef struct _FoPropertyWritingModeClass FoPropertyWritingModeClass;

GType        fo_property_writing_mode_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_writing_mode_new         (void);
FoProperty * fo_property_writing_mode_get_initial (void);

FoEnumAreaDirection fo_property_writing_mode_to_bpd (FoProperty  *writing_mode,
						     GError     **error);
FoEnumAreaDirection fo_property_writing_mode_to_ipd (FoProperty  *writing_mode,
						     GError     **error);
FoEnumAreaDirection fo_property_writing_mode_to_sd (FoProperty  *writing_mode,
						    GError     **error);

G_END_DECLS

#endif /* !__FO_PROPERTY_WRITING_MODE_H__ */
