/* Fo
 * fo-property-source-document.h: 'source-document' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SOURCE_DOCUMENT_H__
#define __FO_PROPERTY_SOURCE_DOCUMENT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* source-document */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <uri-specification> [<uri-specification>]* | none | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_SOURCE_DOCUMENT              (fo_property_source_document_get_type ())
#define FO_PROPERTY_SOURCE_DOCUMENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SOURCE_DOCUMENT, FoPropertySourceDocument))
#define FO_PROPERTY_SOURCE_DOCUMENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SOURCE_DOCUMENT, FoPropertySourceDocumentClass))
#define FO_IS_PROPERTY_SOURCE_DOCUMENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SOURCE_DOCUMENT))
#define FO_IS_PROPERTY_SOURCE_DOCUMENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SOURCE_DOCUMENT))
#define FO_PROPERTY_SOURCE_DOCUMENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SOURCE_DOCUMENT, FoPropertySourceDocumentClass))


/**
 * FoPropertySourceDocument:
 *
 * Instance of the 'source-document' property.
 **/
typedef struct _FoPropertySourceDocument      FoPropertySourceDocument;

/**
 * FoPropertySourceDocumentClass:
 *
 * Class structure for the 'source-document' property.
 **/
typedef struct _FoPropertySourceDocumentClass FoPropertySourceDocumentClass;

GType        fo_property_source_document_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_source_document_new         (void);
FoProperty * fo_property_source_document_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SOURCE_DOCUMENT_H__ */
