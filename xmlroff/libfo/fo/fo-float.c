/* Fo
 * fo-float.c: Float formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-neutral-fo.h"
#include "fo-float.h"


enum {
  PROP_0
};

struct _FoFloat
{
  FoFo parent_instance;

};

struct _FoFloatClass
{
  FoFoClass parent_class;
  
};

static void fo_float_class_init  (FoFloatClass *klass);
static void fo_float_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_float_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_float_finalize    (GObject           *object);
static void fo_float_debug_dump_properties (FoFo *fo, gint depth);

static gpointer parent_class;

GType
fo_float_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoFloatClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_float_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoFloat),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_neutral_fo_info =
      {
        NULL,
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoFloat",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_NEUTRAL_FO,
                                   &fo_neutral_fo_info);
    }
  
  return object_type;
}

static void
fo_float_class_init (FoFloatClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_float_finalize;

  object_class->set_property = fo_float_set_property;
  object_class->get_property = fo_float_get_property;

  FO_FO_CLASS (klass)->debug_dump_properties = fo_float_debug_dump_properties;
}

static void
fo_float_finalize (GObject *object)
{
  FoFloat *fo_float;

  fo_float = FO_FLOAT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_float_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value G_GNUC_UNUSED,
                         GParamSpec      *pspec)
{
  FoFloat *fo_float;

  fo_float = FO_FLOAT (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_float_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value G_GNUC_UNUSED,
                         GParamSpec      *pspec)
{
  FoFloat *fo_float;

  fo_float = FO_FLOAT (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_float_new:
 * 
 * Creates a new #FoFloat initialized to default value.
 * 
 * Return value: the new #FoFloat
 **/
FoFo*
fo_float_new (void)
{
  return FO_FO (g_object_new (fo_float_get_type (),
			      NULL));
}

void
fo_float_debug_dump_properties (FoFo *fo, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FLOAT (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s(No properties)",
	 indent);

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
