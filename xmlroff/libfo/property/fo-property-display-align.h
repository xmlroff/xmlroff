/* Fo
 * fo-property-display-align.h: 'display-align' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_DISPLAY_ALIGN_H__
#define __FO_PROPERTY_DISPLAY_ALIGN_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* display-align */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* auto | before | center | after | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_DISPLAY_ALIGN              (fo_property_display_align_get_type ())
#define FO_PROPERTY_DISPLAY_ALIGN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_DISPLAY_ALIGN, FoPropertyDisplayAlign))
#define FO_PROPERTY_DISPLAY_ALIGN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_DISPLAY_ALIGN, FoPropertyDisplayAlignClass))
#define FO_IS_PROPERTY_DISPLAY_ALIGN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_DISPLAY_ALIGN))
#define FO_IS_PROPERTY_DISPLAY_ALIGN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_DISPLAY_ALIGN))
#define FO_PROPERTY_DISPLAY_ALIGN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_DISPLAY_ALIGN, FoPropertyDisplayAlignClass))


/**
 * FoPropertyDisplayAlign:
 *
 * Instance of the 'display-align' property.
 **/
typedef struct _FoPropertyDisplayAlign      FoPropertyDisplayAlign;

/**
 * FoPropertyDisplayAlignClass:
 *
 * Class structure for the 'display-align' property.
 **/
typedef struct _FoPropertyDisplayAlignClass FoPropertyDisplayAlignClass;

GType        fo_property_display_align_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_display_align_new         (void);
FoProperty * fo_property_display_align_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_DISPLAY_ALIGN_H__ */
