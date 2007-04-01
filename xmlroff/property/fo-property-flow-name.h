/* Fo
 * fo-property-flow-name.h: 'flow-name' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-flow-name.h,v 1.4 2004/03/24 11:56:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_FLOW_NAME_H__
#define __FO_PROPERTY_FLOW_NAME_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* flow-name */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <name> */
/* Initial value: an empty name */

#define FO_TYPE_PROPERTY_FLOW_NAME              (fo_property_flow_name_get_type ())
#define FO_PROPERTY_FLOW_NAME(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FLOW_NAME, FoPropertyFlowName))
#define FO_PROPERTY_FLOW_NAME_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FLOW_NAME, FoPropertyFlowNameClass))
#define FO_IS_PROPERTY_FLOW_NAME(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FLOW_NAME))
#define FO_IS_PROPERTY_FLOW_NAME_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FLOW_NAME))
#define FO_PROPERTY_FLOW_NAME_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FLOW_NAME, FoPropertyFlowNameClass))


typedef struct _FoPropertyFlowName      FoPropertyFlowName;
typedef struct _FoPropertyFlowNameClass FoPropertyFlowNameClass;

GType        fo_property_flow_name_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_flow_name_new         (void);
FoProperty * fo_property_flow_name_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FLOW_NAME_H__ */
