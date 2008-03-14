/* Fo
 * fo-property-space-before.h: 'space-before' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_BEFORE_H__
#define __FO_PROPERTY_SPACE_BEFORE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* space-before */
/* <space> | <percentage> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_SPACE_BEFORE              (fo_property_space_before_get_type ())
#define FO_PROPERTY_SPACE_BEFORE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_BEFORE, FoPropertySpaceBefore))
#define FO_PROPERTY_SPACE_BEFORE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_BEFORE, FoPropertySpaceBeforeClass))
#define FO_IS_PROPERTY_SPACE_BEFORE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_BEFORE))
#define FO_IS_PROPERTY_SPACE_BEFORE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_BEFORE))
#define FO_PROPERTY_SPACE_BEFORE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_BEFORE, FoPropertySpaceBeforeClass))


typedef struct _FoPropertySpaceBefore      FoPropertySpaceBefore;
typedef struct _FoPropertySpaceBeforeClass FoPropertySpaceBeforeClass;

GType       fo_property_space_before_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_before_new         (void);
FoProperty* fo_property_space_before_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_BEFORE_H__ */
