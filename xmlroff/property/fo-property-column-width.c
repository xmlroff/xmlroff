/* Fo
 * fo-property-column-width.c: 'column-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-column-width.c,v 1.5 2004/03/24 12:31:06 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "datatype/fo-pcw.h"
#include "fo-property-private.h"
#include "fo-property-font-size.h"
#include "fo-property-column-width.h"

/* column-width */
/* <length> | <percentage> */
/* NO ENUMERATED VALUE */

struct _FoPropertyColumnWidth
{
  FoProperty parent_instance;
};

struct _FoPropertyColumnWidthClass
{
  FoPropertyClass parent_class;
};

static void fo_property_column_width_init         (FoPropertyColumnWidth      *property_column_width);
static void fo_property_column_width_class_init   (FoPropertyColumnWidthClass *klass);
static void fo_property_column_width_finalize     (GObject       *object);

static FoDatatype* fo_property_column_width_resolve_enum (const gchar *token,
                                                          FoContext   *context,
                                                          GError     **error);
static FoDatatype* fo_property_column_width_validate (FoDatatype *datatype,
                                                      FoContext  *context,
                                                      GError    **error);
static FoProperty* fo_property_column_width_new_from_expr (FoPropertyClass *property_class,
							   const gchar *expr,
							   FoContext   *context,
							   FoProperty    *current_font_size,
							   FoFo *fo_node,
							   GError **error);

static const gchar class_name[] = "column-width";
static gpointer parent_class;

/**
 * fo_property_column_width_get_type:
 * 
 * Register the FoPropertyColumnWidth type if not already registered and
 * return its GType value
 * 
 * Return value: GType of FoPropertyColumnWidth
 **/
GType
fo_property_column_width_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyColumnWidthClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_property_column_width_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyColumnWidth),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_column_width_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_column_width_init:
 * @column_width: FoPropertyColumnWidth object to initialise
 * 
 * Implements GInstanceInitFunc for FoPropertyColumnWidth
 **/
void
fo_property_column_width_init (FoPropertyColumnWidth *column_width)
{
  FO_PROPERTY (column_width)->value =
    NULL;
}

/**
 * fo_property_column_width_class_init:
 * @klass: FoPropertyColumnWidthClass object to initialise
 * 
 * Implements GClassInitFunc for FoPropertyColumnWidthClass
 **/
void
fo_property_column_width_class_init (FoPropertyColumnWidthClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_column_width_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_column_width_resolve_enum;
  property_class->resolve_percent =
    fo_property_column_width_resolve_percent;
  property_class->validate =
    fo_property_column_width_validate;
  property_class->get_initial =
    fo_property_column_width_get_initial;
  property_class->new_from_expr =
    fo_property_column_width_new_from_expr;
}

/**
 * fo_property_column_width_finalize:
 * @object: FoPropertyColumnWidth object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoPropertyColumnWidth
 **/
void
fo_property_column_width_finalize (GObject *object)
{
  FoPropertyColumnWidth *column_width;

  column_width = FO_PROPERTY_COLUMN_WIDTH (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_column_width_new:
 * 
 * Creates a new #FoPropertyColumnWidth initialized to default value.
 * 
 * Return value: the new #FoPropertyColumnWidth
 **/
FoProperty*
fo_property_column_width_new (void)
{
  FoProperty* column_width;

  column_width =
    FO_PROPERTY (g_object_new (fo_property_column_width_get_type (), NULL));

  return column_width;
}

/**
 * fo_property_column_width_resolve_enum:
 * @token:   Token from the XML attribute value to be evaluated as an
 *            enumeration token
 * @context: FoContext object from which to possibly inherit values
 * @error:   Information about an error that has occurred
 * 
 * Compare @token against the enumeration tokens that are valid for the
 * current FO property.  If @token is valid, returns either an FoEnum datatype
 * representing the enumeration token or a different datatype representing
 * the enumeration token's resolved value.  If @token is not valid,
 * sets @error and returns NULL
 * 
 * Return value: Resolved enumeration value or NULL
 **/
FoDatatype*
fo_property_column_width_resolve_enum (const gchar *token,
                                       FoContext   *context,
                                       GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_ENUMERATION_TOKEN,
		   _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		   class_name,
		   token);
      return NULL;
}

/**
 * fo_property_column_width_resolve_percent:
 * @percentage: The percentage.
 * @font_size:  Current font-size property value.
 * @fo_node:    Current #FoFo node.
 * @context:    Current #FoContext.
 * @error:      #GError.
 * 
 * Resolves percentage values in 'column-width' property value
 * expressions.
 * 
 * Return value: Resolved value for @percentage.
 **/
FoDatatype*
fo_property_column_width_resolve_percent (gdouble            percentage,
					  const FoDatatype  *font_size,
					  const FoFo        *fo_node,
					  const FoContext   *context,
					  GError           **error)
{
  FoFo *table;
  FoFoAreaIterator *iterator;
  FoArea *table_area;
  gdouble child_ipdim;

  table = FO_FO (fo_node_get_ancestor_or_self_by_name (FO_NODE (fo_node),
						       "table"));

  g_assert (table != NULL);

  iterator = fo_fo_get_area_iterator (table);

  table_area = fo_fo_area_iterator_get_area (iterator);

  g_free (iterator);

  g_assert (table_area != NULL);

  child_ipdim = fo_area_get_child_available_ipdim (table_area);

  return fo_length_new_with_value (child_ipdim * percentage * 0.01);
}

/**
 * fo_property_column_width_validate:
 * @datatype: FoDatatype to be validated against allowed datatypes and
 *            values for current property
 * @context:  FoContext object from which to possibly inherit values
 * @error:    Information about an error that has occurred
 * 
 * Validates @datatype against allowed values.  Returns @datatype, a
 * replacement datatype value, or NULL if validation failed
 * 
 * Return value: Valid datatype value or NULL
 **/
FoDatatype*
fo_property_column_width_validate (FoDatatype *datatype,
                                   FoContext  *context,
                                   GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_LENGTH (datatype))
    {
      return datatype;
    }
  else if (FO_IS_PERCENTAGE (datatype))
    {
      return datatype;
    }
  else if (FO_IS_PCW (datatype))
    {
      return datatype;
    }
  else
    {
      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   fo_object_sprintf (datatype),
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      return NULL;
    }
}

/**
 * fo_property_column_width_new_from_expr:
 * @property_class:    #FoPropertyColumnWidth class.
 * @expr:              Expression to be evaluated.
 * @context:           #FoContext for inherited values.
 * @current_font_size: Current font size for resolving 'em' values.
 * @fo_node:           The current #FoFo node.
 * @error:             #GError for indicating any error that occurs.
 * 
 * Evaluate @expr and create a new instance of @property_class with
 * value of @epr.
 *
 * Other parameters (except @error) provide context for evaluating
 * @expr.
 * 
 * Return value: A new instance of #FoPropertyColumnWidth, or NULL if error.
 **/
FoProperty*
fo_property_column_width_new_from_expr (FoPropertyClass *property_class,
					const gchar *expr,
					FoContext   *context,
					FoProperty    *current_font_size,
					FoFo *fo_node,
					GError **error)
{
  FoProperty *property;
  FoDatatype *datatype;
  FoDatatype *string_datatype;
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
    fo_expr_eval (expr,
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

  g_object_unref (datatype);

  string_datatype = fo_string_new_with_value (expr);
  property =
    (FoProperty *) g_object_new (G_OBJECT_CLASS_TYPE (property_class),
				 "value",
				 string_datatype,
				 NULL);

  return property;
}

/**
 * fo_property_column_width_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_column_width_get_initial (void)
{
  static FoProperty *column_width = NULL;

  if (column_width == NULL)
    {
      column_width = fo_property_column_width_new ();
    }

  return column_width;
}
