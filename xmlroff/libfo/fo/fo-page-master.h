/* Fo
 * fo-page-master.h: Abstract 'page-master' formatting object
 *
 * Copyright (C) 2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_MASTER_H__
#define __FO_PAGE_MASTER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/fo/fo-page-sequence-walker.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoPageMaster:
 *
 * Instance of the 'page-master' formatting object.
 **/
typedef struct _FoPageMaster      FoPageMaster;

/**
 * FoPageMasterClass:
 *
 * Class structure for the 'page-master' formatting object.
 **/
typedef struct _FoPageMasterClass FoPageMasterClass;

#define FO_TYPE_PAGE_MASTER              (fo_page_master_get_type ())
#define FO_PAGE_MASTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_MASTER, FoPageMaster))
#define FO_PAGE_MASTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_MASTER, FoPageMasterClass))
#define FO_IS_PAGE_MASTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_MASTER))
#define FO_IS_PAGE_MASTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_MASTER))
#define FO_PAGE_MASTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_MASTER, FoPageMasterClass))


GType        fo_page_master_get_type (void) G_GNUC_CONST;
FoFo *       fo_page_master_new      (void);

FoProperty * fo_page_master_get_master_name (FoFo       *fo_fo);
void         fo_page_master_set_master_name (FoFo       *fo_fo,
					     FoProperty *new_master_name);

FoPageSequenceWalker * fo_page_master_new_walker (FoFo    *fo_fo,
						  GError **error);

#define FO_PAGE_MASTER_ERROR (fo_page_master_error_quark ())

GQuark fo_page_master_error_quark (void) G_GNUC_CONST;

typedef enum
{
  FO_PAGE_MASTER_ERROR_FAILED,            /* Generic error code */
  FO_PAGE_MASTER_ERROR_WARNING,	          /* Non-fatal error */
  FO_PAGE_MASTER_ERROR_NO_WALKER,         /* No 'walker' object defined
					     for class. */
  FO_PAGE_MASTER_ERROR_LAST
} FoPageMasterError;

extern const char *fo_page_master_error_messages[FO_PAGE_MASTER_ERROR_LAST];

G_END_DECLS

#endif /* !__FO_PAGE_MASTER_H__ */
