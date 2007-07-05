/* Fo
 * fo-page-sequence.h: 'page-sequence' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_H__
#define __FO_PAGE_SEQUENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoPageSequence:
 *
 * Instance of the 'page-sequence' formatting object.
 **/
typedef struct _FoPageSequence      FoPageSequence;

/**
 * FoPageSequenceClass:
 *
 * Class structure for the 'page-sequence' formatting object.
 **/
typedef struct _FoPageSequenceClass FoPageSequenceClass;

#define FO_TYPE_PAGE_SEQUENCE              (fo_page_sequence_get_type ())
#define FO_PAGE_SEQUENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_SEQUENCE, FoPageSequence))
#define FO_PAGE_SEQUENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_SEQUENCE, FoPageSequenceClass))
#define FO_IS_PAGE_SEQUENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_SEQUENCE))
#define FO_IS_PAGE_SEQUENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_SEQUENCE))
#define FO_PAGE_SEQUENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_SEQUENCE, FoPageSequenceClass))


GType        fo_page_sequence_get_type (void) G_GNUC_CONST;
FoFo *       fo_page_sequence_new      (void);

FoProperty * fo_page_sequence_get_format (FoFo       *fo_fo);
void         fo_page_sequence_set_format (FoFo       *fo_fo,
                                          FoProperty *new_format);
FoProperty * fo_page_sequence_get_grouping_separator (FoFo       *fo_fo);
void         fo_page_sequence_set_grouping_separator (FoFo       *fo_fo,
                                                      FoProperty *new_grouping_separator);
FoProperty * fo_page_sequence_get_grouping_size (FoFo       *fo_fo);
void         fo_page_sequence_set_grouping_size (FoFo       *fo_fo,
                                                 FoProperty *new_grouping_size);
FoProperty * fo_page_sequence_get_id (FoFo       *fo_fo);
void         fo_page_sequence_set_id (FoFo       *fo_fo,
                                      FoProperty *new_id);
FoProperty * fo_page_sequence_get_letter_value (FoFo       *fo_fo);
void         fo_page_sequence_set_letter_value (FoFo       *fo_fo,
                                                FoProperty *new_letter_value);
FoProperty * fo_page_sequence_get_master_reference (FoFo       *fo_fo);
void         fo_page_sequence_set_master_reference (FoFo       *fo_fo,
                                                    FoProperty *new_master_reference);

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_H__ */
