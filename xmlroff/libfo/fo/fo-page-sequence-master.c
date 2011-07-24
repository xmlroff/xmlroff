/* Fo
 * fo-page-sequence-master.c: 'page-sequence-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-page-sequence-master-private.h"
#include "fo/fo-tree.h"
#include "fo/fo-single-page-master-reference.h"
#include "fo/fo-repeatable-page-master-reference.h"
#include "fo/fo-repeatable-page-master-alternatives.h"
#include "fo/fo-sequenced-page-sequence-walker.h"
#include "property/fo-property-master-name.h"

static void fo_page_sequence_master_class_init  (FoPageSequenceMasterClass *klass);
static void fo_page_sequence_master_dispose    (GObject           *object);
static gboolean fo_page_sequence_master_validate_content (FoFo    *fo,
                                                          GError **error);

static FoPageSequenceWalker * _new_walker (FoFo    *fo_fo,
					   GError **error);
static gpointer parent_class;

/**
 * fo_page_sequence_master_get_type:
 * 
 * Register the #FoPageSequenceMaster object type.
 * 
 * Return value: #GType value of the #FoPageSequenceMaster object type.
 **/
GType
fo_page_sequence_master_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoPageSequenceMasterClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) fo_page_sequence_master_class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoPageSequenceMaster),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_PAGE_MASTER,
                                            "FoPageSequenceMaster",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_page_sequence_master_class_init:
 * @klass: #FoPageSequenceMasterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPageSequenceMasterClass.
 **/
void
fo_page_sequence_master_class_init (FoPageSequenceMasterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);
  FoPageMasterClass *page_master_class = FO_PAGE_MASTER_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  page_master_class->new_walker = _new_walker;

  object_class->dispose = fo_page_sequence_master_dispose;

  FO_FO_CLASS (klass)->area_new2 = NULL;
}

/**
 * fo_page_sequence_master_dispose:
 * @object: #FoPageSequenceMaster object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoPageSequenceMaster.
 **/
void
fo_page_sequence_master_dispose (GObject *object)
{
  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * fo_page_sequence_master_new:
 * 
 * Creates a new #FoPageSequenceMaster initialized to default value.
 * 
 * Return value: the new #FoPageSequenceMaster.
 **/
FoFo*
fo_page_sequence_master_new (void)
{
  return FO_FO (g_object_new (fo_page_sequence_master_get_type (),
                              NULL));
}

/**
 * fo_page_sequence_master_validate_content:
 * @fo:    #FoPageMaster object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_page_sequence_master_validate_content (FoFo    *fo,
                                          GError **error)
{
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  FoNode *fo_node = FO_NODE (fo);

  fo_fo_trim_whitespace_children (fo);

  gint n_children = fo_node_n_children (fo_node);

  if (n_children == 0)
    {
      goto error;
    }

  FoNode *child_node = fo_node_first_child (fo_node);

  while (child_node)
    {
      if (FO_IS_SINGLE_PAGE_MASTER_REFERENCE (child_node) ||
	  FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (child_node) ||
	  FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES (child_node))
	{
	  child_node = fo_node_next_sibling (child_node);
	}
      else
	{
	  goto error;
	}
    }

  return FALSE;

 error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (fo));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
}

/**
 * _new_walker:
 * @fo_fo: The #FoPageMaster object.
 * 
 * Gets a new #FoPageSequenceWalker for @fo.
 **/
static FoPageSequenceWalker *
_new_walker (FoFo  *fo_fo,
	     GError **error)
{
  g_return_val_if_fail (FO_IS_PAGE_MASTER (fo_fo), NULL);

  return FO_PAGE_SEQUENCE_WALKER (fo_sequenced_page_sequence_walker_new (fo_fo));
}
