/* Fo
 * fo-footnote.h: Footnote formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FOOTNOTE_H__
#define __FO_FOOTNOTE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoFootnote      FoFootnote;
typedef struct _FoFootnoteClass FoFootnoteClass;

#define FO_TYPE_FOOTNOTE              (fo_footnote_get_type ())
#define FO_FOOTNOTE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FOOTNOTE, FoFootnote))
#define FO_FOOTNOTE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FOOTNOTE, FoFootnoteClass))
#define FO_IS_FOOTNOTE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FOOTNOTE))
#define FO_IS_FOOTNOTE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FOOTNOTE))
#define FO_FOOTNOTE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FOOTNOTE, FoFootnoteClass))


GType         fo_footnote_get_type      (void) G_GNUC_CONST;
FoFo *fo_footnote_new (void);

void fo_footnote_set_role (FoFo *fo_fo,
                           FoProperty *new_role);
FoProperty *fo_footnote_get_role (FoFo *fo_fo);
void fo_footnote_set_source_document (FoFo *fo_fo,
                                      FoProperty *new_source_document);
FoProperty *fo_footnote_get_source_document (FoFo *fo_fo);

G_END_DECLS

#endif /* !__FO_FOOTNOTE_H__ */
