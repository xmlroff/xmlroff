/* Fo
 * fo-property-end-indent.h: 'end-indent' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-end-indent.h,v 1.4 2003/05/16 10:40:07 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_END_INDENT_H__
#define __FO_PROPERTY_END_INDENT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* end-indent */
/* <length> | <percentage> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_END_INDENT              (fo_property_end_indent_get_type ())
#define FO_PROPERTY_END_INDENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_END_INDENT, FoPropertyEndIndent))
#define FO_PROPERTY_END_INDENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_END_INDENT, FoPropertyEndIndentClass))
#define FO_IS_PROPERTY_END_INDENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_END_INDENT))
#define FO_IS_PROPERTY_END_INDENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_END_INDENT))
#define FO_PROPERTY_END_INDENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_END_INDENT, FoPropertyEndIndentClass))


typedef struct _FoPropertyEndIndent      FoPropertyEndIndent;
typedef struct _FoPropertyEndIndentClass FoPropertyEndIndentClass;

GType       fo_property_end_indent_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_end_indent_new         (void);
FoProperty* fo_property_end_indent_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_END_INDENT_H__ */
