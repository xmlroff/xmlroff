/* Fo
 * fo-token.c: Token datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-token.c,v 1.3 2005/03/10 17:38:27 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-token.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoToken
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoTokenClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_token_init         (FoToken      *token);
static void fo_token_class_init   (FoTokenClass *klass);
static void fo_token_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_token_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_token_finalize     (GObject       *object);

FoDatatype* fo_token_copy(FoDatatype *datatype);
gchar*      fo_token_sprintf (FoDatatype *datatype);

static gpointer parent_class;

GType
fo_token_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoTokenClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_token_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoToken),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_token_init,
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoToken",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_token_init (FoToken *token)
{
  token->value = NULL;
}

static void
fo_token_class_init (FoTokenClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_token_finalize;

  object_class->set_property = fo_token_set_property;
  object_class->get_property = fo_token_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
						     _("Value"),
						     _("Token value"),
							NULL,
						     G_PARAM_READWRITE));

  FO_DATATYPE_CLASS (klass)->copy = fo_token_copy;
  FO_DATATYPE_CLASS (klass)->print_sprintf = fo_token_sprintf;
}

static void
fo_token_finalize (GObject *object)
{
  FoToken *token;

  token = FO_TOKEN (object);

  g_free(token->value);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_token_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoToken *token;

  token = FO_TOKEN (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_token_set_value (token, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_token_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoToken *token;

  token = FO_TOKEN (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_token_get_value (token));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_token_new:
 * 
 * Creates a new #FoToken initialized to default value.
 * 
 * Return value: the new #FoToken
 **/
FoDatatype *
fo_token_new (void)
{
  FoDatatype *token;

  token = FO_DATATYPE (g_object_new (fo_token_get_type (), NULL));
  
  return token;
}

/* value */
void
fo_token_set_value (FoToken *token,
		       const gchar* new_value)
{
  g_return_if_fail (token != NULL);
  g_return_if_fail (FO_IS_TOKEN (token));

  token->value = g_strdup(new_value);
  /*g_object_notify(G_OBJECT(token), "value");*/
}

gchar*
fo_token_get_value (FoToken *token)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_TOKEN (token), NULL);

  return g_strdup(token->value);
}

FoDatatype*
fo_token_copy(FoDatatype *datatype)
{
  FoDatatype* token;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_TOKEN (datatype), NULL);

  token = fo_token_new ();
  FO_TOKEN (token)->value = g_strdup (FO_TOKEN (datatype)->value);

  return (FO_DATATYPE(token));
}

gchar*
fo_token_sprintf (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_TOKEN (datatype), NULL);

  return (g_strdup_printf("%s", FO_TOKEN (datatype)->value));
}
