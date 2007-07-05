/* Fo
 * fo-tblr.c: 'Top-bottom-left-right' datatype
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-tblr.h"
#include "fo-length.h"

enum {
  PROP_0,
  PROP_TOP,
  PROP_BOTTOM,
  PROP_LEFT,
  PROP_RIGHT
};

struct _FoTblr
{
  FoDatatype parent_instance;

  FoDatatype *top;
  FoDatatype *bottom;
  FoDatatype *left;
  FoDatatype *right;
};

struct _FoTblrClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_tblr_class_init   (FoTblrClass *klass);
static void fo_tblr_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_tblr_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_tblr_finalize     (GObject       *object);

gchar*      fo_tblr_sprintf (FoObject *object);
FoDatatype* fo_tblr_copy (FoDatatype *datatype);

static void fo_tblr_set_top         (FoDatatype *datatype,
				     FoDatatype * new_top);
static void fo_tblr_set_bottom      (FoDatatype *datatype,
				     FoDatatype *new_bottom);
static void fo_tblr_set_left        (FoDatatype *datatype,
				     FoDatatype *new_left);
static void fo_tblr_set_right       (FoDatatype *datatype,
				     FoDatatype *new_right);
static gpointer parent_class;

/**
 * fo_tblr_get_type:
 * @void: 
 * 
 * Register the #FoTblr object type.
 * 
 * Return value: GType value of the #FoTblr object type.
 **/
GType
fo_tblr_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoTblrClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_tblr_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoTblr),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoTblr",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_tblr_class_init:
 * @klass: FoTblrClass object to initialise
 * 
 * Implements GClassInitFunc for FoTblrClass
 **/
void
fo_tblr_class_init (FoTblrClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_tblr_finalize;

  object_class->set_property = fo_tblr_set_property;
  object_class->get_property = fo_tblr_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_tblr_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_tblr_copy;

  g_object_class_install_property (object_class,
                                   PROP_TOP,
                                   g_param_spec_object ("top",
							_("Top"),
							_("Tblr top value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_BOTTOM,
                                   g_param_spec_object ("bottom",
							_("Bottom"),
							_("Tblr bottom value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_LEFT,
                                   g_param_spec_object ("left",
							_("Left"),
							_("Tblr left value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_RIGHT,
                                   g_param_spec_object ("right",
							_("Right"),
							_("Tblr right value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_tblr_finalize:
 * @object: FoTblr object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTblr
 **/
void
fo_tblr_finalize (GObject *object)
{
  FoTblr *tblr;

  tblr = FO_TBLR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_tblr_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoTblr
 **/
void
fo_tblr_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *tblr;

  tblr = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_TOP:
      fo_tblr_set_top (tblr, g_value_get_object (value));
      break;
    case PROP_BOTTOM:
      fo_tblr_set_bottom (tblr, g_value_get_object (value));
      break;
    case PROP_LEFT:
      fo_tblr_set_left (tblr, g_value_get_object (value));
      break;
    case PROP_RIGHT:
      fo_tblr_set_right (tblr, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_tblr_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoTblr
 **/
void
fo_tblr_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *datatype;

  datatype = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_TOP:
      g_value_set_object (value, fo_tblr_get_top (datatype));
      break;
    case PROP_BOTTOM:
      g_value_set_object (value, fo_tblr_get_bottom (datatype));
      break;
    case PROP_LEFT:
      g_value_set_object (value, fo_tblr_get_left (datatype));
      break;
    case PROP_RIGHT:
      g_value_set_object (value, fo_tblr_get_right (datatype));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_tblr_new:
 * 
 * Creates a new #FoTblr initialized to default value.
 * 
 * Return value: the new #FoTblr
 **/
FoDatatype *
fo_tblr_new (void)
{
  FoDatatype *tblr;

  tblr = FO_DATATYPE (g_object_new (fo_tblr_get_type (),
				    "top",
				    fo_length_get_length_zero (),
				    "bottom",
				    fo_length_get_length_zero (),
				    "left",
				    fo_length_get_length_zero (),
				    "right",
				    fo_length_get_length_zero (),
				    NULL));
  
  return tblr;
}

/**
 * fo_tblr_new_from_values:
 * @top:    #FoDatatype to use as top value
 * @bottom: #FoDatatype to use as bottom value
 * @left:   #FoDatatype to use as left value
 * @right:  #FoDatatype to use as right value
 * 
 * Creates a new #FoTblr with top, bottom, left and right
 * components set to provided values.
 * 
 * Return value: New #FoTblr
 **/
FoDatatype*
fo_tblr_new_from_values (FoDatatype *top,
			 FoDatatype *bottom,
			 FoDatatype *left,
			 FoDatatype *right)
{
  FoDatatype *tblr;

  g_return_val_if_fail (FO_IS_DATATYPE (top),    NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (bottom), NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (left),   NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (right),  NULL);

  tblr = fo_tblr_new ();

  fo_tblr_set_top    (tblr, top);
  fo_tblr_set_bottom (tblr, bottom);
  fo_tblr_set_left   (tblr, left);
  fo_tblr_set_right  (tblr, right);

  return tblr;
}

/**
 * fo_tblr_get_top:
 * @datatype: #FoTblr
 * 
 * Gets the top component value of @datatype.
 * 
 * Return value: The top value of @datatype.
 **/
FoDatatype *
fo_tblr_get_top (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_TBLR (datatype), 0);

  return FO_TBLR (datatype)->top;
}

/**
 * fo_tblr_set_top:
 * @datatype: #FoTblr
 * @new_top:  New top value
 * 
 * Sets the top component of @datatype
 **/
void
fo_tblr_set_top (FoDatatype *datatype,
		 FoDatatype *new_top)
{
  FoTblr *tblr = (FoTblr *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_TBLR (datatype));
  g_return_if_fail (FO_IS_DATATYPE (new_top));

  if (new_top)
    g_object_ref (G_OBJECT (new_top));
  if (tblr->top)
    g_object_unref (G_OBJECT (tblr->top));
  tblr->top = new_top;
  /*g_object_notify(G_OBJECT(datatype), "top");*/
}

/**
 * fo_tblr_get_bottom:
 * @datatype: #FoTblr
 * 
 * Gets the .bottom component value of @datatype
 * 
 * Return value: The bottom value of @datatype
 **/
FoDatatype *
fo_tblr_get_bottom (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_TBLR (datatype), 0);

  return FO_TBLR (datatype)->bottom;
}

/**
 * fo_tblr_set_bottom:
 * @datatype:     #FoTblr
 * @new_bottom:  New .bottom value
 * 
 * Sets the bottom component of @datatype
 **/
void
fo_tblr_set_bottom (FoDatatype *datatype,
		    FoDatatype *new_bottom)
{
  FoTblr *tblr = (FoTblr *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_TBLR (datatype));
  g_return_if_fail (FO_IS_DATATYPE (new_bottom));

  if (new_bottom)
    g_object_ref (G_OBJECT (new_bottom));
  if (tblr->bottom)
    g_object_unref (G_OBJECT (tblr->bottom));
  tblr->bottom = new_bottom;
  /*g_object_notify(G_OBJECT(datatype), "bottom");*/
}

/**
 * fo_tblr_get_left:
 * @datatype: #FoTblr
 * 
 * Gets the .left component value of @datatype
 * 
 * Return value: The left value of @datatype
 **/
FoDatatype *
fo_tblr_get_left (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_TBLR (datatype), 0);

  return FO_TBLR (datatype)->left;
}

/**
 * fo_tblr_set_left:
 * @datatype:     #FoTblr
 * @new_left:  New .left value
 * 
 * Sets the .left component of @datatype
 **/
void
fo_tblr_set_left (FoDatatype *datatype,
		  FoDatatype *new_left)
{
  FoTblr *tblr = (FoTblr *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_TBLR (datatype));
  g_return_if_fail (FO_IS_DATATYPE (new_left));

  if (new_left)
    g_object_ref (G_OBJECT (new_left));
  if (tblr->left)
    g_object_unref (G_OBJECT (tblr->left));
  tblr->left = new_left;
  /*g_object_notify(G_OBJECT(datatype), "left");*/
}

/**
 * fo_tblr_get_right:
 * @datatype: #FoTblr
 * 
 * Gets the .right component value of @datatype
 * 
 * Return value: The right value of @datatype
 **/
FoDatatype *
fo_tblr_get_right (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_TBLR (datatype), 0);

  return FO_TBLR (datatype)->right;
}

/**
 * fo_tblr_set_right:
 * @datatype:     #FoTblr
 * @new_right:  New .right value
 * 
 * Sets the right component of @datatype
 **/
void
fo_tblr_set_right (FoDatatype *datatype,
		   FoDatatype *new_right)
{
  FoTblr *tblr = (FoTblr *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_TBLR (datatype));
  g_return_if_fail (FO_IS_DATATYPE (new_right));

  if (new_right)
    g_object_ref (G_OBJECT (new_right));
  if (tblr->right)
    g_object_unref (G_OBJECT (tblr->right));
  tblr->right = new_right;
  /*g_object_notify(G_OBJECT(datatype), "right");*/
}

/**
 * fo_tblr_sprintf:
 * @object: #FoTblr whose value is to be printed
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoTblr.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object
 **/
gchar*
fo_tblr_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_TBLR (object), NULL);

  return (g_strdup_printf("top: %s; bottom: %s; left: %s; right: %s",
			  fo_object_sprintf (FO_TBLR (object)->top),
			  fo_object_sprintf (FO_TBLR (object)->bottom),
			  fo_object_sprintf (FO_TBLR (object)->left),
			  fo_object_sprintf (FO_TBLR (object)->right)));
}

/**
 * fo_tblr_copy:
 * @datatype: Source #FoTblr.
 * 
 * Creates a copy of @datatype.
 * 
 * Return value: Copy of @datatype.
 **/
FoDatatype*
fo_tblr_copy (FoDatatype *datatype)
{
  FoDatatype *tblr;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_TBLR (datatype), NULL);

  tblr = fo_tblr_new ();
  fo_tblr_set_top (tblr,
		   FO_TBLR(datatype)->top);
  fo_tblr_set_bottom (tblr,
		      FO_TBLR(datatype)->bottom);
  fo_tblr_set_left (tblr,
		    FO_TBLR(datatype)->left);
  fo_tblr_set_right (tblr,
		     FO_TBLR(datatype)->right);

  return (tblr);
}
