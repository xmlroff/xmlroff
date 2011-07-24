/* Fo
 * fo-static-content.c: 'static-content' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-cbpbp-fo-private.h"
#include "fo/fo-static-content-private.h"
#include "fo/fo-static-content-area.h"
#include "fo/fo-simple-page-master.h"
#include "fo/fo-page-sequence.h"
#include "property/fo-property-flow-name.h"

enum {
  PROP_0,
  PROP_FLOW_NAME
};

static void fo_static_content_class_init  (FoStaticContentClass *klass);
static void fo_static_content_cbpbp_fo_init (FoCBPBPFoIface *iface);
static void fo_static_content_get_property (GObject      *object,
                                            guint         prop_id,
                                            GValue       *value,
                                            GParamSpec   *pspec);
static void fo_static_content_set_property (GObject      *object,
                                            guint         prop_id,
                                            const GValue *value,
                                            GParamSpec   *pspec);
static void fo_static_content_finalize    (GObject           *object);
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

static FoProperty * fo_static_content_get_background_color    (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_after_color  (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_after_style  (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_after_width  (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_before_color (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_before_style (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_before_width (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_end_color    (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_end_style    (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_end_width    (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_start_color  (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_start_style  (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_border_start_width  (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_padding_after       (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_padding_before      (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_padding_end         (FoFo *fo_static_content);
static FoProperty * fo_static_content_get_padding_start       (FoFo *fo_flow);

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
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      static const GInterfaceInfo fo_cbpbp_fo_info =
	{
	  (GInterfaceInitFunc) fo_static_content_cbpbp_fo_init,	 /* interface_init */
	  NULL,
	  NULL
	};

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoStaticContent",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_CBPBP_FO,
                                   &fo_cbpbp_fo_info);
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

  fofo_class->validate_content =
    fo_fo_validate_content_block_plus;
  fofo_class->validate2 =
    fo_static_content_validate;
  fofo_class->update_from_context = fo_static_content_update_from_context;
  fofo_class->debug_dump_properties = fo_static_content_debug_dump_properties;
  fofo_class->area_new2 = fo_static_content_area_new;
  fofo_class->get_area_fo =
    fo_static_content_get_region_master;

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
 * fo_static_content_cbpbp_fo_init:
 * @iface: #FoCBPBPFoIFace structure for this class.
 * 
 * Initialize #FoCBPBPFoIface interface for this class.
 **/
void
fo_static_content_cbpbp_fo_init (FoCBPBPFoIface *iface)
{
  iface->get_background_color = fo_static_content_get_background_color;
  iface->get_border_after_color = fo_static_content_get_border_after_color;
  iface->get_border_after_style = fo_static_content_get_border_after_style;
  iface->get_border_after_width = fo_static_content_get_border_after_width;
  iface->get_border_before_color = fo_static_content_get_border_before_color;
  iface->get_border_before_style = fo_static_content_get_border_before_style;
  iface->get_border_before_width = fo_static_content_get_border_before_width;
  iface->get_border_end_color = fo_static_content_get_border_end_color;
  iface->get_border_end_style = fo_static_content_get_border_end_style;
  iface->get_border_end_width = fo_static_content_get_border_end_width;
  iface->get_border_start_color = fo_static_content_get_border_start_color;
  iface->get_border_start_style = fo_static_content_get_border_start_style;
  iface->get_border_start_width = fo_static_content_get_border_start_width;
  iface->get_padding_after = fo_static_content_get_padding_after;
  iface->get_padding_before = fo_static_content_get_padding_before;
  iface->get_padding_end = fo_static_content_get_padding_end;
  iface->get_padding_start = fo_static_content_get_padding_start;
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
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_static_content_set_flow_name (fo, NULL);

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
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  FoStaticContent *fo_static_content = FO_STATIC_CONTENT (fo);

  FoDatatype *flow_name_datatype =
    fo_property_get_value (fo_static_content_get_flow_name (fo));

  if (flow_name_datatype == NULL) {
    g_set_error (error,
		 FO_FO_ERROR,
		 FO_FO_ERROR_DATATYPE_NULL,
		 _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE_NULL]),
		 "flow-name");
    return;
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
      fo_static_content->region_master = region_master;
    }
  else
    {
      g_assert_not_reached();
    }
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
 * fo_static_content_get_background_color:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #background-color property of @fo_static_content
 *
 * Return value: The "background-color" property value
**/
FoProperty *
fo_static_content_get_background_color (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_background_color (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_after_color:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-after-color property of @fo_static_content
 *
 * Return value: The "border-after-color" property value
**/
FoProperty *
fo_static_content_get_border_after_color (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_after_color (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_after_style:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-after-style property of @fo_static_content
 *
 * Return value: The "border-after-style" property value
**/
FoProperty *
fo_static_content_get_border_after_style (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_after_style (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_after_width:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-after-width property of @fo_static_content
 *
 * Return value: The "border-after-width" property value
**/
FoProperty *
fo_static_content_get_border_after_width (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_after_width (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_before_color:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-before-color property of @fo_static_content
 *
 * Return value: The "border-before-color" property value
**/
FoProperty *
fo_static_content_get_border_before_color (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_before_color (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_before_style:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-before-style property of @fo_static_content
 *
 * Return value: The "border-before-style" property value
**/
FoProperty *
fo_static_content_get_border_before_style (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_before_style (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_before_width:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-before-width property of @fo_static_content
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_static_content_get_border_before_width (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_before_width (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_end_color:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-end-color property of @fo_static_content
 *
 * Return value: The "border-end-color" property value
**/
FoProperty *
fo_static_content_get_border_end_color (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_end_color (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_end_style:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-end-style property of @fo_static_content
 *
 * Return value: The "border-end-style" property value
**/
FoProperty *
fo_static_content_get_border_end_style (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_end_style (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_end_width:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-end-width property of @fo_static_content
 *
 * Return value: The "border-end-width" property value
**/
FoProperty *
fo_static_content_get_border_end_width (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_end_width (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_start_color:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-start-color property of @fo_static_content
 *
 * Return value: The "border-start-color" property value
**/
FoProperty *
fo_static_content_get_border_start_color (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_start_color (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_start_style:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-start-style property of @fo_static_content
 *
 * Return value: The "border-start-style" property value
**/
FoProperty *
fo_static_content_get_border_start_style (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_start_style (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_border_start_width:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #border-start-width property of @fo_static_content
 *
 * Return value: The "border-start-width" property value
**/
FoProperty *
fo_static_content_get_border_start_width (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_border_start_width (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_padding_after:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #padding-after property of @fo_static_content
 *
 * Return value: The "padding-after" property value
**/
FoProperty *
fo_static_content_get_padding_after (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_padding_after (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_padding_before:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #padding-before property of @fo_static_content
 *
 * Return value: The "padding-before" property value
**/
FoProperty *
fo_static_content_get_padding_before (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_padding_before (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_padding_end:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #padding-end property of @fo_static_content
 *
 * Return value: The "padding-end" property value
**/
FoProperty *
fo_static_content_get_padding_end (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_padding_end (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_padding_start:
 * @fo_static_content: The #FoStaticContent object
 *
 * Gets the #padding-start property of @fo_static_content
 *
 * Return value: The "padding-start" property value
**/
FoProperty *
fo_static_content_get_padding_start (FoFo *fo_static_content)
{
  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_cbpbp_fo_get_padding_start (fo_static_content_get_region_master (fo_static_content));
}

/**
 * fo_static_content_get_region_master:
 * @fo_fo: The #FoStaticContent object
 *
 * Gets the #region_master instance variable of @static_content
 *
 * Return value: The "region_master" value
**/
FoFo *
fo_static_content_get_region_master (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_fo), NULL);

  return FO_STATIC_CONTENT (fo_fo)->region_master;
}

/*
 * These get/set functions are completely auto-generated.
 */

/**
 * fo_static_content_get_flow_name:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "flow-name" property of @fo_fo.
 *
 * Return value: The "flow-name" property value.
**/
FoProperty *
fo_static_content_get_flow_name (FoFo *fo_fo)
{
  FoStaticContent *fo_static_content = (FoStaticContent *) fo_fo;

  g_return_val_if_fail (fo_static_content != NULL, NULL);
  g_return_val_if_fail (FO_IS_STATIC_CONTENT (fo_static_content), NULL);

  return fo_static_content->flow_name;
}

/**
 * fo_static_content_set_flow_name:
 * @fo_fo: The #FoFo object.
 * @new_flow_name: The new "flow-name" property value.
 * 
 * Sets the "flow-name" property of @fo_fo to @new_flow_name.
 **/
void
fo_static_content_set_flow_name (FoFo *fo_fo,
		         FoProperty *new_flow_name)
{
  FoStaticContent *fo_static_content = (FoStaticContent *) fo_fo;

  g_return_if_fail (fo_static_content != NULL);
  g_return_if_fail (FO_IS_STATIC_CONTENT (fo_static_content));
  g_return_if_fail ((new_flow_name == NULL) ||
		    FO_IS_PROPERTY_FLOW_NAME (new_flow_name));

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
