/* Fo
 * fo-static-content.h: 'static-content' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-static-content.h,v 1.4 2005/11/23 22:16:33 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_STATIC_CONTENT_H__
#define __FO_STATIC_CONTENT_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoStaticContent:
 *
 * Instance of the 'static-content' formatting object.
 **/
typedef struct _FoStaticContent      FoStaticContent;

/**
 * FoStaticContentClass:
 *
 * Class structure for the 'static-content' formatting object.
 **/
typedef struct _FoStaticContentClass FoStaticContentClass;

#define FO_TYPE_STATIC_CONTENT              (fo_static_content_get_type ())
#define FO_STATIC_CONTENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_STATIC_CONTENT, FoStaticContent))
#define FO_STATIC_CONTENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_STATIC_CONTENT, FoStaticContentClass))
#define FO_IS_STATIC_CONTENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_STATIC_CONTENT))
#define FO_IS_STATIC_CONTENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_STATIC_CONTENT))
#define FO_STATIC_CONTENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_STATIC_CONTENT, FoStaticContentClass))


GType        fo_static_content_get_type (void) G_GNUC_CONST;
FoFo *       fo_static_content_new      (void);

FoProperty * fo_static_content_get_flow_name (FoFo       *fo_fo);
void         fo_static_content_set_flow_name (FoFo       *fo_fo,
                                              FoProperty *new_flow_name);

G_END_DECLS

#endif /* !__FO_STATIC_CONTENT_H__ */
