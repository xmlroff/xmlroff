/* Fo
 * fo-flow.c: 'flow' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-cbpbp-fo-private.h"
#include "fo/fo-flow-private.h"
#include "property/fo-property-flow-name.h"
#include "fo/fo-flow-area.h"
#include "fo/fo-simple-page-master.h"
#include "fo/fo-page-sequence.h"
#include "fo/fo-region-body.h"
#include "fo/fo-region.h"

enum {
  PROP_0,
  PROP_FLOW_NAME
};

static void _class_init            (FoFlowClass    *klass);
static void _cbpbp_fo_init         (FoCBPBPFoIface *iface);
static void _get_property          (GObject        *object,
				    guint           prop_id,
				    GValue         *value,
				    GParamSpec     *pspec);
static void _set_property          (GObject        *object,
				    guint           prop_id,
				    const GValue   *value,
				    GParamSpec     *pspec);
static void _dispose               (GObject        *object);
static gboolean _validate_content  (FoFo           *fo,
				    GError        **error);
static void _validate              (FoFo           *fo,
				    FoContext      *current_context,
				    FoContext      *parent_context,
				    GError        **error);
static void _update_from_context   (FoFo           *fo,
				    FoContext      *context);
static void _debug_dump_properties (FoFo           *fo,
				    gint            depth);

/* Functions implementing FoCBPBPFo interface. */
static FoProperty * fo_flow_get_background_color    (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_after_color  (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_after_style  (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_after_width  (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_before_color (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_before_style (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_before_width (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_end_color    (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_end_style    (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_end_width    (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_start_color  (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_start_style  (FoFo *fo_flow);
static FoProperty * fo_flow_get_border_start_width  (FoFo *fo_flow);
static FoProperty * fo_flow_get_padding_after       (FoFo *fo_flow);
static FoProperty * fo_flow_get_padding_before      (FoFo *fo_flow);
static FoProperty * fo_flow_get_padding_end         (FoFo *fo_flow);
static FoProperty * fo_flow_get_padding_start       (FoFo *fo_flow);

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
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoFlow),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
        };

      static const GInterfaceInfo fo_cbpbp_fo_info =
	{
	  (GInterfaceInitFunc) _cbpbp_fo_init,	 /* interface_init */
	  NULL,
	  NULL
	};

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoFlow",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_CBPBP_FO,
                                   &fo_cbpbp_fo_info);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoFlowClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoFlowClass.
 **/
static void
_class_init (FoFlowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->dispose = _dispose;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  fofo_class->validate_content =
    _validate_content;
  fofo_class->validate2 =
    _validate;
  fofo_class->update_from_context = _update_from_context;
  fofo_class->debug_dump_properties = _debug_dump_properties;
  fofo_class->area_new2 = fo_flow_area_new2;
  fofo_class->get_area_fo =
    fo_flow_get_region_master;

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
 * _cbpbp_fo_init:
 * @iface: #FoCBPBPFoIFace structure for this class.
 * 
 * Initialize #FoCBPBPFoIface interface for this class.
 **/
static void
_cbpbp_fo_init (FoCBPBPFoIface *iface)
{
  iface->get_background_color = fo_flow_get_background_color;
  iface->get_border_after_color = fo_flow_get_border_after_color;
  iface->get_border_after_style = fo_flow_get_border_after_style;
  iface->get_border_after_width = fo_flow_get_border_after_width;
  iface->get_border_before_color = fo_flow_get_border_before_color;
  iface->get_border_before_style = fo_flow_get_border_before_style;
  iface->get_border_before_width = fo_flow_get_border_before_width;
  iface->get_border_end_color = fo_flow_get_border_end_color;
  iface->get_border_end_style = fo_flow_get_border_end_style;
  iface->get_border_end_width = fo_flow_get_border_end_width;
  iface->get_border_start_color = fo_flow_get_border_start_color;
  iface->get_border_start_style = fo_flow_get_border_start_style;
  iface->get_border_start_width = fo_flow_get_border_start_width;
  iface->get_padding_after = fo_flow_get_padding_after;
  iface->get_padding_before = fo_flow_get_padding_before;
  iface->get_padding_end = fo_flow_get_padding_end;
  iface->get_padding_start = fo_flow_get_padding_start;
}

/**
 * _dispose:
 * @object: #FoFlow object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoFlow.
 **/
static void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_flow_set_flow_name (fo, NULL);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoFlow.
 **/
void
_get_property (GObject    *object,
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
 * set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoFlow.
 **/
void
_set_property (GObject      *object,
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
 * _validate_content:
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
_validate_content (FoFo    *fo,
		   GError **error)
{
  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_FLOW (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  return fo_fo_validate_content_block_plus (fo, error);
}

/**
 * _validate:
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
_validate (FoFo      *fo,
	   FoContext *current_context,
	   FoContext *parent_context,
	   GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FLOW (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  FoFlow *fo_flow = FO_FLOW (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  FoDatatype *flow_name_datatype =
    fo_property_get_value (fo_flow_get_flow_name (fo));

  if (flow_name_datatype == NULL) {
    g_set_error (error,
		 FO_FO_ERROR,
		 FO_FO_ERROR_DATATYPE_NULL,
		 _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE_NULL]),
		 "flow-name");
  }

  gchar *flow_name =
    fo_name_get_value (flow_name_datatype);

  FoFo *page_sequence =
    FO_FO (fo_node_parent (FO_NODE (fo)));

  FoFo *region_master = NULL;
  if (page_sequence != NULL)
    {
      region_master =
	fo_simple_page_master_region_name_get (fo_page_sequence_get_page_master (page_sequence),
					       flow_name);
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

  g_free (flow_name);

  fo_context_set_writing_mode (current_context,
			       fo_region_get_writing_mode (fo_flow->region_master));

}

/**
 * _update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
_update_from_context (FoFo      *fo,
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
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
_debug_dump_properties (FoFo *fo,
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
 * fo_flow_get_background_color:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #background-color property of @fo_flow
 *
 * Return value: The "background-color" property value
**/
FoProperty *
fo_flow_get_background_color (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_background_color (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_after_color:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-after-color property of @fo_flow
 *
 * Return value: The "border-after-color" property value
**/
FoProperty *
fo_flow_get_border_after_color (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_after_color (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_after_style:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-after-style property of @fo_flow
 *
 * Return value: The "border-after-style" property value
**/
FoProperty *
fo_flow_get_border_after_style (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_after_style (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_after_width:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-after-width property of @fo_flow
 *
 * Return value: The "border-after-width" property value
**/
FoProperty *
fo_flow_get_border_after_width (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_after_width (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_before_color:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-before-color property of @fo_flow
 *
 * Return value: The "border-before-color" property value
**/
FoProperty *
fo_flow_get_border_before_color (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_before_color (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_before_style:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-before-style property of @fo_flow
 *
 * Return value: The "border-before-style" property value
**/
FoProperty *
fo_flow_get_border_before_style (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_before_style (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_before_width:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-before-width property of @fo_flow
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_flow_get_border_before_width (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_before_width (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_end_color:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-end-color property of @fo_flow
 *
 * Return value: The "border-end-color" property value
**/
FoProperty *
fo_flow_get_border_end_color (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_end_color (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_end_style:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-end-style property of @fo_flow
 *
 * Return value: The "border-end-style" property value
**/
FoProperty *
fo_flow_get_border_end_style (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_end_style (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_end_width:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-end-width property of @fo_flow
 *
 * Return value: The "border-end-width" property value
**/
FoProperty *
fo_flow_get_border_end_width (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_end_width (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_start_color:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-start-color property of @fo_flow
 *
 * Return value: The "border-start-color" property value
**/
FoProperty *
fo_flow_get_border_start_color (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_start_color (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_start_style:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-start-style property of @fo_flow
 *
 * Return value: The "border-start-style" property value
**/
FoProperty *
fo_flow_get_border_start_style (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_start_style (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_border_start_width:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #border-start-width property of @fo_flow
 *
 * Return value: The "border-start-width" property value
**/
FoProperty *
fo_flow_get_border_start_width (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_border_start_width (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_padding_after:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #padding-after property of @fo_flow
 *
 * Return value: The "padding-after" property value
**/
FoProperty *
fo_flow_get_padding_after (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_padding_after (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_padding_before:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #padding-before property of @fo_flow
 *
 * Return value: The "padding-before" property value
**/
FoProperty *
fo_flow_get_padding_before (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_padding_before (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_padding_end:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #padding-end property of @fo_flow
 *
 * Return value: The "padding-end" property value
**/
FoProperty *
fo_flow_get_padding_end (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_padding_end (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_padding_start:
 * @fo_flow: The @FoFlow object
 *
 * Gets the #padding-start property of @fo_flow
 *
 * Return value: The "padding-start" property value
**/
FoProperty *
fo_flow_get_padding_start (FoFo *fo_flow)
{
  g_return_val_if_fail (fo_flow != NULL, NULL);
  g_return_val_if_fail (FO_IS_FLOW (fo_flow), NULL);

  return fo_cbpbp_fo_get_padding_start (fo_flow_get_region_master (fo_flow));
}

/**
 * fo_flow_get_region_master:
 * @fo_fo: The @FoFlow object
 *
 * Gets the #region_master instance variable of @flow
 *
 * Return value: The "region_master" value
**/
FoFo *
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
FoProperty *
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
  g_return_if_fail ((new_flow_name == NULL) ||
		    FO_IS_PROPERTY_FLOW_NAME (new_flow_name));

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
