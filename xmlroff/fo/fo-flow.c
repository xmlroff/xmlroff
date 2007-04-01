/* Fo
 * fo-flow.c: 'flow' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-flow.c,v 1.7 2006/03/07 23:59:26 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-flow-private.h"
#include "property/fo-property-flow-name.h"
#include "fo/fo-flow-area.h"
#include "fo/fo-simple-page-master.h"
#include "fo/fo-page-sequence-private.h"
#include "fo/fo-region-body.h"

enum {
  PROP_0,
  PROP_FLOW_NAME
};

static void fo_flow_class_init  (FoFlowClass *klass);
static void fo_flow_get_property (GObject      *object,
                                  guint         prop_id,
                                  GValue       *value,
                                  GParamSpec   *pspec);
static void fo_flow_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec);
static void fo_flow_finalize    (GObject           *object);
static gboolean fo_flow_validate_content (FoFo    *fo,
                                          GError **error);
static void fo_flow_validate (FoFo      *fo,
                              FoContext *current_context,
                              FoContext *parent_context,
                              GError   **error);
static void fo_flow_update_from_context (FoFo      *fo,
                                         FoContext *context);
static void fo_flow_debug_dump_properties (FoFo *fo,
                                           gint  depth);

static const gchar class_name[] = "flow";
static gpointer parent_class;

/**
 * fo_flow_get_type:
 * 
 * Register the #FoFlow object type.
 * 
 * Return value: #GType value of the #FoFlow object type.
 **/
GType
fo_flow_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoFlowClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_flow_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoFlow),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_flow_class_init:
 * @klass: #FoFlowClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoFlowClass.
 **/
void
fo_flow_class_init (FoFlowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_flow_finalize;

  object_class->get_property = fo_flow_get_property;
  object_class->set_property = fo_flow_set_property;

  fofo_class->validate_content = fo_flow_validate_content;
  fofo_class->validate2 = fo_flow_validate;
  fofo_class->update_from_context = fo_flow_update_from_context;
  fofo_class->debug_dump_properties = fo_flow_debug_dump_properties;
  fofo_class->area_new = fo_flow_area_new;
  fofo_class->area_new2 = fo_flow_area_new2;

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
 * fo_flow_finalize:
 * @object: #FoFlow object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoFlow.
 **/
void
fo_flow_finalize (GObject *object)
{
  FoFlow *fo_flow;

  fo_flow = FO_FLOW (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_flow_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoFlow.
 **/
void
fo_flow_get_property (GObject    *object,
                      guint       prop_id,
                      GValue     *value,
                      GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_FLOW_NAME:
      g_value_set_object (value, G_OBJECT (fo_flow_get_flow_name (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_flow_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoFlow.
 **/
void
fo_flow_set_property (GObject      *object,
                      guint         prop_id,
                      const GValue *value,
                      GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_FLOW_NAME:
      fo_flow_set_flow_name (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_flow_new:
 * 
 * Creates a new #FoFlow initialized to default value.
 * 
 * Return value: the new #FoFlow.
 **/
FoFo*
fo_flow_new (void)
{
  return FO_FO (g_object_new (fo_flow_get_type (),
                              NULL));
}

/**
 * fo_flow_validate_content:
 * @fo:    #FoFlow object to validate.
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
fo_flow_validate_content (FoFo    *fo,
                          GError **error)
{
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_FLOW (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  return fo_fo_validate_content_block_plus (fo, error);
}

/**
 * fo_flow_validate:
 * @fo:              #FoFlow object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_flow_validate (FoFo      *fo,
                  FoContext *current_context,
                  FoContext *parent_context,
                  GError   **error)
{
  FoFlow *fo_flow;
  FoPageSequence *page_sequence;
  FoFo *region_master;
  FoDatatype *flow_name_datatype;
  gchar *flow_name;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FLOW (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_flow = FO_FLOW (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  flow_name_datatype = fo_property_get_value (fo_flow_get_flow_name (fo));

  if (flow_name_datatype == NULL) {
    g_set_error (error,
		 FO_FO_ERROR,
		 FO_FO_ERROR_DATATYPE_NULL,
		 _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE_NULL]),
		 "flow-name");
  }

  flow_name =
    fo_name_get_value (flow_name_datatype);

  /*
  if (fo->parent)
    page_sequence = FO_PAGE_SEQUENCE (fo->parent);
  else
  */
    page_sequence = FO_PAGE_SEQUENCE (fo_node_parent (FO_NODE (fo)));

  if (page_sequence != NULL)
    {
      region_master = fo_simple_page_master_region_name_get (page_sequence->page_master, flow_name);
      /*
      g_print ("Master: %s\n", fo_object_sprintf (page_master));

      fo_object_debug_dump (page_master, 0);
      */
      fo_flow->region_master = region_master;
    }
  else
    {
      g_assert_not_reached();
    }

  fo_context_set_writing_mode (current_context,
			       fo_region_body_get_writing_mode (fo_flow->region_master));

}

/**
 * fo_flow_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_flow_update_from_context (FoFo      *fo,
                             FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FLOW (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_flow_set_flow_name (fo,
			  fo_context_get_flow_name (context));
}

/**
 * fo_flow_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_flow_debug_dump_properties (FoFo *fo,
                               gint  depth)
{
  FoFlow *fo_flow;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FLOW (fo));

  fo_flow = FO_FLOW (fo);

  fo_object_debug_dump (fo_flow->flow_name, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_flow_get_region_master:
 * @fo_fo: The @FoFlow object
 *
 * Gets the #region_master instance variable of @flow
 *
 * Return value: The "region_master" value
**/
FoFo*
fo_flow_get_region_master (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_fo), NULL);

  return FO_FLOW (fo_fo)->region_master;
}

/**
 * fo_flow_get_flow_name:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "flow-name" property of @fo_fo.
 *
 * Return value: The "flow-name" property value.
**/
FoProperty*
fo_flow_get_flow_name (FoFo *fo_fo)
{
  FoFlow *fo_flow = (FoFlow *) fo_fo;

  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_flow->flow_name;
}

/**
 * fo_flow_set_flow_name:
 * @fo_fo: The #FoFo object.
 * @new_flow_name: The new "flow-name" property value.
 * 
 * Sets the "flow-name" property of @fo_fo to @new_flow_name.
 **/
void
fo_flow_set_flow_name (FoFo *fo_fo,
		         FoProperty *new_flow_name)
{
  FoFlow *fo_flow = (FoFlow *) fo_fo;

  g_return_if_fail (fo_flow != NULL);
  g_return_if_fail (FO_IS_FLOW (fo_flow));
  g_return_if_fail (FO_IS_PROPERTY_FLOW_NAME (new_flow_name));

  if (new_flow_name != NULL)
    {
      g_object_ref (new_flow_name);
    }
  if (fo_flow->flow_name != NULL)
    {
      g_object_unref (fo_flow->flow_name);
    }
  fo_flow->flow_name = new_flow_name;
  /*g_object_notify (G_OBJECT (fo_flow), "flow-name");*/
}
