/* Fo
 * fo-keep.c: Keep datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
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

static void _init         (FoKeep      *keep);
static void _class_init   (FoKeepClass *klass);
static void _set_property (GObject       *object,
			   guint          prop_id,
			   const GValue  *value,
			   GParamSpec    *pspec);
static void _get_property (GObject       *object,
			   guint          prop_id,
			   GValue        *value,
			   GParamSpec    *pspec);
static void _dispose      (GObject       *object);

static gchar*       _sprintf           (FoObject   *object);
static FoDatatype * _copy              (FoDatatype *datatype);
static void         _set_within_line   (FoDatatype *keep,
					FoDatatype *new_within_line);
static void         _set_within_column (FoDatatype *keep,
					FoDatatype *new_within_column);
static void         _set_within_page   (FoDatatype *keep,
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
        (GClassInitFunc) _class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoKeep),
        0,              /* n_preallocs */
        (GInstanceInitFunc) _init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoKeep",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * _init:
 * @keep: #FoKeep object to initialise
 * 
 * Implements GInstanceInitFunc for #FoKeep
 **/
void
_init (FoKeep *keep)
{
  keep->within_page =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_AUTO));
  keep->within_column =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_AUTO));
  keep->within_line =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_AUTO));
}

/**
 * _class_init:
 * @klass: FoKeepClass object to initialise
 * 
 * Implements GClassInitFunc for FoKeepClass
 **/
void
_class_init (FoKeepClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->dispose = _dispose;

  object_class->set_property = _set_property;
  object_class->get_property = _get_property;

  FO_DATATYPE_CLASS (klass)->copy = _copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = _sprintf;

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
 * _dispose:
 * @object: FoKeep object to dispose
 * 
 * Implements GObjectDisposeFunc for FoKeep
 **/
void
_dispose (GObject *object)
{
  FoKeep *keep = FO_KEEP (object);

  if (keep->within_page != NULL)
    {
      g_object_unref (keep->within_page);
      keep->within_page = NULL;
    }

  if (keep->within_column != NULL)
    {
      g_object_unref (keep->within_column);
      keep->within_column = NULL;
    }

  if (keep->within_line != NULL)
    {
      g_object_unref (keep->within_line);
      keep->within_line = NULL;
    }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}


/**
 * _get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoKeep
 **/
void
_get_property (GObject         *object,
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
 * _set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoKeep
 **/
void
_set_property (GObject         *object,
	       guint            prop_id,
	       const GValue    *value,
	       GParamSpec      *pspec)
{
  FoDatatype *keep;

  keep = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_WITHIN_LINE:
      _set_within_line (keep, g_value_get_object (value));
      break;
    case PROP_WITHIN_COLUMN:
      _set_within_column (keep, g_value_get_object (value));
      break;
    case PROP_WITHIN_PAGE:
      _set_within_page (keep, g_value_get_object (value));
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
  return FO_DATATYPE (g_object_new (fo_keep_get_type (),
				    NULL));
}

/**
 * fo_keep_new_with_value:
 * @value: Keep of the new #FoKeep
 * 
 * Creates a new #FoKeep set to @value
 * 
 * Return value: The new #FoKeep
 **/
FoDatatype *
fo_keep_new_with_value (FoDatatype *value)
{
  FoDatatype *keep = fo_keep_new ();

  _set_within_page (keep, value);
  _set_within_column (keep, value);
  _set_within_line (keep, value);

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
FoDatatype *
fo_keep_get_keep_always (void)
{
  static FoDatatype *keep = NULL;

  if (keep == NULL)
    {
      keep =
	fo_keep_new_with_value (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_ALWAYS));
    }

  return keep;
}

/**
 * fo_keep_get_within_page:
 * @datatype: #FoKeep
 * 
 * Gets the .within-page component value of @datatype
 * 
 * Return value: The .within-page value of @datatype
 **/
FoDatatype *
fo_keep_get_within_page (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), 0);

  return FO_KEEP (datatype)->within_page;
}

/**
 * _set_within_page:
 * @datatype:     #FoKeep
 * @new_within_page:  New .within-page value
 * 
 * Sets the .within-page component of @datatype
 **/
static void
_set_within_page (FoDatatype *datatype,
		  FoDatatype *new_within_page)
{
  FoKeep *keep = (FoKeep *) datatype;

  g_return_if_fail (keep != NULL);
  g_return_if_fail (FO_IS_KEEP (keep));
  g_return_if_fail ((new_within_page == NULL) ||
		    FO_IS_DATATYPE (new_within_page));

  if (new_within_page != NULL)
    {
      g_object_ref (new_within_page);
    }
  if (keep->within_page != NULL)
    {
      g_object_unref (keep->within_page);
    }

  keep->within_page = new_within_page;
  /*g_object_notify(G_OBJECT(keep), "within-page");*/
}

/**
 * fo_keep_get_within_column:
 * @datatype: #FoKeep
 * 
 * Gets the .within-column component value of @datatype
 * 
 * Return value: The .within-column value of @datatype
 **/
FoDatatype *
fo_keep_get_within_column (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), 0);

  return FO_KEEP (datatype)->within_column;
}

/**
 * _set_within_column:
 * @datatype:     #FoKeep
 * @new_within_column:  New .within-column value
 * 
 * Sets the .within-column component of @datatype
 **/
static void
_set_within_column (FoDatatype *datatype,
		    FoDatatype *new_within_column)
{
  FoKeep *keep = (FoKeep *) datatype;

  g_return_if_fail (keep != NULL);
  g_return_if_fail (FO_IS_KEEP (keep));
  g_return_if_fail ((new_within_column == NULL) ||
		    FO_IS_DATATYPE (new_within_column));

  if (new_within_column != NULL)
    {
      g_object_ref (new_within_column);
    }

  if (keep->within_column != NULL)
    {
      g_object_unref (keep->within_column);
    }

  keep->within_column = new_within_column;
  /*g_object_notify(G_OBJECT(keep), "within-column");*/
}

/**
 * fo_keep_get_within_line:
 * @datatype: #FoKeep
 * 
 * Gets the .within-line component value of @datatype
 * 
 * Return value: The .within-line value of @datatype
 **/
FoDatatype *
fo_keep_get_within_line (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (datatype), 0);

  return FO_KEEP (datatype)->within_line;
}

/**
 * _set_within_line:
 * @datatype:     #FoKeep
 * @new_within_line:  New .within-line value
 * 
 * Sets the .within-line component of @datatype
 **/
static void
_set_within_line (FoDatatype *datatype,
		  FoDatatype *new_within_line)
{
  FoKeep *keep = (FoKeep *) datatype;

  g_return_if_fail (keep != NULL);
  g_return_if_fail (FO_IS_KEEP (keep));
  g_return_if_fail ((new_within_line == NULL) ||
		    FO_IS_DATATYPE (new_within_line));

  if (new_within_line != NULL)
    {
      g_object_ref (new_within_line);
    }

  if (keep->within_line != NULL)
    {
      g_object_unref (keep->within_line);
    }

  keep->within_line = new_within_line;
  /*g_object_notify(G_OBJECT(keep), "within-line");*/
}

/**
 * _sprintf:
 * @object: 
 *
 * 
 *
 * Returns: 
 **/
static gchar*
_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_KEEP (object), NULL);

  gchar *within_page = fo_object_sprintf (FO_KEEP (object)->within_page);
  gchar *within_column = fo_object_sprintf (FO_KEEP (object)->within_column);
  gchar *within_line = fo_object_sprintf (FO_KEEP (object)->within_line);

  gchar *string = g_strdup_printf ("page: %s; column: %s; line: %s",
				   within_page,
				   within_column,
				   within_line);

  g_free (within_line);
  g_free (within_column);
  g_free (within_page);

  return string;
}

/**
 * _copy:
 * @datatype: Source #FoKeep
 * 
 * Creates a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
static FoDatatype *
_copy (FoDatatype *datatype)
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
FoDatatype *
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
			 ((fo_enum_get_value (within_line) ==
			   FO_ENUM_ENUM_AUTO) ||
			  (fo_enum_get_value (within_line) ==
			   FO_ENUM_ENUM_ALWAYS))),
			NULL);
  g_return_val_if_fail (within_column == NULL ||
			FO_IS_INTEGER (within_column) ||
			(FO_IS_ENUM (within_column) &&
			 ((fo_enum_get_value (within_column) ==
			   FO_ENUM_ENUM_AUTO) ||
			  (fo_enum_get_value (within_column) ==
			   FO_ENUM_ENUM_ALWAYS))),
			NULL);
  g_return_val_if_fail (within_page == NULL ||
			FO_IS_INTEGER (within_page) ||
			(FO_IS_ENUM (within_page) &&
			 ((fo_enum_get_value (within_page) ==
			   FO_ENUM_ENUM_AUTO) ||
			  (fo_enum_get_value (within_page) ==
			   FO_ENUM_ENUM_ALWAYS))),
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
	  use_keep = _copy (shortform);
	}

      if (within_line != NULL)
	{
	  _set_within_line (use_keep,
			    within_line);
	}

      if (within_column != NULL)
	{
	  _set_within_column (use_keep,
			      within_column);
	}

      if (within_page != NULL)
	{
	  _set_within_page (use_keep,
			    within_page);
	}
    }

  return use_keep;
}
