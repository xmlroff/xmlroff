/* Fo
 * fo-region-body.c: 'region-body' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-region-body-private.h"
#include "fo/fo-region-body-area.h"
#include "fo-context-util.h"
#include "fo/fo-simple-page-master.h"
#include "property/fo-property-border.h"
#include "property/fo-property-padding.h"
#include "property/fo-property-margin.h"
#include "property/fo-property-end-indent.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-region-name.h"
#include "property/fo-property-space-after.h"
#include "property/fo-property-space-before.h"
#include "property/fo-property-start-indent.h"

enum {
  PROP_0,
  PROP_END_INDENT,
  PROP_MARGIN_BOTTOM,
  PROP_MARGIN_LEFT,
  PROP_MARGIN_RIGHT,
  PROP_MARGIN_TOP,
  PROP_SPACE_AFTER,
  PROP_SPACE_BEFORE,
  PROP_START_INDENT
};

static void fo_region_body_class_init  (FoRegionBodyClass *klass);
static void fo_region_body_get_property (GObject      *object,
                                         guint         prop_id,
                                         GValue       *value,
                                         GParamSpec   *pspec);
static void fo_region_body_set_property (GObject      *object,
                                         guint         prop_id,
                                         const GValue *value,
                                         GParamSpec   *pspec);
static void fo_region_body_finalize    (GObject           *object);
static void fo_region_body_validate (FoFo      *fo,
                                     FoContext *current_context,
                                     FoContext *parent_context,
                                     GError   **error);
static void fo_region_body_update_from_context (FoFo      *fo,
                                                FoContext *context);
static void fo_region_body_debug_dump_properties (FoFo *fo,
                                                  gint  depth);

static gpointer parent_class;

/**
 * fo_region_body_get_type:
 * 
 * Register the #FoRegionBody object type.
 * 
 * Return value: #GType value of the #FoRegionBody object type.
 **/
GType
fo_region_body_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoRegionBodyClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) fo_region_body_class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRegionBody),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_REGION,
                                            "FoRegionBody",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_region_body_class_init:
 * @klass: #FoRegionBodyClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRegionBodyClass.
 **/
void
fo_region_body_class_init (FoRegionBodyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_region_body_finalize;

  object_class->get_property = fo_region_body_get_property;
  object_class->set_property = fo_region_body_set_property;

  fofo_class->validate_content =
    fo_fo_validate_content_empty;
  fofo_class->validate2 =
    fo_region_body_validate;
  fofo_class->update_from_context = fo_region_body_update_from_context;
  fofo_class->debug_dump_properties = fo_region_body_debug_dump_properties;
  fofo_class->generate_reference_area = TRUE;
  fofo_class->area_new2 =
    fo_region_body_area_new;

  g_object_class_install_property
    (object_class,
     PROP_END_INDENT,
     g_param_spec_object ("end-indent",
			  _("End Indent"),
			  _("End Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_BOTTOM,
     g_param_spec_object ("margin-bottom",
			  _("Margin Bottom"),
			  _("Margin Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_LEFT,
     g_param_spec_object ("margin-left",
			  _("Margin Left"),
			  _("Margin Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_RIGHT,
     g_param_spec_object ("margin-right",
			  _("Margin Right"),
			  _("Margin Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_TOP,
     g_param_spec_object ("margin-top",
			  _("Margin Top"),
			  _("Margin Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER,
     g_param_spec_object ("space-after",
			  _("Space After"),
			  _("Space After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE,
     g_param_spec_object ("space-before",
			  _("Space Before"),
			  _("Space Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_START_INDENT,
     g_param_spec_object ("start-indent",
			  _("Start Indent"),
			  _("Start Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_region_body_finalize:
 * @object: #FoRegionBody object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRegionBody.
 **/
void
fo_region_body_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_region_body_set_end_indent (fo, NULL);
  fo_region_body_set_margin_bottom (fo, NULL);
  fo_region_body_set_margin_left (fo, NULL);
  fo_region_body_set_margin_right (fo, NULL);
  fo_region_body_set_margin_top (fo, NULL);
  fo_region_body_set_space_after (fo, NULL);
  fo_region_body_set_space_before (fo, NULL);
  fo_region_body_set_start_indent (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_region_body_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRegionBody.
 **/
void
fo_region_body_get_property (GObject    *object,
                             guint       prop_id,
                             GValue     *value,
                             GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_END_INDENT:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_end_indent (fo_fo)));
      break;
    case PROP_MARGIN_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_margin_bottom (fo_fo)));
      break;
    case PROP_MARGIN_LEFT:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_margin_left (fo_fo)));
      break;
    case PROP_MARGIN_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_margin_right (fo_fo)));
      break;
    case PROP_MARGIN_TOP:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_margin_top (fo_fo)));
      break;
    case PROP_SPACE_AFTER:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_space_after (fo_fo)));
      break;
    case PROP_SPACE_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_space_before (fo_fo)));
      break;
    case PROP_START_INDENT:
      g_value_set_object (value, G_OBJECT (fo_region_body_get_start_indent (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_body_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRegionBody.
 **/
void
fo_region_body_set_property (GObject      *object,
                             guint         prop_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_END_INDENT:
      fo_region_body_set_end_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_BOTTOM:
      fo_region_body_set_margin_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_LEFT:
      fo_region_body_set_margin_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_RIGHT:
      fo_region_body_set_margin_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_TOP:
      fo_region_body_set_margin_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER:
      fo_region_body_set_space_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE:
      fo_region_body_set_space_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_START_INDENT:
      fo_region_body_set_start_indent (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_body_new:
 * 
 * Creates a new #FoRegionBody initialized to default value.
 * 
 * Return value: the new #FoRegionBody.
 **/
FoFo*
fo_region_body_new (void)
{
  return FO_FO (g_object_new (fo_region_body_get_type (),
                              NULL));
}

/**
 * fo_region_body_validate:
 * @fo:              #FoRegionBody object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_region_body_validate (FoFo      *fo,
                         FoContext *current_context,
                         FoContext *parent_context,
                         GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_context_util_border_resolve (current_context, parent_context);
  fo_context_util_paddings_resolve (current_context, parent_context);
  fo_context_util_margins_indents_resolve (fo,
					   current_context,
					   parent_context);
  fo_context_util_margins_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  FoDatatype *region_name_datatype =
    fo_property_get_value (fo_region_get_region_name (fo));

  gchar *region_name = NULL;
  if (region_name_datatype != NULL)
    {
      region_name =
	fo_name_get_value (region_name_datatype);
    }
  else
    {
      /* Need a freeable string because g_free() needed
	 if name had come from fo_name_get_value(). */
      region_name = g_strdup ("xsl-region-body");

      /* Also set the 'region-name' property to its default. */
      region_name_datatype =
	fo_name_new_with_value (region_name);
      FoProperty *region_name_prop =
	fo_property_region_name_new ();
      fo_property_set_value (region_name_prop,
			     region_name_datatype);
      fo_region_set_region_name (fo,
				 region_name_prop);
    }

  FoFo *simple_page_master = FO_FO (fo_node_parent (FO_NODE (fo)));

  if (simple_page_master != NULL)
    {
      fo_simple_page_master_set_region_body (simple_page_master,
					     fo);
    }
  else
    {
      g_assert_not_reached();
    }

  g_free (region_name);
}

/**
 * fo_region_body_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_region_body_update_from_context (FoFo      *fo,
                                    FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);

  fo_region_body_set_end_indent (fo,
			  fo_context_get_end_indent (context));
  fo_region_body_set_margin_bottom (fo,
			  fo_context_get_margin_bottom (context));
  fo_region_body_set_margin_left (fo,
			  fo_context_get_margin_left (context));
  fo_region_body_set_margin_right (fo,
			  fo_context_get_margin_right (context));
  fo_region_body_set_margin_top (fo,
			  fo_context_get_margin_top (context));
  fo_region_body_set_space_after (fo,
			  fo_context_get_space_after (context));
  fo_region_body_set_space_before (fo,
			  fo_context_get_space_before (context));
  fo_region_body_set_start_indent (fo,
			  fo_context_get_start_indent (context));
}

/**
 * fo_region_body_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_region_body_debug_dump_properties (FoFo *fo,
                                      gint  depth)
{
  FoRegionBody *fo_region_body;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo));

  fo_region_body = FO_REGION_BODY (fo);

  fo_object_debug_dump (fo_region_body->end_indent, depth);
  fo_object_debug_dump (fo_region_body->margin_bottom, depth);
  fo_object_debug_dump (fo_region_body->margin_left, depth);
  fo_object_debug_dump (fo_region_body->margin_right, depth);
  fo_object_debug_dump (fo_region_body->margin_top, depth);
  fo_object_debug_dump (fo_region_body->space_after, depth);
  fo_object_debug_dump (fo_region_body->space_before, depth);
  fo_object_debug_dump (fo_region_body->start_indent, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_region_body_get_end_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "end-indent" property of @fo_fo.
 *
 * Return value: The "end-indent" property value.
**/
FoProperty *
fo_region_body_get_end_indent (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->end_indent;
}

/**
 * fo_region_body_set_end_indent:
 * @fo_fo: The #FoFo object.
 * @new_end_indent: The new "end-indent" property value.
 * 
 * Sets the "end-indent" property of @fo_fo to @new_end_indent.
 **/
void
fo_region_body_set_end_indent (FoFo *fo_fo,
		         FoProperty *new_end_indent)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_end_indent == NULL) ||
		    FO_IS_PROPERTY_END_INDENT (new_end_indent));

  if (new_end_indent != NULL)
    {
      g_object_ref (new_end_indent);
    }
  if (fo_region_body->end_indent != NULL)
    {
      g_object_unref (fo_region_body->end_indent);
    }
  fo_region_body->end_indent = new_end_indent;
  /*g_object_notify (G_OBJECT (fo_region_body), "end-indent");*/
}

/**
 * fo_region_body_get_margin_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-bottom" property of @fo_fo.
 *
 * Return value: The "margin-bottom" property value.
**/
FoProperty *
fo_region_body_get_margin_bottom (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->margin_bottom;
}

/**
 * fo_region_body_set_margin_bottom:
 * @fo_fo: The #FoFo object.
 * @new_margin_bottom: The new "margin-bottom" property value.
 * 
 * Sets the "margin-bottom" property of @fo_fo to @new_margin_bottom.
 **/
void
fo_region_body_set_margin_bottom (FoFo *fo_fo,
		         FoProperty *new_margin_bottom)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_margin_bottom == NULL) ||
		    FO_IS_PROPERTY_MARGIN_BOTTOM (new_margin_bottom));

  if (new_margin_bottom != NULL)
    {
      g_object_ref (new_margin_bottom);
    }
  if (fo_region_body->margin_bottom != NULL)
    {
      g_object_unref (fo_region_body->margin_bottom);
    }
  fo_region_body->margin_bottom = new_margin_bottom;
  /*g_object_notify (G_OBJECT (fo_region_body), "margin-bottom");*/
}

/**
 * fo_region_body_get_margin_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-left" property of @fo_fo.
 *
 * Return value: The "margin-left" property value.
**/
FoProperty *
fo_region_body_get_margin_left (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->margin_left;
}

/**
 * fo_region_body_set_margin_left:
 * @fo_fo: The #FoFo object.
 * @new_margin_left: The new "margin-left" property value.
 * 
 * Sets the "margin-left" property of @fo_fo to @new_margin_left.
 **/
void
fo_region_body_set_margin_left (FoFo *fo_fo,
		         FoProperty *new_margin_left)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_margin_left == NULL) ||
		    FO_IS_PROPERTY_MARGIN_LEFT (new_margin_left));

  if (new_margin_left != NULL)
    {
      g_object_ref (new_margin_left);
    }
  if (fo_region_body->margin_left != NULL)
    {
      g_object_unref (fo_region_body->margin_left);
    }
  fo_region_body->margin_left = new_margin_left;
  /*g_object_notify (G_OBJECT (fo_region_body), "margin-left");*/
}

/**
 * fo_region_body_get_margin_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-right" property of @fo_fo.
 *
 * Return value: The "margin-right" property value.
**/
FoProperty *
fo_region_body_get_margin_right (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->margin_right;
}

/**
 * fo_region_body_set_margin_right:
 * @fo_fo: The #FoFo object.
 * @new_margin_right: The new "margin-right" property value.
 * 
 * Sets the "margin-right" property of @fo_fo to @new_margin_right.
 **/
void
fo_region_body_set_margin_right (FoFo *fo_fo,
		         FoProperty *new_margin_right)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_margin_right == NULL) ||
		    FO_IS_PROPERTY_MARGIN_RIGHT (new_margin_right));

  if (new_margin_right != NULL)
    {
      g_object_ref (new_margin_right);
    }
  if (fo_region_body->margin_right != NULL)
    {
      g_object_unref (fo_region_body->margin_right);
    }
  fo_region_body->margin_right = new_margin_right;
  /*g_object_notify (G_OBJECT (fo_region_body), "margin-right");*/
}

/**
 * fo_region_body_get_margin_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-top" property of @fo_fo.
 *
 * Return value: The "margin-top" property value.
**/
FoProperty *
fo_region_body_get_margin_top (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->margin_top;
}

/**
 * fo_region_body_set_margin_top:
 * @fo_fo: The #FoFo object.
 * @new_margin_top: The new "margin-top" property value.
 * 
 * Sets the "margin-top" property of @fo_fo to @new_margin_top.
 **/
void
fo_region_body_set_margin_top (FoFo *fo_fo,
		         FoProperty *new_margin_top)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_margin_top == NULL) ||
		    FO_IS_PROPERTY_MARGIN_TOP (new_margin_top));

  if (new_margin_top != NULL)
    {
      g_object_ref (new_margin_top);
    }
  if (fo_region_body->margin_top != NULL)
    {
      g_object_unref (fo_region_body->margin_top);
    }
  fo_region_body->margin_top = new_margin_top;
  /*g_object_notify (G_OBJECT (fo_region_body), "margin-top");*/
}

/**
 * fo_region_body_get_space_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-after" property of @fo_fo.
 *
 * Return value: The "space-after" property value.
**/
FoProperty *
fo_region_body_get_space_after (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->space_after;
}

/**
 * fo_region_body_set_space_after:
 * @fo_fo: The #FoFo object.
 * @new_space_after: The new "space-after" property value.
 * 
 * Sets the "space-after" property of @fo_fo to @new_space_after.
 **/
void
fo_region_body_set_space_after (FoFo *fo_fo,
		         FoProperty *new_space_after)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_space_after == NULL) ||
		    FO_IS_PROPERTY_SPACE_AFTER (new_space_after));

  if (new_space_after != NULL)
    {
      g_object_ref (new_space_after);
    }
  if (fo_region_body->space_after != NULL)
    {
      g_object_unref (fo_region_body->space_after);
    }
  fo_region_body->space_after = new_space_after;
  /*g_object_notify (G_OBJECT (fo_region_body), "space-after");*/
}

/**
 * fo_region_body_get_space_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-before" property of @fo_fo.
 *
 * Return value: The "space-before" property value.
**/
FoProperty *
fo_region_body_get_space_before (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->space_before;
}

/**
 * fo_region_body_set_space_before:
 * @fo_fo: The #FoFo object.
 * @new_space_before: The new "space-before" property value.
 * 
 * Sets the "space-before" property of @fo_fo to @new_space_before.
 **/
void
fo_region_body_set_space_before (FoFo *fo_fo,
		         FoProperty *new_space_before)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_space_before == NULL) ||
		    FO_IS_PROPERTY_SPACE_BEFORE (new_space_before));

  if (new_space_before != NULL)
    {
      g_object_ref (new_space_before);
    }
  if (fo_region_body->space_before != NULL)
    {
      g_object_unref (fo_region_body->space_before);
    }
  fo_region_body->space_before = new_space_before;
  /*g_object_notify (G_OBJECT (fo_region_body), "space-before");*/
}

/**
 * fo_region_body_get_start_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "start-indent" property of @fo_fo.
 *
 * Return value: The "start-indent" property value.
**/
FoProperty *
fo_region_body_get_start_indent (FoFo *fo_fo)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_val_if_fail (fo_region_body != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BODY (fo_region_body), NULL);

  return fo_region_body->start_indent;
}

/**
 * fo_region_body_set_start_indent:
 * @fo_fo: The #FoFo object.
 * @new_start_indent: The new "start-indent" property value.
 * 
 * Sets the "start-indent" property of @fo_fo to @new_start_indent.
 **/
void
fo_region_body_set_start_indent (FoFo *fo_fo,
		         FoProperty *new_start_indent)
{
  FoRegionBody *fo_region_body = (FoRegionBody *) fo_fo;

  g_return_if_fail (fo_region_body != NULL);
  g_return_if_fail (FO_IS_REGION_BODY (fo_region_body));
  g_return_if_fail ((new_start_indent == NULL) ||
		    FO_IS_PROPERTY_START_INDENT (new_start_indent));

  if (new_start_indent != NULL)
    {
      g_object_ref (new_start_indent);
    }
  if (fo_region_body->start_indent != NULL)
    {
      g_object_unref (fo_region_body->start_indent);
    }
  fo_region_body->start_indent = new_start_indent;
  /*g_object_notify (G_OBJECT (fo_region_body), "start-indent");*/
}
