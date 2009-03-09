/* Fo
 * fo-xsl-formatter.c: Object type for libxslt XSLT processor
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <string.h>
#include "fo-utils.h"
#include "fo-xml-doc-private.h"
#include "fo-xml-node-private.h"
#include "fo-doc-private.h"
#include "fo-doc-gp.h"
#include "fo-xsl-formatter.h"
#include "fo/fo-fo-private.h"
#include "fo/fo-all-fo.h"
#include "property/fo-property-eval.h"
#include "area/fo-area.h"
#include "area/fo-area-tree.h"
#include "area-to-pdf.h"
#include <libxml/xmlversion.h>
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

const char *fo_xsl_formatter_error_messages [] = {
  N_("FoXslFormatter error"),
  N_("XSLT format failed"),
  N_("Unable to parse stylesheet file: %s"),
  N_("No input result tree specified"),
  N_("Result tree does not have an XSL-FO root element:: URI: %s; local-name: %s"),
  N_("No area tree present"),
  N_("No output FoDoc specified"),
  N_("Specified FoDoc is not FoDoc object type"),
  N_("Unknown 'fo:' element type: %s"),
};

#define XSL_FO_NAMESPACE \
    "http://www.w3.org/1999/XSL/Format"

struct _FoXslFormatter
{
  FoLibfoModule parent_instance;

  FoXmlDoc *result_tree;

  FoDoc    *fo_doc;

  FoFo     *fo_tree;
  FoArea   *area_tree;
};

struct _FoXslFormatterClass
{
  FoLibfoModuleClass parent_class;
};

enum {
  PROP_0,
  PROP_RESULT_TREE,
  PROP_FO_TREE,
  PROP_AREA_TREE,
  PROP_FO_DOC
};

static void fo_xsl_formatter_class_init   (FoXslFormatterClass *klass);
static void fo_xsl_formatter_finalize     (GObject             *object);

static const LibfoVersionInfo * _version_info ();

static void fo_xsl_formatter_get_property (GObject             *object,
					   guint                prop_id,
					   GValue              *value,
					   GParamSpec          *pspec);
static void fo_xsl_formatter_set_property (GObject             *object,
					   guint                prop_id,
					   const GValue        *value,
					   GParamSpec          *pspec);

static gpointer parent_class;

static LibfoVersionInfo version_info =
  {
    LIBFO_MODULE_XSL_FORMATTER,
    "xsl-formatter",
    "FoXslFormatter",
    LIBFO_VERSION,
    LIBFO_VERSION_STRING,
    LIBFO_VERSION,
    LIBFO_VERSION_STRING
  };

/**
 * fo_xsl_formatter_error_quark:
 * 
 * Get the error quark for #FoXslFormatter.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: #GQuark associated with #FoXslFormatter errors.
 **/
GQuark
fo_xsl_formatter_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoXslFormatter error");
  return quark;
}


/**
 * fo_xsl_formatter_get_type:
 * 
 * Register the #FoXslFormatter object type.
 * 
 * Return value: #GType value of the #FoXslFormatter object type.
p **/
GType fo_xsl_formatter_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoXslFormatterClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_xsl_formatter_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoXslFormatter),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_LIBFO_MODULE,
                                            "FoXslFormatter",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_xsl_formatter_class_init:
 * @klass: #FoXslFormatterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoXslFormatterClass.
 **/
void
fo_xsl_formatter_class_init (FoXslFormatterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoLibfoModuleClass *fo_libfo_module_class =
    FO_LIBFO_MODULE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->get_property = fo_xsl_formatter_get_property;
  object_class->set_property = fo_xsl_formatter_set_property;
  object_class->finalize     = fo_xsl_formatter_finalize;

  fo_libfo_module_class->version        = libfo_version;
  fo_libfo_module_class->version_string = libfo_version_string;
  fo_libfo_module_class->version_info   = _version_info;

  g_object_class_install_property
    (object_class,
     PROP_RESULT_TREE,
     g_param_spec_pointer ("result-tree",
			   _("Result Tree FoXmlDoc"),
			   _("Result of XSLT transform"),
			   G_PARAM_WRITABLE));

  g_object_class_install_property
    (object_class,
     PROP_FO_TREE,
     g_param_spec_object ("fo-tree",
			_("FO tree"),
			_("Formatting Object tree"),
			G_TYPE_OBJECT,
			G_PARAM_READABLE));

  g_object_class_install_property
    (object_class,
     PROP_AREA_TREE,
     g_param_spec_object ("area-tree",
			_("Area tree"),
			_("Area tree"),
			G_TYPE_OBJECT,
			G_PARAM_READABLE));

  g_object_class_install_property
    (object_class,
     PROP_FO_DOC,
     g_param_spec_object ("fo-doc",
			_("FoDoc"),
			_("Output document"),
			FO_TYPE_DOC,
			G_PARAM_WRITABLE));
}

/**
 * fo_xsl_formatter_finalize:
 * @object: #FoObject object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoXslFormatter.
 **/
void
fo_xsl_formatter_finalize  (GObject *object)
{
  FoXslFormatter *fo_xsl_formatter;

  fo_xsl_formatter = FO_XSL_FORMATTER (object);

  if (fo_xsl_formatter->result_tree != NULL)
    {
      fo_xml_doc_unref (fo_xsl_formatter->result_tree);
    }

  if (fo_xsl_formatter->fo_tree != NULL)
    {
      g_object_unref (fo_xsl_formatter->fo_tree);
    }

  if (fo_xsl_formatter->area_tree != NULL)
    {
      g_object_unref (fo_xsl_formatter->area_tree);
    }

  if (fo_xsl_formatter->fo_doc != NULL)
    {
      g_object_unref (fo_xsl_formatter->fo_doc);
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

const LibfoVersionInfo *
_version_info ()
{
  version_info.runtime = libfo_version ();
  version_info.runtime_string = libfo_version_string ();

  return &version_info;
}

/**
 * fo_xsl_formatter_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoXslFormatter
 **/
void
fo_xsl_formatter_get_property (GObject        *object,
			       guint           param_id,
			       GValue         *value,
			       GParamSpec     *pspec)
{
  FoXslFormatter *xsl_formatter = FO_XSL_FORMATTER (object);
  
  switch (param_id)
    {
    case PROP_FO_TREE:
      g_value_set_object (value, xsl_formatter->fo_tree);
      break;
    case PROP_AREA_TREE:
      g_value_set_object (value, xsl_formatter->area_tree);
      break;
    case PROP_RESULT_TREE:
    case PROP_FO_DOC:
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_xsl_formatter_set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoXslFormatter
 **/
void
fo_xsl_formatter_set_property (GObject      *object,
			       guint         param_id,
			       const GValue *value,
			       GParamSpec   *pspec)
{
  FoXslFormatter *fo_xsl_formatter;

  fo_xsl_formatter = FO_XSL_FORMATTER (object);

  switch (param_id)
    {
    case PROP_RESULT_TREE:
      fo_xsl_formatter_set_result_tree (fo_xsl_formatter,
					g_value_get_pointer (value));
      break;
    case PROP_FO_DOC:
      fo_xsl_formatter_set_fo_doc (fo_xsl_formatter,
				   g_value_get_object (value));
      break;
    case PROP_FO_TREE:
    case PROP_AREA_TREE:
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_xsl_formatter_new:
 * 
 * Creates a new #FoXslFormatter initialized to default value.
 * 
 * Return value: The new #FoXslFormatter.
 **/
FoXslFormatter *
fo_xsl_formatter_new (void)
{
  FoXslFormatter* xsl_formatter;

  xsl_formatter =
    g_object_new (fo_xsl_formatter_get_type (),
		  NULL);

  return xsl_formatter;
}

/**
 * fo_xml_element_node_to_fo_node:
 * @node:  #xmlNodePtr for which to create a #FoFo.
 * @error: Indication of any error that occurred.
 * 
 * Creates a #FoFo corresponding to @node.
 * 
 * Return value: New @FoFo, or %NULL if an error occurred.
 **/
static FoFo*
fo_xml_element_node_to_fo_node (xmlNodePtr node,
				GError **error)
{
  FoFo *fo_node = NULL;
  gboolean ok = FALSE;
  gchar *name;

  g_return_val_if_fail (node != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  name = (gchar *) node->name;

  /* Hand-built parsing of node name to determine FoFo type. */
  switch (name[0]) {
  case 'b':
    switch (name[1]) {
    case 'a':
      if (strcmp (name, "basic-link") == 0) {
	fo_node = fo_basic_link_new ();
	ok = TRUE;
      }
      break; /* end 'ba' */
    case 'i':
      if (strcmp (name, "bidi-override") == 0) {
	fo_node = fo_bidi_override_new ();
	ok = TRUE;
      }
      break; /* end 'bi' */
    case 'l':
      if (strcmp (name, "block") == 0) {
	fo_node = fo_block_new ();
	ok = TRUE;
      } else if (strcmp (name, "block-container") == 0) {
	fo_node = fo_block_container_new ();
	ok = TRUE;
      }
      break; /* end 'bl' */
    }
    break; /* end 'b' */
  case 'c':
    if (name[1] == 'h') {
      if (strcmp (name, "character") == 0) {
	fo_node = fo_character_new ();
	ok = TRUE;
      }
    } else if (name[1] == 'o') {
      if (strcmp (name, "color-profile") == 0) {
	fo_node = fo_color_profile_new ();
	ok = TRUE;
      } else if (strcmp (name, "conditional-page-master-reference") == 0) {
	fo_node = fo_conditional_page_master_reference_new ();
	ok = TRUE;
      }
    }
    break; /* end 'c' */
  case 'd':
    if (strcmp (name, "declarations") == 0) {
      fo_node = fo_declarations_new ();
      ok = TRUE;
    }
    break; /* end 'd' */
  case 'e':
    if (strcmp (name, "external-graphic") == 0)
      {
	xmlChar *base_uri = xmlNodeGetBase (node->doc, node);
	fo_node = fo_external_graphic_new_with_base_uri ((const gchar *) base_uri);
	ok = TRUE;
      }
    break; /* end 'e' */
  case 'f':
    if ((name[1] == 'l') && (name[2] == 'o')) {
      if (strcmp (name, "flow") == 0) {
	fo_node = fo_flow_new ();
	fo_node->flow = g_object_ref (fo_node);
	ok = TRUE;
      } else if (strcmp (name, "float") == 0) {
	fo_node = fo_float_new ();
	ok = TRUE;
      }
    } else if (name[1] == 'o') {
      if (strncmp (name, "footnote", 8) == 0) {
	if (name[8] == '\0') {
	  fo_node = fo_footnote_new ();
	  ok = TRUE;
	} else if (strcmp (&name[8], "-body") == 0) {
	  fo_node = fo_footnote_body_new ();
	  ok = TRUE;
	}
      }
    }
    break; /* end 'f' */
  case 'i':
    if (name[1] == 'n') {
      if (strcmp (name, "initial-property-set") == 0) {
	fo_node = fo_initial_property_set_new ();
	ok = TRUE;
      } else if (strncmp (name, "inline", 6) == 0) {
	if (name[6] == '\0') {
	  fo_node = fo_inline_new ();
	  ok = TRUE;
	} else if (strcmp (&name[6], "-container") == 0) {
	  fo_node = fo_inline_container_new ();
	  ok = TRUE;
	}
      } else if (strcmp (name, "instream-foreign-object") == 0) {
	fo_node = fo_instream_foreign_object_new ();
	ok = TRUE;
      }
    }
    break; /* end 'i' */
  case 'l':
    switch (name[1]) {
    case 'a':
      if (strcmp (name, "layout-master-set") == 0) {
	fo_node = fo_layout_master_set_new ();
	ok = TRUE;
      }
      break; /* end 'la' */
    case 'e':
      if (strcmp (name, "leader") == 0) {
	fo_node = fo_leader_new ();
	ok = TRUE;
      }
      break; /* end 'le' */
    case 'i':
      if (strncmp (name, "list-", 5) == 0) {
	if (strcmp (&name[5], "block") == 0) {
	  fo_node = fo_list_block_new ();
	  ok = TRUE;
	} else if (strcmp (&name[5], "item") == 0) {
	  fo_node = fo_list_item_new ();
	  ok = TRUE;
	} else if (strcmp (&name[5], "item-body") == 0) {
	  fo_node = fo_list_item_body_new ();
	  ok = TRUE;
	} else if (strcmp (&name[5], "item-label") == 0) {
	  fo_node = fo_list_item_label_new ();
	  ok = TRUE;
	}
      }
      break; /* end 'li' */
    }
    break; /* end 'l' */
  case 'm':
    if (name[1] == 'a') {
      if (strcmp (name, "marker") == 0) {
	fo_node = fo_marker_new ();
	ok = TRUE;
      }
    } else if (strncmp (name, "multi-", 6) == 0) {
      if (strcmp (&name[6], "case") == 0) {
	fo_node = fo_multi_case_new ();
	ok = TRUE;
      } else if (strcmp (&name[6], "properties") == 0) {
	fo_node = fo_multi_properties_new ();
	ok = TRUE;
      } else if (strcmp (&name[6], "property-set") == 0) {
	fo_node = fo_multi_property_set_new ();
	ok = TRUE;
      } else if (strcmp (&name[6], "switch") == 0) {
	fo_node = fo_multi_switch_new ();
	ok = TRUE;
      } else if (strcmp (&name[6], "toggle") == 0) {
	fo_node = fo_multi_toggle_new ();
	ok = TRUE;
      }
    }
    break; /* end 'm' */
  case 'p':
    if (strncmp (name, "page-", 5) == 0) {
      if (strncmp (&name[5], "number", 6) == 0) {
	if (name[11] == '\0') {
	  fo_node = fo_page_number_new ();
	  ok = TRUE;
	} else if (strcmp (&name[11], "-citation") == 0) {
	  fo_node = fo_page_number_citation_new ();
	  ok = TRUE;
	}
      } else if (strncmp (&name[5], "sequence", 8) == 0) {
	if (name[13] == '\0') {
	  fo_node = fo_page_sequence_new ();
	  ok = TRUE;
	} else if (strcmp (&name[13], "-master") == 0) {
	  fo_node = fo_page_sequence_master_new ();
	  ok = TRUE;
	}
      }
    }
    break; /* end 'p' */
  case 'r':
    switch (name[1]) {
    case 'e':
      if (strncmp (name, "region-", 7) == 0) {
	if (strcmp (&name[7], "after") == 0) {
	  fo_node = fo_region_after_new ();
	  ok = TRUE;
	} else if (strcmp (&name[7], "before") == 0) {
	  fo_node = fo_region_before_new ();
	  ok = TRUE;
	} else if (strcmp (&name[7], "body") == 0) {
	  fo_node = fo_region_body_new ();
	  ok = TRUE;
	} else if (strcmp (&name[7], "end") == 0) {
	  fo_node = fo_region_end_new ();
	  ok = TRUE;
	} else if (strcmp (&name[7], "start") == 0) {
	  fo_node = fo_region_start_new ();
	  ok = TRUE;
	}
      } else if (strncmp (name, "repeatable-page-master-", 23) == 0) {
	if (strcmp (&name[23], "alternatives") == 0) {
	  fo_node = fo_repeatable_page_master_alternatives_new ();
	  ok = TRUE;
	} else if (strcmp (&name[23], "reference") == 0) {
	  fo_node = fo_repeatable_page_master_reference_new ();
	  ok = TRUE;
	}
      } else if (strcmp (name, "retrieve-marker") == 0) {
	fo_node = fo_retrieve_marker_new ();
	ok = TRUE;
      }
      break; /* end 're' */
    case 'o':
      if (strcmp (name, "root") == 0) {
	fo_node = fo_root_new ();
	ok = TRUE;
      }
      break; /* end 'ro' */
    }
    break; /* end 'r' */
  case 's':
    if (name[1] == 'i') {
      if (strcmp (name, "simple-page-master") == 0) {
	fo_node = fo_simple_page_master_new ();
	ok = TRUE;
      } else if (strcmp (name, "single-page-master-reference") == 0) {
	fo_node = fo_single_page_master_reference_new ();
	ok = TRUE;
      }
    } else if (name[1] == 't') {
      if (strcmp (name, "static-content") == 0) {
	fo_node = fo_static_content_new ();
	ok = TRUE;
      }
    }
    break; /* end 's' */
  case 't':
    if (strncmp (name, "table", 5) == 0) {
      if (name[5] == '\0') {
	fo_node = fo_table_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-and-caption") == 0) {
	fo_node = fo_table_and_caption_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-body") == 0) {
	fo_node = fo_table_body_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-caption") == 0) {
	fo_node = fo_table_caption_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-cell") == 0) {
	fo_node = fo_table_cell_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-column") == 0) {
	fo_node = fo_table_column_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-footer") == 0) {
	fo_node = fo_table_footer_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-header") == 0) {
	fo_node = fo_table_header_new ();
	ok = TRUE;
      } else if (strcmp (&name[5], "-row") == 0) {
	fo_node = fo_table_row_new ();
	ok = TRUE;
      } /* end 'table' */
    } else if (strcmp (name, "title") == 0) {
      fo_node = fo_title_new ();
      ok = TRUE;
    }
    break; /* end 't' */
  case 'w':
    if (strcmp (name, "wrapper") == 0) {
      fo_node = fo_wrapper_new ();
      ok = TRUE;
    }
    break; /* end 'w' */
  }    

  if (!ok)
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_UNKNOWN_FO,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_UNKNOWN_FO]),
		   name);
      return NULL;
    }
  else
    {
      FoXmlNode *element = fo_xml_node_new ();
      fo_xml_node_set_xml_node (element, node);
      fo_fo_set_element (fo_node, element);
      return fo_node;
    }
}

/**
 * fo_xml_node_to_fo_subtree:
 * @node:      #xmlNodePtr for which to create a subtree.
 * @parent_fo: Parent #FoFo to which to add new subtree.
 * @error:     Indication of any error that occurred.
 * 
 * For the xmlNode tree rooted at @node, creates the corresponding
 * #FoFo tree and adds it as the last child of @parent_fo.
 *
 * Removes processing instructions and comments.  Throws error for all
 * other node types except element nodes and document nodes.
 **/
static void
fo_new_xml_to_fo_tree (xmlNodePtr node,
		       FoFo *parent_fo,
		       GError **error)
{
  FoFo *fo_node = NULL;
  FoFo *fo_text = NULL;
  GError *tmp_error = NULL;

  g_return_if_fail (node != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  switch (node->type)
    {
    case XML_ELEMENT_NODE:
      if ((node->ns != NULL) &&
	  (strcmp ((gchar *) node->ns->href,
		   XSL_FO_NAMESPACE) == 0 ))
	{
	  fo_node = fo_xml_element_node_to_fo_node (node,
						    &tmp_error);

	  if (tmp_error != NULL)
	    {
	      g_propagate_error (error, tmp_error);
	      return;
	    }

#if defined(LIBFO_DEBUG) && 0
	  g_message ("new_xml_to_fo_tree:: fo_node: %s",
		     fo_object_sprintf (FO_OBJECT (fo_node)));
#endif

	  if (fo_node)
	    {
	      fo_node_append (FO_NODE (parent_fo),
			      FO_NODE (fo_node));
	    }

	  node = node->children;

	  while (node)
	    {
	      /* Get the next node now, since current node may be PI or
		 comment that is unlinked and freed in following call to
		 fo_xml_node_to_fo_node() */
	      xmlNodePtr next_node = node->next;

	      fo_new_xml_to_fo_tree (node,
				     fo_node,
				     &tmp_error);

	      if (tmp_error != NULL)
		{
		  g_propagate_error (error, tmp_error);
		  return;
		}

	      node = next_node;
	    }
	}
      break;
    case XML_ATTRIBUTE_NODE:
      g_error (_("Unexpected node type: ATTRIBUTE"));
      break;
    case XML_TEXT_NODE:
      {
	gchar *text = (gchar *) xmlNodeGetContent (node);

	if (fo_fo_get_allow_mixed_content (parent_fo))
	  {
	    fo_text = fo_text_new ();
	    fo_node_append (FO_NODE (parent_fo),
			    FO_NODE (fo_text));
	    fo_text_set_value (fo_text, text);
	  }
	else
	  {
	    gchar *text_ptr = text;
	    gboolean whitespace_only = TRUE;

	    while (*text_ptr)
	      {
		if (!g_ascii_isspace (*text_ptr++))
		  {
		    whitespace_only = FALSE;
		    break;
		  }
	      }

	    if (!whitespace_only)
	      {
		g_error (_("Text node should contain only whitespace characters: \"%s\""), text);
	      }
	    xmlUnlinkNode (node);
	    xmlFreeNode (node);
	  }

	xmlFree (text);
      }
      break;
    case XML_CDATA_SECTION_NODE:
      g_error (_("Unexpected node type: CDATA SECTION"));
      break;
    case XML_ENTITY_REF_NODE:
      g_error (_("Unexpected node type: ENTITY REF"));
      break;
    case XML_ENTITY_NODE:
      g_error (_("Unexpected node type: ENTITY"));
      break;
    case XML_PI_NODE:
      /* Fall through */
    case XML_COMMENT_NODE:
      /* Unlink from the node tree */
      xmlUnlinkNode (node);
      /* Free the node */
      xmlFreeNode (node);
      break;
    case XML_DOCUMENT_NODE:
	  node = node->children;

	  while (node)
	    {
	      /* Get the next node now, since current node may be PI or
		 comment that is unlinked and freed in following call to
		 fo_xml_node_to_fo_node() */
	      xmlNodePtr next_node = node->next;

	      fo_new_xml_to_fo_tree (node,
				     parent_fo,
				     &tmp_error);
	      if (tmp_error != NULL)
		{
		  g_propagate_error (error, tmp_error);
		  return;
		}

	      node = next_node;
	    }
      /*
      g_error (_("Unexpected node type: DOCUMENT"));
      */
      break;
    case XML_DOCUMENT_TYPE_NODE:
      g_error (_("Unexpected node type: DOCUMENT TYPE"));
      break;
    case XML_DOCUMENT_FRAG_NODE:
      g_error (_("Unexpected node type: DOCUMENT FRAG"));
      break;
    case XML_NOTATION_NODE:
      g_error (_("Unexpected node type: NOTATION"));
      break;
    case XML_HTML_DOCUMENT_NODE:
      g_error (_("Unexpected node type: HTML DOCUMENT"));
      break;
    case XML_DTD_NODE:
      g_error (_("Unexpected node type: DTD"));
      break;
    case XML_ELEMENT_DECL:
      g_error (_("Unexpected node type: ELEMENT DECL"));
      break;
    case XML_ATTRIBUTE_DECL:
      g_error (_("Unexpected node type: ATTRIBUTE DECL"));
      break;
    case XML_ENTITY_DECL:
      g_error (_("Unexpected node type: ENTITY DECL"));
      break;
    case XML_NAMESPACE_DECL:
      g_error (_("Unexpected node type: NAMESPACE DECL"));
      break;
    case XML_XINCLUDE_START:
      g_error (_("Unexpected node type: XINCLUDE START"));
      break;
    case XML_XINCLUDE_END:
      g_error (_("Unexpected node type: XINCLUDE END"));
      break;
    case XML_DOCB_DOCUMENT_NODE:
      g_error (_("Unexpected node type: DOCB DOCUMENT"));
      break;
    }
}

/**
 * xml_doc_to_fo_and_area_trees:
 * @res:                  Result tree.
 * @fo_doc:               #FoDoc to which to write output.
 * @fo_tree:              Pointer to generated FO tree.
 * @area_tree:            Pointer to generated area tree.
 * @continue_after_error: Whether to continue after a formatting error.
 * @debug_level:          What debugging output to generate.
 * @error:                Indication of any error that occurred.
 * 
 * Generates FO and area trees from @res result tree.
 **/
static void
xml_doc_to_fo_and_area_trees (FoXmlDoc     *result_tree,
			      FoDoc        *fo_doc,
			      FoFo        **fo_tree,
			      FoArea      **area_tree,
			      gboolean      continue_after_error,
			      FoDebugFlag   debug_level,
			      FoWarningFlag warning_mode,
			      GError      **error)
{
  xmlDocPtr res = fo_xml_doc_get_xml_doc (result_tree);
  FoFo *new_fo_tree = fo_tree_new ();
  FoArea *new_area_tree;
  FoContext *new_fo_context;
  GHashTable *prop_eval_hash = NULL;
  FoArea *new_area = NULL;
  GError *tmp_error = NULL;

  /* Check the xmlDocPtr isn't null */
  g_return_if_fail (res != NULL);
  /* Check the xmlDocPtr has a document element */
  g_return_if_fail (res->children != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  prop_eval_hash = fo_property_eval_init_hash (prop_eval_hash);
  new_fo_context = fo_context_new ();
  fo_context_initialize (new_fo_context);
  new_area_tree = fo_area_tree_new ();
  new_fo_tree->areas = g_list_append (new_fo_tree->areas, new_area_tree);
  fo_fo_set_context (new_fo_tree, new_fo_context);
  new_fo_tree->tree = new_fo_tree;

  /* Create the FO tree from the result document. */
  fo_new_xml_to_fo_tree ((xmlNodePtr) res,
			 new_fo_tree,
			 &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (/*FO_OBJECT (new_fo_tree),*/
					error,
					tmp_error);
      return;
    }

  /* Check that the structure of the FO tree conforms to the spec. */
  /* Do not traverse the leaf nodes. */
  fo_node_traverse (FO_NODE (new_fo_tree),
		    G_POST_ORDER,
		    G_TRAVERSE_NON_LEAFS,
		    -1,
		    (FoNodeTraverseFunc) fo_fo_validate_content,
		    NULL);
#if defined(LIBFO_DEBUG) && 0
  fo_object_debug_dump (new_fo_tree, 0);
#endif
  /* Recursively both resolve property values and generate areas
     starting at the top of the FO tree. */
  fo_fo_children_properties_resolve (new_fo_tree,
				     new_area_tree,
				     &new_area,
				     prop_eval_hash,
				     fo_doc,
				     continue_after_error,
				     debug_level,
				     warning_mode,
				     &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (/*FO_OBJECT (new_fo_tree),*/
					error,
					tmp_error);
      return;
    }

#if defined(LIBFO_DEBUG) && 0
  fo_object_debug_dump (new_fo_tree, 0);
  fo_object_debug_dump (new_area_tree, 0);
#endif
  *fo_tree = new_fo_tree;
  *area_tree = new_area_tree;

  g_hash_table_destroy (prop_eval_hash);
}

/**
 * fo_xsl_formatter_format:
 * @fo_xsl_formatter: #FoXslFormatter.
 * @libfo_context:    #FoLibfoContext.
 * @error:            #GError.
 * 
 * Formats @fo_xsl_formatter.
 * 
 * Outputs debug info according to debug mode set in @libfo_context.
 *
 * Return value: Success indication.
 **/
gboolean
fo_xsl_formatter_format (FoXslFormatter *fo_xsl_formatter,
			 FoLibfoContext *libfo_context,
			 GError        **error)
{
  FoDebugFlag debug = FO_DEBUG_NONE;
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo_xsl_formatter != NULL, FALSE);
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context), FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

  debug = fo_libfo_context_get_debug_mode (libfo_context);

  if (fo_xsl_formatter->result_tree == NULL)
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_RESULT_TREE,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NO_RESULT_TREE]));
      return FALSE;
    }

  xmlNodePtr root_element =
    xmlDocGetRootElement (fo_xml_doc_get_xml_doc (fo_xsl_formatter->result_tree));

  if ((strcmp ((gchar *) root_element->name, "root") != 0) ||
      (root_element->ns == NULL) ||
      (strcmp ((gchar *) root_element->ns->href, XSL_FO_NAMESPACE) != 0))
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_RESULT_TREE_NOT_FO,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_RESULT_TREE_NOT_FO]),
		   root_element->ns == NULL ? NULL : root_element->ns->href,
		   root_element->name);
      return FALSE;
    }

  if (fo_xsl_formatter->fo_doc == NULL)
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_FO_DOC,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NO_FO_DOC]));
      return FALSE;
    }

  if (!FO_IS_DOC (fo_xsl_formatter->fo_doc))
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_FO_DOC,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NOT_FO_DOC]));
      return FALSE;
    }

  if (fo_xsl_formatter->fo_tree != NULL &&
      fo_xsl_formatter->area_tree != NULL)
    {
      return TRUE;
    }
  else
    {
      xml_doc_to_fo_and_area_trees (fo_xsl_formatter->result_tree,
				    fo_xsl_formatter->fo_doc,
				    &(fo_xsl_formatter->fo_tree),
				    &(fo_xsl_formatter->area_tree),
				    fo_libfo_context_get_continue_after_error (libfo_context),
				    fo_libfo_context_get_debug_mode (libfo_context),
				    fo_libfo_context_get_warning_mode (libfo_context),
				    &tmp_error);

      if (debug & FO_DEBUG_FO)
	{
	  fo_object_debug_dump (fo_xsl_formatter->fo_tree,
				0);
	}

      if (debug & FO_DEBUG_AREA)
	{
	  fo_object_debug_dump (fo_xsl_formatter->area_tree,
				0);
	}

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return FALSE;
	}
      else
	{
	  return TRUE;
	}
    }
}

/**
 * fo_xsl_formatter_draw:
 * @fo_xsl_formatter: #FoXslFormatter.
 * @libfo_context:    #FoLibfoContext.
 * @error:            #GError.
 * 
 * Formats @fo_xsl_formatter.
 * 
 * Return value: Success indication.
 **/
gboolean
fo_xsl_formatter_draw (FoXslFormatter *fo_xsl_formatter,
		       FoLibfoContext *libfo_context,
		       GError        **error)
{
  FoAreaToPDFData fo_area_to_pdf_data = {NULL, 0};

  g_return_val_if_fail (fo_xsl_formatter != NULL, FALSE);
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context), FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

  if (fo_xsl_formatter->result_tree == NULL)
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_RESULT_TREE,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NO_RESULT_TREE]));
      return FALSE;
    }

  if (fo_xsl_formatter->fo_doc == NULL)
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_FO_DOC,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NO_FO_DOC]));
      return FALSE;
    }

  if (!FO_IS_DOC (fo_xsl_formatter->fo_doc))
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_FO_DOC,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NOT_FO_DOC]));
      return FALSE;
    }

  if (fo_xsl_formatter->area_tree == NULL)
    {
      g_set_error (error,
		   FO_XSL_FORMATTER_ERROR,
		   FO_XSL_FORMATTER_ERROR_NO_AREA_TREE,
		   _(fo_xsl_formatter_error_messages[FO_XSL_FORMATTER_ERROR_NO_AREA_TREE]));
      return FALSE;
    }


  fo_area_to_pdf_data.fo_doc = fo_xsl_formatter->fo_doc;
  fo_area_to_pdf_data.debug_level =
    fo_libfo_context_get_debug_mode (libfo_context);

  fo_area_tree_to_pdf (fo_xsl_formatter->area_tree,
		       &fo_area_to_pdf_data);

  return TRUE;
}

/**
 * fo_xsl_formatter_get_result_tree:
 * @fo_xsl_formatter: #FoXslFormatter
 * 
 * Get the filename in @fo_xsl_formatter.
 * 
 * Return value: Filename of file parsed to make @fo_xsl_formatter.
 **/
FoXmlDoc *
fo_xsl_formatter_get_result_tree (FoXslFormatter *fo_xsl_formatter)
{
  g_return_val_if_fail (fo_xsl_formatter != NULL, NULL);

  return fo_xsl_formatter->result_tree;
}

/**
 * fo_xsl_formatter_set_result_tree:
 * @fo_xsl_formatter: #FoXslFormatter
 * @result_tree:      Result of previous parse or transformation.
 * 
 * Set the result tree in @fo_xsl_formatter.  Voids the current FO and
 * area trees.
 **/
void
fo_xsl_formatter_set_result_tree (FoXslFormatter *fo_xsl_formatter,
				  FoXmlDoc       *result_tree)
{
  g_return_if_fail (fo_xsl_formatter != NULL);

  if (fo_xsl_formatter->result_tree != NULL)
    g_free (fo_xsl_formatter->result_tree);

  if (fo_xsl_formatter->fo_tree != NULL)
    {
      g_object_unref (fo_xsl_formatter->fo_tree);
      fo_xsl_formatter->fo_tree = NULL;
    }

  if (fo_xsl_formatter->area_tree != NULL)
    {
      g_object_unref (fo_xsl_formatter->area_tree);
      fo_xsl_formatter->area_tree = NULL;
    }

  fo_xsl_formatter->result_tree = fo_xml_doc_ref (result_tree);
}

/**
 * fo_xsl_formatter_set_fo_doc:
 * @fo_xsl_formatter: #FoXslFormatter
 * @fo_doc:           #FoDoc for use as output of formatter.
 * 
 * Set the #FoDoc in @fo_xsl_formatter.  Voids the current FO and area
 * trees.
 **/
void
fo_xsl_formatter_set_fo_doc (FoXslFormatter *fo_xsl_formatter,
			     FoDoc          *fo_doc)
{
  g_return_if_fail (fo_xsl_formatter != NULL);
  g_return_if_fail (fo_doc != NULL);

  if (fo_xsl_formatter->fo_doc != NULL)
    g_object_unref (fo_xsl_formatter->fo_doc);

  if (fo_xsl_formatter->fo_tree != NULL)
    {
      g_object_unref (fo_xsl_formatter->fo_tree);
      fo_xsl_formatter->fo_tree = NULL;
    }

  if (fo_xsl_formatter->area_tree != NULL)
    {
      g_object_unref (fo_xsl_formatter->area_tree);
      fo_xsl_formatter->area_tree = NULL;
    }

  fo_xsl_formatter->fo_doc = g_object_ref (fo_doc);
}

/**
 * fo_xsl_formatter_get_fo_tree:
 * @fo_xsl_formatter: #FoXslFormatter
 * 
 * Get the #FoFo tree created by @fo_xsl_formatter.
 * 
 * Return value: #FoFo tree created by @fo_xsl_formatter.
 **/
GObject *
fo_xsl_formatter_get_fo_tree (FoXslFormatter *fo_xsl_formatter)
{
  g_return_val_if_fail (fo_xsl_formatter != NULL, NULL);

  return G_OBJECT (fo_xsl_formatter->fo_tree);
}

/**
 * fo_xsl_formatter_get_area_tree:
 * @fo_xsl_formatter: #FoXslFormatter
 * 
 * Get the #FoArea tree created by @fo_xsl_formatter.
 * 
 * Return value: #FoArea tree created by @fo_xsl_formatter.
 **/
GObject *
fo_xsl_formatter_get_area_tree (FoXslFormatter *fo_xsl_formatter)
{
  g_return_val_if_fail (fo_xsl_formatter != NULL, NULL);

  return G_OBJECT (fo_xsl_formatter->area_tree);
}
