/* Fo
 * fo-color_profile.h: 'color-profile' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-color-profile.h,v 1.3 2003/04/15 11:43:26 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_COLOR_PROFILE_H__
#define __FO_COLOR_PROFILE_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoColorProfile      FoColorProfile;
typedef struct _FoColorProfileClass FoColorProfileClass;

#define FO_TYPE_COLOR_PROFILE              (fo_color_profile_get_type ())
#define FO_COLOR_PROFILE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_COLOR_PROFILE, FoColorProfile))
#define FO_COLOR_PROFILE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_COLOR_PROFILE, FoColorProfileClass))
#define FO_IS_COLOR_PROFILE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_COLOR_PROFILE))
#define FO_IS_COLOR_PROFILE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_COLOR_PROFILE))
#define FO_COLOR_PROFILE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_COLOR_PROFILE, FoColorProfileClass))


GType        fo_color_profile_get_type (void) G_GNUC_CONST;
FoFo *       fo_color_profile_new      (void);

FoProperty * fo_color_profile_get_src (FoFo       *fo_fo);
void         fo_color_profile_set_src (FoFo       *fo_fo,
                                       FoProperty *new_src);

G_END_DECLS

#endif /* !__FO_COLOR_PROFILE_H__ */
