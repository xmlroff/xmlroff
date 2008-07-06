/* Fo
 * fo-fo.h: Base formatting object of formatting object system
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FO_H__
#define __FO_FO_H__

#include <libfo/fo-utils.h>

typedef struct _FoFo      FoFo;
typedef struct _FoFoClass FoFoClass;

#include <libfo/fo-doc.h>
#include <libfo/fo-context.h>
#include <libfo/area/fo-area.h>
#include <libfo/fo-node.h>

G_BEGIN_DECLS

#define FO_FO_ERROR (fo_fo_error_quark ())

GQuark fo_fo_error_quark (void) G_GNUC_CONST;

typedef enum
{
  FO_FO_ERROR_FAILED,            /* Generic error code */
  FO_FO_ERROR_WARNING,	         /* Non-fatal error */
  FO_FO_ERROR_EMPTY,             /* FO should not be empty */
  FO_FO_ERROR_NOT_EMPTY,         /* FO should be empty */
  FO_FO_ERROR_NOT_BLOCK,         /* FO should contain (%block;)+ */
  FO_FO_ERROR_INVALID_CHILD,     /* FO not allowed as child of parent FO */
  FO_FO_ERROR_INVALID_CONTENT,   /* FO content does not match content model */
  FO_FO_ERROR_ENUMERATION_TOKEN, /* Unrecognised enumeration token */
  FO_FO_ERROR_DATATYPE,          /* Invalid datatype value for property */
  FO_FO_ERROR_DATATYPE_REPLACE,  /* Invalid datatype value for property replaced */
  FO_FO_ERROR_DATATYPE_NULL,     /* Invalid datatype value for property: NULL */
  FO_FO_ERROR_UNSUPPORTED_PROPERTY,	/* Unsupported property */
  FO_FO_ERROR_NO_IMAGE,		 /* No image */
  FO_FO_ERROR_LAST
} FoFoError;

extern const char *fo_fo_error_messages[FO_FO_ERROR_LAST];

#define FO_TYPE_FO              (fo_fo_get_type ())
#define FO_FO(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_FO, FoFo))
#define FO_FO_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_FO, FoFoClass))
#define FO_IS_FO(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_FO))
#define FO_IS_FO_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_FO))
#define FO_FO_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_FO, FoFoClass))


typedef struct _FoFoAreaNew2Context FoFoAreaNew2Context;

struct _FoFoAreaNew2Context
{
  FoDoc        *fo_doc;
  FoArea       *parent_area;
  FoArea      **new_area;
  gboolean      continue_after_error;
  FoDebugFlag   debug_level;
  FoWarningFlag warning_mode;
};

typedef struct _FoFoAreaIterator FoFoAreaIterator;

GType         fo_fo_get_type      (void) G_GNUC_CONST;
FoFo *fo_fo_new           (void);
void fo_fo_debug_dump_properties (FoFo *fo, gint depth);
void fo_fo_set_context         (FoFo      *fo_fo,
				FoContext *new_context);
FoContext* fo_fo_get_context   (FoFo      *fo_fo);
void fo_fo_update_from_context (FoFo      *fo_fo,
				FoContext *context);
FoFo *     fo_fo_get_flow    (FoFo *fo_fo);
FoFo *     fo_fo_get_tree    (FoFo *fo_fo);
gboolean   fo_fo_get_generate_reference_area (FoFo *fo_fo);
gboolean   fo_fo_get_allow_mixed_content     (FoFo *fo_fo);
gboolean   fo_fo_validate_content (FoFo *fo,
				   GError **error);
gboolean   fo_fo_resolve_property_attributes (FoNode  *fo_node,
					      gpointer data);
void       fo_fo_children_properties_resolve (FoFo         *this_fo,
					      FoArea       *this_fo_parent_area,
					      FoArea      **new_area,
					      GHashTable   *prop_eval_hash,
					      FoDoc        *fo_doc,
					      gboolean      continue_after_error,
					      FoDebugFlag   debug_level,
					      FoWarningFlag warning_mode,
					      GError      **error);
void       fo_fo_validate    (FoFo *fo,
			      FoContext *current_context,
			      FoContext *parent_context,
			      GError   **error);
FoFo *     fo_fo_clone       (FoFo *original);

#ifndef FO_DISABLE_DEPRECATED
void       fo_fo_area_new    (FoFo    *fo,
			      FoDoc   *fo_doc,
			      FoArea  *parent_area,
			      FoArea **new_area,
			      guint    debug_level);
#endif /* FO_DISABLE_DEPRECATED */

void       fo_fo_area_new2   (FoFo                *fo,
			      FoFoAreaNew2Context *context,
			      GError             **error);
void fo_fo_trim_whitespace_children (FoFo *fo);
/* "validate_content" functions for use with fo_node_traverse() */
gboolean fo_fo_validate_content_empty (FoFo *fo,
				       GError **error);
gboolean fo_fo_validate_content_block_plus (FoFo *fo,
					    GError **error);
#if 0
/* "validate_content" functions for use with fo_node_children_foreach() */
void fo_fo_validate_pcdata_or_inline (FoNode   *fo_node,
				      gboolean *is_not_pcdata_inline);
void fo_fo_validate_block_or_whitespace (FoNode   *fo_node,
					 gboolean *is_not_block_or_whitespace);
#endif
void fo_fo_validate_pcdata_inline_block_neutral (FoNode  *fo_node,
						 gpointer data);
FoFoAreaIterator* fo_fo_get_area_iterator      (FoFo *fo);
FoArea*           fo_fo_area_iterator_get_area (const FoFoAreaIterator *iterator);
gboolean          fo_fo_area_iterator_next     (FoFoAreaIterator *iterator);

G_END_DECLS

#endif /* !__FO_FO_H__ */
