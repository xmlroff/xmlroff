/* Fo
 * fo-datatype.c: Datatype datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-datatype.c,v 1.5 2004/06/01 16:53:18 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <math.h>
#include "libfo/fo-utils.h"
#include "fo-datatype-private.h"
#include "fo-datatype.h"
#include "fo-integer.h"
#include "fo-boolean.h"
#include "fo-number.h"
#include "fo-percentage.h"
#include "fo-pcw.h"
#include "fo-length.h"
#include "fo-error.h"

static void fo_datatype_base_class_init  (FoDatatypeClass *klass);
static void fo_datatype_class_init  (FoDatatypeClass *klass);
static void fo_datatype_finalize    (GObject           *object);

static void fo_datatype_debug_dump (FoObject *object, gint depth);
static FoDatatype* fo_datatype_copy_default (FoDatatype *datatype);

static gpointer parent_class;

/**
 * fo_datatype_get_type:
 * 
 * Register the FoDatatype object type.
 * 
 * Return value: GType value of the FoDatatype object type.
 **/
GType
fo_datatype_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoDatatypeClass),
        (GBaseInitFunc) fo_datatype_base_class_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_datatype_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoDatatype),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoDatatype",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * fo_datatype_base_class_init:
 * @klass: #FoDatatypeClass object to initialise
 * 
 * Implements #GBaseInitFunc for #FoDatatype
 **/
static void
fo_datatype_base_class_init (FoDatatypeClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);

  FO_OBJECT_CLASS (fo_object_class)->debug_dump = fo_datatype_debug_dump;
}

/**
 * fo_datatype_class_init:
 * @klass: #FoDatatypeClass object to initialise
 * 
 * Implements GClassInitFunc for #FoDatatypeClass
 **/
void
fo_datatype_class_init (FoDatatypeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_datatype_finalize;

  klass->copy = fo_datatype_copy_default;
}

/**
 * fo_datatype_finalize:
 * @object: #FoDatatype object to finalize
 * 
 * Implements GObjectFinalizeFunc for #FoDatatype
 **/
void
fo_datatype_finalize (GObject *object)
{
  FoDatatype *datatype;

  datatype = FO_DATATYPE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_datatype_new:
 * 
 * Creates a new #FoDatatype initialized to default value.
 * 
 * Return value: the new #FoDatatype
 **/
FoDatatype *
fo_datatype_new (void)
{
  FoDatatype *datatype;

  datatype = FO_DATATYPE (g_object_new (fo_datatype_get_type (), NULL));
  
  return datatype;
}

/**
 * fo_datatype_copy:
 * @datatype: #FoDatatype to be copied
 * 
 * Makes a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_datatype_copy (FoDatatype *datatype)
{
  return FO_DATATYPE_GET_CLASS (datatype)->copy (datatype);
}

/**
 * fo_datatype_copy_default:
 * @datatype: #FoDatatype to be copied
 * 
 * Warns that @datatype does not have a "copy" function
 * 
 * Return value: NULL
 **/
FoDatatype*
fo_datatype_copy_default (FoDatatype *datatype)
{
  g_warning ("%s does not have a \"copy\" function.",
	     fo_object_sprintf (FO_OBJECT (datatype)));

  return NULL;
}

/**
 * fo_datatype_debug_dump:
 * @object: #FoDatatype object to dump
 * @depth:  Relative offset to add to dump output
 * 
 * Implements debug_dump class method of #FoObject for all #FoDatatype
 * subclasses.
 *
 * Uses the sprintf class method of #FoObject of @object.
 **/
void
fo_datatype_debug_dump (FoObject *object, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *object_sprintf, *datatype_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_DATATYPE (object));

  object_sprintf = fo_object_debug_sprintf (object);
  datatype_sprintf = fo_object_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s : %s",
	 indent,
	 object_sprintf,
	 datatype_sprintf);

  g_free (object_sprintf);
  g_free (datatype_sprintf);
  g_free (indent);
}

/**
 * fo_datatype_get_condity_discard:
 * 
 * Return value: The #FoDatatype value for conditionality="discard"
 **/
FoDatatype*
fo_datatype_get_condity_discard (void)
{
  static FoDatatype *enum_discard = NULL;

  if (!enum_discard)
    {
      enum_discard =
	fo_boolean_get_false ();
    }

  return enum_discard;
}

/**
 * fo_datatype_get_condity_retain:
 * 
 * Return value: The #FoDatatype value for conditionality="retain"
 **/
FoDatatype*
fo_datatype_get_condity_retain (void)
{
  static FoDatatype *enum_retain = NULL;

  if (!enum_retain)
    {
      enum_retain =
	fo_boolean_get_true ();
    }

  return enum_retain;
}

/**
 * fo_datatype_error_quark:
 * 
 * Get the error quark for #FoDatatype.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoDatatype errors
 **/
GQuark
fo_datatype_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoDatatype error");
  return quark;
}

const char *fo_datatype_error_messages [] = {
  N_("Invalid datatype for context."),
  N_("Cannot add datatypes '%s' and '%s'."),
  N_("Cannot subtract datatypes '%s' and '%s'."),
  N_("Cannot multiply datatypes '%s' and '%s'."),
  N_("Cannot divide datatypes '%s' and '%s'."),
  N_("Cannot get modulus of datatypes '%s' and '%s'."),
  N_("Incompatible types in 'max' operation: '%s' and '%s'."),
  N_("Incompatible types in 'min' operation: '%s' and '%s'."),
  N_("Type with non-zero unit power in 'floor' operation: '%s'."),
  N_("Type with non-zero unit power in 'round' operation: '%s'."),
  N_("Type with non-zero unit power in 'ceiling' operation: '%s'."),
  N_("Non-numeric type in 'abs' operation: '%s'."),
  N_("Invalid type in 'negate' operation: '%s'."),
};

/**
 * fo_datatype_add:
 * @arg1: #FoDatatype.
 * @arg2: #FoDatatype.
 * 
 * Find addition of the values of @arg1 and @arg2.  @arg1 and @arg2
 * are unchanged.
 * 
 * The type of the return value depends on the types of @arg1 and
 * @arg2:
 *
 * fo_datatype_add (#FoInteger,    #FoInteger)    --> #FoInteger
 * fo_datatype_add (#FoInteger,    #FoNumber)     --> #FoNumber
 * fo_datatype_add (#FoNumber,     #FoInteger)    --> #FoNumber
 * fo_datatype_add (#FoNumber,     #FoNumber)     --> #FoNumber
 * fo_datatype_add (#FoLength,     #FoLength)     --> #FoLength
 * fo_datatype_add (#FoPercentage, #FoPercentage) --> #FoPercentage
 *
 * Return value: #FoDatatype with value that is equal to addition of
 * values of @arg1 and @arg2, or #FoError if cannot compute addition
 * of @arg1 and @arg2.  The type of the return value depends on the
 * types of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_add (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);

  if (FO_IS_INTEGER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_integer_new_with_value (fo_integer_get_value (arg1) +
					      fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_integer_get_value (arg1) +
					     fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_NUMBER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) +
					     fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) +
					     fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_LENGTH (arg1))
    {
      if (FO_IS_LENGTH (arg2)) {
	result = fo_length_new_with_value (fo_length_get_value (arg1) +
					   fo_length_get_value (arg2));
      }
      else if (FO_IS_PCW (arg2))
	{
	  result = g_object_ref (arg2);
	}
    }
  else if (FO_IS_PERCENTAGE (arg1))
    {
      if (FO_IS_PERCENTAGE (arg2)) {
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 fo_percentage_get_value (arg1) +
				 fo_percentage_get_value (arg2));
      }
    }
  else if (FO_IS_PCW (arg1))
    {
      if (FO_IS_PCW (arg2))
	{
	result = fo_pcw_new_with_value (fo_pcw_get_value (arg1) +
					fo_pcw_get_value (arg2));
	}
      else if (FO_IS_LENGTH (arg2))
	{
	  result = g_object_ref (arg1);
	}
    }


  if (result == NULL)
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_ADD,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_ADD],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg1);
  g_object_unref (arg2);

  return result;
}

/**
 * fo_datatype_sub:
 * @arg1: #FoDatatype.
 * @arg2: #FoDatatype.
 * 
 * Find subtraction of the value of @arg2 from the value of @arg1.
 * @arg1 and @arg2 are unchanged.
 * 
 * The type of the return value depends on the types of @arg1 and
 * @arg2:
 *
 * fo_datatype_sub (#FoInteger,    #FoInteger)    --> #FoInteger
 * fo_datatype_sub (#FoInteger,    #FoNumber)     --> #FoNumber
 * fo_datatype_sub (#FoNumber,     #FoInteger)    --> #FoNumber
 * fo_datatype_sub (#FoNumber,     #FoNumber)     --> #FoNumber
 * fo_datatype_sub (#FoLength,     #FoLength)     --> #FoLength
 * fo_datatype_sub (#FoPercentage, #FoPercentage) --> #FoPercentage
 *
 * Return value: #FoDatatype with value that is equal to subtraction
 * of the value of @arg2 from the value of @arg1, or #FoError if
 * cannot compute subisor of @arg1 and @arg2.  The type of the return
 * value depends on the types of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_sub (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);

  if (FO_IS_INTEGER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_integer_new_with_value (fo_integer_get_value (arg1) -
					      fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_integer_get_value (arg1) -
					     fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_NUMBER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) -
					     fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) -
					     fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_LENGTH (arg1))
    {
      if (FO_IS_LENGTH (arg2)) {
	result = fo_length_new_with_value (fo_length_get_value (arg1) -
					   fo_length_get_value (arg2));
      }
    }
  else if (FO_IS_PERCENTAGE (arg1))
    {
      if (FO_IS_PERCENTAGE (arg2)) {
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 fo_percentage_get_value (arg1) -
				 fo_percentage_get_value (arg2));
      }
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_SUB,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_SUB],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg1);
  g_object_unref (arg2);

  return result;
}

/**
 * fo_datatype_mul:
 * @arg1: #FoDatatype.
 * @arg2: #FoDatatype.
 * 
 * Find multiple of values of @arg1 and @arg2.  @arg1 and @arg2 are
 * unchanged.
 * 
 * The type of the return value depends on the types of @arg1 and
 * @arg2:
 *
 * fo_datatype_mul (#FoInteger,    #FoInteger)    --> #FoInteger
 * fo_datatype_mul (#FoInteger,    #FoNumber)     --> #FoNumber
 * fo_datatype_mul (#FoInteger,    #FoLength)     --> #FoLength
 * fo_datatype_mul (#FoInteger,    #FoPercentage) --> #FoInteger
 * fo_datatype_mul (#FoNumber,     #FoInteger)    --> #FoNumber
 * fo_datatype_mul (#FoNumber,     #FoNumber)     --> #FoNumber
 * fo_datatype_mul (#FoNumber,     #FoLength)     --> #FoLength
 * fo_datatype_mul (#FoNumber,     #FoPercentage) --> #FoNumber
 * fo_datatype_mul (#FoLength,     #FoInteger)    --> #FoLength
 * fo_datatype_mul (#FoLength,     #FoNumber)     --> #FoLength
 * fo_datatype_mul (#FoLength,     #FoPercentage) --> #FoLength
 * fo_datatype_mul (#FoPercentage, #FoInteger)    --> #FoInteger
 * fo_datatype_mul (#FoPercentage, #FoNumber)     --> #FoNumber
 * fo_datatype_mul (#FoPercentage, #FoLength)     --> #FoLength
 * fo_datatype_mul (#FoPercentage, #FoPercentage) --> #FoPercentage
 *
 * Return value: #FoDatatype with value that is equal to mulisor of
 * values of @arg1 and @arg2, or #FoError if cannot compute mulisor of
 * @arg1 and @arg2.  The type of the return value depends on the types
 * of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_mul (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);

  if (FO_IS_INTEGER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_integer_new_with_value (fo_integer_get_value (arg1) *
					      fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_integer_get_value (arg1) *
					     fo_number_get_value (arg2));
	}
      else if (FO_IS_LENGTH (arg2))
	{
	result = fo_length_new_with_value (fo_integer_get_value (arg1) *
					   fo_length_get_value (arg2));
	}
      else if (FO_IS_PERCENTAGE (arg2))
	{
	  result =
	    fo_integer_new_with_value (fo_integer_get_value (arg1) *
				       fo_percentage_get_value (arg2) * 0.01);
	}
    }
  else if (FO_IS_NUMBER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) *
					     fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) *
					     fo_number_get_value (arg2));
	}
      else if (FO_IS_LENGTH (arg2))
	{
	result = fo_length_new_with_value (fo_number_get_value (arg1) *
					   fo_length_get_value (arg2));
	}
      else if (FO_IS_PERCENTAGE (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) *
					     fo_percentage_get_value (arg2) * 0.01);
	}
    }
  else if (FO_IS_LENGTH (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	result = fo_length_new_with_value (fo_length_get_value (arg1) *
					   fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	result = fo_length_new_with_value (fo_length_get_value (arg1) *
					   fo_number_get_value (arg2));
	}
      else if (FO_IS_PERCENTAGE (arg2))
	{
	result =
	  fo_length_new_with_value (fo_length_get_value (arg1) *
				    fo_percentage_get_value (arg2) * 0.01);
	}
    }
  else if (FO_IS_PERCENTAGE (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result =
	    fo_integer_new_with_value (fo_percentage_get_value (arg1) * 0.01 *
				       fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_percentage_get_value (arg1) * 0.01 *
					     fo_number_get_value (arg2));
	}
      else if (FO_IS_LENGTH (arg2))
	{
	result =
	  fo_length_new_with_value (fo_percentage_get_value (arg1) * 0.01 *
				    fo_length_get_value (arg2));
	}
      else if (FO_IS_PERCENTAGE (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 fo_percentage_get_value (arg1) * 0.01 *
				 fo_percentage_get_value (arg2));
	}
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_MUL,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_MUL],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg1);
  g_object_unref (arg2);

  return result;
}

/**
 * fo_datatype_div:
 * @arg1: #FoDatatype.
 * @arg2: #FoDatatype.
 * 
 * Find divisor of values of @arg1 and @arg2.  @arg1 and @arg2 are
 * unchanged.
 * 
 * The type of the return value depends on the types of @arg1 and
 * @arg2:
 *
 * fo_datatype_div (#FoInteger,    #FoInteger)    --> #FoInteger
 * fo_datatype_div (#FoInteger,    #FoNumber)     --> #FoNumber
 * fo_datatype_div (#FoNumber,     #FoInteger)    --> #FoNumber
 * fo_datatype_div (#FoNumber,     #FoNumber)     --> #FoNumber
 * fo_datatype_div (#FoLength,     #FoLength)     --> #FoNumber
 * fo_datatype_div (#FoLength,     #FoInteger)    --> #FoLength
 * fo_datatype_div (#FoLength,     #FoNumber)     --> #FoLength
 * fo_datatype_div (#FoLength,     #FoPercentage) --> #FoLength
 * fo_datatype_div (#FoPercentage, #FoPercentage) --> #FoPercentage
 * fo_datatype_div (#FoPercentage, #FoNumber)     --> #FoPercentage
 * fo_datatype_div (#FoPercentage, #FoInteger)    --> #FoPercentage
 *
 * Return value: #FoDatatype with value that is equal to divisor of
 * values of @arg1 and @arg2, or #FoError if cannot compute divisor of
 * @arg1 and @arg2.  The type of the return value depends on the types
 * of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_div (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);

  if (FO_IS_INTEGER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_integer_new_with_value (fo_integer_get_value (arg1) /
					      fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_integer_get_value (arg1) /
					     fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_NUMBER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) /
					     fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_number_get_value (arg1) /
					     fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_LENGTH (arg1))
    {
      if (FO_IS_LENGTH (arg2))
	{
	  result = fo_number_new_with_value (fo_length_get_value (arg1) /
					     fo_length_get_value (arg2));
	}
      else if (FO_IS_INTEGER (arg2))
	{
	result = fo_length_new_with_value (fo_length_get_value (arg1) /
					   fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	result = fo_length_new_with_value (fo_length_get_value (arg1) /
					   fo_number_get_value (arg2));
	}
      else if (FO_IS_PERCENTAGE (arg2))
	{
	result =
	  fo_length_new_with_value (fo_length_get_value (arg1) /
				    (0.01 * fo_percentage_get_value (arg2)));
	}
    }
  else if (FO_IS_PERCENTAGE (arg1))
    {
      if (FO_IS_PERCENTAGE (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 fo_percentage_get_value (arg1) /
				 fo_percentage_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 fo_percentage_get_value (arg1) /
				 fo_number_get_value (arg2));
	}
      else if (FO_IS_INTEGER (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 fo_percentage_get_value (arg1) /
				 fo_integer_get_value (arg2));
	}
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_DIV,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_DIV],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg1);
  g_object_unref (arg2);

  return result;
}

/**
 * fo_datatype_mod:
 * @arg1: #FoDatatype.
 * @arg2: #FoDatatype.
 * 
 * Find modulus of values of @arg1 and @arg2.  @arg1 and @arg2 are
 * unchanged.
 * 
 * The type of the return value depends on the types of @arg1 and
 * @arg2:
 *
 * fo_datatype_mod (#FoInteger,    #FoInteger)    --> #FoInteger
 * fo_datatype_mod (#FoInteger,    #FoNumber)     --> #FoNumber
 * fo_datatype_mod (#FoNumber,     #FoInteger)    --> #FoNumber
 * fo_datatype_mod (#FoNumber,     #FoNumber)     --> #FoNumber
 * fo_datatype_mod (#FoLength,     #FoLength)     --> #FoNumber
 * fo_datatype_mod (#FoLength,     #FoInteger)    --> #FoNumber
 * fo_datatype_mod (#FoLength,     #FoNumber)     --> #FoNumber
 * fo_datatype_mod (#FoLength,     #FoPercentage) --> #FoNumber
 * fo_datatype_mod (#FoPercentage, #FoPercentage) --> #FoNumber
 * fo_datatype_mod (#FoPercentage, #FoNumber)     --> #FoPercentage
 * fo_datatype_mod (#FoPercentage, #FoInteger)    --> #FoPercentage
 *
 * Return value: #FoDatatype with value that is equal to modulus of
 * values of @arg1 and @arg2, or #FoError if cannot compute modulus of
 * @arg1 and @arg2.  The type of the return value depends on the types
 * of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_mod (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);

  if (FO_IS_INTEGER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_integer_new_with_value (fo_integer_get_value (arg1) %
					      fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value (fo_integer_get_value (arg1) %
					     (int) fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_NUMBER (arg1))
    {
      if (FO_IS_INTEGER (arg2))
	{
	  result = fo_number_new_with_value ((int) fo_number_get_value (arg1) %
					     fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value ((int) fo_number_get_value (arg1) %
					     (int) fo_number_get_value (arg2));
	}
    }
  else if (FO_IS_LENGTH (arg1))
    {
      if (FO_IS_LENGTH (arg2))
	{
	  result = fo_number_new_with_value ((int) fo_length_get_value (arg1) %
					     (int) fo_length_get_value (arg2));
	}
      else if (FO_IS_INTEGER (arg2))
	{
	  result = fo_number_new_with_value ((int) fo_length_get_value (arg1) %
					     fo_integer_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	  result = fo_number_new_with_value ((int) fo_length_get_value (arg1) %
					     (int) fo_number_get_value (arg2));
	}
      else if (FO_IS_PERCENTAGE (arg2))
	{
	  result = fo_number_new_with_value ((int) fo_length_get_value (arg1) %
					     (int) (0.01 *
						    fo_percentage_get_value (arg2)));
	}
    }
  else if (FO_IS_PERCENTAGE (arg1))
    {
      if (FO_IS_PERCENTAGE (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 (int) fo_percentage_get_value (arg1) %
				 (int) fo_percentage_get_value (arg2));
	}
      else if (FO_IS_NUMBER (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 (int) fo_percentage_get_value (arg1) %
				 (int) fo_number_get_value (arg2));
	}
      else if (FO_IS_INTEGER (arg2))
	{
	result = fo_percentage_new ();

	fo_percentage_set_value (result,
				 (int) fo_percentage_get_value (arg1) %
				 (int) fo_integer_get_value (arg2));
	}
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_MOD,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_MOD],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg1);
  g_object_unref (arg2);

  return result;
}

/**
 * fo_datatype_max:
 * @arg1: Instance of child type of #FoDatatype.
 * @arg2: #FoDatatype of same child type as @arg1.
 * 
 * Find maximum of values of @arg1 and @arg2.  @arg1 and @arg2 are
 * unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg1 and @arg2 and with
 * value that is equal to maximum of values of @arg1 and @arg2, or
 * #FoError if cannot compute maximum of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_max (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);

  if (FO_IS_NUMBER (arg1) && FO_IS_NUMBER (arg2))
    {
      result =
	g_object_ref (fo_number_get_value (arg1) >
		      fo_number_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_LENGTH (arg1) && FO_IS_LENGTH (arg2))
    {
      result =
	g_object_ref (fo_length_get_value (arg1) >
		      fo_length_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_INTEGER (arg1) && FO_IS_INTEGER (arg2))
    {
      result =
	g_object_ref (fo_integer_get_value (arg1) >
		      fo_integer_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_NUMBER (arg1) && FO_IS_INTEGER (arg2))
    {
      result =
	g_object_ref (fo_number_get_value (arg1) >
		      fo_integer_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_INTEGER (arg1) && FO_IS_NUMBER (arg2))
    {
      result =
	g_object_ref (fo_integer_get_value (arg1) >
		      fo_number_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_PERCENTAGE (arg1) && FO_IS_PERCENTAGE (arg2))
    {
      result =
	g_object_ref (fo_percentage_get_value (arg1) >
		      fo_percentage_get_value (arg2) ?
		      arg1 : arg2);
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_MAX,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_MAX],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref(arg1);
  g_object_unref(arg2);

  return result;
}

/**
 * fo_datatype_min:
 * @arg1: Instance of child type of #FoDatatype.
 * @arg2: #FoDatatype of same child type as @arg1.
 * 
 * Find minimum of values of @arg1 and @arg2.  @arg1 and @arg2 are
 * unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg1 and @arg2 and with
 * value that is equal to minimum of values of @arg1 and @arg2, or
 * #FoError if cannot compute minimum of @arg1 and @arg2.
 **/
FoDatatype*
fo_datatype_min (FoDatatype *arg1,
		 FoDatatype *arg2)
{
  FoDatatype *result = NULL;

  g_return_val_if_fail (FO_IS_DATATYPE (arg1), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (arg2), NULL);
  
  if (FO_IS_NUMBER (arg1) && FO_IS_NUMBER (arg2))
    {
      result =
	g_object_ref (fo_number_get_value (arg1) <
		      fo_number_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_LENGTH (arg1) && FO_IS_LENGTH (arg2))
    {
      result =
	g_object_ref (fo_length_get_value (arg1) <
		      fo_length_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_INTEGER (arg1) && FO_IS_INTEGER (arg2))
    {
      result =
	g_object_ref (fo_integer_get_value (arg1) <
		      fo_integer_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_NUMBER (arg1) && FO_IS_INTEGER (arg2))
    {
      result =
	g_object_ref (fo_number_get_value (arg1) <
		      fo_integer_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_INTEGER (arg1) && FO_IS_NUMBER (arg2))
    {
      result =
	g_object_ref (fo_integer_get_value (arg1) <
		      fo_number_get_value (arg2) ?
		      arg1 : arg2);
    }
  else if (FO_IS_PERCENTAGE (arg1) && FO_IS_PERCENTAGE (arg2))
    {
      result =
	g_object_ref (fo_percentage_get_value (arg1) <
		      fo_percentage_get_value (arg2) ?
		      arg1 : arg2);
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_MIN,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_MIN],
		     fo_object_sprintf (arg1),
		     fo_object_sprintf (arg2));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg1);
  g_object_unref (arg2);

  return result;
}

/**
 * fo_datatype_floor:
 * @arg: #FoDatatype.
 * 
 * Computed floor value of value of @arg.  @arg is unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg and with value that
 * is floor value of value of @arg, or #FoError if cannot compute
 * floor of @arg.
 **/
FoDatatype*
fo_datatype_floor (FoDatatype *arg)
{
  FoDatatype *result = NULL;
  gdouble value;

  g_return_val_if_fail (FO_IS_DATATYPE (arg), NULL);

  if (FO_IS_NUMBER (arg))
    {
    value = fo_number_get_value (arg);

    result = fo_integer_new_with_value (floor (value));
    }
  else if (FO_IS_PERCENTAGE (arg))
    {
    value = fo_percentage_get_value (arg);

    result = fo_percentage_new ();
    fo_percentage_set_value (result, floor (value));
    }
  else if (!FO_IS_INTEGER (arg))
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_FLOOR,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_FLOOR],
		     fo_object_sprintf (arg));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg);

  return result;
}

/**
 * fo_datatype_ceiling:
 * @arg: #FoDatatype.
 * 
 * Computed ceiling value of value of @arg.  @arg is unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg and with value that
 * is ceiling value of value of @arg, or #FoError if cannot compute
 * ceiling of @arg.
 **/
FoDatatype*
fo_datatype_ceiling (FoDatatype *arg)
{
  FoDatatype *result = NULL;
  gdouble value;

  g_return_val_if_fail (FO_IS_DATATYPE (arg), NULL);

  if (FO_IS_NUMBER (arg))
    {
    value = fo_number_get_value (arg);

    result = fo_integer_new_with_value (ceil (value));
    }
  else if (FO_IS_PERCENTAGE (arg))
    {
    value = fo_percentage_get_value (arg);

    result = fo_percentage_new ();
    fo_percentage_set_value (result, ceil (value));
    }
  else if (!FO_IS_INTEGER (arg))
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_CEILING,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_CEILING],
		     fo_object_sprintf (arg));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg);

  return result;
}

/**
 * fo_datatype_round:
 * @arg: #FoDatatype to round.
 * 
 * Computed rounded value of value of @arg.  @arg is unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg and with value that
 * is rounded value of value of @arg, of #FoError is cannot round
 * @arg.
 **/
FoDatatype*
fo_datatype_round (FoDatatype *arg)
{
  FoDatatype *result = NULL;
  gdouble result_value;
  gdouble value;

  g_return_val_if_fail (FO_IS_DATATYPE (arg), NULL);

  if (FO_IS_NUMBER (arg))
    {
      value = fo_number_get_value (arg);
      result_value = (double)((int) value);

      if (value >= result_value + 0.5)
	{
	  result_value = result_value + 1;
	}

      result = fo_integer_new_with_value (result_value);
    }
  else if (FO_IS_PERCENTAGE (arg))
    {
      value = fo_percentage_get_value (arg);
      result_value = (double)((int) value);

      if (value >= result_value + 0.5)
	{
	  result_value = result_value + 1;
	}

      result = fo_percentage_new ();
      fo_percentage_set_value (result, result_value);
    }
  else if (!FO_IS_INTEGER (arg))
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_ROUND,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_ROUND],
		     fo_object_sprintf (arg));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg);

  return result;
}

/**
 * fo_datatype_abs:
 * @arg: #FoDatatype.
 * 
 * Compute absolute value of value of @arg.  @arg is unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg and with value that
 * is absolute value of value of @arg, or #FoError if cannot compute
 * absolute value of @arg.
 **/
FoDatatype*
fo_datatype_abs (FoDatatype *arg)
{
  FoDatatype *result = NULL;
  gdouble value;

  g_return_val_if_fail (FO_IS_DATATYPE (arg), NULL);

  if (FO_IS_NUMBER (arg))
    {
    value = fo_number_get_value (arg);

    if (value < 0)
      {
	result = fo_number_new_with_value (-value);
      }
    else
      {
	g_object_ref (arg);
      }
    }
  else if (FO_IS_PERCENTAGE (arg))
    {
    value = fo_percentage_get_value (arg);

    if (value < 0)
      {
	result = fo_percentage_new ();
	fo_percentage_set_value (result, -value);
      }
    else
      {
	g_object_ref (arg);
      }
    }
  else if (FO_IS_LENGTH (arg))
    {
      value = fo_length_get_value (arg);

    if (value < 0)
      {
	result = fo_length_new_with_value (-value);
      }
    else
      {
	g_object_ref (arg);
      }
    }
  else if (FO_IS_INTEGER (arg))
    {
    value = fo_integer_get_value (arg);

    if (value < 0)
      {
	result = fo_integer_new_with_value (-value);
      }
    else
      {
	g_object_ref (arg);
      }
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_ABS,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_ABS],
		     fo_object_sprintf (arg));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg);

  return result;
}

/**
 * fo_datatype_negate:
 * @arg: #FoDatatype to negate.
 * 
 * Compute negated value of value of @arg.  @arg is unchanged.
 * 
 * Return value: #FoDatatype of same type as @arg and negated value,
 * or #FoError if cannot compute negated value of @arg.
 **/
FoDatatype*
fo_datatype_negate (FoDatatype *arg)
{
  FoDatatype *result = NULL;
  gdouble value;

  g_return_val_if_fail (FO_IS_DATATYPE (arg), NULL);

  if (FO_IS_NUMBER (arg))
    {
      value = fo_number_get_value (arg);

      result = fo_number_new_with_value (-value);
    }
  else if (FO_IS_PERCENTAGE (arg))
    {
      value = fo_percentage_get_value (arg);

      result = fo_percentage_new ();
      fo_percentage_set_value (result, -value);
    }
  else if (FO_IS_INTEGER (arg))
    {
      value = fo_integer_get_value (arg);

      result = fo_integer_new_with_value (-value);
    }
  else if (FO_IS_LENGTH (arg))
    {
      value = fo_length_get_value (arg);

      result = fo_length_new_with_value (-value);
    }
  else
    {
      GError *error =
	g_error_new (FO_DATATYPE_ERROR,
		     FO_DATATYPE_ERROR_NEGATE,
		     fo_datatype_error_messages[FO_DATATYPE_ERROR_NEGATE],
		     fo_object_sprintf (arg));

      result = fo_error_new_with_value (error);				   
    }

  g_object_unref (arg);

  return result;
}
