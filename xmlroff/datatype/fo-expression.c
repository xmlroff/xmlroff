/* Fo
 * fo-expression.c: Expression datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-expression.c,v 1.4 2005/03/10 17:38:29 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-expression.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoExpression
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoExpressionClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_expression_init         (FoExpression      *expression);
static void fo_expression_class_init   (FoExpressionClass *klass);
static void fo_expression_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_expression_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_expression_finalize     (GObject       *object);

FoDatatype* fo_expression_copy(FoDatatype *datatype);
gchar*      fo_expression_sprintf (FoObject *datatype);

static gpointer parent_class;

GType
fo_expression_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoExpressionClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_expression_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoExpression),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_expression_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoExpression",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_expression_init (FoExpression *expression)
{
  expression->value = NULL;
}

static void
fo_expression_class_init (FoExpressionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_expression_finalize;

  object_class->set_property = fo_expression_set_property;
  object_class->get_property = fo_expression_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
						     _("Value"),
						     _("Expression value"),
							NULL,
						     G_PARAM_READWRITE));

  FO_DATATYPE_CLASS (klass)->copy = fo_expression_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_expression_sprintf;
}

static void
fo_expression_finalize (GObject *object)
{
  FoExpression *expression;

  expression = FO_EXPRESSION (object);

  g_free(expression->value);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_expression_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *expression;

  expression = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_expression_set_value (expression, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_expression_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *expression;

  expression = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_expression_get_value (expression));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_expression_new:
 * 
 * Creates a new #FoExpression initialized to default value.
 * 
 * Return value: the new #FoExpression
 **/
FoDatatype *
fo_expression_new (void)
{
  FoDatatype *expression;

  expression = FO_DATATYPE (g_object_new (fo_expression_get_type (), NULL));
  
  return expression;
}

/* value */
void
fo_expression_set_value (FoDatatype *expression,
			 const gchar* new_value)
{
  g_return_if_fail (expression != NULL);
  g_return_if_fail (FO_IS_EXPRESSION (expression));

  FO_EXPRESSION (expression)->value = g_strdup (new_value);
  /*g_object_notify (G_OBJECT (expression), "value");*/
}

gchar*
fo_expression_get_value (FoDatatype *expression)
{
  g_return_val_if_fail (expression != NULL, NULL);
  g_return_val_if_fail (FO_IS_EXPRESSION (expression), NULL);

  return g_strdup (FO_EXPRESSION (expression)->value);
}

FoDatatype*
fo_expression_copy(FoDatatype *datatype)
{
  FoDatatype* expression;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_EXPRESSION (datatype), NULL);

  expression = fo_expression_new ();
  FO_EXPRESSION (expression)->value = g_strdup (FO_EXPRESSION (datatype)->value);

  return expression;
}

gchar*
fo_expression_sprintf (FoObject *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_EXPRESSION (datatype), NULL);

  return (g_strdup_printf("%s", FO_EXPRESSION (datatype)->value));
}
