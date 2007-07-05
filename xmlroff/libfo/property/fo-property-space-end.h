/* Fo
 * fo-property-space-end.h: 'space-end' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_END_H__
#define __FO_PROPERTY_SPACE_END_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-end */
/* <space> | <percentage> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_SPACE_END              (fo_property_space_end_get_type ())
#define FO_PROPERTY_SPACE_END(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_END, FoPropertySpaceEnd))
#define FO_PROPERTY_SPACE_END_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_END, FoPropertySpaceEndClass))
#define FO_IS_PROPERTY_SPACE_END(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_END))
#define FO_IS_PROPERTY_SPACE_END_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_END))
#define FO_PROPERTY_SPACE_END_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_END, FoPropertySpaceEndClass))


typedef struct _FoPropertySpaceEnd      FoPropertySpaceEnd;
typedef struct _FoPropertySpaceEndClass FoPropertySpaceEndClass;

GType       fo_property_space_end_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_end_new         (void);
FoProperty* fo_property_space_end_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_END_H__ */
