/* Fo
 * fo-property.h: FoProperty superclass of all property classes
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property.c,v 1.10 2006/07/25 20:00:21 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-object.h"
#include "fo-all-datatype.h"
#include "fo-context.h"
#include "fo-property-private.h"
#include "fo-property-font-size.h"
/*#include <expression-parser.h>*/

const gchar *fo_property_error_messages [] = {
  N_("Property error."),
  N_("Property expression evaluation failed."),
  N_("Attempt to convert to enumeration value when property has no values defined."),
  N_("Values of '%s' property cannot be negative: %s"),
  N_("Value of property '%s' should not be zero-length.")
};

enum {
  PROP_0,
  PROP_VALUE
};

static void fo_property_base_init  (FoPropertyClass *klass);
static void fo_property_base_finalize  (FoPropertyClass *klass);
static void fo_property_class_init  (FoPropertyClass *klass);
static void fo_property_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_property_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_property_finalize    (GObject           *object);

static FoDatatype* fo_property_get_value_default (FoProperty *property);
static void        fo_property_set_value_default (FoProperty *property,
					       FoDatatype *new_value);
static FoDatatype* fo_property_resolve_enum_default (const gchar *token,
						     FoContext   *context,
						     GError     **error);
static FoDatatype* fo_property_resolve_percent_default (gdouble           percentage,
							const FoDatatype *font_size,
							const FoFo       *fo_node,
							const FoContext  *context,
							GError          **err);
static FoProperty* fo_property_new_from_expr_default (FoPropertyClass *property_class,
						      const gchar *expr,
						      FoContext   *context,
						      FoProperty    *current_font_size,
						      FoFo *fo_node,
						      GError **error);
gchar* fo_property_sprintf         (FoObject *object);
static void fo_property_debug_dump (FoObject *object,
				    gint      depth);
static gpointer parent_class;

GQuark
fo_property_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("Property error");
  return quark;
}

/**
 * fo_property_get_type:
 * 
 * Register the #FoProperty object type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType value of the #FoProperty object type.
 **/
GType
fo_property_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyClass),
        (GBaseInitFunc) fo_property_base_init,
        (GBaseFinalizeFunc) fo_property_base_finalize,
        (GClassInitFunc) fo_property_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoProperty),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoProperty",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * fo_property_base_init:
 * @klass: #FoPropertyClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyClass.
 **/
void
fo_property_base_init (FoPropertyClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);

  klass->is_inherited = FALSE;
  klass->is_shorthand = FALSE;
  klass->expr_env_list = fo_expr_env_list_new ();
  klass->new_from_expr = fo_property_new_from_expr_default;
  klass->expr_eval = fo_expr_eval;
  klass->set_value = fo_property_set_value_default;
  klass->get_value = fo_property_get_value_default;
  klass->resolve_percent = fo_property_resolve_percent_default;

  fo_object_class->print_sprintf = fo_property_sprintf;
  fo_object_class->debug_dump = fo_property_debug_dump;
}

/**
 * fo_property_base_finalize:
 * @klass: #FoPropertyClass object to finalise.
 * 
 * Implements #GBaseFinalizeFunc for #FoPropertyClass.
 **/
void
fo_property_base_finalize (FoPropertyClass *klass)
{
  fo_expr_env_list_free (klass->expr_env_list);
}

/**
 * fo_property_class_init:
 * @klass: #FoPropertyClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyClass.
 **/
void
fo_property_class_init (FoPropertyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_property_finalize;

  object_class->set_property = fo_property_set_property;
  object_class->get_property = fo_property_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_object ("value",
							_("property value"),
							_("Property value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE));

  klass->resolve_enum = fo_property_resolve_enum_default;
}

/**
 * fo_property_finalize:
 * @object: #FoProperty object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoProperty.
 **/
void
fo_property_finalize (GObject *object)
{
  FoProperty *property;

  property = FO_PROPERTY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoProperty.
 **/
void
fo_property_set_property (GObject         *object,
			  guint            prop_id,
			  const GValue    *value,
			  GParamSpec      *pspec)
{
  FoProperty *property;

  property = FO_PROPERTY (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_property_set_value (property, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_property_get_property:
 * @object:  #GObject whose property will be retreived.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoProperty.
 **/
void
fo_property_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoProperty *property;

  property = FO_PROPERTY (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_instance (value,
			  fo_property_get_value (property));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_property_new:
 * 
 * Creates a new #FoProperty initialized to default value.
 * 
 * Return value: the new #FoProperty.
 **/
FoProperty*
fo_property_new (void)
{
  FoProperty *property;

  property = FO_PROPERTY (g_object_new (fo_property_get_type (), NULL));
  
  return property;
}


/**
 * fo_property_get_value:
 * @property: #FoProperty object whose value is to be retrieved.
 * 
 * Returns the current value property value of @property.
 * 
 * Return value: The current 'value' property value.
 **/
FoDatatype*
fo_property_get_value (FoProperty *property)
{
  g_return_val_if_fail (property != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY (property), NULL);

  return FO_PROPERTY_GET_CLASS (property)->get_value (property);
}

/**
 * fo_property_set_value:
 * @property:  #FoProperty object whose value is to be set.
 * @new_value: New value for the property.
 * 
 * Sets the 'value' property of @property.
 **/
void
fo_property_set_value (FoProperty *property,
		       FoDatatype *new_value)
{
  g_return_if_fail (property != NULL);
  g_return_if_fail (FO_IS_PROPERTY (property));

  FO_PROPERTY_GET_CLASS (property)->set_value (property, new_value);
}

/**
 * fo_property_get_value_default:
 * @property: FoProperty object whose value is to be retrieved
 * 
 * Returns the current #value property value of @property
 * 
 * Return value: The current #value property value
 **/
FoDatatype*
fo_property_get_value_default (FoProperty *property)
{
  g_return_val_if_fail (property != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY (property), NULL);

  return property->value;
}

/**
 * fo_property_set_value_default:
 * @property:  FoProperty object whose value is to be set
 * @new_value: New value for the property
 * 
 * Sets the #value property of @property
 **/
void
fo_property_set_value_default (FoProperty *property,
			       FoDatatype *new_value)
{
  g_return_if_fail (property != NULL);
  g_return_if_fail (FO_IS_PROPERTY (property));
  g_return_if_fail (new_value == NULL || FO_IS_DATATYPE (new_value));

  if (new_value != NULL)
    g_object_ref (G_OBJECT (new_value));
  if (property->value != NULL)
    g_object_unref (G_OBJECT (property->value));
  property->value = new_value;
  /*g_object_notify(G_OBJECT(property), "value");*/
}

/**
 * fo_property_resolve_enum_default:
 * @token: 
 * @context: 
 * @error: 
 * 
 * 
 * 
 * Return value: 
 **/
FoDatatype*
fo_property_resolve_enum_default (const gchar *token,
				  FoContext   *context,
				  GError     **error)
{
  g_warning ("This property doesn't have any enumerated values.\n");

  g_set_error (error,
	       FO_PROPERTY_ERROR,
	       FO_PROPERTY_ERROR_NO_ENUMERATION,
	       fo_property_error_messages[FO_PROPERTY_ERROR_NO_ENUMERATION]);
  return NULL;
}

/**
 * fo_property_resolve_percent_default:
 * @percentage: Percentage value to resolve.
 * @font_size:  Font size to use if a percentage of font-size.
 * @fo_node:    Current #FoFo.
 * @context:    #FoContext of parent #FoFo.
 * @err:        Indicates whether an error occurs.
 * 
 * Resolves @percentage as a percentage of a known value which,
 * depending on the property, could be the current font-size value or
 * some property value of the current #FoFo or its first #FoArea.
 * 
 * Return value: #FoDatatype representing resolved value.
 **/
FoDatatype*
fo_property_resolve_percent_default (gdouble            percentage,
				     const FoDatatype  *font_size,
				     const FoFo        *fo_node,
				     const FoContext   *context,
				     GError           **err)
{
  FoDatatype *percentage_datatype;

  percentage_datatype = fo_percentage_new ();
  fo_percentage_set_value (percentage_datatype,
			   percentage);

  return percentage_datatype;
}

/**
 * fo_property_new_from_string:
 * @property_class:    #FoPropertyClass or subclass of property.
 * @expr:              Expression to be evaluated as a string.
 * @context:           #FoContext for inherited values.
 * @current_font_size: Current font size for resolving 'em' values.
 * @fo_node:           The current #FoFo node.
 * @error:             #GError for indicating any error that occurs.
 * 
 * Evaluate @expr and create a new instance of @property_class with
 * value of @expr.
 *
 * Other parameters (except @error) provide context for evaluating
 * @expr.
 * 
 * Return value: A new instance of @property_class, or NULL if error.
 **/
FoProperty*
fo_property_new_from_string (FoPropertyClass *property_class,
			     const gchar *expr,
			     FoContext   *context,
			     FoProperty    *current_font_size,
			     FoFo *fo_node,
			     GError **error)
{
  FoProperty *property;
  FoDatatype *datatype;
  GError *tmp_error = NULL;
  const gchar *property_name = NULL;

  g_return_val_if_fail (FO_IS_PROPERTY_CLASS (property_class), NULL);
  g_return_val_if_fail (expr != NULL, NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail
    (current_font_size == NULL || FO_IS_PROPERTY_FONT_SIZE (current_font_size),
     NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  property_name = G_OBJECT_CLASS_NAME (property_class);

  datatype = fo_string_new_with_value (expr);

  datatype = property_class->validate (datatype, context, &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (error, tmp_error);
      return NULL;
    }

  property =
    (FoProperty *) g_object_new (G_OBJECT_CLASS_TYPE (property_class),
				 "value",
				 datatype,
				 NULL);

  return property;
}

/**
 * fo_property_new_from_expr_default:
 * @property_class:    #FoPropertyClass or subclass of property.
 * @expr:              Expression to be evaluated.
 * @context:           #FoContext for inherited values.
 * @current_font_size: Current font size for resolving 'em' values.
 * @fo_node:           The current #FoFo node.
 * @error:             #GError for indicating any error that occurs.
 * 
 * Evaluate @expr and create a new instance of @property_class with
 * value of @expr.
 *
 * Other parameters (except @error) provide context for evaluating
 * @expr.
 * 
 * Return value: A new instance of @property_class, or NULL if error.
 **/
FoProperty*
fo_property_new_from_expr_default (FoPropertyClass *property_class,
				   const gchar *expr,
				   FoContext   *context,
				   FoProperty    *current_font_size,
				   FoFo *fo_node,
				   GError **error)
{
  FoProperty *property;
  FoDatatype *datatype;
  GError *tmp_error = NULL;
  const gchar *property_name = NULL;

  g_return_val_if_fail (FO_IS_PROPERTY_CLASS (property_class), NULL);
  g_return_val_if_fail (expr != NULL, NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail
    (current_font_size == NULL || FO_IS_PROPERTY_FONT_SIZE (current_font_size),
     NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  property_name = G_OBJECT_CLASS_NAME (property_class);

  datatype =
    property_class->expr_eval (expr,
			       property_name,
			       property_class->resolve_enum,
			       property_class->resolve_percent,
			       current_font_size,
			       fo_node,
			       context,
			       property_class->expr_env_list,
			       &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (error, tmp_error);
      return NULL;
    }

  datatype = property_class->validate (datatype, context, &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (error, tmp_error);
      return NULL;
    }

  property =
    (FoProperty *) g_object_new (G_OBJECT_CLASS_TYPE (property_class),
				 "value",
				 datatype,
				 NULL);

  return property;
}

FoProperty*
fo_property_new_from_expr (FoPropertyClass *property_class,
			   const gchar *expr,
			   FoContext   *context,
			   FoProperty    *current_font_size,
			   FoFo *fo_node,
			   GError **error)
{
  g_return_val_if_fail (FO_IS_PROPERTY_CLASS (property_class), NULL);

  if (*expr == '\0')
    {
      gchar *property_name = G_OBJECT_CLASS_NAME (property_class);

      g_set_error (error,
		   FO_PROPERTY_ERROR,
		   FO_PROPERTY_ERROR_ZERO_LENGTH,
		   fo_property_error_messages[FO_PROPERTY_ERROR_ZERO_LENGTH],
		   property_name);

      return NULL;
    }

  return property_class->new_from_expr (property_class,
					expr,
					context,
					current_font_size,
					fo_node,
					error);
}
/**
 * fo_property_class_is_inherited:
 * @property_class: #FoPropertyClass or a subclass of #FoPropertyClass.
 * 
 * Indicates whether the XSL property represented by @property_class
 * is defined in the XSL 1.0 Recommendation as an inherited property.
 * 
 * Return value: TRUE if @property_class is inherited, FALSE if not.
 **/
gboolean
fo_property_class_is_inherited (FoPropertyClass *property_class)
{
  g_return_val_if_fail (FO_IS_PROPERTY_CLASS (property_class), FALSE);

  return (FO_PROPERTY_CLASS (property_class)->is_inherited);
}

/**
 * fo_property_is_inherited:
 * @property: 
 * 
 * Indicates whether the XSL property represented by @property is
 * defined in the XSL 1.0 Recommendation as an inherited property.
 * 
 * Return value: TRUE if @property is inherited, FALSE otherwise
 **/
gboolean
fo_property_is_inherited (FoProperty *property)
{
  g_return_val_if_fail (FO_IS_PROPERTY (property), FALSE);

  return fo_property_class_is_inherited (FO_PROPERTY_GET_CLASS (property));
}

/**
 * fo_property_class_is_shorthand:
 * @property_class: #FoPropertyClass or a subclass of #FoPropertyClass.
 * 
 * Indicates whether the XSL property represented by @property_class
 * is defined in the XSL 1.0 Recommendation as a shorthand property.
 * 
 * Return value: TRUE if @property_class is a shorthand, FALSE if not.
 **/
gboolean
fo_property_class_is_shorthand (FoPropertyClass *property_class)
{
  g_return_val_if_fail (FO_IS_PROPERTY_CLASS (property_class), FALSE);

  return (FO_PROPERTY_CLASS (property_class)->is_shorthand);
}

/**
 * fo_property_is_shorthand:
 * @property: 
 * 
 * Indicates whether the XSL property represented by @property is
 * defined in the XSL 1.0 Recommendation as a shorthand property.
 * 
 * Return value: TRUE if @property is a shorthand, FALSE otherwise
 **/
gboolean
fo_property_is_shorthand (FoProperty *property)
{
  g_return_val_if_fail (FO_IS_PROPERTY (property), FALSE);

  return fo_property_class_is_shorthand (FO_PROPERTY_GET_CLASS (property));
}

/**
 * fo_property_sprintf:
 * @object: Object to be named
 * 
 * Returns a string representing the property and its current value.
 * The returned value should be freed when no longer needed.
 *
 * Return value: A newly allocated string
 **/
gchar*
fo_property_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY (object), NULL);

  return
    g_strdup_printf ("%s: %s",
		     g_type_name (G_TYPE_FROM_INSTANCE (object)),
		     fo_object_sprintf (FO_PROPERTY (object)->value));
}

/**
 * fo_property_debug_dump:
 * @object: 
 * @depth: 
 * 
 * 
 **/
void
fo_property_debug_dump (FoObject *object, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_PROPERTY (object));

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);
  g_free (indent);

  fo_object_debug_dump (fo_property_get_value (FO_PROPERTY (object)),
			depth + 2);
}
