/* Fo
 * fo-page-sequence-walker.c: Walker for a page sequence
 *
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo-page-sequence-walker-private.h"

/**
 * SECTION:fo-page-sequence-walker
 * @short_description: Abstract 'page-sequence-walker' formatting object
 *
 * A page-sequence walker finds the next page master for a
 * page-sequnce.
 */

const char *fo_page_sequence_walker_error_messages[] = {
  N_("Failed"),
  N_("Warning"),
  N_("No 'next_page_master()' function for object: %s"),
  N_("No 'end_page_masters()' function for object: %s")
};

static void _base_class_init (FoPageSequenceWalkerClass *klass);
static void _class_init      (FoPageSequenceWalkerClass *klass);
static void _dispose         (GObject                   *object);

static FoFo * _next_page_master_default (FoPageSequenceWalker *walker,
					 GError              **error);
static FoFo * _end_page_masters_default (FoPageSequenceWalker *walker,
					 GError              **error);

static gpointer parent_class;

/**
 * fo_page_sequence_walker_get_type:
 * 
 * Register the #FoPageSequenceWalker object type.
 * 
 * Return value: #GType value of the #FoPageSequenceWalker object type.
 **/
GType
fo_page_sequence_walker_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoPageSequenceWalkerClass),
	  (GBaseInitFunc) NULL,
	  (GBaseFinalizeFunc) NULL,
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoPageSequenceWalker),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoPageSequenceWalker",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * _base_class_init:
 * @klass: #FoPageSequenceWalkerClass base class
 *         object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPageSequenceWalkerClass
 **/
static void
_base_class_init (FoPageSequenceWalkerClass *klass)
{
  klass->next_page_master = _next_page_master_default;
  klass->end_page_masters = _end_page_masters_default;
}

/**
 * _class_init:
 * @klass: #FoPageSequenceWalkerClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPageSequenceWalkerClass.
 **/
static void
_class_init (FoPageSequenceWalkerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->dispose = _dispose;
}

/**
 * _dispose:
 * @object: #FoPageSequenceWalker object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoPageSequenceWalker.
 **/
static void
_dispose (GObject *object)
{
  FoPageSequenceWalker *fo_page_sequence_walker;

  fo_page_sequence_walker = FO_PAGE_SEQUENCE_WALKER (object);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * fo_page_sequence_walker_new:
 * 
 * Creates a new #FoPageSequenceWalker initialized to default value.
 * 
 * Return value: the new #FoPageSequenceWalker
 **/
FoPageSequenceWalker *
fo_page_sequence_walker_new (void)
{
  return FO_PAGE_SEQUENCE_WALKER (g_object_new (fo_page_sequence_walker_get_type (),
						NULL));
}

/**
 * _next_page_master_default:
 * @walker: The #FoPageSequenceWalke object.
 * @error:  Indication of any error that occurred.
 * 
 * Complain because the subclass hasn't overwritten this.
 **/
static FoFo *
_next_page_master_default (FoPageSequenceWalker *walker,
			   GError              **error)
{
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_WALKER (walker), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  g_set_error (error,
	       FO_PAGE_SEQUENCE_WALKER_ERROR,
	       FO_PAGE_SEQUENCE_WALKER_ERROR_NO_NEXT,
	       _(fo_page_sequence_walker_error_messages[FO_PAGE_SEQUENCE_WALKER_ERROR_NO_NEXT]),
	       fo_object_sprintf (FO_OBJECT (walker)));
  return NULL;
}

/**
 * fo_page_sequence_walker_next_page_master:
 * @walker: The #FoPageSequenceWalke object.
 * @error:  Indication of any error that occurred.
 * 
 * Gets the next #FoPageMaster in the page sequence.
 **/
FoFo *
fo_page_sequence_walker_next_page_master (FoPageSequenceWalker *walker,
					  GError              **error)
{
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_WALKER (walker), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  return FO_PAGE_SEQUENCE_WALKER_GET_CLASS (walker)->next_page_master (walker,
								       error);
}

/**
 * _end_page_masters_default:
 * @walker: The #FoPageSequenceWalke object.
 * @error:  Indication of any error that occurred.
 * 
 * Complain because the subclass hasn't overwritten this.
 **/
static FoFo *
_end_page_masters_default (FoPageSequenceWalker *walker,
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
 * fo_page_sequence_walker_end_page_masters:
 * @walker: The #FoPageSequenceWalke object.
 * @error:  Indication of any error that occurred.
 * 
 * Gets any #FoPageMaster needed at the end of the page sequence.
 **/
FoFo *
fo_page_sequence_walker_end_page_masters (FoPageSequenceWalker *walker,
					  GError              **error)
{
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_WALKER (walker), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  return FO_PAGE_SEQUENCE_WALKER_GET_CLASS (walker)->end_page_masters (walker,
								       error);
}

/**
 * fo_page_sequence_walker_error_quark:
 * 
 * Gets the #GQuark identifying #FoPageSequenceWalker errors.
 * 
 * Return value: #GQuark identifying #FoPageSequenceWalker errors.
 **/
GQuark
fo_page_sequence_walker_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("fo-page-sequence-walker-error");
  return quark;
}
