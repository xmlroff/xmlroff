/* Fo
 * fo-fixed-page-sequence-walker.h: Walker for a fixed page sequence
 *
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FIXED_PAGE_SEQUENCE_WALKER_H__
#define __FO_FIXED_PAGE_SEQUENCE_WALKER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

#define FO_TYPE_FIXED_PAGE_SEQUENCE_WALKER              (fo_fixed_page_sequence_walker_get_type ())
#define FO_FIXED_PAGE_SEQUENCE_WALKER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FIXED_PAGE_SEQUENCE_WALKER, FoFixedPageSequenceWalker))
#define FO_FIXED_PAGE_SEQUENCE_WALKER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FIXED_PAGE_SEQUENCE_WALKER, FoFixedPageSequenceWalkerClass))
#define FO_IS_FIXED_PAGE_SEQUENCE_WALKER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FIXED_PAGE_SEQUENCE_WALKER))
#define FO_IS_FIXED_PAGE_SEQUENCE_WALKER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FIXED_PAGE_SEQUENCE_WALKER))
#define FO_FIXED_PAGE_SEQUENCE_WALKER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FIXED_PAGE_SEQUENCE_WALKER, FoFixedPageSequenceWalkerClass))

typedef struct _FoFixedPageSequenceWalker      FoFixedPageSequenceWalker;
typedef struct _FoFixedPageSequenceWalkerClass FoFixedPageSequenceWalkerClass;

#define FO_FIXED_PAGE_SEQUENCE_WALKER_ERROR fo_fixed_page_sequence_walker_error_quark ()
GQuark fo_fixed_page_sequence_walker_error_quark (void);

GType  fo_fixed_page_sequence_walker_get_type  (void) G_GNUC_CONST;
FoFixedPageSequenceWalker * fo_fixed_page_sequence_walker_new (FoFo *page_master);

FoFo * fo_fixed_page_sequence_walker_get_page_master (FoFixedPageSequenceWalker *fpsw);

G_END_DECLS

#endif /* !__FO_FIXED_PAGE_SEQUENCE_WALKER_H__ */
