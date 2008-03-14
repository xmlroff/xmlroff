/* Fo
 * fo-property-margin-left.h: 'margin-left' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_MARGIN_LEFT_H__
#define __FO_PROPERTY_MARGIN_LEFT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* margin-left */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <margin-width> | inherit */
/* Initial value: 0pt */

#define FO_TYPE_PROPERTY_MARGIN_LEFT              (fo_property_margin_left_get_type ())
#define FO_PROPERTY_MARGIN_LEFT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MARGIN_LEFT, FoPropertyMarginLeft))
#define FO_PROPERTY_MARGIN_LEFT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MARGIN_LEFT, FoPropertyMarginLeftClass))
#define FO_IS_PROPERTY_MARGIN_LEFT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MARGIN_LEFT))
#define FO_IS_PROPERTY_MARGIN_LEFT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MARGIN_LEFT))
#define FO_PROPERTY_MARGIN_LEFT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MARGIN_LEFT, FoPropertyMarginLeftClass))


typedef struct _FoPropertyMarginLeft      FoPropertyMarginLeft;
typedef struct _FoPropertyMarginLeftClass FoPropertyMarginLeftClass;

GType       fo_property_margin_left_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_margin_left_new         (void);
FoProperty* fo_property_margin_left_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MARGIN_LEFT_H__ */
