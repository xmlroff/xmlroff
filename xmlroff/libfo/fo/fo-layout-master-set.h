/* Fo
 * fo-layout_master_set.h: 'layout-master-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LAYOUT_MASTER_SET_H__
#define __FO_LAYOUT_MASTER_SET_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoLayoutMasterSet      FoLayoutMasterSet;
typedef struct _FoLayoutMasterSetClass FoLayoutMasterSetClass;

#define FO_TYPE_LAYOUT_MASTER_SET              (fo_layout_master_set_get_type ())
#define FO_LAYOUT_MASTER_SET(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LAYOUT_MASTER_SET, FoLayoutMasterSet))
#define FO_LAYOUT_MASTER_SET_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LAYOUT_MASTER_SET, FoLayoutMasterSetClass))
#define FO_IS_LAYOUT_MASTER_SET(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LAYOUT_MASTER_SET))
#define FO_IS_LAYOUT_MASTER_SET_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LAYOUT_MASTER_SET))
#define FO_LAYOUT_MASTER_SET_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LAYOUT_MASTER_SET, FoLayoutMasterSetClass))


GType        fo_layout_master_set_get_type      (void) G_GNUC_CONST;
FoFo *       fo_layout_master_set_new (void);


G_END_DECLS

#endif /* !__FO_LAYOUT_MASTER_SET_H__ */
