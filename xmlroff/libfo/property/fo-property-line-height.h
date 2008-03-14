/* Fo
 * fo-property-line-height.h: 'line-height' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_LINE_HEIGHT_H__
#define __FO_PROPERTY_LINE_HEIGHT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* line-height */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* normal | <length> | <number> | <percentage> | <space> | inherit */
/* Initial value: normal */

#define FO_TYPE_PROPERTY_LINE_HEIGHT              (fo_property_line_height_get_type ())
#define FO_PROPERTY_LINE_HEIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_LINE_HEIGHT, FoPropertyLineHeight))
#define FO_PROPERTY_LINE_HEIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_LINE_HEIGHT, FoPropertyLineHeightClass))
#define FO_IS_PROPERTY_LINE_HEIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_LINE_HEIGHT))
#define FO_IS_PROPERTY_LINE_HEIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_LINE_HEIGHT))
#define FO_PROPERTY_LINE_HEIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_LINE_HEIGHT, FoPropertyLineHeightClass))


typedef struct _FoPropertyLineHeight      FoPropertyLineHeight;
typedef struct _FoPropertyLineHeightClass FoPropertyLineHeightClass;

GType        fo_property_line_height_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_line_height_new         (void);
FoProperty * fo_property_line_height_get_initial (void);
FoProperty * fo_property_line_height_resolve     (FoProperty *line_height,
						  FoProperty *font_size);

G_END_DECLS

#endif /* !__FO_PROPERTY_LINE_HEIGHT_H__ */
