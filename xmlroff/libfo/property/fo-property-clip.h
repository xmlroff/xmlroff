/* Fo
 * fo-property-clip.h: 'clip' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_CLIP_H__
#define __FO_PROPERTY_CLIP_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* clip */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <shape> | auto | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_CLIP              (fo_property_clip_get_type ())
#define FO_PROPERTY_CLIP(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_CLIP, FoPropertyClip))
#define FO_PROPERTY_CLIP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_CLIP, FoPropertyClipClass))
#define FO_IS_PROPERTY_CLIP(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_CLIP))
#define FO_IS_PROPERTY_CLIP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_CLIP))
#define FO_PROPERTY_CLIP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_CLIP, FoPropertyClipClass))


typedef struct _FoPropertyClip      FoPropertyClip;
typedef struct _FoPropertyClipClass FoPropertyClipClass;

GType        fo_property_clip_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_clip_new         (void);
FoProperty * fo_property_clip_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_CLIP_H__ */
