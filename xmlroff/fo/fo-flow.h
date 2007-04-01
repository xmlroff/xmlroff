/* Fo
 * fo-flow.h: 'flow' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-flow.h,v 1.4 2006/03/07 23:59:26 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_FLOW_H__
#define __FO_FLOW_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoFlow:
 *
 * Instance of the 'flow' formatting object.
 **/
typedef struct _FoFlow      FoFlow;

/**
 * FoFlowClass:
 *
 * Class structure for the 'flow' formatting object.
 **/
typedef struct _FoFlowClass FoFlowClass;

#define FO_TYPE_FLOW              (fo_flow_get_type ())
#define FO_FLOW(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FLOW, FoFlow))
#define FO_FLOW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FLOW, FoFlowClass))
#define FO_IS_FLOW(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FLOW))
#define FO_IS_FLOW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FLOW))
#define FO_FLOW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FLOW, FoFlowClass))


GType        fo_flow_get_type (void) G_GNUC_CONST;
FoFo *       fo_flow_new      (void);

FoFo *       fo_flow_get_region_master (FoFo       *fo_fo);
FoProperty * fo_flow_get_flow_name     (FoFo       *fo_fo);
void         fo_flow_set_flow_name     (FoFo       *fo_fo,
					FoProperty *new_flow_name);

G_END_DECLS

#endif /* !__FO_FLOW_H__ */
