/* Fo
 * fo-retrieve_marker.c: Retrieve Marker formatting object
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
#include "fo-retrieve-marker.h"


enum {
  PROP_0
};

struct _FoRetrieveMarker
{
  FoFo parent_instance;

};

struct _FoRetrieveMarkerClass
{
  FoFoClass parent_class;
  
};

static void fo_retrieve_marker_class_init  (FoRetrieveMarkerClass *klass);
static void fo_retrieve_marker_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_retrieve_marker_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_retrieve_marker_finalize    (GObject           *object);
static void fo_retrieve_marker_debug_dump_properties (FoFo *fo, gint depth);

static gpointer parent_class;

GType
fo_retrieve_marker_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoRetrieveMarkerClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_retrieve_marker_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoRetrieveMarker),
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
                                            "FoRetrieveMarker",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_NEUTRAL_FO,
                                   &fo_neutral_fo_info);
    }
  
  return object_type;
}

static void
fo_retrieve_marker_class_init (FoRetrieveMarkerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_retrieve_marker_finalize;

  object_class->set_property = fo_retrieve_marker_set_property;
  object_class->get_property = fo_retrieve_marker_get_property;

  FO_FO_CLASS (klass)->debug_dump_properties = fo_retrieve_marker_debug_dump_properties;
  FO_FO_CLASS (klass)->update_from_context = fo_retrieve_marker_update_from_context;

}

static void
fo_retrieve_marker_finalize (GObject *object)
{
  FoRetrieveMarker *fo_retrieve_marker;

  fo_retrieve_marker = FO_RETRIEVE_MARKER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_retrieve_marker_set_property (GObject     *object,
				 guint        prop_id,
				 const GValue *value G_GNUC_UNUSED,
				 GParamSpec   *pspec)
{
  FoRetrieveMarker *fo_retrieve_marker;

  fo_retrieve_marker = FO_RETRIEVE_MARKER (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_retrieve_marker_get_property (GObject    *object,
				 guint       prop_id,
				 GValue     *value G_GNUC_UNUSED,
				 GParamSpec *pspec)
{
  FoRetrieveMarker *fo_retrieve_marker;

  fo_retrieve_marker = FO_RETRIEVE_MARKER (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_retrieve_marker_new:
 * 
 * Creates a new #FoRetrieveMarker initialized to default value.
 * 
 * Return value: the new #FoRetrieveMarker
 **/
FoFo*
fo_retrieve_marker_new (void)
{
  return FO_FO (g_object_new (fo_retrieve_marker_get_type (), NULL));
}

void
fo_retrieve_marker_update_from_context (FoFo      *fo,
					FoContext *context G_GNUC_UNUSED)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_RETRIEVE_MARKER (fo));

}

void
fo_retrieve_marker_debug_dump_properties (FoFo *fo,
					  gint  depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_RETRIEVE_MARKER (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s(No properties)",
	 indent);

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
