/* Fo
 * fo-footnote_body.h: 'footnote-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-footnote-body.h,v 1.3 2004/03/24 11:52:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_FOOTNOTE_BODY_H__
#define __FO_FOOTNOTE_BODY_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoFootnoteBody      FoFootnoteBody;
typedef struct _FoFootnoteBodyClass FoFootnoteBodyClass;

#define FO_TYPE_FOOTNOTE_BODY              (fo_footnote_body_get_type ())
#define FO_FOOTNOTE_BODY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FOOTNOTE_BODY, FoFootnoteBody))
#define FO_FOOTNOTE_BODY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FOOTNOTE_BODY, FoFootnoteBodyClass))
#define FO_IS_FOOTNOTE_BODY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FOOTNOTE_BODY))
#define FO_IS_FOOTNOTE_BODY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FOOTNOTE_BODY))
#define FO_FOOTNOTE_BODY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FOOTNOTE_BODY, FoFootnoteBodyClass))


GType        fo_footnote_body_get_type (void) G_GNUC_CONST;
FoFo *       fo_footnote_body_new      (void);

FoProperty * fo_footnote_body_get_role (FoFo       *fo_fo);
void         fo_footnote_body_set_role (FoFo       *fo_fo,
                                        FoProperty *new_role);
FoProperty * fo_footnote_body_get_source_document (FoFo       *fo_fo);
void         fo_footnote_body_set_source_document (FoFo       *fo_fo,
                                                   FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_FOOTNOTE_BODY_H__ */
