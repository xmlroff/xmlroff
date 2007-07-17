/* Fo
 * fo-static-content.c: 'static-content' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-static-content-private.h"
#include "property/fo-property-flow-name.h"

enum {
  PROP_0,
  PROP_FLOW_NAME
};

static void fo_static_content_class_init  (FoStaticContentClass *klass);
static void fo_static_content_get_property (GObject      *object,
                                            guint         prop_id,
                                            GValue       *value,
                                            GParamSpec   *pspec);
static void fo_static_content_set_property (GObject      *object,
                                            guint         prop_id,
                                            const GValue *value,
                                            GParamSpec   *pspec);
static void fo_static_content_finalize    (GObject           *object);
static gboolean fo_static_content_validate_content (FoFo    *fo,
                                                    GError **error);
static void fo_static_content_validate (FoFo      *fo,
                                        FoContext *current_context,
                                        FoContext *parent_context,
                                        GError   **error);
static void fo_static_content_update_from_context (FoFo      *fo,
                                                   FoContext *context);
static void fo_static_content_debug_dump_properties (FoFo *fo,
                                                     gint  depth);
static void fo_static_content_children_properties_resolve (FoFo       *this_fo,
							   FoArea     *this_fo_parent_area,
							   FoArea    **new_area,
							   GHashTable *prop_eval_hash,
							   FoDoc      *fo_doc,
							   gboolean    continue_after_error,
							   FoDebugFlag   debug_level,
							   FoWarningFlag warning_mode,
							   GError      **error);

static gpointer parent_class;

/**
 * fo_static_content_get_type:
 * 
 * Register the #FoStaticContent object type.
 * 
 * Return value: #GType value of the #FoStaticContent object type.
 **/
GType
fo_static_content_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoStaticContentClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_static_content_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoStaticContent),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "static-content",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_static_content_class_init:
 * @klass: #FoStaticContentClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoStaticContentClass.
 **/
void
fo_static_content_class_init (FoStaticContentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_static_content_finalize;

  object_class->get_property = fo_static_content_get_property;
  object_class->set_property = fo_static_content_set_property;

  fofo_class->validate_content = fo_static_content_validate_content;
  fofo_class->validate2 = fo_static_content_validate;
  fofo_class->update_from_context = fo_static_content_update_from_context;
  fofo_class->debug_dump_properties = fo_static_content_debug_dump_properties;
  fofo_class->children_properties_resolve =
    fo_static_content_children_properties_resolve;

  g_object_class_install_property
    (object_class,
     PROP_FLOW_NAME,
     g_param_spec_object ("flow-name",
			  _("Flow Name"),
			  _("Flow Name property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_static_content_finalize:
 * @object: #FoStaticContent object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoStaticContent.
 **/
void
fo_static_content_finalize (GObject *object)
{
  FoStaticContent *fo_static_content;

  fo_static_content = FO_STATIC_CONTENT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_static_content_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoStaticContent.
 **/
void
fo_static_content_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_FLOW_NAME:
      g_value_set_object (value, G_OBJECT (fo_static_content_get_flow_name (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_static_content_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoStaticContent.
 **/
void
fo_static_content_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_FLOW_NAME:
      fo_static_content_set_flow_name (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_static_content_new:
 * 
 * Creates a new #FoStaticContent initialized to default value.
 * 
 * Return value: the new #FoStaticContent.
 **/
FoFo*
fo_static_content_new (void)
{
  return FO_FO (g_object_new (fo_static_content_get_type (),
			      NULL));
}

void
fo_static_content_children_properties_resolve (FoFo         *this_fo,
					       FoArea       *this_fo_parent_area,
					       FoArea      **new_area,
					       GHashTable   *prop_eval_hash,
					       FoDoc        *fo_doc,
					       gboolean      continue_after_error,
					       FoDebugFlag   debug_level,
					       FoWarningFlag warning_mode,
					       GError      **error)
{
  FoArea *this_fo_area = NULL;
  FoFoAreaNew2Context area_new2_context;
  FoPropertyResolveContext prop_context;

  g_return_if_fail (FO_IS_FO (this_fo));
  g_return_if_fail (FO_IS_AREA (this_fo_parent_area));
  g_return_if_fail (*new_area == NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  prop_context.reference_area       = fo_area_get_reference (this_fo_parent_area);
  prop_context.prop_eval_hash       = prop_eval_hash;
  prop_context.continue_after_error = continue_after_error;
  prop_context.debug_level          = debug_level;
  prop_context.warning_mode         = warning_mode;
  prop_context.error                = NULL;

  fo_fo_resolve_property_attributes (FO_NODE (this_fo),
				     &prop_context);

  area_new2_context.fo_doc               = fo_doc;
  area_new2_context.parent_area          = this_fo_parent_area;
  area_new2_context.new_area             = &this_fo_area;
  area_new2_context.continue_after_error = continue_after_error;
  area_new2_context.debug_level          = debug_level;

  *new_area = NULL;
}

/**
 * fo_static_content_validate_content:
 * @fo:    #FoStaticContent object to validate.
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
fo_static_content_validate_content (FoFo    *fo,
                                    GError **error)
{
  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  return fo_fo_validate_content_block_plus (fo, error);
}

/**
 * fo_static_content_validate:
 * @fo:              #FoStaticContent object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_static_content_validate (FoFo      *fo,
                            FoContext *current_context,
                            FoContext *parent_context,
                            GError   **error)
{
  FoStaticContent *fo_static_content;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_static_content = FO_STATIC_CONTENT (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_static_content_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_static_content_update_from_context (FoFo      *fo,
                                       FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_static_content_set_flow_name (fo,
			  fo_context_get_flow_name (context));
}

/**
 * fo_static_content_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_static_content_debug_dump_properties (FoFo *fo,
                                         gint  depth)
{
  FoStaticContent *fo_static_content;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo));

  fo_static_content = FO_STATIC_CONTENT (fo);

  fo_object_debug_dump (fo_static_content->flow_name, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_static_content_get_flow_name:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "flow-name" property of @fo_fo.
 *
 * Return value: The "flow-name" property value.
**/
FoProperty*
fo_static_content_get_flow_name (FoFo *fo_fo)
{
  FoStaticContent *fo_static_content = (FoStaticContent *) fo_fo;

  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_static_content->flow_name;
}

/**
 * fo_static_content_set_flow_name:
 * @fo_fo: The #FoFo object
 * @new_flow_name: The new "flow-name" property value
 * 
 * Sets the "flow-name" property of @fo_fo to @new_flow_name
 **/
void
fo_static_content_set_flow_name (FoFo *fo_fo,
		         FoProperty *new_flow_name)
{
  FoStaticContent *fo_static_content = (FoStaticContent *) fo_fo;

  g_return_if_fail (fo_static_content != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo_static_content));
  g_return_if_fail (FO_IS_PROPERTY_FLOW_NAME (new_flow_name));

  if (new_flow_name != NULL)
    {
      g_object_ref (new_flow_name);
    }
  if (fo_static_content->flow_name != NULL)
    {
      g_object_unref (fo_static_content->flow_name);
    }
  fo_static_content->flow_name = new_flow_name;
  /*g_object_notify (G_OBJECT (fo_static_content), "flow-name");*/
}
