/* Fo
 * fo-id.c: Id datatype
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-id.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoId
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoIdClass
{
  FoDatatypeClass parent_class;

};

static void fo_id_class_init   (FoIdClass     *klass);
static void fo_id_get_property (GObject       *object,
				guint          prop_id,
				GValue        *value,
				GParamSpec    *pspec);
static void fo_id_set_property (GObject       *object,
				guint          prop_id,
				const GValue  *value,
				GParamSpec    *pspec);
static void fo_id_finalize     (GObject       *object);

static FoDatatype * fo_id_copy (FoDatatype    *datatype);
static gchar*       fo_id_sprintf (FoObject *object);

static FoDatatype * fo_id_new       (void);
static void         fo_id_set_value (FoDatatype  *id,
				     const gchar* new_value);

static gpointer parent_class;

/**
 * fo_id_get_type:
 *
 * Register the #FoId object type.
 *
 * Return value: #GType value of the #FoId object type.
 **/
GType
fo_id_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoIdClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_id_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoId),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoId",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_id_class_init:
 * @klass: #FoIdClass class object to initialise.
 *
 * Implements #GClassInitFunc for #FoIdClass.
 **/
void
fo_id_class_init (FoIdClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_id_finalize;

  object_class->set_property = fo_id_set_property;
  object_class->get_property = fo_id_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
						     _("Value"),
						     _("Id value"),
							NULL,
						     G_PARAM_READWRITE));

  FO_DATATYPE_CLASS (klass)->copy = fo_id_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_id_sprintf;
}

/**
 * fo_id_finalize:
 * @object: #FoId object to finalize.
 *
 * Implements #GObjectFinalizeFunc for #FoId.
 **/
void
fo_id_finalize (GObject *object)
{
  FoId *id;

  id = FO_ID (object);

  g_free(id->value);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_id_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 *
 * Implements #GObjectGetPropertyFunc for #FoId.
 **/
void
fo_id_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *id;

  id = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_id_get_value (id));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_id_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 *
 * Implements #GObjectSetPropertyFunc for #FoId.
 **/
void
fo_id_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *id;

  id = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_id_set_value (id, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_id_new:
 *
 * Creates a new #FoId initialized to default value.
 *
 * Return value: the new #FoId
 **/
FoDatatype *
fo_id_new (void)
{
  FoDatatype *id;

  id = FO_DATATYPE (g_object_new (fo_id_get_type (), NULL));

  return id;
}

/**
 * fo_id_new_with_value:
 * @value: Id of new #FoId.
 *
 * Creates a new #FoId initialized to @value.
 *
 * Return value: the new #FoId.
 **/
FoDatatype *
fo_id_new_with_value (const gchar* value)
{
  FoDatatype *id = fo_id_new ();

  fo_id_set_value (id, value);

  return id;
}

/**
 * fo_id_get_value:
 * @id: #FoId.
 *
 * Get the value of @id.
 *
 * Return value: String value of @id.  Must be freed by caller.
 **/
gchar*
fo_id_get_value (FoDatatype *id)
{
  g_return_val_if_fail (id != NULL, NULL);
  g_return_val_if_fail (FO_IS_ID (id), NULL);

  return g_strdup (FO_ID (id)->value);
}

/**
 * fo_id_set_value:
 * @id:    #FoId.
 * @new_value: New value for @id.
 *
 * Set the value of @id.
 **/
void
fo_id_set_value (FoDatatype *id,
		 const gchar* new_value)
{
  g_return_if_fail (id != NULL);
  g_return_if_fail (FO_IS_ID (id));

  FO_ID (id)->value = g_strdup (new_value);
  /*g_object_notify(G_OBJECT(id), "value");*/
}

/**
 * fo_id_copy:
 * @datatype: #FoId to be copied.
 *
 * Create a copy of @datatype.
 *
 * Return value: New #FoId.
 **/
FoDatatype*
fo_id_copy(FoDatatype *datatype)
{
  FoDatatype* id;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_ID (datatype), NULL);

  id = fo_id_new ();
  FO_ID (id)->value = g_strdup (FO_ID (datatype)->value);

  return (FO_DATATYPE(id));
}

/**
 * fo_id_sprintf:
 * @object: #FoId to be printed.
 *
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 *
 * Return value: String representation of @object.
 **/
gchar*
fo_id_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_ID (object), NULL);

  return (g_strdup_printf("%s", FO_ID (object)->value));
}
