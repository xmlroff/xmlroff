/* Fo
 * fo-property-end-indent.c: 'end-indent' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-end-indent.h"

/* Inherited: TRUE */
/* Shorthand: FALSE */
/* end-indent */
/* <length> | <percentage> | inherit */
/* NO ENUMERATED VALUE */


struct _FoPropertyEndIndent
{
  FoProperty parent_instance;
};

struct _FoPropertyEndIndentClass
{
  FoPropertyClass parent_class;
};

static void fo_property_end_indent_init         (FoPropertyEndIndent      *property_end_indent);
static void fo_property_end_indent_class_init   (FoPropertyEndIndentClass *klass);
static void fo_property_end_indent_finalize     (GObject       *object);

static FoDatatype* fo_property_end_indent_resolve_enum (const gchar *token,
                                                        FoContext   *context,
                                                        GError     **error);
static FoDatatype* fo_property_end_indent_validate (FoDatatype *datatype,
                                                    FoContext  *context,
                                                    GError    **error);

static const gchar class_name[] = "FoPropertyEndIndent";
static gpointer parent_class;

/**
 * fo_property_end_indent_get_type:
 * 
 * Register the #FoPropertyEndIndent type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyEndIndent.
 **/
GType
fo_property_end_indent_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyEndIndentClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_end_indent_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyEndIndent),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_end_indent_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_end_indent_init:
 * @end_indent: #FoPropertyEndIndent object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyEndIndent.
 **/
void
fo_property_end_indent_init (FoPropertyEndIndent *end_indent)
{
  FO_PROPERTY (end_indent)->value =
    g_object_ref (fo_length_get_length_zero ());
}

/**
 * fo_property_end_indent_class_init:
 * @klass: #FoPropertyEndIndentClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyEndIndentClass.
 **/
void
fo_property_end_indent_class_init (FoPropertyEndIndentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_end_indent_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_end_indent_resolve_enum;
  property_class->validate =
    fo_property_end_indent_validate;
  property_class->get_initial =
    fo_property_end_indent_get_initial;
}

/**
 * fo_property_end_indent_finalize:
 * @object: #FoPropertyEndIndent object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyEndIndent.
 **/
void
fo_property_end_indent_finalize (GObject *object)
{
  FoPropertyEndIndent *end_indent;

  end_indent = FO_PROPERTY_END_INDENT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_end_indent_new:
 * 
 * Creates a new #FoPropertyEndIndent initialized to default value.
 * 
 * Return value: the new #FoPropertyEndIndent.
 **/
FoProperty*
fo_property_end_indent_new (void)
{
  FoProperty* end_indent;

  end_indent =
    FO_PROPERTY (g_object_new (fo_property_end_indent_get_type (),
                               NULL));

  return end_indent;
}

/**
 * fo_property_end_indent_resolve_enum:
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
fo_property_end_indent_resolve_enum (const gchar *token,
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
 * fo_property_end_indent_validate:
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
fo_property_end_indent_validate (FoDatatype *datatype,
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
 * fo_property_end_indent_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_end_indent_get_initial (void)
{
  static FoProperty *end_indent = NULL;

  if (end_indent == NULL)
    {
      end_indent = fo_property_end_indent_new ();
    }

  return end_indent;
}
