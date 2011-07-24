/* Fo
 * fo-page-sequence-walker.h: Walker for a page sequence
 *
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_WALKER_H__
#define __FO_PAGE_SEQUENCE_WALKER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-page-sequence.h>

G_BEGIN_DECLS

#define FO_TYPE_PAGE_SEQUENCE_WALKER              (fo_page_sequence_walker_get_type ())
#define FO_PAGE_SEQUENCE_WALKER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_SEQUENCE_WALKER, FoPageSequenceWalker))
#define FO_PAGE_SEQUENCE_WALKER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_SEQUENCE_WALKER, FoPageSequenceWalkerClass))
#define FO_IS_PAGE_SEQUENCE_WALKER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_SEQUENCE_WALKER))
#define FO_IS_PAGE_SEQUENCE_WALKER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_SEQUENCE_WALKER))
#define FO_PAGE_SEQUENCE_WALKER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_SEQUENCE_WALKER, FoPageSequenceWalkerClass))

typedef struct _FoPageSequenceWalker      FoPageSequenceWalker;
typedef struct _FoPageSequenceWalkerClass FoPageSequenceWalkerClass;

GType                  fo_page_sequence_walker_get_type  (void) G_GNUC_CONST;
FoPageSequenceWalker * fo_page_sequence_walker_new       (void);

FoPageSequenceWalker * fo_page_sequence_walker_new_from_page_sequence (FoFo *page_sequence,
								       GError **error);

FoFo * fo_page_sequence_walker_next_page_master (FoPageSequenceWalker *walker,
						 GError              **error);
FoFo * fo_page_sequence_walker_end_page_masters (FoPageSequenceWalker *walker,
						 GError              **error);

#define FO_PAGE_SEQUENCE_WALKER_ERROR fo_page_sequence_walker_error_quark ()
GQuark fo_page_sequence_walker_error_quark (void);

typedef enum
{
  FO_PAGE_SEQUENCE_WALKER_ERROR_FAILED,    /* Generic error code */
  FO_PAGE_SEQUENCE_WALKER_ERROR_WARNING,   /* Non-fatal error */
  FO_PAGE_SEQUENCE_WALKER_ERROR_NO_NEXT,   /* No 'next_page_master'
					      function defined for class. */
  FO_PAGE_SEQUENCE_WALKER_ERROR_NO_END,    /* No 'end_page_masters'
					      function defined for class. */
  FO_PAGE_SEQUENCE_WALKER_ERROR_LAST
} FoPageSequenceWalkerError;

extern const char *fo_page_sequence_walker_error_messages[FO_PAGE_SEQUENCE_WALKER_ERROR_LAST];

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_WALKER_H__ */
