/* Fo
 * fo-property-font-family.c: 'font-family' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-font-family.c,v 1.8 2005/05/03 22:46:49 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include <pangoxsl/pango-xsl-attributes.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-family.h"
/*#include "expression-parser.h"*/
#include "expr/fo-expr-eval.h"

/* font-family */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* [[ <family-name> | <generic-family> ],]* [<family-name> | <generic-family>] | inherit */
/* Initial value: depends on user agent */

struct _FoPropertyFontFamily
{
  FoProperty parent_instance;
};

struct _FoPropertyFontFamilyClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_family_init         (FoPropertyFontFamily      *property_font_family);
static void fo_property_font_family_class_init   (FoPropertyFontFamilyClass *klass);
static void fo_property_font_family_finalize     (GObject       *object);
static void fo_property_font_family_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype* fo_property_font_family_resolve_enum (const gchar *token,
                                                         FoContext   *context,
                                                         GError     **error);
static FoDatatype* fo_property_font_family_validate (FoDatatype *datatype,
                                                     FoContext  *context,
                                                     GError    **error);
static FoProperty * fo_property_font_family_new_from_expr (FoPropertyClass *property_class,
							   const gchar *expr,
							   FoContext   *context,
							   FoProperty    *current_font_size,
							   FoFo *fo_node,
							   GError **error);

static PangoAttribute * fo_property_font_family_new_attr (FoProperty *property);

static const gchar class_name[] = "font-family";
static gpointer parent_class;

/**
 * fo_property_font_family_get_type:
 * 
 * Register the #FoPropertyFontFamily type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFontFamily.
 **/
GType
fo_property_font_family_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFontFamilyClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_font_family_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontFamily),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_font_family_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_font_family_text_property_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);

      g_type_add_interface_static (object_type,
                                   FO_TYPE_PROPERTY_TEXT_PROPERTY,
                                   &fo_property_text_property_info);
    }

  return object_type;
}

/**
 * fo_property_font_family_init:
 * @font_family: #FoPropertyFontFamily object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontFamily.
 **/
void
fo_property_font_family_init (FoPropertyFontFamily *font_family)
{
  FO_PROPERTY (font_family)->value =
    fo_string_new_with_value ("sans-serif");
}

/**
 * fo_property_font_family_class_init:
 * @klass: #FoPropertyFontFamilyClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontFamilyClass.
 **/
void
fo_property_font_family_class_init (FoPropertyFontFamilyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_font_family_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_font_family_resolve_enum;
  property_class->validate =
    fo_property_font_family_validate;
  property_class->new_from_expr =
    fo_property_font_family_new_from_expr;
  property_class->get_initial =
    fo_property_font_family_get_initial;
}

/**
 * fo_property_font_family_finalize:
 * @object: #FoPropertyFontFamily object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFontFamily.
 **/
void
fo_property_font_family_finalize (GObject *object)
{
  FoPropertyFontFamily *font_family;

  font_family = FO_PROPERTY_FONT_FAMILY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_font_family_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_font_family_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_font_family_new_attr;
}

/**
 * fo_property_font_family_new:
 * 
 * Creates a new #FoPropertyFontFamily initialized to default value.
 * 
 * Return value: the new #FoPropertyFontFamily.
 **/
FoProperty*
fo_property_font_family_new (void)
{
  FoProperty* font_family;

  font_family =
    FO_PROPERTY (g_object_new (fo_property_font_family_get_type (),
                               NULL));

  return font_family;
}

/**
 * fo_property_font_family_resolve_enum:
 * @token:   Token from the XML attribute value to be evaluated as an
 *           enumeration token.
 * @context: #FoContext object from which to possibly inherit values.
 * @error:   Information about any error that has occurred.
 * 
 * Compare @token against the enumeration tokens that are valid for the
 * current FO property.  If @token is valid, returns either an #FoEnum datatype
 * representing the enumeration token or a different datatype representing
 * the enumeration token's resolved value.  If @token is not valid,
 * sets @error and returns NULL.
 * 
 * Return value: Resolved enumeration value or NULL.
 **/
FoDatatype*
fo_property_font_family_resolve_enum (const gchar *token,
                                      FoContext   *context,
                                      GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "serif") == 0) ||
      (strcmp (token, "sans-serif") == 0) ||
      (strcmp (token, "cursive") == 0) ||
      (strcmp (token, "fantasy") == 0) ||
      (strcmp (token, "monospace") == 0) ||
      (strcmp (token, "serif") == 0) ||
      (strcmp (token, "sans-serif") == 0) ||
      (strcmp (token, "cursive") == 0) ||
      (strcmp (token, "fantasy") == 0) ||
      (strcmp (token, "monospace") == 0))
    {
      return fo_string_new_with_value (token);
    }
  else
    {
      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_ENUMERATION_TOKEN,
		   _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		   class_name,
		   token);
      return NULL;
    }
}

/**
 * fo_property_font_family_validate:
 * @datatype: #FoDatatype to be validated against allowed datatypes and
 *            values for current property.
 * @context:  #FoContext object from which to possibly inherit values.
 * @error:    Information about any error that has occurred.
 * 
 * Validates @datatype against allowed values.  Returns @datatype, a
 * replacement datatype value, or NULL if validation failed.
 * 
 * Return value: Valid datatype value or NULL.
 **/
FoDatatype*
fo_property_font_family_validate (FoDatatype *datatype,
                                  FoContext  *context,
                                  GError    **error)
{
  FoDatatype *new_datatype;
  GError     *tmp_error = NULL;
  gchar      *token;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_STRING (datatype))
    {
      return datatype;
    }
  else if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

      if ((value == FO_ENUM_ENUM_SERIF) ||
          (value == FO_ENUM_ENUM_SANS_SERIF) ||
          (value == FO_ENUM_ENUM_CURSIVE) ||
          (value == FO_ENUM_ENUM_FANTASY) ||
          (value == FO_ENUM_ENUM_MONOSPACE) ||
          (value == FO_ENUM_ENUM_SERIF) ||
          (value == FO_ENUM_ENUM_SANS_SERIF) ||
          (value == FO_ENUM_ENUM_CURSIVE) ||
          (value == FO_ENUM_ENUM_FANTASY) ||
          (value == FO_ENUM_ENUM_MONOSPACE))
	{
	  return datatype;
	}
      else
	{
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);

	  g_set_error (error,
		       FO_FO_ERROR,
		       FO_FO_ERROR_ENUMERATION_TOKEN,
		       _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		       class_name,
		       datatype_sprintf,
		       g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

	  g_object_unref (datatype);

	  g_free (datatype_sprintf);

	  return NULL;
	}
    }
  else if (FO_IS_NAME (datatype))
    {
      gchar *name_string = fo_name_get_value (datatype);
      new_datatype = fo_string_new_with_value (name_string);

      g_free (name_string);
      g_object_unref (datatype);

      return (new_datatype);
    }
  else
    {
      gchar *datatype_sprintf = fo_object_sprintf (datatype);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   datatype_sprintf,
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      g_free (datatype_sprintf);

      return NULL;
    }
}

/**
 * fo_property_font_family_new_from_expr:
 * @property_class:    #FoPropertyFontFamily class.
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
 * Return value: A new instance of #FoPropertyFontFamily, or NULL if error.
 **/
FoProperty*
fo_property_font_family_new_from_expr (FoPropertyClass *property_class,
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
      if (g_error_matches (tmp_error,
			   FO_EXPR_ERROR,
			   FO_EXPR_ERROR_EXTRA_EXPR))
	{
	  gchar *new_expr = g_strconcat ("'", expr, "'", NULL);

	  g_clear_error (&tmp_error);

	  datatype =
	    fo_expr_eval (new_expr,
			  property_name,
			  property_class->resolve_enum,
			  property_class->resolve_percent,
			  current_font_size,
			  fo_node,
			  context,
			  property_class->expr_env_list,
			  &tmp_error);
	  g_free (new_expr);
	}

      if (tmp_error != NULL)
	{
	  g_message (tmp_error->message);
	  g_propagate_error (error,
			     tmp_error);
	  return NULL;
	}
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

/**
 * fo_property_font_family_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_font_family_get_initial (void)
{
  static FoProperty *font_family = NULL;

  if (font_family == NULL)
    {
      font_family =
	fo_property_font_family_new ();
    }

  return font_family;
}

/**
 * fo_property_font_family_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute
 * 
 * Makes a new #PangoAttribute representing the current property
 * 
 * Return value: New #PangoAttribute
 **/
PangoAttribute*
fo_property_font_family_new_attr (FoProperty *property)
{
  gchar *pango_font_family;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_FAMILY (property), NULL);

  pango_font_family =
    fo_string_get_value (property->value);

  PangoAttribute *pango_attr = pango_attr_family_new (pango_font_family);

  g_free (pango_font_family);

  return pango_attr;
}
