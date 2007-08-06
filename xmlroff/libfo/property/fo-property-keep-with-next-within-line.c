/* Fo
 * fo-property-keep-with-next-within-line.c: 'keep-with-next-within-line' property
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
/*
#include "property/fo-property-text-property.h"
*/
#include "property/fo-property-font-size.h"
#include "property/fo-property-keep-with-next-within-line.h"
#include "property/fo-property-util.h"

/* keep-with-next-within-line */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

struct _FoPropertyKeepWithNextWithinLine
{
  FoProperty parent_instance;
};

struct _FoPropertyKeepWithNextWithinLineClass
{
  FoPropertyClass parent_class;
};

static void fo_property_keep_with_next_within_line_init         (FoPropertyKeepWithNextWithinLine      *property_keep_with_next_within_line);
static void fo_property_keep_with_next_within_line_class_init   (FoPropertyKeepWithNextWithinLineClass *klass);
static void fo_property_keep_with_next_within_line_finalize     (GObject       *object);

static FoDatatype* fo_property_keep_with_next_within_line_validate (FoDatatype *datatype,
                                                                    FoContext  *context,
                                                                    GError    **error);
/*
PangoAttribute * fo_property_keep_with_next_within_line_new_attr (FoProperty *property);
static void fo_property_keep_with_next_within_line_text_property_init (FoPropertyTextPropertyIface *iface);
*/
static const gchar class_name[] = "FoPropertyKeepWithNextWithinLine";
static gpointer parent_class;

/**
 * fo_property_keep_with_next_within_line_get_type:
 * 
 * Register the #FoPropertyKeepWithNextWithinLine type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyKeepWithNextWithinLine.
 **/
GType
fo_property_keep_with_next_within_line_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyKeepWithNextWithinLineClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_keep_with_next_within_line_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyKeepWithNextWithinLine),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_keep_with_next_within_line_init,
	NULL		/* value_table */
      };

      /*
      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_keep_with_next_within_line_text_property_init, / * interface_init * /
        NULL,
        NULL
      };
      */

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
      /*
      g_type_add_interface_static (object_type,
                                   FO_TYPE_PROPERTY_TEXT_PROPERTY,
                                   &fo_property_text_property_info);
      */
    }

  return object_type;
}

/**
 * fo_property_keep_with_next_within_line_init:
 * @keep_with_next_within_line: #FoPropertyKeepWithNextWithinLine object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyKeepWithNextWithinLine.
 **/
void
fo_property_keep_with_next_within_line_init (FoPropertyKeepWithNextWithinLine *keep_with_next_within_line)
{
  FO_PROPERTY (keep_with_next_within_line)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_keep_with_next_within_line_class_init:
 * @klass: #FoPropertyKeepWithNextWithinLineClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyKeepWithNextWithinLineClass.
 **/
void
fo_property_keep_with_next_within_line_class_init (FoPropertyKeepWithNextWithinLineClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_keep_with_next_within_line_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_always_enum;
  property_class->validate =
    fo_property_keep_with_next_within_line_validate;
  property_class->get_initial =
    fo_property_keep_with_next_within_line_get_initial;
}

/**
 * fo_property_keep_with_next_within_line_finalize:
 * @object: #FoPropertyKeepWithNextWithinLine object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyKeepWithNextWithinLine.
 **/
void
fo_property_keep_with_next_within_line_finalize (GObject *object)
{
  FoPropertyKeepWithNextWithinLine *keep_with_next_within_line;

  keep_with_next_within_line = FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_keep_with_next_within_line_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class
 **/
/*
void
fo_property_keep_with_next_within_line_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_keep_with_next_within_line_new_attr;
}
*/

/**
 * fo_property_keep_with_next_within_line_new:
 * 
 * Creates a new #FoPropertyKeepWithNextWithinLine initialized to default value.
 * 
 * Return value: the new #FoPropertyKeepWithNextWithinLine.
 **/
FoProperty*
fo_property_keep_with_next_within_line_new (void)
{
  FoProperty* keep_with_next_within_line;

  keep_with_next_within_line =
    FO_PROPERTY (g_object_new (fo_property_keep_with_next_within_line_get_type (),
                               NULL));

  return keep_with_next_within_line;
}

/**
 * fo_property_keep_with_next_within_line_validate:
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
fo_property_keep_with_next_within_line_validate (FoDatatype *datatype,
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

  if (FO_IS_ENUM (datatype))
    {
      return datatype;
    }
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_auto_always_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return NULL;
	}

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_auto_always_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return NULL;
	}

      return new_datatype;
    }
  else if (FO_IS_INTEGER (datatype))
    {
      return datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      new_datatype =
        fo_integer_new_with_value ((gint) fo_number_get_value (datatype));

      g_object_unref (datatype);

      return new_datatype;
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
 * fo_property_keep_with_next_within_line_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_keep_with_next_within_line_get_initial (void)
{
  static FoProperty *keep_with_next_within_line = NULL;

  if (keep_with_next_within_line == NULL)
    {
      keep_with_next_within_line =
	fo_property_keep_with_next_within_line_new ();
    }

  return keep_with_next_within_line;
}

/**
 * fo_property_keep_with_next_within_line_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
/*
PangoAttribute*
fo_property_keep_with_next_within_line_new_attr (FoProperty *property)
{
  FoDatatype *datatype;
  gint pango_keep_with_next_within_line = G_MININT;

  g_return_val_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (property),
			NULL);

  datatype = property->value;

  if (FO_IS_INTEGER (datatype))
    {
      pango_keep_with_next_within_line =
	fo_integer_get_value (datatype);
    }
  else if (FO_IS_ENUM (datatype))
    {
      guint value = fo_enum_get_value (datatype);

      if (value == FO_ENUM_ENUM_AUTO)
	{
	  pango_keep_with_next_within_line = G_MININT;
	}
      else if (value == FO_ENUM_ENUM_ALWAYS)
	{
	  pango_keep_with_next_within_line = G_MAXINT;
	}
      else
	{
	  g_assert_not_reached ();
	}
    }
  else
    {
      g_assert_not_reached ();
    }

  return pango_attr_keep_with_next_within_line_new (pango_keep_with_next_within_line);
}
*/
