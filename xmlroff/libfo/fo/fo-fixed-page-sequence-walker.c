/* Fo
 * fo-fixed-page-sequence-walker.c: Walker for a fixed page sequence
 *
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo-fixed-page-sequence-walker.h"
#include "fo-page-sequence-walker-private.h"
#include "fo/fo-simple-page-master.h"

/**
 * SECTION:fo-fixed-page-sequence-walker
 * @short_description: Walker for a fixed page sequence
 *
 * Returns the same fixed page master for all pages.
 */

struct _FoFixedPageSequenceWalker
{
  FoPageSequenceWalker parent_instance;

  FoFo *page_master;
};

struct _FoFixedPageSequenceWalkerClass
{
  FoPageSequenceWalkerClass parent_class;
};

enum {
  PROP_0,
  PROP_PAGE_MASTER
};

static void _class_init (FoFixedPageSequenceWalkerClass *klass);
static void _get_property (GObject      *object,
			   guint         prop_id,
			   GValue       *value,
			   GParamSpec   *pspec);
static void _set_property (GObject      *object,
			   guint         prop_id,
			   const GValue *value,
			   GParamSpec   *pspec);
static void _dispose      (GObject      *object);
static gchar* _sprintf    (FoObject *object);

static FoFo * _next_page_master (FoPageSequenceWalker *walker,
				 GError              **error);
static FoFo * _end_page_masters (FoPageSequenceWalker *walker,
				 GError              **error);
static void   _set_page_master  (FoFixedPageSequenceWalker *fpsw,
				 FoFo                      *new_page_master);

static gpointer parent_class;

/**
 * fo_page_sequence_walker_get_type:
 * 
 * Register the #FoFixedPageSequenceWalker object type.
 * 
 * Return value: #GType value of the #FoFixedPageSequenceWalker object type.
 **/
GType
fo_fixed_page_sequence_walker_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoFixedPageSequenceWalkerClass),
	  (GBaseInitFunc) NULL,
	  (GBaseFinalizeFunc) NULL,
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoFixedPageSequenceWalker),
	  0,              /* n_preallocs */
	  (GInstanceInitFunc) NULL,
	  NULL	 	  /* value_table */
	};
      
      object_type = g_type_register_static (FO_TYPE_PAGE_SEQUENCE_WALKER,
                                            "FoFixedPageSequenceWalker",
                                            &object_info,
					    0);
    }
  
  return object_type;
}

/**
 * _class_init:
 * @klass: #FoFixedPageSequenceWalkerClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoFixedPageSequenceWalkerClass.
 **/
static void
_class_init (FoFixedPageSequenceWalkerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoPageSequenceWalkerClass *walker_class =
    FO_PAGE_SEQUENCE_WALKER_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  walker_class->next_page_master = _next_page_master;
  walker_class->end_page_masters = _end_page_masters;

  fo_object_class->print_sprintf = _sprintf;

  object_class->dispose = _dispose;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  g_object_class_install_property
    (object_class,
     PROP_PAGE_MASTER,
     g_param_spec_object ("page-master",
			  _("Page master"),
			  _("Page master"),
			  FO_TYPE_PAGE_MASTER,
			  G_PARAM_READWRITE
			  | G_PARAM_CONSTRUCT_ONLY
			  | G_PARAM_STATIC_STRINGS));
}

/**
 * _dispose:
 * @object: #FoFixedPageSequenceWalker object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoFixedPageSequenceWalker.
 **/
static void
_dispose (GObject *object)
{
  FoFixedPageSequenceWalker *fo_page_sequence_walker;

  fo_page_sequence_walker = FO_FIXED_PAGE_SEQUENCE_WALKER (object);

  g_object_unref (fo_page_sequence_walker->page_master);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoPageMaster.
 **/
void
_get_property (GObject    *object,
	       guint       prop_id,
	       GValue     *value,
	       GParamSpec *pspec)
{
  FoFixedPageSequenceWalker *fpsw =
    FO_FIXED_PAGE_SEQUENCE_WALKER (object);

  switch (prop_id)
    {
    case PROP_PAGE_MASTER:
      g_value_set_object (value,
			  G_OBJECT (fo_fixed_page_sequence_walker_get_page_master (fpsw)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoPageMaster.
 **/
void
_set_property (GObject      *object,
	       guint         prop_id,
	       const GValue *value,
	       GParamSpec   *pspec)
{
  FoFixedPageSequenceWalker *fpsw =
    FO_FIXED_PAGE_SEQUENCE_WALKER (object);

  switch (prop_id)
    {
    case PROP_PAGE_MASTER:
      _set_page_master (fpsw, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_fixed_page_sequence_walker_new:
 * 
 * Creates a new #FoFixedPageSequenceWalker initialized to default value.
 * 
 * Return value: the new #FoFixedPageSequenceWalker
 **/
FoFixedPageSequenceWalker *
fo_fixed_page_sequence_walker_new (FoFo *page_master)
{
  return
    FO_FIXED_PAGE_SEQUENCE_WALKER (g_object_new (fo_fixed_page_sequence_walker_get_type (),
						 "page-master",
						 page_master,
						 NULL));
}

static gchar*
_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_FIXED_PAGE_SEQUENCE_WALKER (object), NULL);

  return (g_strdup_printf("%s",
			  g_type_name (G_TYPE_FROM_INSTANCE (object))));
}

/**
 * _next_page_master:
 * @walker: The #FoPageSequenceWalke object.
 * @error:  Indication of any error that occurred.
 * 
 * Gets the next #FoPageMaster in the page sequence.
 **/
static FoFo *
_next_page_master (FoPageSequenceWalker *walker,
		   GError              **error)
{
  g_return_val_if_fail (FO_IS_FIXED_PAGE_SEQUENCE_WALKER (walker),
			NULL);
  g_return_val_if_fail (error == NULL || *error == NULL,
			NULL);

  return FO_FIXED_PAGE_SEQUENCE_WALKER (walker)->page_master;
}

/**
 * _end_page_masters:
 * @walker: The #FoPageSequenceWalke object.
 * @error:  Indication of any error that occurred.
 * 
 * Gets any #FoPageMaster needed at the end of the page sequence.
 **/
static FoFo *
_end_page_masters (FoPageSequenceWalker *walker,
		   GError              **error)
{
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_WALKER (walker), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  g_set_error (error,
	       FO_PAGE_SEQUENCE_WALKER_ERROR,
	       FO_PAGE_SEQUENCE_WALKER_ERROR_NO_END,
	       _(fo_page_sequence_walker_error_messages[FO_PAGE_SEQUENCE_WALKER_ERROR_NO_END]),
	       fo_object_sprintf (FO_OBJECT (walker)));
  return NULL;
}

/**
 * fo_fixed_page_sequence_walker_get_page_master:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "master-name" property of @fo_fo.
 *
 * Return value: The "master-name" property value.
**/
FoFo *
fo_fixed_page_sequence_walker_get_page_master (FoFixedPageSequenceWalker *fpsw)
{
  g_return_val_if_fail (fpsw != NULL, NULL);
  g_return_val_if_fail (FO_IS_FIXED_PAGE_SEQUENCE_WALKER (fpsw), NULL);

  return fpsw->page_master;
}

/**
 * fo_fixed_page_sequence_walker_set_page_master:
 * @fo_fo: The #FoFo object.
 * @new_page_master: The new "master-name" property value.
 * 
 * Sets the "master-name" property of @fo_fo to @new_page_master.
 **/
static void
_set_page_master (FoFixedPageSequenceWalker *fpsw,
		  FoFo                      *new_page_master)
{
  g_return_if_fail (fpsw != NULL);
  g_return_if_fail (FO_IS_FIXED_PAGE_SEQUENCE_WALKER (fpsw));
  g_return_if_fail ((new_page_master == NULL) ||
		    FO_IS_SIMPLE_PAGE_MASTER (new_page_master));

  if (new_page_master != NULL)
    {
      g_object_ref (new_page_master);
    }
  if (fpsw->page_master != NULL)
    {
      g_object_unref (fpsw->page_master);
    }
  fpsw->page_master = new_page_master;
  /*g_object_notify (G_OBJECT (fpsw), "master-name");*/
}
