/* Fo
 * fo-sequenced-page-sequence-walker.h: Walker for a sequenced page sequence
 *
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SEQUENCED_PAGE_SEQUENCE_WALKER_H__
#define __FO_SEQUENCED_PAGE_SEQUENCE_WALKER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

#define FO_TYPE_SEQUENCED_PAGE_SEQUENCE_WALKER              (fo_sequenced_page_sequence_walker_get_type ())
#define FO_SEQUENCED_PAGE_SEQUENCE_WALKER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_SEQUENCED_PAGE_SEQUENCE_WALKER, FoSequencedPageSequenceWalker))
#define FO_SEQUENCED_PAGE_SEQUENCE_WALKER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_SEQUENCED_PAGE_SEQUENCE_WALKER, FoSequencedPageSequenceWalkerClass))
#define FO_IS_SEQUENCED_PAGE_SEQUENCE_WALKER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_SEQUENCED_PAGE_SEQUENCE_WALKER))
#define FO_IS_SEQUENCED_PAGE_SEQUENCE_WALKER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_SEQUENCED_PAGE_SEQUENCE_WALKER))
#define FO_SEQUENCED_PAGE_SEQUENCE_WALKER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_SEQUENCED_PAGE_SEQUENCE_WALKER, FoSequencedPageSequenceWalkerClass))

typedef struct _FoSequencedPageSequenceWalker      FoSequencedPageSequenceWalker;
typedef struct _FoSequencedPageSequenceWalkerClass FoSequencedPageSequenceWalkerClass;

#define FO_SEQUENCED_PAGE_SEQUENCE_WALKER_ERROR fo_sequenced_page_sequence_walker_error_quark ()
GQuark fo_sequenced_page_sequence_walker_error_quark (void);

GType  fo_sequenced_page_sequence_walker_get_type  (void) G_GNUC_CONST;
FoSequencedPageSequenceWalker * fo_sequenced_page_sequence_walker_new (FoFo *page_master);

FoFo * fo_sequenced_page_sequence_walker_get_page_master (FoSequencedPageSequenceWalker *fpsw);

G_END_DECLS

#endif /* !__FO_SEQUENCED_PAGE_SEQUENCE_WALKER_H__ */
