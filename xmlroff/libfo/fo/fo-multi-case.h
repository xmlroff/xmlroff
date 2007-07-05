/* Fo
 * fo-multi-case.h: 'multi-case' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_MULTI_CASE_H__
#define __FO_MULTI_CASE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoMultiCase      FoMultiCase;
typedef struct _FoMultiCaseClass FoMultiCaseClass;

#define FO_TYPE_MULTI_CASE              (fo_multi_case_get_type ())
#define FO_MULTI_CASE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_MULTI_CASE, FoMultiCase))
#define FO_MULTI_CASE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_MULTI_CASE, FoMultiCaseClass))
#define FO_IS_MULTI_CASE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_MULTI_CASE))
#define FO_IS_MULTI_CASE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_MULTI_CASE))
#define FO_MULTI_CASE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_MULTI_CASE, FoMultiCaseClass))


GType        fo_multi_case_get_type (void) G_GNUC_CONST;
FoFo *       fo_multi_case_new      (void);

FoProperty * fo_multi_case_get_id (FoFo       *fo_fo);
void         fo_multi_case_set_id (FoFo       *fo_fo,
                                   FoProperty *new_id);
FoProperty * fo_multi_case_get_role (FoFo       *fo_fo);
void         fo_multi_case_set_role (FoFo       *fo_fo,
                                     FoProperty *new_role);
FoProperty * fo_multi_case_get_source_document (FoFo       *fo_fo);
void         fo_multi_case_set_source_document (FoFo       *fo_fo,
                                                FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_MULTI_CASE_H__ */
