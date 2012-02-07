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

static void _base_class_init  (FoAreaReferenceClass *klass);
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
        (GBaseInitFunc) _base_class_init,
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

/**
 * _base_class_init:
 * @klass: #FoAreaReferenceClass base class object to initialise
 * 
 * Implements #GBaseInitFunc for #FoAreaReferenceClass
 **/
void
_base_class_init (FoAreaReferenceClass *klass)
{
  FO_AREA_CLASS (klass)->update_after_clone =
    _update_after_clone;
}

static void
fo_area_reference_class_init (FoAreaReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_reference_finalize;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  FO_AREA_CLASS (klass)->debug_dump_properties =
    _debug_dump_properties;
  FO_AREA_CLASS (klass)->size_request = _size_request;

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

/**
 * _size_request:
 * @child: Child area
 * 
 * Check that the parent area of @child has sufficient space for
 * @child.  If not enough space, request that the parent has
 * sufficient space allocated for it, then adjust @child and its
 * siblings as necessary to fit into the resized parent area.
 * 
 * Return value: Pointer to the last area generated from @child after
 * any reallocation and resizing
 **/
static FoArea*
_size_request (FoArea *child)
{
  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_parent (child)), NULL);

  FoArea *child_original_next_part = child->next_part;

  gdouble child_height = fo_area_area_get_height (child);
  gdouble child_space_before = fo_area_area_get_space_before (child);
  gdouble child_space_after = fo_area_area_get_space_after (child);

  FoArea *parent = fo_area_parent (child);
  gdouble child_available_bpdim = fo_area_get_child_available_bpdim (parent);

#if defined(LIBFO_DEBUG) && 1
  g_message ("size_request_default (%p):: parent: %s; generated by: %s; available_height: %g",
	     child,
	     fo_object_debug_sprintf (parent),
	     fo_object_debug_sprintf (parent->generated_by),
	     child_available_bpdim);
  g_message ("size_request_default (%p):: child: %s; generated by: %s; height: %g; space_before: %g; space_after: %g",
	     child,
	     fo_object_debug_sprintf (child),
	     fo_object_debug_sprintf (child->generated_by),
	     child_height,
	     child_space_before,
	     child_space_after);
#endif

  gdouble total_child_height = 0;
  fo_area_children_foreach (parent,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);
#if defined(LIBFO_DEBUG) && 1
  g_message ("size_request_default (%p):: child total: %g",
	     child,
	     total_child_height);
#endif

  fo_area_area_set_height (parent,
			   total_child_height +
			   fo_area_area_get_space_before (parent) +
			   fo_area_area_get_border_before (parent) +
			   fo_area_area_get_padding_before (parent) +
			   fo_area_area_get_padding_after (parent) +
			   fo_area_area_get_border_after (parent) +
			   fo_area_area_get_space_after (parent));

  /* Don't bother doing a size_request if still fit within
     available height */
  if (child_available_bpdim < fo_area_area_get_height (parent))
    {
      parent = fo_area_size_request (parent);
      gdouble child_available_ipdim =
	MAX (fo_area_get_available_width (parent) -
	     fo_area_area_get_border_start (parent) -
	     fo_area_area_get_padding_start (parent) -
	     fo_area_area_get_padding_end (parent) -
	     fo_area_area_get_border_end (parent),
	     0);
      fo_area_set_child_available_ipdim (parent, child_available_ipdim);
      child_available_bpdim =
	MAX (fo_area_get_available_height (parent) -
	     fo_area_area_get_space_before (parent) -
	     fo_area_area_get_border_before (parent) -
	     fo_area_area_get_padding_before (parent) -
	     fo_area_area_get_padding_after (parent) -
	     fo_area_area_get_border_after (parent) -
	     fo_area_area_get_space_after (parent),
	     0);
      fo_area_set_child_available_bpdim (parent, child_available_bpdim);
#if defined(LIBFO_DEBUG) && 1
      g_message ("size_request_default:: child: %s; new parent: %s; generated by: %s; available_height: %g; child_available_ipdim: %g; child_available_bpdim: %g",
		 fo_object_debug_sprintf (child),
		 fo_object_debug_sprintf (parent),
		 fo_object_debug_sprintf (parent->generated_by),
		 fo_area_get_available_height (parent),
		 child_available_ipdim,
		 child_available_bpdim);
#endif
  }

  total_child_height = 0;
  fo_area_children_foreach (parent,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);
#if defined(LIBFO_DEBUG) && 1
  g_message ("size_request_default (%p):: new child total: %g",
	     child,
	     total_child_height);
#endif
  fo_area_set_next_x (parent,
		      fo_area_area_get_start_indent (parent) +
		      fo_area_area_get_border_start (parent) +
		      fo_area_area_get_padding_start (parent));
  fo_area_set_next_y (parent,
		      - (fo_area_area_get_space_before (parent) +
			 fo_area_area_get_border_before (parent) +
			 fo_area_area_get_padding_before (parent)));

  if (total_child_height <= child_available_bpdim)
    {
      GValue value = { 0, {{0}, {0}} };

      /* Every FO that gererates a reference area has
	 'display-align'. */
      g_object_get_property (G_OBJECT (parent->generated_by),
			     "display-align",
			     &value);

      FoProperty *prop_display_align =
	g_value_get_object (&value);

     FoDatatype *display_align =
      fo_property_get_value (prop_display_align);

     FoEnumEnum display_align_enum =
       fo_enum_get_value (display_align);

      gdouble next_y;
      switch (display_align_enum)
	{
	case FO_ENUM_ENUM_AUTO:
	  /* Treat as 'before' while 'relative-align' is
	     unimplemented. */
	case FO_ENUM_ENUM_BEFORE:
	  next_y =
	    - (fo_area_area_get_border_before (child) +
	       fo_area_area_get_padding_before (child));
	  break;
	case FO_ENUM_ENUM_CENTER:
	  next_y =
	    - (fo_area_area_get_border_before (child) +
	       fo_area_area_get_padding_before (child) +
	       (child_available_bpdim -
		total_child_height) / 2.0);
	  break;
	case FO_ENUM_ENUM_AFTER:
	  next_y =
	    - (fo_area_area_get_border_before (child) +
	       fo_area_area_get_padding_before (child) +
	       (child_available_bpdim -
		total_child_height));
	  break;
	default:
	  g_assert_not_reached ();
	}
      fo_area_set_next_y (child,
			  next_y);
      /* Since the children all fit within the allowed height, adjust
	 their sizes and positions in sequence. */
      fo_area_children_foreach (parent,
				G_TRAVERSE_ALL,
				&fo_area_size_adjust,
				NULL);

#if defined(LIBFO_DEBUG) && 1
      g_message ("size_request_default (%p):: return:: parent->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (parent)),
		 fo_object_debug_sprintf (fo_area_last_child (parent)->generated_by));
#endif
      FoArea *return_child = child;

      while ((return_child->next_part != NULL) &&
	     (return_child->next_part != child_original_next_part))
	{
	  return_child = return_child->next_part;
	}

      return return_child;
      /*
      return fo_area_last_child (parent);
      */
    }
  else
    {
      fo_area_children_foreach (parent,
				G_TRAVERSE_ALL,
				&fo_area_set_or_split,
				NULL);
#if defined(LIBFO_DEBUG) && 1
      g_message ("size_request_default (%p):: total > available:: return:: parent->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (parent)),
		 fo_object_debug_sprintf (fo_area_last_child (parent)->generated_by));
#endif
      FoArea *return_child = child;

      while ((return_child->next_part != NULL) &&
	     (return_child->next_part != child_original_next_part))
	{
	  return_child = return_child->next_part;
	}

      return return_child;
      /*
      return fo_area_last_child (parent);
      */
    }
}
