/* Fo
 * fo-list-item-body.c: 'list-item-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-fo.h"
#include "fo-fo-private.h"
#include "fo-list-item-body.h"
#include "fo-list-item-body-private.h"
#include "fo-list-item-body-area.h"
#include "property/fo-property-id.h"
#include "property/fo-property-keep-together.h"
#include "property/fo-property-keep-together-within-column.h"
#include "property/fo-property-keep-together-within-line.h"
#include "property/fo-property-keep-together-within-page.h"
#include "property/fo-property-role.h"
#include "property/fo-property-source-document.h"

enum {
  PROP_0,
  PROP_ID,
  PROP_KEEP_TOGETHER,
  PROP_KEEP_TOGETHER_WITHIN_COLUMN,
  PROP_KEEP_TOGETHER_WITHIN_LINE,
  PROP_KEEP_TOGETHER_WITHIN_PAGE,
  PROP_ROLE,
  PROP_SOURCE_DOCUMENT
};

static void fo_list_item_body_class_init  (FoListItemBodyClass *klass);
static void fo_list_item_body_get_property (GObject      *object,
                                            guint         prop_id,
                                            GValue       *value,
                                            GParamSpec   *pspec);
static void fo_list_item_body_set_property (GObject      *object,
                                            guint         prop_id,
                                            const GValue *value,
                                            GParamSpec   *pspec);
static void fo_list_item_body_finalize    (GObject           *object);
static gboolean fo_list_item_body_validate_content (FoFo    *fo,
                                                    GError **error);
static void fo_list_item_body_validate (FoFo      *fo,
                                        FoContext *current_context,
                                        FoContext *parent_context,
                                        GError   **error);
static void fo_list_item_body_update_from_context (FoFo      *fo,
                                                   FoContext *context);
static void fo_list_item_body_debug_dump_properties (FoFo *fo,
                                                     gint  depth);

static gpointer parent_class;

/**
 * fo_list_item_body_get_type:
 * 
 * Register the #FoListItemBody object type.
 * 
 * Return value: #GType value of the #FoListItemBody object type.
 **/
GType
fo_list_item_body_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoListItemBodyClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_list_item_body_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoListItemBody),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoListItemBody",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_list_item_body_class_init:
 * @klass: #FoListItemBodyClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoListItemBodyClass.
 **/
void
fo_list_item_body_class_init (FoListItemBodyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_list_item_body_finalize;

  object_class->get_property = fo_list_item_body_get_property;
  object_class->set_property = fo_list_item_body_set_property;

  fofo_class->validate_content = fo_list_item_body_validate_content;
  fofo_class->validate2 = fo_list_item_body_validate;
  fofo_class->update_from_context = fo_list_item_body_update_from_context;
  fofo_class->debug_dump_properties = fo_list_item_body_debug_dump_properties;
  fofo_class->area_new2 = fo_list_item_body_area_new2;

  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER,
     g_param_spec_object ("keep-together",
			  _("Keep Together"),
			  _("Keep Together property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_COLUMN,
     g_param_spec_object ("keep-together-within-column",
			  _("Keep Together Within Column"),
			  _("Keep Together Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_LINE,
     g_param_spec_object ("keep-together-within-line",
			  _("Keep Together Within Line"),
			  _("Keep Together Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_PAGE,
     g_param_spec_object ("keep-together-within-page",
			  _("Keep Together Within Page"),
			  _("Keep Together Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SOURCE_DOCUMENT,
     g_param_spec_object ("source-document",
			  _("Source Document"),
			  _("Source Document property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_list_item_body_finalize:
 * @object: #FoListItemBody object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoListItemBody.
 **/
void
fo_list_item_body_finalize (GObject *object)
{
  FoListItemBody *fo_list_item_body;

  fo_list_item_body = FO_LIST_ITEM_BODY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_list_item_body_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoListItemBody.
 **/
void
fo_list_item_body_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_id (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_keep_together (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_keep_together_within_column (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_keep_together_within_line (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_keep_together_within_page (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_list_item_body_get_source_document (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_list_item_body_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoListItemBody.
 **/
void
fo_list_item_body_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      fo_list_item_body_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER:
      fo_list_item_body_set_keep_together (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      fo_list_item_body_set_keep_together_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      fo_list_item_body_set_keep_together_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      fo_list_item_body_set_keep_together_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_list_item_body_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_list_item_body_set_source_document (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_list_item_body_new:
 * 
 * Creates a new #FoListItemBody initialized to default value.
 * 
 * Return value: the new #FoListItemBody.
 **/
FoFo*
fo_list_item_body_new (void)
{
  return FO_FO (g_object_new (fo_list_item_body_get_type (), NULL));
}

/**
 * fo_list_item_body_validate_content:
 * @fo:    #FoListItemBody object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_list_item_body_validate_content (FoFo    *fo,
                                    GError **error)
{
  /*GError *tmp_error;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  return fo_fo_validate_content_block_plus (fo, error);
}

/**
 * fo_list_item_body_validate:
 * @fo:              #FoListItemBody object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_list_item_body_validate (FoFo      *fo,
                            FoContext *current_context,
                            FoContext *parent_context,
                            GError   **error)
{
  FoListItemBody *fo_list_item_body;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_list_item_body = FO_LIST_ITEM_BODY (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_list_item_body_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_list_item_body_update_from_context (FoFo *fo,
                                       FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_list_item_body_set_id (fo,
			  fo_context_get_id (context));
  fo_list_item_body_set_keep_together (fo,
			  fo_context_get_keep_together (context));
  fo_list_item_body_set_keep_together_within_column (fo,
			  fo_context_get_keep_together_within_column (context));
  fo_list_item_body_set_keep_together_within_line (fo,
			  fo_context_get_keep_together_within_line (context));
  fo_list_item_body_set_keep_together_within_page (fo,
			  fo_context_get_keep_together_within_page (context));
  fo_list_item_body_set_role (fo,
			  fo_context_get_role (context));
  fo_list_item_body_set_source_document (fo,
			  fo_context_get_source_document (context));
}

/**
 * fo_list_item_body_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_list_item_body_debug_dump_properties (FoFo *fo, gint depth)
{
  FoListItemBody *fo_list_item_body;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo));

  fo_list_item_body = FO_LIST_ITEM_BODY (fo);

  fo_object_debug_dump (fo_list_item_body->id, depth);
  fo_object_debug_dump (fo_list_item_body->keep_together, depth);
  fo_object_debug_dump (fo_list_item_body->keep_together_within_column, depth);
  fo_object_debug_dump (fo_list_item_body->keep_together_within_line, depth);
  fo_object_debug_dump (fo_list_item_body->keep_together_within_page, depth);
  fo_object_debug_dump (fo_list_item_body->role, depth);
  fo_object_debug_dump (fo_list_item_body->source_document, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_list_item_body_get_id:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "id" property of @fo_fo
 *
 * Return value: The "id" property value
**/
FoProperty*
fo_list_item_body_get_id (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->id;
}

/**
 * fo_list_item_body_set_id:
 * @fo_fo: The #FoFo object
 * @new_id: The new "id" property value
 * 
 * Sets the "id" property of @fo_fo to @new_id
 **/
void
fo_list_item_body_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_list_item_body->id != NULL)
    {
      g_object_unref (fo_list_item_body->id);
    }
  fo_list_item_body->id = new_id;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "id");*/
}

/**
 * fo_list_item_body_get_keep_together:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together" property of @fo_fo
 *
 * Return value: The "keep-together" property value
**/
FoProperty*
fo_list_item_body_get_keep_together (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->keep_together;
}

/**
 * fo_list_item_body_set_keep_together:
 * @fo_fo: The #FoFo object
 * @new_keep_together: The new "keep-together" property value
 * 
 * Sets the "keep-together" property of @fo_fo to @new_keep_together
 **/
void
fo_list_item_body_set_keep_together (FoFo *fo_fo,
		         FoProperty *new_keep_together)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER (new_keep_together));

  if (new_keep_together != NULL)
    {
      g_object_ref (new_keep_together);
    }
  if (fo_list_item_body->keep_together != NULL)
    {
      g_object_unref (fo_list_item_body->keep_together);
    }
  fo_list_item_body->keep_together = new_keep_together;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "keep-together");*/
}

/**
 * fo_list_item_body_get_keep_together_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-column" property of @fo_fo
 *
 * Return value: The "keep-together-within-column" property value
**/
FoProperty*
fo_list_item_body_get_keep_together_within_column (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->keep_together_within_column;
}

/**
 * fo_list_item_body_set_keep_together_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_column: The new "keep-together-within-column" property value
 * 
 * Sets the "keep-together-within-column" property of @fo_fo to @new_keep_together_within_column
 **/
void
fo_list_item_body_set_keep_together_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_column)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (new_keep_together_within_column));

  if (new_keep_together_within_column != NULL)
    {
      g_object_ref (new_keep_together_within_column);
    }
  if (fo_list_item_body->keep_together_within_column != NULL)
    {
      g_object_unref (fo_list_item_body->keep_together_within_column);
    }
  fo_list_item_body->keep_together_within_column = new_keep_together_within_column;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "keep-together-within-column");*/
}

/**
 * fo_list_item_body_get_keep_together_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-line" property of @fo_fo
 *
 * Return value: The "keep-together-within-line" property value
**/
FoProperty*
fo_list_item_body_get_keep_together_within_line (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->keep_together_within_line;
}

/**
 * fo_list_item_body_set_keep_together_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_line: The new "keep-together-within-line" property value
 * 
 * Sets the "keep-together-within-line" property of @fo_fo to @new_keep_together_within_line
 **/
void
fo_list_item_body_set_keep_together_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_line)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (new_keep_together_within_line));

  if (new_keep_together_within_line != NULL)
    {
      g_object_ref (new_keep_together_within_line);
    }
  if (fo_list_item_body->keep_together_within_line != NULL)
    {
      g_object_unref (fo_list_item_body->keep_together_within_line);
    }
  fo_list_item_body->keep_together_within_line = new_keep_together_within_line;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "keep-together-within-line");*/
}

/**
 * fo_list_item_body_get_keep_together_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-page" property of @fo_fo
 *
 * Return value: The "keep-together-within-page" property value
**/
FoProperty*
fo_list_item_body_get_keep_together_within_page (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->keep_together_within_page;
}

/**
 * fo_list_item_body_set_keep_together_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_page: The new "keep-together-within-page" property value
 * 
 * Sets the "keep-together-within-page" property of @fo_fo to @new_keep_together_within_page
 **/
void
fo_list_item_body_set_keep_together_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_page)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (new_keep_together_within_page));

  if (new_keep_together_within_page != NULL)
    {
      g_object_ref (new_keep_together_within_page);
    }
  if (fo_list_item_body->keep_together_within_page != NULL)
    {
      g_object_unref (fo_list_item_body->keep_together_within_page);
    }
  fo_list_item_body->keep_together_within_page = new_keep_together_within_page;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "keep-together-within-page");*/
}

/**
 * fo_list_item_body_get_role:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "role" property of @fo_fo
 *
 * Return value: The "role" property value
**/
FoProperty*
fo_list_item_body_get_role (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->role;
}

/**
 * fo_list_item_body_set_role:
 * @fo_fo: The #FoFo object
 * @new_role: The new "role" property value
 * 
 * Sets the "role" property of @fo_fo to @new_role
 **/
void
fo_list_item_body_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_list_item_body->role != NULL)
    {
      g_object_unref (fo_list_item_body->role);
    }
  fo_list_item_body->role = new_role;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "role");*/
}

/**
 * fo_list_item_body_get_source_document:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "source-document" property of @fo_fo
 *
 * Return value: The "source-document" property value
**/
FoProperty*
fo_list_item_body_get_source_document (FoFo *fo_fo)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_val_if_fail (fo_list_item_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body), NULL);

  return fo_list_item_body->source_document;
}

/**
 * fo_list_item_body_set_source_document:
 * @fo_fo: The #FoFo object
 * @new_source_document: The new "source-document" property value
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document
 **/
void
fo_list_item_body_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoListItemBody *fo_list_item_body = (FoListItemBody *) fo_fo;

  g_return_if_fail (fo_list_item_body != NULL);
  g_return_if_fail (FO_IS_LIST_ITEM_BODY (fo_list_item_body));
  g_return_if_fail (FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_list_item_body->source_document != NULL)
    {
      g_object_unref (fo_list_item_body->source_document);
    }
  fo_list_item_body->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_list_item_body), "source-document");*/
}
