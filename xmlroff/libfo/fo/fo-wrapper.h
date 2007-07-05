/* Fo
 * fo-wrapper.h: 'wrapper' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_H__
#define __FO_WRAPPER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoWrapper:
 *
 * Instance of the 'wrapper' formatting object.
 **/
typedef struct _FoWrapper      FoWrapper;

/**
 * FoWrapperClass:
 *
 * Class structure for the 'wrapper' formatting object.
 **/
typedef struct _FoWrapperClass FoWrapperClass;

#define FO_TYPE_WRAPPER              (fo_wrapper_get_type ())
#define FO_WRAPPER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_WRAPPER, FoWrapper))
#define FO_WRAPPER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_WRAPPER, FoWrapperClass))
#define FO_IS_WRAPPER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_WRAPPER))
#define FO_IS_WRAPPER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_WRAPPER))
#define FO_WRAPPER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_WRAPPER, FoWrapperClass))


GType        fo_wrapper_get_type (void) G_GNUC_CONST;
FoFo *       fo_wrapper_new      (void);

FoProperty * fo_wrapper_get_id (FoFo       *fo_fo);
void         fo_wrapper_set_id (FoFo       *fo_fo,
                                FoProperty *new_id);

G_END_DECLS

#endif /* !__FO_WRAPPER_H__ */
