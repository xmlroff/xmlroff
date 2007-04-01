/* Fo
 * fo-length-cond.c: 'length-conditional' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-length-conditional.c,v 1.7 2005/03/10 17:38:30 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-length-conditional.h"
#include "fo-boolean.h"
#include "fo-enum.h"
#include "fo-length.h"
#include "fo-percentage.h"


enum {
  PROP_0,
  PROP_LENGTH,
  PROP_CONDITY
};

struct _FoLengthCond
{
  FoDatatype parent_instance;

  gdouble  length;
  gboolean retain;
};

struct _FoLengthCondClass
{
  FoDatatypeClass parent_class;
};

static void fo_length_cond_init         (FoLengthCond      *length_cond);
static void fo_length_cond_class_init   (FoLengthCondClass *klass);
static void fo_length_cond_set_property (GObject           *object,
					 guint              prop_id,
					 const GValue      *value,
					 GParamSpec        *pspec);
static void fo_length_cond_get_property (GObject           *object,
					 guint              prop_id,
					 GValue            *value,
					 GParamSpec        *pspec);
static void fo_length_cond_finalize     (GObject           *object);

gchar*      fo_length_cond_sprintf      (FoObject          *object);
FoDatatype* fo_length_cond_copy         (FoDatatype        *datatype);

static gpointer parent_class;

/**
 * fo_length_cond_get_type:
 * @void: 
 * 
 * Register the #FoLengthCond object type.
 * 
 * Return value: GType value of the #FoLengthCond object type.
 **/
GType
fo_length_cond_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLengthCondClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_length_cond_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLengthCond),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_length_cond_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoLengthCond",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_length_cond_init:
 * @length_cond: #FoLengthCond object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoLengthCond.
 **/
void
fo_length_cond_init (FoLengthCond *length_cond)
{
  length_cond->length = 0.0;
  length_cond->retain = FALSE;
}

/**
 * fo_length_cond_class_init:
 * @klass: FoLengthCondClass object to initialise
 * 
 * Implements GClassInitFunc for FoLengthCondClass
 **/
void
fo_length_cond_class_init (FoLengthCondClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_length_cond_finalize;

  object_class->set_property = fo_length_cond_set_property;
  object_class->get_property = fo_length_cond_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_length_cond_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_length_cond_copy;

  g_object_class_install_property (object_class,
                                   PROP_LENGTH,
                                   g_param_spec_double ("length",
							_("Length"),
							_("Length_Cond length"),
						       -G_MAXDOUBLE,
						       G_MAXDOUBLE,
						       0,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_CONDITY,
                                   g_param_spec_boolean ("conditionality",
							 _("Conditionality"),
							 _("Whether or not the space must always be retained"),
							 FALSE,
							 G_PARAM_READWRITE |
							 G_PARAM_CONSTRUCT_ONLY));
}

static void
fo_length_cond_finalize (GObject *object)
{
  FoLengthCond *length_cond;

  length_cond = FO_LENGTH_COND (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_length_cond_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoSpace
 **/
static void
fo_length_cond_get_property (GObject         *object,
			     guint            prop_id,
			     GValue          *value,
			     GParamSpec      *pspec)
{
  FoDatatype *length_cond;

  length_cond = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_LENGTH:
      g_value_set_double (value, fo_length_cond_get_length (length_cond));
      break;
    case PROP_CONDITY:
      g_value_set_boolean (value, fo_length_cond_get_condity (length_cond));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_cond_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoSpace
 **/
static void
fo_length_cond_set_property (GObject         *object,
			     guint            prop_id,
			     const GValue    *value,
			     GParamSpec      *pspec)
{
  FoDatatype *length_cond;

  length_cond = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_LENGTH:
      fo_length_cond_set_length (length_cond, g_value_get_double (value));
      break;
    case PROP_CONDITY:
      fo_length_cond_set_condity (length_cond, g_value_get_boolean (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_cond_new:
 * 
 * Creates a new #FoLengthCond initialized to default value.
 * 
 * Return value: the new #FoLengthCond
 **/
FoDatatype *
fo_length_cond_new (void)
{
  FoDatatype *length_cond = NULL;

  length_cond = FO_DATATYPE (g_object_new (fo_length_cond_get_type (),
					   NULL));
  
  return length_cond;
}

/**
 * fo_length_cond_new_with_value:
 * @length:  Length component of the new #FoLengthCond
 * @condity: Conditionality component of the new #FoLengthCond
 * 
 * Creates a new #FoLengthCond set to @length and @condity
 * 
 * Return value: The new #FoLengthCond
 **/
FoDatatype*
fo_length_cond_new_with_value (gdouble  length,
			       gboolean condity)
{
  FoDatatype *length_cond = fo_length_cond_new ();

  fo_length_cond_set_length  (length_cond, length);
  fo_length_cond_set_condity (length_cond, condity);

  return length_cond;
}

/**
 * fo_length_cond_new_from_length:
 * @length: #FoLength to use as initial value.
 * 
 * Creates a new #FoLengthCond with .length component set to @length
 * and .conditionality component set to default value.
 * 
 * Return value: New #FoLengthCond.
 **/
FoDatatype*
fo_length_cond_new_from_length (FoDatatype *length)
{
  FoDatatype *length_cond;
  gdouble length_val;

  g_return_val_if_fail (FO_IS_LENGTH (length), NULL);

  length_val = fo_length_get_value (length);

  length_cond = fo_length_cond_new ();

  fo_length_cond_set_length (length_cond, length_val);

  return length_cond;
}

/**
 * fo_length_cond_set_length:
 * @datatype:    #FoLengthCond
 * @new_length:  New .length value
 * 
 * Sets the .length component of @datatype
 **/
void
fo_length_cond_set_length (FoDatatype *datatype,
			   gdouble     new_length)
{
  FoLengthCond *length_cond = (FoLengthCond *) datatype;

  g_return_if_fail (length_cond != NULL);
  g_return_if_fail (FO_IS_LENGTH_COND (length_cond));

  length_cond->length = new_length;
  /*g_object_notify(G_OBJECT(length_cond), "length");*/
}

/**
 * fo_length_cond_get_length:
 * @datatype: #FoLengthCond
 * 
 * Gets the .length component value of @datatype
 * 
 * Return value: The .length value of @datatype
 **/
gdouble
fo_length_cond_get_length (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0.0);
  g_return_val_if_fail (FO_IS_LENGTH_COND (datatype), 0.0);

  return FO_LENGTH_COND (datatype)->length;
}

/**
 * fo_length_cond_set_condity:
 * @datatype:     #FoLengthCond
 * @new_condity:  New .condity value
 * 
 * Sets the .condity component of @datatype
 **/
void
fo_length_cond_set_condity (FoDatatype *datatype,
			    gboolean    new_condity)
{
  FoLengthCond *length_cond = (FoLengthCond *) datatype;

  g_return_if_fail (length_cond != NULL);
  g_return_if_fail (FO_IS_LENGTH_COND (length_cond));

  length_cond->retain = new_condity;
  /*g_object_notify(G_OBJECT(length_cond), "conditionality");*/
}

/**
 * fo_length_cond_get_condity:
 * @datatype: #FoLengthCond
 * 
 * Gets the .conditionality component value of @datatype
 * 
 * Return value: The .conditionality component value of @datatype
 **/
gboolean
fo_length_cond_get_condity (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, FALSE);
  g_return_val_if_fail (FO_IS_LENGTH_COND (datatype), FALSE);

  return FO_LENGTH_COND (datatype)->retain;
}

/**
 * fo_length_cond_sprintf:
 * @object: #FoLengthCond whose value is to be printed
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoLengthCond.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object
 **/
gchar*
fo_length_cond_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_COND (object), NULL);

  return
    g_strdup_printf ("length: %0gpt; condity: %s",
		     FO_LENGTH_COND (object)->length,
		     FO_LENGTH_COND (object)->retain ? "retain" : "discard");
}

/**
 * fo_length_cond_copy:
 * @datatype: Source #FoLengthCond
 * 
 * Creates a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_length_cond_copy (FoDatatype *datatype)
{
  FoDatatype* length_cond;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_COND (datatype), NULL);

  length_cond = fo_length_cond_new ();
  FO_LENGTH_COND (length_cond)->length = FO_LENGTH_COND (datatype)->length;
  FO_LENGTH_COND (length_cond)->retain = FO_LENGTH_COND (datatype)->retain;

  return (length_cond);
}

/**
 * fo_length_cond_get_length_cond_zero:
 * 
 * Get an #FoLengthCond with the well-known value of 0pt/discard.
 * 
 * Return value: The #FoLengthCond.
 **/
FoDatatype *
fo_length_cond_get_length_cond_zero (void)
{
  static FoDatatype *length_cond = NULL;

  if (length_cond == NULL)
    {
      length_cond = fo_length_cond_new ();
    }

  return length_cond;
}

/**
 * fo_length_cond_resolve:
 * @shortform: Single-value short form of the length-conditional, or NULL
 * @length:    .length component of the space, or NULL
 * @condity:   .conditionality component of the space, or NULL
 * @error:     #GError used for reporting errors
 * 
 * Resolve the shortform and components of the length-conditional in
 * accordance with Section 5.11, Datatypes, of the XSL 1.0
 * Recommendation.
 * 
 * Return value: Compound space datatype, or NULL if an error occurred
 **/
FoDatatype*
fo_length_cond_resolve (FoDatatype *shortform,
			FoDatatype *length,
			FoDatatype *condity,
			GError **error)
{
  FoDatatype *use_length_cond = NULL;

  g_return_val_if_fail (shortform == NULL ||
			FO_IS_LENGTH (shortform) ||
			FO_IS_LENGTH_COND (shortform),
			NULL);
  g_return_val_if_fail (length == NULL ||
			FO_IS_LENGTH (length),
			NULL);
  g_return_val_if_fail (condity == NULL ||
			FO_IS_BOOLEAN (condity), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_LENGTH_COND (shortform) &&
      length == NULL &&
      condity == NULL)
    {
      return fo_length_cond_copy (shortform);
    }

  if (shortform == NULL)
    {
      use_length_cond = fo_length_cond_new ();
    }
  else if (FO_IS_LENGTH_COND (shortform))
    {
      use_length_cond = fo_length_cond_copy (shortform);
    }
  else if (FO_IS_LENGTH (shortform))
    {
      use_length_cond = fo_length_cond_new_from_length (shortform);
    }
  else
    {
      g_assert_not_reached ();
    }

  if (length != NULL)
    {
      if (FO_IS_LENGTH (length))
	{
	  fo_length_cond_set_length (use_length_cond,
				     fo_length_get_value (length));
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  if (condity != NULL)
    {
      gboolean condity_boolean =
	fo_boolean_get_value (condity);

      fo_length_cond_set_condity (use_length_cond, condity_boolean);
    }

  return use_length_cond;
}
