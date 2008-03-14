/* Fo
 * fo-property-text-indent.h: 'text-indent' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_TEXT_INDENT_H__
#define __FO_PROPERTY_TEXT_INDENT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* text-indent */
/* <length> | <percentage> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_TEXT_INDENT              (fo_property_text_indent_get_type ())
#define FO_PROPERTY_TEXT_INDENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_TEXT_INDENT, FoPropertyTextIndent))
#define FO_PROPERTY_TEXT_INDENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_TEXT_INDENT, FoPropertyTextIndentClass))
#define FO_IS_PROPERTY_TEXT_INDENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_TEXT_INDENT))
#define FO_IS_PROPERTY_TEXT_INDENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_TEXT_INDENT))
#define FO_PROPERTY_TEXT_INDENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_TEXT_INDENT, FoPropertyTextIndentClass))


typedef struct _FoPropertyTextIndent      FoPropertyTextIndent;
typedef struct _FoPropertyTextIndentClass FoPropertyTextIndentClass;

GType       fo_property_text_indent_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_text_indent_new         (void);
FoProperty* fo_property_text_indent_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_TEXT_INDENT_H__ */
