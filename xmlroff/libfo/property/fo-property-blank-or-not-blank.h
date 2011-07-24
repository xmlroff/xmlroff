/* Fo
 * fo-property-blank-or-not-blank.h: 'blank-or-not-blank' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BLANK_OR_NOT_BLANK_H__
#define __FO_PROPERTY_BLANK_OR_NOT_BLANK_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* blank-or-not-blank */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* blank | not-blank | any | inherit */
/* Initial value: any */

#define FO_TYPE_PROPERTY_BLANK_OR_NOT_BLANK              (fo_property_blank_or_not_blank_get_type ())
#define FO_PROPERTY_BLANK_OR_NOT_BLANK(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BLANK_OR_NOT_BLANK, FoPropertyBlankOrNotBlank))
#define FO_PROPERTY_BLANK_OR_NOT_BLANK_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BLANK_OR_NOT_BLANK, FoPropertyBlankOrNotBlankClass))
#define FO_IS_PROPERTY_BLANK_OR_NOT_BLANK(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BLANK_OR_NOT_BLANK))
#define FO_IS_PROPERTY_BLANK_OR_NOT_BLANK_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BLANK_OR_NOT_BLANK))
#define FO_PROPERTY_BLANK_OR_NOT_BLANK_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BLANK_OR_NOT_BLANK, FoPropertyBlankOrNotBlankClass))


/**
 * FoPropertyBlankOrNotBlank:
 *
 * Instance of the 'blank-or-not-blank' property.
 **/
typedef struct _FoPropertyBlankOrNotBlank      FoPropertyBlankOrNotBlank;

/**
 * FoPropertyBlankOrNotBlankClass:
 *
 * Class structure for the 'blank-or-not-blank' property.
 **/
typedef struct _FoPropertyBlankOrNotBlankClass FoPropertyBlankOrNotBlankClass;

GType        fo_property_blank_or_not_blank_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_blank_or_not_blank_new         (void);
FoProperty * fo_property_blank_or_not_blank_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BLANK_OR_NOT_BLANK_H__ */
