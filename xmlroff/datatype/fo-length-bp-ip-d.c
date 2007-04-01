/* Fo
 * fo-length-bp-ip-d.c: 'lenght-bp-ip-direction' datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-length-bp-ip-d.c,v 1.5 2005/11/04 14:24:28 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-enum.h"
#include "fo-length.h"
#include "fo-length-bp-ip-d.h"


enum {
  PROP_0,
  PROP_LENGTH_BPD,
  PROP_LENGTH_IPD
};

struct _FoLengthBpIpD
{
  FoDatatype parent_instance;

  FoDatatype *length_bpd;
  FoDatatype *length_ipd;
};

struct _FoLengthBpIpDClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_length_bp_ip_d_class_init   (FoLengthBpIpDClass *klass);
static void fo_length_bp_ip_d_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_length_bp_ip_d_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_length_bp_ip_d_finalize     (GObject       *object);

gchar*      fo_length_bp_ip_d_sprintf (FoObject *object);
FoDatatype* fo_length_bp_ip_d_copy (FoDatatype *datatype);
static void fo_length_bp_ip_d_set_length_bpd  (FoDatatype *datatype,
					    FoDatatype *new_length_bpd);
static void fo_length_bp_ip_d_set_length_ipd (FoDatatype *datatype,
					   FoDatatype *new_length_ipd);

static gpointer parent_class;

/**
 * fo_length_bp_ip_d_get_type:
 * @void: 
 * 
 * Register the #FoLengthBpIpD object type.
 * 
 * Return value: GType value of the #FoLengthBpIpD object type.
 **/
GType
fo_length_bp_ip_d_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLengthBpIpDClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_length_bp_ip_d_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLengthBpIpD),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoLengthBpIpD",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_length_bp_ip_d_class_init:
 * @klass: FoLengthBpIpDClass object to initialise
 * 
 * Implements GClassInitFunc for FoLengthBpIpDClass
 **/
void
fo_length_bp_ip_d_class_init (FoLengthBpIpDClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_length_bp_ip_d_finalize;

  object_class->set_property = fo_length_bp_ip_d_set_property;
  object_class->get_property = fo_length_bp_ip_d_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_length_bp_ip_d_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_length_bp_ip_d_copy;

  g_object_class_install_property (object_class,
                                   PROP_LENGTH_BPD,
                                   g_param_spec_object ("length-bpd",
							_("Length bpd"),
							_("Length in block-progression-direction"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_LENGTH_IPD,
                                   g_param_spec_object ("length_ipd",
							_("Length ipd"),
							_("Length in inline-progression-direction"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

}

static void
fo_length_bp_ip_d_finalize (GObject *object)
{
  FoLengthBpIpD *length_bp_ip_d;

  length_bp_ip_d = FO_LENGTH_BP_IP_D (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_length_bp_ip_d_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *length_bp_ip_d;

  length_bp_ip_d = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_LENGTH_BPD:
      fo_length_bp_ip_d_set_length_bpd (length_bp_ip_d, g_value_get_object (value));
      break;
    case PROP_LENGTH_IPD:
      fo_length_bp_ip_d_set_length_ipd (length_bp_ip_d, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_length_bp_ip_d_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *length_bp_ip_d;

  length_bp_ip_d = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_LENGTH_BPD:
      g_value_set_object (value, fo_length_bp_ip_d_get_length_bpd (length_bp_ip_d));
      break;
    case PROP_LENGTH_IPD:
      g_value_set_object (value, fo_length_bp_ip_d_get_length_ipd (length_bp_ip_d));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_bp_ip_d_new:
 * 
 * Creates a new #FoLengthBpIpD initialized to default value.
 * 
 * Return value: the new #FoLengthBpIpD
 **/
FoDatatype *
fo_length_bp_ip_d_new (void)
{
  FoDatatype *length_bp_ip_d = NULL;

  length_bp_ip_d = FO_DATATYPE (g_object_new (fo_length_bp_ip_d_get_type (),
					   "length_bpd",
					   fo_length_get_length_zero (),
					   "length_ipd",
					   fo_length_get_length_zero (),
					   NULL));
  
  return length_bp_ip_d;
}

/**
 * fo_length_bp_ip_d_new_with_value:
 * @length_bpd: .block-progression-direction component of the new #FoLengthBpIpD
 * @length_ipd: .inline-progression-direction component of the new #FoLengthBpIpD
 * 
 * Creates a new #FoLengthBpIpD set to @length_bpd and @length_ipd
 * 
 * Return value: The new #FoLengthBpIpD
 **/
FoDatatype*
fo_length_bp_ip_d_new_with_value (FoDatatype *length_bpd,
				  FoDatatype *length_ipd)
{
  FoDatatype *length_bp_ip_d = fo_length_bp_ip_d_new ();

  g_return_val_if_fail (FO_IS_LENGTH (length_bpd), NULL);
  g_return_val_if_fail (FO_IS_LENGTH (length_ipd), NULL);

  fo_length_bp_ip_d_set_length_bpd (length_bp_ip_d, length_bpd);
  fo_length_bp_ip_d_set_length_ipd (length_bp_ip_d, length_ipd);

  return length_bp_ip_d;
}

/**
 * fo_length_bp_ip_d_set_length_bpd:
 * @datatype:    #FoLengthBpIpD
 * @new_length:  New .block-progression-direction value
 * 
 * Sets the .block-progression-direction component of @datatype
 **/
void
fo_length_bp_ip_d_set_length_bpd (FoDatatype *datatype,
				  FoDatatype *new_length_bpd)
{
  FoLengthBpIpD *length_bp_ip_d = (FoLengthBpIpD *) datatype;

  g_return_if_fail (length_bp_ip_d != NULL);
  g_return_if_fail (FO_IS_LENGTH_BP_IP_D (length_bp_ip_d));
  g_return_if_fail (FO_IS_LENGTH (new_length_bpd));

  if (new_length_bpd)
    g_object_ref (G_OBJECT (new_length_bpd));
  if (length_bp_ip_d->length_bpd)
    g_object_unref (G_OBJECT (length_bp_ip_d->length_bpd));
  length_bp_ip_d->length_bpd = new_length_bpd;
  /*g_object_notify(G_OBJECT(length_bp_ip_d), "block-progression-direction");*/
}

/**
 * fo_length_bp_ip_d_get_length_bpd:
 * @datatype: #FoLengthBpIpD
 * 
 * Gets the .block-progression-direction component value of @datatype
 * 
 * Return value: The .block-progression-direction value of @datatype
 **/
FoDatatype*
fo_length_bp_ip_d_get_length_bpd (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_BP_IP_D (datatype), 0);

  return FO_LENGTH_BP_IP_D (datatype)->length_bpd;
}

/**
 * fo_length_bp_ip_d_set_length_ipd:
 * @datatype:     #FoLengthBpIpD
 * @new_length_ipd:  New .length_ipd value
 * 
 * Sets the .length_ipd component of @datatype
 **/
void
fo_length_bp_ip_d_set_length_ipd (FoDatatype *datatype,
				  FoDatatype *new_length_ipd)
{
  FoLengthBpIpD *length_bp_ip_d = (FoLengthBpIpD *) datatype;

  g_return_if_fail (length_bp_ip_d != NULL);
  g_return_if_fail (FO_IS_LENGTH_BP_IP_D (length_bp_ip_d));
  g_return_if_fail (FO_IS_DATATYPE (new_length_ipd));

  if (new_length_ipd)
    g_object_ref (G_OBJECT (new_length_ipd));
  if (length_bp_ip_d->length_ipd)
    g_object_unref (G_OBJECT (length_bp_ip_d->length_ipd));
  length_bp_ip_d->length_ipd = new_length_ipd;
  /*g_object_notify(G_OBJECT(length_bp_ip_d), "inline-progression-direction");*/
}

/**
 * fo_length_bp_ip_d_get_length_ipd:
 * @datatype: #FoLengthBpIpD
 * 
 * Gets the .inline-progression-direction component value of @datatype
 * 
 * Return value: The .inline-progression-direction component value of @datatype
 **/
FoDatatype*
fo_length_bp_ip_d_get_length_ipd (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_BP_IP_D (datatype), 0);

  return FO_LENGTH_BP_IP_D (datatype)->length_ipd;
}

/**
 * fo_length_bp_ip_d_sprintf:
 * @object: #FoLengthBpIpD whose value is to be printed
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoLengthBpIpD.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object
 **/
gchar*
fo_length_bp_ip_d_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_BP_IP_D (object), NULL);

  return g_strdup_printf ("length_bpd: %s; length_ipd: %s",
			  fo_object_sprintf (FO_LENGTH_BP_IP_D (object)->length_bpd),
			  fo_object_sprintf (FO_LENGTH_BP_IP_D (object)->length_ipd));
}

/**
 * fo_length_bp_ip_d_copy:
 * @datatype: Source #FoLengthBpIpD
 * 
 * Creates a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_length_bp_ip_d_copy (FoDatatype *datatype)
{
  FoDatatype* length_bp_ip_d;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_BP_IP_D (datatype), NULL);

  length_bp_ip_d = fo_length_bp_ip_d_new ();
  fo_length_bp_ip_d_set_length_bpd (length_bp_ip_d,
				    FO_LENGTH_BP_IP_D(datatype)->length_bpd);
  fo_length_bp_ip_d_set_length_ipd (length_bp_ip_d,
				    FO_LENGTH_BP_IP_D(datatype)->length_ipd);

  return (length_bp_ip_d);
}
