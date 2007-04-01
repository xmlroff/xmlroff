/* Fo
 * fo-unknown.c: Unknown datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-unknown.c,v 1.5 2005/03/10 17:38:30 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-unknown.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoUnknown
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoUnknownClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_unknown_init         (FoUnknown      *unknown);
static void fo_unknown_class_init   (FoUnknownClass *klass);
static void fo_unknown_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_unknown_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_unknown_finalize     (GObject       *object);

FoDatatype* fo_unknown_copy (FoDatatype *datatype);
gchar*      fo_unknown_sprintf (FoObject *datatype);

static gpointer parent_class;

GType
fo_unknown_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoUnknownClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_unknown_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoUnknown),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_unknown_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoUnknown",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_unknown_init (FoUnknown *unknown)
{
  unknown->value = NULL;
}

static void
fo_unknown_class_init (FoUnknownClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_unknown_finalize;

  object_class->set_property = fo_unknown_set_property;
  object_class->get_property = fo_unknown_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
						     _("Value"),
						     _("Unknown value"),
							NULL,
						     G_PARAM_READWRITE));

  FO_DATATYPE_CLASS (klass)->copy = fo_unknown_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_unknown_sprintf;
}

static void
fo_unknown_finalize (GObject *object)
{
  FoUnknown *unknown;

  unknown = FO_UNKNOWN (object);

  g_free(unknown->value);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_unknown_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *unknown;

  unknown = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_unknown_set_value (unknown, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_unknown_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *unknown;

  unknown = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_unknown_get_value (unknown));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_unknown_new:
 * 
 * Creates a new #FoUnknown initialized to default value.
 * 
 * Return value: the new #FoUnknown
 **/
FoDatatype *
fo_unknown_new (void)
{
  FoDatatype *unknown;

  unknown = FO_DATATYPE (g_object_new (fo_unknown_get_type (), NULL));
  
  return unknown;
}

/* value */
gchar*
fo_unknown_get_value (FoDatatype *unknown)
{
  g_return_val_if_fail (unknown != NULL, NULL);
  g_return_val_if_fail (FO_IS_UNKNOWN (unknown), NULL);

  return g_strdup (FO_UNKNOWN (unknown)->value);
}

void
fo_unknown_set_value (FoDatatype   *unknown,
		      const gchar*  new_value)
{
  g_return_if_fail (unknown != NULL);
  g_return_if_fail (FO_IS_UNKNOWN (unknown));

  FO_UNKNOWN (unknown)->value = g_strdup (new_value);
  /*g_object_notify (G_OBJECT (unknown), "value");*/
}

FoDatatype *
fo_unknown_copy(FoDatatype *datatype)
{
  FoDatatype* unknown;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_UNKNOWN (datatype), NULL);

  unknown = fo_unknown_new ();
  FO_UNKNOWN (unknown)->value = g_strdup (FO_UNKNOWN (datatype)->value);

  return (FO_DATATYPE(unknown));
}

gchar*
fo_unknown_sprintf (FoObject *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_UNKNOWN (datatype), NULL);

  return (g_strdup_printf("%s", FO_UNKNOWN (datatype)->value));
}
