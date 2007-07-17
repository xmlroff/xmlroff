/* Fo
 * fo-keep.c: Keep datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-keep.h"
#include "fo-enum.h"
#include "fo-length.h"
#include "fo-integer.h"
#include "fo-percentage.h"
#include "fo-boolean.h"

enum {
  PROP_0,
  PROP_WITHIN_LINE,
  PROP_WITHIN_COLUMN,
  PROP_WITHIN_PAGE
};

struct _FoKeep
{
  FoDatatype parent_instance;

  FoDatatype *within_line;
  FoDatatype *within_column;
  FoDatatype *within_page;
};

struct _FoKeepClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_keep_init         (FoKeep      *keep);
static void fo_keep_class_init   (FoKeepClass *klass);
static void fo_keep_set_property (GObject       *object,
				  guint          prop_id,
				  const GValue  *value,
				  GParamSpec    *pspec);
static void fo_keep_get_property (GObject       *object,
				  guint          prop_id,
				  GValue        *value,
				  GParamSpec    *pspec);
static void fo_keep_finalize     (GObject       *object);

static gchar*      fo_keep_sprintf           (FoObject   *object);
static FoDatatype* fo_keep_copy              (FoDatatype *datatype);
static void        fo_keep_set_within_line   (FoDatatype *keep,
					      FoDatatype *new_within_line);
static void        fo_keep_set_within_column (FoDatatype *keep,
					      FoDatatype *new_within_column);
static void        fo_keep_set_within_page   (FoDatatype *keep,
					      FoDatatype *new_within_page);

static gpointer parent_class;

/**
 * fo_keep_get_type:
 * 
 * Register the #FoKeep object type.
 * 
 * Return value: GType value of the #FoKeep object type.
 **/
GType
fo_keep_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoKeepClass),
	NULL,		/* base_init */
	NULL,		/* base_finalize */
        (GClassInitFunc) fo_keep_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoKeep),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_keep_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoKeep",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_keep_init:
 * @keep: #FoKeep object to initialise
 * 
 * Implements GInstanceInitFunc for #FoKeep
 **/
void
fo_keep_init (FoKeep *keep)
{
  keep->within_page = g_object_ref (fo_enum_get_enum_auto ());
  keep->within_column = g_object_ref (fo_enum_get_enum_auto ());
  keep->within_line = g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_keep_class_init:
 * @klass: FoKeepClass object to initialise
 * 
 * Implements GClassInitFunc for FoKeepClass
 **/
void
fo_keep_class_init (FoKeepClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_keep_finalize;

  object_class->set_property = fo_keep_set_property;
  object_class->get_property = fo_keep_get_property;

  FO_DATATYPE_CLASS (klass)->copy = fo_keep_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_keep_sprintf;

  g_object_class_install_property (object_class,
                                   PROP_WITHIN_LINE,
                                   g_param_spec_object ("within-line",
							_("Within Line"),
							_("Keep within line value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_WITHIN_COLUMN,
                                   g_param_spec_object ("within-column",
							_("Within Column"),
							_("Keep within column value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_WITHIN_PAGE,
                                   g_param_spec_object ("within-page",
							_("Within Page"),
							_("Keep within page value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));


}

/**
 * fo_keep_finalize:
 * @object: FoKeep object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoKeep
 **/
void
fo_keep_finalize (GObject *object)
{
  FoKeep *keep;

  keep = FO_KEEP (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_keep_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoKeep
 **/
void
fo_keep_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *keep;

  keep = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_WITHIN_LINE:
      fo_keep_set_within_line (keep, g_value_get_object (value));
      break;
    case PROP_WITHIN_COLUMN:
      fo_keep_set_within_column (keep, g_value_get_object (value));
      break;
    case PROP_WITHIN_PAGE:
      fo_keep_set_within_page (keep, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_keep_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoKeep
 **/
void
fo_keep_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *keep;

  keep = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_WITHIN_LINE:
      g_value_set_object (value, fo_keep_get_within_line (keep));
      break;
    case PROP_WITHIN_COLUMN:
      g_value_set_object (value, fo_keep_get_within_column (keep));
      break;
    case PROP_WITHIN_PAGE:
      g_value_set_object (value, fo_keep_get_within_page (keep));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_keep_new:
 * 
 * Creates a new #FoKeep initialized to default value.
 * 
 * Return value: the new #FoKeep
 **/
FoDatatype *
fo_keep_new (void)
{
  FoDatatype *keep;

  keep = FO_DATATYPE (g_object_new (fo_keep_get_type (),
				    "within-page",
				    fo_enum_get_enum_auto (),
				    "within-column",
				    fo_enum_get_enum_auto (),
				    "within-line",
				    fo_enum_get_enum_auto (),
				    NULL));
  
  return keep;
}

/**
 * fo_keep_new_with_value:
 * @value: Keep of the new #FoKeep
 * 
 * Creates a new #FoKeep set to @value
 * 
 * Return value: The new #FoKeep
 **/
FoDatatype*
fo_keep_new_with_value (FoDatatype *value)
{
  FoDatatype *keep = fo_keep_new ();

  fo_keep_set_within_page (keep, value);
  fo_keep_set_within_column (keep, value);
  fo_keep_set_within_line (keep, value);

  return keep;
}

/**
 * fo_keep_get_keep_auto:
 * 
 * Creates a new #FoKeep set to .within-line="auto",
 * .within-column="auto", and .within-page="auto".
 * 
 * Return value: The new #FoKeep
 **/
FoDatatype*
fo_keep_get_keep_auto (void)
{
  static FoDatatype *keep = NULL;

  if (keep == NULL)
    {
      keep = fo_keep_new ();
    }

  return keep;
}

/**
 * fo_keep_get_keep_always:
 * 
 * Creates a new #FoKeep set to .within-line="always",
 * .within-column="always", and .within-page="always".
 * 
 * Return value: The new #FoKeep
 **/
FoDatatype*
fo_keep_get_keep_always (void)
{
  static FoDatatype *keep = NULL;

  if (keep == NULL)
    {
      keep = fo_keep_new ();

      fo_keep_set_within_page (keep, fo_enum_get_always ());
      fo_keep_set_within_column (keep, fo_enum_get_always ());
      fo_keep_set_within_line (keep, fo_enum_get_always());
    }

  return keep;
}

/**
 * fo_keep_set_within_page:
 * @datatype:     #FoKeep
 * @new_within_page:  New .within-page value
 * 
 * Sets the .within-page component of @datatype
 **/
void
fo_keep_set_within_page (FoDatatype *datatype,
			     FoDatatype *new_within_page)
{
  FoKeep *keep = (FoKeep *) datatype;

  g_return_if_fail (keep != NULL);
  g_return_if_fail (FO_IS_KEEP (keep));
  g_return_if_fail (FO_IS_DATATYPE (new_within_page));

  if (new_within_page)
    g_object_ref (G_OBJECT (new_within_page));
  if (keep->within_page)
    g_object_unref (G_OBJECT (keep->within_page));
  keep->within_page = new_within_page;
  /*g_object_notify(G_OBJECT(keep), "within-page");*/
}

/**
 * fo_keep_get_within_page:
 * @datatype: #FoKeep
 * 
 * Gets the .within-page component value of @datatype
 * 
 * Return value: The .within-page value of @datatype
 **/
FoDatatype*
fo_keep_get_within_page (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), 0);

  return FO_KEEP (datatype)->within_page;
}

/**
 * fo_keep_set_within_column:
 * @datatype:     #FoKeep
 * @new_within_column:  New .within-column value
 * 
 * Sets the .within-column component of @datatype
 **/
void
fo_keep_set_within_column (FoDatatype *datatype,
			     FoDatatype *new_within_column)
{
  FoKeep *keep = (FoKeep *) datatype;

  g_return_if_fail (keep != NULL);
  g_return_if_fail (FO_IS_KEEP (keep));
  g_return_if_fail (FO_IS_DATATYPE (new_within_column));

  if (new_within_column)
    g_object_ref (G_OBJECT (new_within_column));
  if (keep->within_column)
    g_object_unref (G_OBJECT (keep->within_column));
  keep->within_column = new_within_column;
  /*g_object_notify(G_OBJECT(keep), "within-column");*/
}

/**
 * fo_keep_get_within_column:
 * @datatype: #FoKeep
 * 
 * Gets the .within-column component value of @datatype
 * 
 * Return value: The .within-column value of @datatype
 **/
FoDatatype*
fo_keep_get_within_column (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), 0);

  return FO_KEEP (datatype)->within_column;
}

/**
 * fo_keep_set_within_line:
 * @datatype:     #FoKeep
 * @new_within_line:  New .within-line value
 * 
 * Sets the .within-line component of @datatype
 **/
void
fo_keep_set_within_line (FoDatatype *datatype,
			 FoDatatype *new_within_line)
{
  FoKeep *keep = (FoKeep *) datatype;

  g_return_if_fail (keep != NULL);
  g_return_if_fail (FO_IS_KEEP (keep));
  g_return_if_fail (FO_IS_DATATYPE (new_within_line));

  if (new_within_line)
    g_object_ref (G_OBJECT (new_within_line));
  if (keep->within_line)
    g_object_unref (G_OBJECT (keep->within_line));
  keep->within_line = new_within_line;
  /*g_object_notify(G_OBJECT(keep), "within-line");*/
}

/**
 * fo_keep_get_within_line:
 * @datatype: #FoKeep
 * 
 * Gets the .within-line component value of @datatype
 * 
 * Return value: The .within-line value of @datatype
 **/
FoDatatype*
fo_keep_get_within_line (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), 0);

  return FO_KEEP (datatype)->within_line;
}

gchar*
fo_keep_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (object), NULL);

  return g_strdup_printf ("page: %s; column: %s; line: %s",
			  fo_object_sprintf (FO_KEEP (object)->within_page),
			  fo_object_sprintf (FO_KEEP (object)->within_column),
			  fo_object_sprintf (FO_KEEP (object)->within_line));
}

/**
 * fo_keep_copy:
 * @datatype: Source #FoKeep
 * 
 * Creates a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_keep_copy (FoDatatype *datatype)
{
  FoDatatype* keep;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), NULL);

  keep = fo_keep_new ();
  FO_KEEP (keep)->within_page =
    FO_KEEP (datatype)->within_page;
  FO_KEEP (keep)->within_column =
    FO_KEEP (datatype)->within_column;
  FO_KEEP (keep)->within_line =
    FO_KEEP (datatype)->within_line;

  return (keep);
}

/**
 * fo_keep_resolve:
 * @shortform:       Single-value short form of the keep, or
 *                     NULL
 * @within_line:     .within-line component of the keep, or NULL
 * @within_column:   .within-column component of the keep, or NULL
 * @within_page:     .within-page component of the keep, or NULL
 * @error:           GError used for reporting errors
 * 
 * Resolve the shortform and components of the keep in
 * accordance with Section 5.11, Datatypes, of the XSL 1.0
 * Recommendation.
 *
 * Does not change the ref-count of any FoDatatype arguments.
 *
 * Return value: Compound keep datatype, or NULL if an error
 *               occurred
 **/
FoDatatype*
fo_keep_resolve (FoDatatype *shortform,
		 FoDatatype *within_line,
		 FoDatatype *within_column,
		 FoDatatype *within_page,
		 GError **error G_GNUC_UNUSED)
{
  FoDatatype *use_keep;

  g_return_val_if_fail (shortform == NULL ||
			FO_IS_KEEP (shortform),
			NULL);
  g_return_val_if_fail (within_line == NULL ||
			FO_IS_INTEGER (within_line) ||
			(FO_IS_ENUM (within_line) &&
			 ((fo_enum_get_value (within_line) == FO_ENUM_ENUM_AUTO) ||
			  (fo_enum_get_value (within_line) == FO_ENUM_ENUM_ALWAYS))),
			NULL);
  g_return_val_if_fail (within_column == NULL ||
			FO_IS_INTEGER (within_column) ||
			(FO_IS_ENUM (within_column) &&
			 ((fo_enum_get_value (within_column) == FO_ENUM_ENUM_AUTO) ||
			  (fo_enum_get_value (within_column) == FO_ENUM_ENUM_ALWAYS))),
			NULL);
  g_return_val_if_fail (within_page == NULL ||
			FO_IS_INTEGER (within_page) ||
			(FO_IS_ENUM (within_page) &&
			 ((fo_enum_get_value (within_page) == FO_ENUM_ENUM_AUTO) ||
			  (fo_enum_get_value (within_page) == FO_ENUM_ENUM_ALWAYS))),
			NULL);

  if (FO_IS_KEEP (shortform) &&
      within_line == NULL &&
      within_column == NULL &&
      within_page == NULL)
    {
      use_keep = shortform;
    }
  else
    {
      if (shortform == NULL)
	{
	  use_keep = fo_keep_new ();
	}
      else
	{
	  use_keep = fo_keep_copy (shortform);
	}

      if (within_line != NULL)
	{
	  fo_keep_set_within_line (use_keep,
				   within_line);
	}

      if (within_column != NULL)
	{
	  fo_keep_set_within_column (use_keep,
				     within_column);
	}

      if (within_page != NULL)
	{
	  fo_keep_set_within_page (use_keep,
				   within_page);
	}
    }

  return use_keep;
}
