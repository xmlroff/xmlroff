/* Fo
 * fo-area-reference.c: reference-area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area-reference-private.h"

enum {
  PROP_0,
  PROP_BPD,
  PROP_IPD,
  PROP_SD
};

static void fo_area_reference_class_init  (FoAreaReferenceClass *klass);
static void _get_property (GObject         *object,
			   guint            prop_id,
			   GValue          *value,
			   GParamSpec      *pspec);
static void _set_property (GObject         *object,
			   guint            prop_id,
			   const GValue    *value,
			   GParamSpec      *pspec);
static void fo_area_reference_finalize    (GObject           *object);

static void _debug_dump_properties (FoArea *area,
				    gint    depth);
static void _update_after_clone    (FoArea *clone,
				    FoArea *original);
static FoArea*  _size_request (FoArea *child);

static gpointer parent_class;

GType
fo_area_reference_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaReferenceClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_reference_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaReference),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_AREA,
                                            "FoAreaReference",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_area_reference_class_init (FoAreaReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_reference_finalize;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  FO_AREA_CLASS (klass)->debug_dump_properties = _debug_dump_properties;
  FO_AREA_CLASS (klass)->update_after_clone = _update_after_clone;

  g_object_class_install_property
    (object_class,
     PROP_BPD,
     g_param_spec_uint ("bpd",
			_("Block progression direction"),
			_("Block progression direction of the reference area"),
			0,
			G_MAXUINT,
			0,
			G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_IPD,
     g_param_spec_uint ("ipd",
			_("Inline progression direction"),
			_("Inline progression direction of the reference area"),
			0,
			G_MAXUINT,
			0,
			G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_SD,
     g_param_spec_uint ("sd",
			_("Shift direction"),
			_("Shift direction of the reference area"),
			0,
			G_MAXUINT,
			0,
			G_PARAM_READWRITE));
}

static void
fo_area_reference_finalize (GObject *object)
{
  FoAreaReference *fo_area_reference;

  fo_area_reference = FO_AREA_REFERENCE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
_get_property (GObject         *object,
	       guint            prop_id,
	       GValue          *value,
	       GParamSpec      *pspec)
{
  FoArea *fo_area_reference;

  fo_area_reference = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_BPD:
      g_value_set_uint (value,
			fo_area_reference_get_bpd (fo_area_reference));
      break;
    case PROP_IPD:
      g_value_set_uint (value,
			fo_area_reference_get_ipd (fo_area_reference));
      break;
    case PROP_SD:
      g_value_set_uint (value,
			fo_area_reference_get_sd (fo_area_reference));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
_set_property (GObject         *object,
	       guint            prop_id,
	       const GValue    *value,
	       GParamSpec      *pspec)
{
  FoArea *fo_area_reference;

  fo_area_reference = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_BPD:
      fo_area_reference_set_bpd (fo_area_reference,
				 g_value_get_uint (value));
      break;
    case PROP_IPD:
      fo_area_reference_set_ipd (fo_area_reference,
				 g_value_get_uint (value));
      break;
    case PROP_SD:
      fo_area_reference_set_sd (fo_area_reference,
				g_value_get_uint (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_reference_new:
 * 
 * Creates a new #FoAreaReference initialized to default value.
 * 
 * Return value: the new #FoAreaReference
 **/
FoArea*
fo_area_reference_new (void)
{
  return FO_AREA (g_object_new (fo_area_reference_get_type (),
				NULL));
}

static gchar *
_direction_to_string (FoEnumAreaDirection direction)
{
  gchar *string = NULL;

  switch (direction)
    {
    case FO_ENUM_AREA_DIRECTION_UNKNOWN:
      string = "unknown";
      break;
    case FO_ENUM_AREA_DIRECTION_LR:
      string = "left-to-right";
      break;
    case FO_ENUM_AREA_DIRECTION_RL:
      string = "right-to-left";
      break;
    case FO_ENUM_AREA_DIRECTION_TB:
      string = "top-to-bottom";
      break;
    case FO_ENUM_AREA_DIRECTION_BT:
      string = "bottom-to-top";
      break;
    }

  return string;
}

void
_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaReference *reference;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_REFERENCE (area));

  reference = FO_AREA_REFERENCE (area);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sbpd: %s",
	 indent,
	 _direction_to_string (reference->bpd));
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sipd: %s",
	 indent,
	 _direction_to_string (reference->ipd));
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%ssd:  %s",
	 indent,
	 _direction_to_string (reference->sd));

  g_free (indent);
  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

/**
 * fo_area_reference_get_bpd:
 * @fo_area: The #FoAreaReference object
 *
 * Gets the "bpd" property of @fo_area
 *
 * Return value: The "bpd" property value
**/
FoEnumAreaDirection
fo_area_reference_get_bpd (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_REFERENCE (fo_area), 0);

  return FO_AREA_REFERENCE (fo_area)->bpd;
}

/**
 * fo_area_reference_set_bpd:
 * @fo_area: The #FoAreaReference object
 * @new_bpd: The new "bpd" property value
 * 
 * Sets the "bpd" property of @fo_area to @new_bpd
**/
void
fo_area_reference_set_bpd (FoArea             *fo_area,
			   FoEnumAreaDirection new_bpd)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_REFERENCE (fo_area));

  FO_AREA_REFERENCE (fo_area)->bpd = new_bpd;
  /*g_object_notify (G_OBJECT (fo_area), "bpd");*/
}

/**
 * fo_area_reference_get_ipd:
 * @fo_area: The #FoAreaReference object
 *
 * Gets the "ipd" property of @fo_area
 *
 * Return value: The "ipd" property value
**/
FoEnumAreaDirection
fo_area_reference_get_ipd (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_REFERENCE (fo_area), 0);

  return FO_AREA_REFERENCE (fo_area)->ipd;
}

/**
 * fo_area_reference_set_ipd:
 * @fo_area: The #FoAreaReference object
 * @new_ipd: The new "ipd" property value
 * 
 * Sets the "ipd" property of @fo_area to @new_ipd
**/
void
fo_area_reference_set_ipd (FoArea             *fo_area,
			   FoEnumAreaDirection new_ipd)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_REFERENCE (fo_area));

  FO_AREA_REFERENCE (fo_area)->ipd = new_ipd;
  /*g_object_notify (G_OBJECT (fo_area), "ipd");*/
}

/**
 * fo_area_reference_get_sd:
 * @fo_area: The #FoAreaReference object
 *
 * Gets the "sd" property of @fo_area
 *
 * Return value: The "sd" property value
**/
FoEnumAreaDirection
fo_area_reference_get_sd (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_REFERENCE (fo_area), 0);

  return FO_AREA_REFERENCE (fo_area)->sd;
}

/**
 * fo_area_reference_set_sd:
 * @fo_area: The #FoAreaReference object
 * @new_sd:  The new "sd" property value
 * 
 * Sets the "sd" property of @fo_area to @new_sd
**/
void
fo_area_reference_set_sd (FoArea             *fo_area,
			  FoEnumAreaDirection new_sd)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_REFERENCE (fo_area));

  FO_AREA_REFERENCE (fo_area)->sd = new_sd;
  /*g_object_notify (G_OBJECT (fo_area), "sd");*/
}

/**
 * _update_after_clone:
 * @clone:    New object cloned from @original
 * @original: Original area object
 * 
 * Update the FoAreaReference-specific instance variables of @clone to
 * match those of @original
 **/
void
_update_after_clone (FoArea *clone,
		     FoArea *original)
{
  FoAreaReference *original_reference = (FoAreaReference *) original;
  FoAreaReference *clone_reference = (FoAreaReference *) clone;

  g_return_if_fail (clone != NULL);
  g_return_if_fail (FO_IS_AREA_REFERENCE (clone));
  g_return_if_fail (original != NULL);
  g_return_if_fail (FO_IS_AREA_REFERENCE (original));

  FO_AREA_CLASS (parent_class)->update_after_clone (clone, original);

  original_reference = FO_AREA_REFERENCE (original);
  clone_reference = FO_AREA_REFERENCE (clone);

  clone_reference->bpd = original_reference->bpd;
  clone_reference->ipd = original_reference->ipd;
  clone_reference->sd = original_reference->sd;

  fo_area_set_reference (clone, clone);
}
