/* Fo
 * fo-datatype-uri-specification.c: Uri Specification datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-uri-specification.c,v 1.8 2005/10/02 22:56:47 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-uri-specification.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoUriSpecification
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoUriSpecificationClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_uri_specification_init         (FoUriSpecification      *uri_specification);
static void fo_uri_specification_class_init   (FoUriSpecificationClass *klass);
static void fo_uri_specification_set_property (GObject       *object,
					       guint          prop_id,
					       const GValue  *value,
					       GParamSpec    *pspec);
static void fo_uri_specification_get_property (GObject       *object,
					       guint          prop_id,
					       GValue        *value,
					       GParamSpec    *pspec);
static void fo_uri_specification_finalize     (GObject       *object);

static FoDatatype * fo_uri_specification_copy      (FoDatatype *datatype);
static gchar*       fo_uri_specification_sprintf   (FoObject *object);
static void         fo_uri_specification_set_value (FoDatatype  *uri_specification,
						    const gchar* new_value);

static gpointer parent_class;

/**
 * fo_uri_specification_get_type:
 * 
 * Register the #FoUriSpecification object type.
 * 
 * Return value: GType value of the #FoUriSpecification object type.
 **/
GType
fo_uri_specification_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoUriSpecificationClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_uri_specification_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoUriSpecification),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_uri_specification_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoUriSpecification",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_uri_specification_init:
 * @uri_specification: #FoUriSpecification object to initialise.
 * 
 * Initialises @uri_specification.
 **/
void
fo_uri_specification_init (FoUriSpecification *uri_specification)
{
  uri_specification->value = NULL;
}

/**
 * fo_uri_specification_class_init:
 * @klass: #FoUriSpecificationClass object to initialise
 * 
 * Implements GClassInitFunc for #FoUriSpecificationClass
 **/
void
fo_uri_specification_class_init (FoUriSpecificationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_uri_specification_finalize;

  object_class->set_property = fo_uri_specification_set_property;
  object_class->get_property = fo_uri_specification_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_uri_specification_sprintf;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
							_("Value"),
							_("Uri-specification value"),
							NULL,
							G_PARAM_READWRITE));

  FO_DATATYPE_CLASS (klass)->copy = fo_uri_specification_copy;
}

/**
 * fo_uri_specification_finalize:
 * @object: #FoUriSpecification object to finalize
 * 
 * Implements GObjectFinalizeFunc for #FoUriSpecification
 **/
void
fo_uri_specification_finalize (GObject *object)
{
  FoUriSpecification *uri_specification;

  uri_specification = FO_URI_SPECIFICATION (object);

  g_free(uri_specification->value);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


void
fo_uri_specification_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *uri_specification;

  uri_specification = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_uri_specification_set_value (uri_specification, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

void
fo_uri_specification_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *uri_specification;

  uri_specification = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_uri_specification_get_value (uri_specification));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_uri_specification_new:
 * 
 * Creates a new #FoUriSpecification initialized to default value.
 * 
 * Return value: the new #FoUriSpecification
 **/
FoDatatype *
fo_uri_specification_new (void)
{
  FoDatatype *uri_specification;

  uri_specification = FO_DATATYPE (g_object_new (fo_uri_specification_get_type (), NULL));
  
  return uri_specification;
}

/**
 * fo_uri_specification_new_with_value:
 * @new_value: Value to use.
 * 
 * Creates a new #FoUriSpecification initialized to specified value.
 * 
 * Return value: the new #FoUriSpecification
 **/
FoDatatype *
fo_uri_specification_new_with_value (const gchar* new_value)
{
  FoDatatype *uri_specification = fo_uri_specification_new();

  fo_uri_specification_set_value (uri_specification, new_value);

  return uri_specification;
}

/* value */
gchar*
fo_uri_specification_get_value (FoDatatype *uri_specification)
{
  g_return_val_if_fail (uri_specification != NULL, NULL);
  g_return_val_if_fail (FO_IS_URI_SPECIFICATION (uri_specification), NULL);

  return g_strdup (FO_URI_SPECIFICATION (uri_specification)->value);
}

void
fo_uri_specification_set_value (FoDatatype  *uri_specification,
				const gchar* new_value)
{
  g_return_if_fail (uri_specification != NULL);
  g_return_if_fail (FO_IS_URI_SPECIFICATION (uri_specification));

  FO_URI_SPECIFICATION (uri_specification)->value = g_strdup (new_value);
  /*g_object_notify (G_OBJECT (uri_specification), "value");*/
}

/**
 * fo_uri_specification_copy:
 * @datatype: #FoUriSpecification to be copied
 * 
 * Makes a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_uri_specification_copy(FoDatatype *datatype)
{
  FoDatatype *uri_specification;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_URI_SPECIFICATION (datatype), NULL);

  uri_specification = fo_uri_specification_new ();
  FO_URI_SPECIFICATION (uri_specification)->value =
    g_strdup (FO_URI_SPECIFICATION (datatype)->value);

  return (uri_specification);
}

/**
 * fo_uri_specification_sprintf:
 * @object: #FoUriSpecification to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_uri_specification_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_URI_SPECIFICATION (object), NULL);

  return (g_strdup_printf ("url(\"%s\")",
			   FO_URI_SPECIFICATION (object)->value));
}
