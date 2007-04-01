/* Fo
 * fo-area-reference.h: Reference area object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-reference.h,v 1.2 2003/03/19 21:12:46 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_AREA_REFERENCE_H__
#define __FO_AREA_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaReference      FoAreaReference;
typedef struct _FoAreaReferenceClass FoAreaReferenceClass;

#define FO_TYPE_AREA_REFERENCE              (fo_area_reference_get_type ())
#define FO_AREA_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_REFERENCE, FoAreaReference))
#define FO_AREA_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_REFERENCE, FoAreaReferenceClass))
#define FO_IS_AREA_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_REFERENCE))
#define FO_IS_AREA_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_REFERENCE))
#define FO_AREA_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_REFERENCE, FoAreaReferenceClass))


GType         fo_area_reference_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_reference_new (void);
void fo_area_reference_set_bpd  (FoArea *fo_area,
				 guint   new_bpd);
guint fo_area_reference_get_bpd (FoArea *fo_area);
void fo_area_reference_set_ipd  (FoArea *fo_area,
				 guint   new_ipd);
guint fo_area_reference_get_ipd (FoArea *fo_area);
void fo_area_reference_set_sd   (FoArea *fo_area,
				 guint   new_sd);
guint fo_area_reference_get_sd  (FoArea *fo_area);

G_END_DECLS

#endif /* !__FO_AREA_REFERENCE_H__ */
