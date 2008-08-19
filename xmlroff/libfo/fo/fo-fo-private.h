/* Fo
 * fo-fo-private.h: Structures private to the base formatting object of
 * the formatting object system
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FO_PRIVATE_H__
#define __FO_FO_PRIVATE_H__

#include <libfo/fo-node-private.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/fo-xml-node.h>

G_BEGIN_DECLS

typedef struct _FoPropertyResolveContext FoPropertyResolveContext;

struct _FoPropertyResolveContext
{
  FoArea       *reference_area;
  GHashTable   *prop_eval_hash;
  gboolean      continue_after_error;
  FoDebugFlag   debug_level;
  FoWarningFlag warning_mode;
  GError      **error;
};

struct _FoFo
{
  FoNode parent_instance;

  FoXmlNode *element;

  FoFo *tree;
  FoFo *flow;
  GList *areas;

  FoContext *context;
};

struct _FoFoClass
{
  FoNodeClass parent_class;

  void     (* debug_dump_properties) (FoFo *fo, gint depth);
  void	   (* update_from_context)   (FoFo *fo,
				      FoContext *context);
  FoFo *   (* clone)                 (FoFo *original);
  void     (* update_after_clone)    (FoFo *clone,
				      FoFo *original);
  gboolean (* validate_content)      (FoFo *fo,
				      GError **error);
  void     (* validate)              (FoFo       *fo,
				      FoContext  *current_context,
				      FoContext  *parent_context);
  void     (* validate2)             (FoFo       *fo,
				      FoContext  *current_context,
				      FoContext  *parent_context,
				      GError    **error);
  void     (* area_new)              (FoFo    *fo,
				      FoDoc   *fo_doc,
				      FoArea  *parent_area,
				      FoArea **new_area,
				      guint    debug_level);
  void     (* area_new2)             (FoFo *fo,
				      FoFoAreaNew2Context *context,
				      GError **error);
  FoNodeTraverseFunc resolve_property_attributes;
  void     (* children_properties_resolve) (FoFo         *parent_fo,
					    FoArea       *parent_fo_parent_area,
					    FoArea      **new_area,
					    GHashTable   *prop_eval_hash,
					    FoDoc        *fo_doc,
					    gboolean      continue_after_error,
					    FoDebugFlag   debug_level,
					    FoWarningFlag warning_mode,
					    GError      **error);

  gboolean generate_reference_area;
  gboolean allow_mixed_content;
};

void fo_fo_children_properties_resolve_default (FoFo       *this_fo,
						FoArea     *this_fo_parent_area,
						FoArea    **new_area,
						GHashTable *prop_eval_hash,
						FoDoc      *fo_doc,
						gboolean    continue_after_error,
						FoDebugFlag   debug_level,
						FoWarningFlag warning_mode,
						GError    **error);

FoXmlNode *  fo_fo_get_element                 (FoFo       *fo_fo);
void         fo_fo_set_element                 (FoFo       *fo_fo,
				                FoXmlNode  *new_element);
void         fo_fo_update_after_clone          (FoFo       *clone,
						FoFo       *original);
void         fo_fo_register_id                 (FoFo       *fo,
						FoDatatype *id);
void         fo_fo_validate_parent             (FoFo *fo,
						FoContext  *current_context,
						FoContext  *parent_context);

G_END_DECLS

#endif /* !__FO_FO_PRIVATE_H__ */
