/* Fo
 * fo-page_sequence_master.h: Page Sequence Master formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-page-sequence-master.h,v 1.2 2003/03/19 21:12:00 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_MASTER_H__
#define __FO_PAGE_SEQUENCE_MASTER_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

typedef struct _FoPageSequenceMaster      FoPageSequenceMaster;
typedef struct _FoPageSequenceMasterClass FoPageSequenceMasterClass;

#define FO_TYPE_PAGE_SEQUENCE_MASTER              (fo_page_sequence_master_get_type ())
#define FO_PAGE_SEQUENCE_MASTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_SEQUENCE_MASTER, FoPageSequenceMaster))
#define FO_PAGE_SEQUENCE_MASTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_SEQUENCE_MASTER, FoPageSequenceMasterClass))
#define FO_IS_PAGE_SEQUENCE_MASTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_SEQUENCE_MASTER))
#define FO_IS_PAGE_SEQUENCE_MASTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_SEQUENCE_MASTER))
#define FO_PAGE_SEQUENCE_MASTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_SEQUENCE_MASTER, FoPageSequenceMasterClass))


GType         fo_page_sequence_master_get_type      (void) G_GNUC_CONST;
FoFo *fo_page_sequence_master_new (void);

void fo_page_sequence_master_set_master_name (FoFo *fo_fo,
                                              FoProperty *new_master_name);
FoProperty *fo_page_sequence_master_get_master_name (FoFo *fo_fo);

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_MASTER_H__ */
