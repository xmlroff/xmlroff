/* Fo
 * fo-table.c: 'table' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "datatype/fo-pcw.h"
#include "expr/fo-expr-eval.h"
#include "expr/fo-expr-func-private.h"
#include "fo/fo-block-fo-private.h"
#include "fo/fo-cbpbp-fo-private.h"
#include "fo/fo-table-border-fo-private.h"
#include "fo/fo-table-private.h"
#include "fo-context-util.h"
#include "fo/fo-table-area.h"
#include "fo/fo-table-column.h"
#include "fo/fo-table-header.h"
#include "fo/fo-table-footer.h"
#include "fo/fo-table-body.h"
#include "fo/fo-table-row.h"
#include "fo/fo-table-cell.h"
#include "property/fo-property-column-width.h"
#include "property/fo-property-border.h"
#include "property/fo-property-margin.h"
#include "property/fo-property-padding.h"
#include "property/fo-property-background-color.h"
#include "property/fo-property-background-image.h"
#include "property/fo-property-block-progression-dimension.h"
#include "property/fo-property-border-after-color.h"
#include "property/fo-property-border-after-precedence.h"
#include "property/fo-property-border-after-style.h"
#include "property/fo-property-border-after-width.h"
#include "property/fo-property-border-before-color.h"
#include "property/fo-property-border-before-precedence.h"
#include "property/fo-property-border-before-style.h"
#include "property/fo-property-border-before-width.h"
#include "property/fo-property-border-bottom-color.h"
#include "property/fo-property-border-bottom-style.h"
#include "property/fo-property-border-bottom-width.h"
#include "property/fo-property-border-collapse.h"
#include "property/fo-property-border-end-color.h"
#include "property/fo-property-border-end-precedence.h"
#include "property/fo-property-border-end-style.h"
#include "property/fo-property-border-end-width.h"
#include "property/fo-property-border-left-color.h"
#include "property/fo-property-border-left-style.h"
#include "property/fo-property-border-left-width.h"
#include "property/fo-property-border-right-color.h"
#include "property/fo-property-border-right-style.h"
#include "property/fo-property-border-right-width.h"
#include "property/fo-property-border-separation.h"
#include "property/fo-property-border-start-color.h"
#include "property/fo-property-border-start-precedence.h"
#include "property/fo-property-border-start-style.h"
#include "property/fo-property-border-start-width.h"
#include "property/fo-property-border-top-color.h"
#include "property/fo-property-border-top-style.h"
#include "property/fo-property-border-top-width.h"
#include "property/fo-property-break-after.h"
#include "property/fo-property-break-before.h"
#include "property/fo-property-end-indent.h"
#include "property/fo-property-height.h"
#include "property/fo-property-id.h"
#include "property/fo-property-inline-progression-dimension.h"
#include "property/fo-property-keep-together.h"
#include "property/fo-property-keep-together-within-column.h"
#include "property/fo-property-keep-together-within-line.h"
#include "property/fo-property-keep-together-within-page.h"
#include "property/fo-property-keep-with-next.h"
#include "property/fo-property-keep-with-next-within-column.h"
#include "property/fo-property-keep-with-next-within-line.h"
#include "property/fo-property-keep-with-next-within-page.h"
#include "property/fo-property-keep-with-previous.h"
#include "property/fo-property-keep-with-previous-within-column.h"
#include "property/fo-property-keep-with-previous-within-line.h"
#include "property/fo-property-keep-with-previous-within-page.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-bottom.h"
#include "property/fo-property-padding-end.h"
#include "property/fo-property-padding-left.h"
#include "property/fo-property-padding-right.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-top.h"
#include "property/fo-property-role.h"
#include "property/fo-property-source-document.h"
#include "property/fo-property-space-after.h"
#include "property/fo-property-space-before.h"
#include "property/fo-property-start-indent.h"
#include "property/fo-property-table-layout.h"
#include "property/fo-property-width.h"
#include "property/fo-property-writing-mode.h"

#define fo_table_make_column_hash_key(column_number,number_columns_spanned) \
           (((column_number) << 16) + (number_columns_spanned))

GType
fo_enum_table_layout_method_get_type (void)
{
  static GType etype = 0;
  if (etype == 0)
    {
      static const GEnumValue values[] = {
        { FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN, "FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN", "unknown" },
        { FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC, "FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC", "automatic" },
        { FO_ENUM_TABLE_LAYOUT_METHOD_FIXED, "FO_ENUM_TABLE_LAYOUT_METHOD_FIXED", "fixed" },
        { 0, NULL, NULL }
      };
      etype = g_enum_register_static ("FoEnumTableLayoutMethod", values);
    }
  return etype;
}

const char *fo_table_error_messages[] = {
  N_("Failed"),
  N_("Warning"),
  N_("Table layout method is unknown."),
  N_("Table layout method is fixed but no 'fo:table-column's specified."),
  N_("No 'fo:table-column' for column number '%d'."),
  N_("'column-width' expression is not a length: '%s'"),
  N_("No area associated with 'fo:table'."),
  N_("table-layout=\"fixed\" but automatic table layout is specified since i-p-d=\"auto\"."),
  N_("Spanning table cells fill entire row."),
  N_("Automatic table layout is not supported.  Falling back to fixed table layout."),
  N_("Unsupported inline-progression-dimension value: $d.")
};

enum {
  PROP_0,
  PROP_LAYOUT_METHOD,
  PROP_MAX_COLUMN_NUMBER,
  PROP_BACKGROUND_COLOR,
  PROP_BACKGROUND_IMAGE,
  PROP_BLOCK_PROGRESSION_DIMENSION,
  PROP_BORDER_AFTER_COLOR,
  PROP_BORDER_AFTER_PRECEDENCE,
  PROP_BORDER_AFTER_STYLE,
  PROP_BORDER_AFTER_WIDTH,
  PROP_BORDER_BEFORE_COLOR,
  PROP_BORDER_BEFORE_PRECEDENCE,
  PROP_BORDER_BEFORE_STYLE,
  PROP_BORDER_BEFORE_WIDTH,
  PROP_BORDER_BOTTOM_COLOR,
  PROP_BORDER_BOTTOM_STYLE,
  PROP_BORDER_BOTTOM_WIDTH,
  PROP_BORDER_COLLAPSE,
  PROP_BORDER_END_COLOR,
  PROP_BORDER_END_PRECEDENCE,
  PROP_BORDER_END_STYLE,
  PROP_BORDER_END_WIDTH,
  PROP_BORDER_LEFT_COLOR,
  PROP_BORDER_LEFT_STYLE,
  PROP_BORDER_LEFT_WIDTH,
  PROP_BORDER_RIGHT_COLOR,
  PROP_BORDER_RIGHT_STYLE,
  PROP_BORDER_RIGHT_WIDTH,
  PROP_BORDER_SEPARATION,
  PROP_BORDER_START_COLOR,
  PROP_BORDER_START_PRECEDENCE,
  PROP_BORDER_START_STYLE,
  PROP_BORDER_START_WIDTH,
  PROP_BORDER_TOP_COLOR,
  PROP_BORDER_TOP_STYLE,
  PROP_BORDER_TOP_WIDTH,
  PROP_BREAK_AFTER,
  PROP_BREAK_BEFORE,
  PROP_END_INDENT,
  PROP_HEIGHT,
  PROP_ID,
  PROP_INLINE_PROGRESSION_DIMENSION,
  PROP_KEEP_TOGETHER,
  PROP_KEEP_TOGETHER_WITHIN_COLUMN,
  PROP_KEEP_TOGETHER_WITHIN_LINE,
  PROP_KEEP_TOGETHER_WITHIN_PAGE,
  PROP_KEEP_WITH_NEXT,
  PROP_KEEP_WITH_NEXT_WITHIN_COLUMN,
  PROP_KEEP_WITH_NEXT_WITHIN_LINE,
  PROP_KEEP_WITH_NEXT_WITHIN_PAGE,
  PROP_KEEP_WITH_PREVIOUS,
  PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN,
  PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE,
  PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE,
  PROP_MARGIN_BOTTOM,
  PROP_MARGIN_LEFT,
  PROP_MARGIN_RIGHT,
  PROP_MARGIN_TOP,
  PROP_PADDING_AFTER,
  PROP_PADDING_BEFORE,
  PROP_PADDING_BOTTOM,
  PROP_PADDING_END,
  PROP_PADDING_LEFT,
  PROP_PADDING_RIGHT,
  PROP_PADDING_START,
  PROP_PADDING_TOP,
  PROP_ROLE,
  PROP_SOURCE_DOCUMENT,
  PROP_SPACE_AFTER,
  PROP_SPACE_BEFORE,
  PROP_START_INDENT,
  PROP_TABLE_LAYOUT,
  PROP_WIDTH,
  PROP_WRITING_MODE
};

static void fo_table_init                 (FoTable        *fo_table);
static void fo_table_base_class_init      (FoTableClass   *klass);
static void fo_table_base_class_finalize  (FoTableClass   *klass);
static void fo_table_class_init           (FoTableClass   *klass);
static void fo_table_block_fo_init        (FoBlockFoIface *iface);
static void fo_table_cbpbp_fo_init        (FoCBPBPFoIface *iface);
static void fo_table_table_border_fo_init (FoTableBorderFoIface *iface);
static void fo_table_get_property (GObject      *object,
                                   guint         prop_id,
                                   GValue       *value,
                                   GParamSpec   *pspec);
static void fo_table_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec);
static void fo_table_finalize    (GObject           *object);
static gboolean fo_table_validate_content (FoFo    *fo,
                                           GError **error);
static void fo_table_validate (FoFo      *fo,
                               FoContext *current_context,
                               FoContext *parent_context,
                               GError   **error);
static void fo_table_update_from_context (FoFo      *fo,
                                          FoContext *context);
static void fo_table_debug_dump_properties (FoFo *fo,
                                            gint  depth);
static void fo_table_resolve_layout_method (FoFo *fo);
static void fo_table_free_hash_key (gpointer key,
				    gpointer value,
				    gpointer user_data);
static void fo_table_resolve_proportional_widths (FoFo    *fo,
						  GError **error);
static void fo_table_resolve_column_offsets (FoFo    *fo,
					     GError **error);

static gpointer parent_class;
static FoExprEnvList *fixed_env_list;
static FoExprEnvList *proportional_env_list;
static FoExprEnvList *proportional_fixed_env_list;

/**
 * fo_table_get_type:
 * 
 * Register the #FoTable object type.
 * 
 * Return value: #GType value of the #FoTable object type.
 **/
GType
fo_table_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoTableClass),
	  (GBaseInitFunc) fo_table_base_class_init,
	  (GBaseFinalizeFunc) fo_table_base_class_finalize,
	  (GClassInitFunc) fo_table_class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoTable),
	  0,              /* n_preallocs */
	  (GInstanceInitFunc) fo_table_init,
	  NULL		/* value_table */
	};

      static const GInterfaceInfo fo_block_fo_info =
	{
	  (GInterfaceInitFunc) fo_table_block_fo_init,	 /* interface_init */
	  NULL,
	  NULL
	};

      static const GInterfaceInfo fo_cbpbp_fo_info =
	{
	  (GInterfaceInitFunc) fo_table_cbpbp_fo_init,	 /* interface_init */
	  NULL,
	  NULL
	};

      static const GInterfaceInfo fo_table_border_fo_info =
      {
	(GInterfaceInitFunc) fo_table_table_border_fo_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoTable",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_BLOCK_FO,
                                   &fo_block_fo_info);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_CBPBP_FO,
                                   &fo_cbpbp_fo_info);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_TABLE_BORDER_FO,
                                   &fo_table_border_fo_info);
    }

  return object_type;
}

/**
 * fo_table_init:
 * @fo_table: #FoTable object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoTable.
 **/
void
fo_table_init (FoTable *fo_table)
{
  fo_table->layout_method = FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN;
  fo_table->column_hash =
    g_hash_table_new (g_int_hash, g_int_equal);
}

/**
 * fo_table_base_class_init:
 * @klass: #FoTableClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoTableClass.
 **/
void
fo_table_base_class_init (FoTableClass *klass G_GNUC_UNUSED)
{
  FoExprEnv *proportional_env;
  FoExprEnv *proportional_fixed_env;

  fixed_env_list = fo_expr_env_list_new ();

  /* Only table-related properties can use
     proportional-column-width(). */
  proportional_env = fo_expr_env_new ();
  fo_expr_env_register_func (proportional_env,
			     "proportional-column-width",
			     fo_expr_func_pcw_prop);
  proportional_env_list = fo_expr_env_list_prepend (fo_expr_env_list_new (),
						    proportional_env);

  proportional_fixed_env = fo_expr_env_new ();
  fo_expr_env_register_func (proportional_fixed_env,
			     "proportional-column-width",
			     fo_expr_func_pcw_prop_fixed);
  proportional_fixed_env_list =
    fo_expr_env_list_prepend (fo_expr_env_list_new (),
			      proportional_fixed_env);
}

/**
 * fo_table_base_class_finalize:
 * @klass: #FoTableClass base class object to initialise.
 * 
 * Implements #GBaseFinalizeFunc for #FoTableClass.
 **/
void
fo_table_base_class_finalize (FoTableClass *klass G_GNUC_UNUSED)
{
  /* FIXME: Free the environments here. */
}

/**
 * fo_table_class_init:
 * @klass: #FoTableClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoTableClass.
 **/
void
fo_table_class_init (FoTableClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_table_finalize;

  object_class->get_property = fo_table_get_property;
  object_class->set_property = fo_table_set_property;

  fofo_class->validate_content =
    fo_table_validate_content;
  fofo_class->validate2 =
    fo_table_validate;
  fofo_class->update_from_context = fo_table_update_from_context;
  fofo_class->debug_dump_properties = fo_table_debug_dump_properties;
  fofo_class->generate_reference_area = TRUE;
  fofo_class->area_new2 = fo_table_area_new;

  g_object_class_install_property
    (object_class,
     PROP_LAYOUT_METHOD,
     g_param_spec_enum ("layout-method",
			_("Table Layout Method"),
			_("Method used when laying out the table"),
			FO_TYPE_ENUM_TABLE_LAYOUT_METHOD,
			FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN,
			G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MAX_COLUMN_NUMBER,
     g_param_spec_int ("max-column-number",
		       _("Maximum Column Number"),
		       _("Largest column number registered for table"),
		       0,
		       G_MAXINT,
		       0,
		       G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BACKGROUND_COLOR,
     g_param_spec_object ("background-color",
			  _("Background Color"),
			  _("Background Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BACKGROUND_IMAGE,
     g_param_spec_object ("background-image",
			  _("Background Image"),
			  _("Background Image property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BLOCK_PROGRESSION_DIMENSION,
     g_param_spec_object ("block-progression-dimension",
			  _("Block Progression Dimension"),
			  _("Block Progression Dimension property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_COLOR,
     g_param_spec_object ("border-after-color",
			  _("Border After Color"),
			  _("Border After Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_PRECEDENCE,
     g_param_spec_object ("border-after-precedence",
			  _("Border After Precedence"),
			  _("Border After Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_STYLE,
     g_param_spec_object ("border-after-style",
			  _("Border After Style"),
			  _("Border After Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_WIDTH,
     g_param_spec_object ("border-after-width",
			  _("Border After Width"),
			  _("Border After Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_COLOR,
     g_param_spec_object ("border-before-color",
			  _("Border Before Color"),
			  _("Border Before Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_PRECEDENCE,
     g_param_spec_object ("border-before-precedence",
			  _("Border Before Precedence"),
			  _("Border Before Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_STYLE,
     g_param_spec_object ("border-before-style",
			  _("Border Before Style"),
			  _("Border Before Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_WIDTH,
     g_param_spec_object ("border-before-width",
			  _("Border Before Width"),
			  _("Border Before Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_COLOR,
     g_param_spec_object ("border-bottom-color",
			  _("Border Bottom Color"),
			  _("Border Bottom Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_STYLE,
     g_param_spec_object ("border-bottom-style",
			  _("Border Bottom Style"),
			  _("Border Bottom Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_WIDTH,
     g_param_spec_object ("border-bottom-width",
			  _("Border Bottom Width"),
			  _("Border Bottom Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_COLLAPSE,
     g_param_spec_object ("border-collapse",
			  _("Border Collapse"),
			  _("Border Collapse property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_COLOR,
     g_param_spec_object ("border-end-color",
			  _("Border End Color"),
			  _("Border End Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_PRECEDENCE,
     g_param_spec_object ("border-end-precedence",
			  _("Border End Precedence"),
			  _("Border End Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_STYLE,
     g_param_spec_object ("border-end-style",
			  _("Border End Style"),
			  _("Border End Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_WIDTH,
     g_param_spec_object ("border-end-width",
			  _("Border End Width"),
			  _("Border End Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_COLOR,
     g_param_spec_object ("border-left-color",
			  _("Border Left Color"),
			  _("Border Left Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_STYLE,
     g_param_spec_object ("border-left-style",
			  _("Border Left Style"),
			  _("Border Left Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_WIDTH,
     g_param_spec_object ("border-left-width",
			  _("Border Left Width"),
			  _("Border Left Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_COLOR,
     g_param_spec_object ("border-right-color",
			  _("Border Right Color"),
			  _("Border Right Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_STYLE,
     g_param_spec_object ("border-right-style",
			  _("Border Right Style"),
			  _("Border Right Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_WIDTH,
     g_param_spec_object ("border-right-width",
			  _("Border Right Width"),
			  _("Border Right Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_SEPARATION,
     g_param_spec_object ("border-separation",
			  _("Border Separation"),
			  _("Border Separation property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_COLOR,
     g_param_spec_object ("border-start-color",
			  _("Border Start Color"),
			  _("Border Start Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_PRECEDENCE,
     g_param_spec_object ("border-start-precedence",
			  _("Border Start Precedence"),
			  _("Border Start Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_STYLE,
     g_param_spec_object ("border-start-style",
			  _("Border Start Style"),
			  _("Border Start Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_WIDTH,
     g_param_spec_object ("border-start-width",
			  _("Border Start Width"),
			  _("Border Start Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_COLOR,
     g_param_spec_object ("border-top-color",
			  _("Border Top Color"),
			  _("Border Top Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_STYLE,
     g_param_spec_object ("border-top-style",
			  _("Border Top Style"),
			  _("Border Top Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_WIDTH,
     g_param_spec_object ("border-top-width",
			  _("Border Top Width"),
			  _("Border Top Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BREAK_AFTER,
     g_param_spec_object ("break-after",
			  _("Break After"),
			  _("Break After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BREAK_BEFORE,
     g_param_spec_object ("break-before",
			  _("Break Before"),
			  _("Break Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_END_INDENT,
     g_param_spec_object ("end-indent",
			  _("End Indent"),
			  _("End Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_HEIGHT,
     g_param_spec_object ("height",
			  _("Height"),
			  _("Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_INLINE_PROGRESSION_DIMENSION,
     g_param_spec_object ("inline-progression-dimension",
			  _("Inline Progression Dimension"),
			  _("Inline Progression Dimension property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER,
     g_param_spec_object ("keep-together",
			  _("Keep Together"),
			  _("Keep Together property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_COLUMN,
     g_param_spec_object ("keep-together-within-column",
			  _("Keep Together Within Column"),
			  _("Keep Together Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_LINE,
     g_param_spec_object ("keep-together-within-line",
			  _("Keep Together Within Line"),
			  _("Keep Together Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_PAGE,
     g_param_spec_object ("keep-together-within-page",
			  _("Keep Together Within Page"),
			  _("Keep Together Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT,
     g_param_spec_object ("keep-with-next",
			  _("Keep With Next"),
			  _("Keep With Next property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT_WITHIN_COLUMN,
     g_param_spec_object ("keep-with-next-within-column",
			  _("Keep With Next Within Column"),
			  _("Keep With Next Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT_WITHIN_LINE,
     g_param_spec_object ("keep-with-next-within-line",
			  _("Keep With Next Within Line"),
			  _("Keep With Next Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT_WITHIN_PAGE,
     g_param_spec_object ("keep-with-next-within-page",
			  _("Keep With Next Within Page"),
			  _("Keep With Next Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS,
     g_param_spec_object ("keep-with-previous",
			  _("Keep With Previous"),
			  _("Keep With Previous property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN,
     g_param_spec_object ("keep-with-previous-within-column",
			  _("Keep With Previous Within Column"),
			  _("Keep With Previous Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE,
     g_param_spec_object ("keep-with-previous-within-line",
			  _("Keep With Previous Within Line"),
			  _("Keep With Previous Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE,
     g_param_spec_object ("keep-with-previous-within-page",
			  _("Keep With Previous Within Page"),
			  _("Keep With Previous Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_BOTTOM,
     g_param_spec_object ("margin-bottom",
			  _("Margin Bottom"),
			  _("Margin Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_LEFT,
     g_param_spec_object ("margin-left",
			  _("Margin Left"),
			  _("Margin Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_RIGHT,
     g_param_spec_object ("margin-right",
			  _("Margin Right"),
			  _("Margin Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_TOP,
     g_param_spec_object ("margin-top",
			  _("Margin Top"),
			  _("Margin Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_AFTER,
     g_param_spec_object ("padding-after",
			  _("Padding After"),
			  _("Padding After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BEFORE,
     g_param_spec_object ("padding-before",
			  _("Padding Before"),
			  _("Padding Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BOTTOM,
     g_param_spec_object ("padding-bottom",
			  _("Padding Bottom"),
			  _("Padding Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_END,
     g_param_spec_object ("padding-end",
			  _("Padding End"),
			  _("Padding End property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_LEFT,
     g_param_spec_object ("padding-left",
			  _("Padding Left"),
			  _("Padding Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_RIGHT,
     g_param_spec_object ("padding-right",
			  _("Padding Right"),
			  _("Padding Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_START,
     g_param_spec_object ("padding-start",
			  _("Padding Start"),
			  _("Padding Start property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_TOP,
     g_param_spec_object ("padding-top",
			  _("Padding Top"),
			  _("Padding Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SOURCE_DOCUMENT,
     g_param_spec_object ("source-document",
			  _("Source Document"),
			  _("Source Document property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER,
     g_param_spec_object ("space-after",
			  _("Space After"),
			  _("Space After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE,
     g_param_spec_object ("space-before",
			  _("Space Before"),
			  _("Space Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_START_INDENT,
     g_param_spec_object ("start-indent",
			  _("Start Indent"),
			  _("Start Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_TABLE_LAYOUT,
     g_param_spec_object ("table-layout",
			  _("Table Layout"),
			  _("Table Layout property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WIDTH,
     g_param_spec_object ("width",
			  _("Width"),
			  _("Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WRITING_MODE,
     g_param_spec_object ("writing-mode",
			  _("Writing Mode"),
			  _("Writing Mode property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_table_block_fo_init:
 * @iface: #FoBlockFoIFace structure for this class.
 * 
 * Initialize #FoBlockFoIface interface for this class.
 **/
void
fo_table_block_fo_init (FoBlockFoIface *iface)
{
  iface->get_background_color = fo_table_get_background_color;
  iface->get_border_after_color = fo_table_get_border_after_color;
  iface->get_border_after_style = fo_table_get_border_after_style;
  iface->get_border_after_width = fo_table_get_border_after_width;
  iface->get_border_before_color = fo_table_get_border_before_color;
  iface->get_border_before_style = fo_table_get_border_before_style;
  iface->get_border_before_width = fo_table_get_border_before_width;
  iface->get_border_end_color = fo_table_get_border_end_color;
  iface->get_border_end_style = fo_table_get_border_end_style;
  iface->get_border_end_width = fo_table_get_border_end_width;
  iface->get_border_start_color = fo_table_get_border_start_color;
  iface->get_border_start_style = fo_table_get_border_start_style;
  iface->get_border_start_width = fo_table_get_border_start_width;
  iface->get_keep_with_previous = fo_table_get_keep_with_previous;
  iface->get_keep_with_next = fo_table_get_keep_with_next;
  iface->get_keep_together = fo_table_get_keep_together;
  iface->get_padding_after = fo_table_get_padding_after;
  iface->get_padding_before = fo_table_get_padding_before;
  iface->get_padding_end = fo_table_get_padding_end;
  iface->get_padding_start = fo_table_get_padding_start;
  iface->get_space_before = fo_table_get_space_before;
  iface->get_space_after = fo_table_get_space_after;
  iface->get_start_indent = fo_table_get_start_indent;
  iface->get_end_indent = fo_table_get_end_indent;
}

/**
 * fo_table_cbpbp_fo_init:
 * @iface: #FoCBPBPFoIFace structure for this class.
 * 
 * Initialize #FoCBPBPFoIface interface for this class.
 **/
void
fo_table_cbpbp_fo_init (FoCBPBPFoIface *iface)
{
  iface->get_background_color = fo_table_get_background_color;
  iface->get_border_after_color = fo_table_get_border_after_color;
  iface->get_border_after_style = fo_table_get_border_after_style;
  iface->get_border_after_width = fo_table_get_border_after_width;
  iface->get_border_before_color = fo_table_get_border_before_color;
  iface->get_border_before_style = fo_table_get_border_before_style;
  iface->get_border_before_width = fo_table_get_border_before_width;
  iface->get_border_end_color = fo_table_get_border_end_color;
  iface->get_border_end_style = fo_table_get_border_end_style;
  iface->get_border_end_width = fo_table_get_border_end_width;
  iface->get_border_start_color = fo_table_get_border_start_color;
  iface->get_border_start_style = fo_table_get_border_start_style;
  iface->get_border_start_width = fo_table_get_border_start_width;
  iface->get_padding_after = fo_table_get_padding_after;
  iface->get_padding_before = fo_table_get_padding_before;
  iface->get_padding_end = fo_table_get_padding_end;
  iface->get_padding_start = fo_table_get_padding_start;
}

/**
 * fo_table_table_border_fo_init:
 * @iface: #FoTableBorderFoIFace structure for this class.
 * 
 * Initialize #FoTableBorderFoIface interface for this class.
 **/
void
fo_table_table_border_fo_init (FoTableBorderFoIface *iface)
{
  iface->get_background_color = fo_table_get_background_color;
  iface->get_border_after_color = fo_table_get_border_after_color;
  iface->get_border_after_precedence = fo_table_get_border_after_precedence;
  iface->get_border_after_style = fo_table_get_border_after_style;
  iface->get_border_after_width = fo_table_get_border_after_width;
  iface->get_border_before_color = fo_table_get_border_before_color;
  iface->get_border_before_precedence = fo_table_get_border_before_precedence;
  iface->get_border_before_style = fo_table_get_border_before_style;
  iface->get_border_before_width = fo_table_get_border_before_width;
  iface->get_border_end_color = fo_table_get_border_end_color;
  iface->get_border_end_precedence = fo_table_get_border_end_precedence;
  iface->get_border_end_style = fo_table_get_border_end_style;
  iface->get_border_end_width = fo_table_get_border_end_width;
  iface->get_border_start_color = fo_table_get_border_start_color;
  iface->get_border_start_precedence = fo_table_get_border_start_precedence;
  iface->get_border_start_style = fo_table_get_border_start_style;
  iface->get_border_start_width = fo_table_get_border_start_width;
}

/**
 * fo_table_finalize:
 * @object: #FoTable object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoTable.
 **/
void
fo_table_finalize (GObject *object)
{
  FoTable *fo_table;

  fo_table = FO_TABLE (object);

  g_hash_table_foreach (fo_table->column_hash,
			fo_table_free_hash_key,
			NULL);
  g_hash_table_destroy (fo_table->column_hash);

  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_table_set_background_color (fo, NULL);
  fo_table_set_background_image (fo, NULL);
  fo_table_set_block_progression_dimension (fo, NULL);
  fo_table_set_border_after_color (fo, NULL);
  fo_table_set_border_after_precedence (fo, NULL);
  fo_table_set_border_after_style (fo, NULL);
  fo_table_set_border_after_width (fo, NULL);
  fo_table_set_border_before_color (fo, NULL);
  fo_table_set_border_before_precedence (fo, NULL);
  fo_table_set_border_before_style (fo, NULL);
  fo_table_set_border_before_width (fo, NULL);
  fo_table_set_border_bottom_color (fo, NULL);
  fo_table_set_border_bottom_style (fo, NULL);
  fo_table_set_border_bottom_width (fo, NULL);
  fo_table_set_border_collapse (fo, NULL);
  fo_table_set_border_end_color (fo, NULL);
  fo_table_set_border_end_precedence (fo, NULL);
  fo_table_set_border_end_style (fo, NULL);
  fo_table_set_border_end_width (fo, NULL);
  fo_table_set_border_left_color (fo, NULL);
  fo_table_set_border_left_style (fo, NULL);
  fo_table_set_border_left_width (fo, NULL);
  fo_table_set_border_right_color (fo, NULL);
  fo_table_set_border_right_style (fo, NULL);
  fo_table_set_border_right_width (fo, NULL);
  fo_table_set_border_separation (fo, NULL);
  fo_table_set_border_start_color (fo, NULL);
  fo_table_set_border_start_precedence (fo, NULL);
  fo_table_set_border_start_style (fo, NULL);
  fo_table_set_border_start_width (fo, NULL);
  fo_table_set_border_top_color (fo, NULL);
  fo_table_set_border_top_style (fo, NULL);
  fo_table_set_border_top_width (fo, NULL);
  fo_table_set_break_after (fo, NULL);
  fo_table_set_break_before (fo, NULL);
  fo_table_set_end_indent (fo, NULL);
  fo_table_set_height (fo, NULL);
  fo_table_set_id (fo, NULL);
  fo_table_set_inline_progression_dimension (fo, NULL);
  fo_table_set_keep_together (fo, NULL);
  fo_table_set_keep_together_within_column (fo, NULL);
  fo_table_set_keep_together_within_line (fo, NULL);
  fo_table_set_keep_together_within_page (fo, NULL);
  fo_table_set_keep_with_next (fo, NULL);
  fo_table_set_keep_with_next_within_column (fo, NULL);
  fo_table_set_keep_with_next_within_line (fo, NULL);
  fo_table_set_keep_with_next_within_page (fo, NULL);
  fo_table_set_keep_with_previous (fo, NULL);
  fo_table_set_keep_with_previous_within_column (fo, NULL);
  fo_table_set_keep_with_previous_within_line (fo, NULL);
  fo_table_set_keep_with_previous_within_page (fo, NULL);
  fo_table_set_margin_bottom (fo, NULL);
  fo_table_set_margin_left (fo, NULL);
  fo_table_set_margin_right (fo, NULL);
  fo_table_set_margin_top (fo, NULL);
  fo_table_set_padding_after (fo, NULL);
  fo_table_set_padding_before (fo, NULL);
  fo_table_set_padding_bottom (fo, NULL);
  fo_table_set_padding_end (fo, NULL);
  fo_table_set_padding_left (fo, NULL);
  fo_table_set_padding_right (fo, NULL);
  fo_table_set_padding_start (fo, NULL);
  fo_table_set_padding_top (fo, NULL);
  fo_table_set_role (fo, NULL);
  fo_table_set_source_document (fo, NULL);
  fo_table_set_space_after (fo, NULL);
  fo_table_set_space_before (fo, NULL);
  fo_table_set_start_indent (fo, NULL);
  fo_table_set_table_layout (fo, NULL);
  fo_table_set_width (fo, NULL);
  fo_table_set_writing_mode (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_table_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoTable.
 **/
void
fo_table_get_property (GObject    *object,
                       guint       prop_id,
                       GValue     *value,
                       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_LAYOUT_METHOD:
      g_value_set_enum (value, fo_table_get_layout_method (fo_fo));
      break;
    case PROP_MAX_COLUMN_NUMBER:
      g_value_set_int (value, fo_table_get_max_column_number (fo_fo));
      break;
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_table_get_background_image (fo_fo)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_table_get_block_progression_dimension (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_after_precedence (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_before_precedence (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_COLLAPSE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_collapse (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_end_precedence (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_SEPARATION:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_separation (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_start_precedence (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_border_top_width (fo_fo)));
      break;
    case PROP_BREAK_AFTER:
      g_value_set_object (value, G_OBJECT (fo_table_get_break_after (fo_fo)));
      break;
    case PROP_BREAK_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_table_get_break_before (fo_fo)));
      break;
    case PROP_END_INDENT:
      g_value_set_object (value, G_OBJECT (fo_table_get_end_indent (fo_fo)));
      break;
    case PROP_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_table_get_height (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_table_get_id (fo_fo)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_table_get_inline_progression_dimension (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_together (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_together_within_column (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_together_within_line (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_together_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_next (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_next_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_next_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_next_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_previous (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_previous_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_previous_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_table_get_keep_with_previous_within_page (fo_fo)));
      break;
    case PROP_MARGIN_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_table_get_margin_bottom (fo_fo)));
      break;
    case PROP_MARGIN_LEFT:
      g_value_set_object (value, G_OBJECT (fo_table_get_margin_left (fo_fo)));
      break;
    case PROP_MARGIN_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_table_get_margin_right (fo_fo)));
      break;
    case PROP_MARGIN_TOP:
      g_value_set_object (value, G_OBJECT (fo_table_get_margin_top (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_table_get_padding_top (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_table_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_table_get_source_document (fo_fo)));
      break;
    case PROP_SPACE_AFTER:
      g_value_set_object (value, G_OBJECT (fo_table_get_space_after (fo_fo)));
      break;
    case PROP_SPACE_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_table_get_space_before (fo_fo)));
      break;
    case PROP_START_INDENT:
      g_value_set_object (value, G_OBJECT (fo_table_get_start_indent (fo_fo)));
      break;
    case PROP_TABLE_LAYOUT:
      g_value_set_object (value, G_OBJECT (fo_table_get_table_layout (fo_fo)));
      break;
    case PROP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_table_get_width (fo_fo)));
      break;
    case PROP_WRITING_MODE:
      g_value_set_object (value, G_OBJECT (fo_table_get_writing_mode (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_table_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoTable.
 **/
void
fo_table_set_property (GObject      *object,
                       guint         prop_id,
                       const GValue *value,
                       GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      fo_table_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_table_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      fo_table_set_block_progression_dimension (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_table_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_PRECEDENCE:
      fo_table_set_border_after_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_table_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_table_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_table_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_PRECEDENCE:
      fo_table_set_border_before_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_table_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_table_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_table_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_table_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_table_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_COLLAPSE:
      fo_table_set_border_collapse (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_table_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_PRECEDENCE:
      fo_table_set_border_end_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_table_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_table_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_table_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_table_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_table_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_table_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_table_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_table_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_SEPARATION:
      fo_table_set_border_separation (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_table_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_PRECEDENCE:
      fo_table_set_border_start_precedence (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_table_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_table_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_table_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_table_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_table_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BREAK_AFTER:
      fo_table_set_break_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_BREAK_BEFORE:
      fo_table_set_break_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_END_INDENT:
      fo_table_set_end_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_HEIGHT:
      fo_table_set_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_table_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      fo_table_set_inline_progression_dimension (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER:
      fo_table_set_keep_together (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      fo_table_set_keep_together_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      fo_table_set_keep_together_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      fo_table_set_keep_together_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT:
      fo_table_set_keep_with_next (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      fo_table_set_keep_with_next_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      fo_table_set_keep_with_next_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      fo_table_set_keep_with_next_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      fo_table_set_keep_with_previous (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      fo_table_set_keep_with_previous_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      fo_table_set_keep_with_previous_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      fo_table_set_keep_with_previous_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_BOTTOM:
      fo_table_set_margin_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_LEFT:
      fo_table_set_margin_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_RIGHT:
      fo_table_set_margin_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_TOP:
      fo_table_set_margin_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_table_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_table_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_table_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_table_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_table_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_table_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_table_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_table_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_table_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_table_set_source_document (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER:
      fo_table_set_space_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE:
      fo_table_set_space_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_START_INDENT:
      fo_table_set_start_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_TABLE_LAYOUT:
      fo_table_set_table_layout (fo_fo, g_value_get_object (value));
      break;
    case PROP_WIDTH:
      fo_table_set_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_WRITING_MODE:
      fo_table_set_writing_mode (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_table_new:
 * 
 * Creates a new #FoTable initialized to default value.
 * 
 * Return value: the new #FoTable.
 **/
FoFo*
fo_table_new (void)
{
  return FO_FO (g_object_new (fo_table_get_type (),
                              NULL));
}

/**
 * fo_table_error_quark:
 * 
 * Create and return the #GQuark for use as the error domain for
 * table.
 * 
 * Return value: Error domain #GQuark.
 **/
GQuark
fo_table_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("fo-table-error");
  return quark;
}

/**
 * fo_table_free_hash_key:
 * @key:       The key
 * @value:     The value (unused)
 * @user_data: Extra data (unused)
 * 
 * Free a single hash key
 **/
static void
fo_table_free_hash_key (gpointer key,
			gpointer value G_GNUC_UNUSED,
			gpointer user_data G_GNUC_UNUSED)
{
  g_free (key);
}

/**
 * fo_table_debug_dump_hash:
 * @key: 
 * @value: 
 * @data: 
 * 
 * Log the key and value combination of a hash table entry.
 **/
void
fo_table_debug_dump_hash (gpointer key,
			  gpointer value,
			  gpointer data)
{
  gchar *indent = g_strnfill (GPOINTER_TO_INT (data) * 2, ' ');
  gchar *value_string = fo_object_debug_sprintf (value);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%d,%d : %s",
	 indent,
	 *((int *) key) >> 16,
	 *((int *) key) & 0xff,
	 value_string);

  g_free (value_string);
  g_free (indent);
}

/**
 * fo_table_get_proportional_unit:
 * @fo: #FoTable for which to get proportional unit.
 * 
 * Get the length in points of one proportional unit for @fo.
 * 
 * Return value: The length in points of one proportional unit.
 **/
gdouble
fo_table_get_proportional_unit (FoFo *fo)
{
  g_return_val_if_fail (FO_IS_TABLE (fo), 0.0);

  return FO_TABLE (fo)->proportional_unit;
}

FoDatatype*
fo_table_eval_column_fixed_width (FoFo *table_column,
				  GError **error)
{
  FoProperty *column_font_size = NULL;
  FoProperty *column_column_width = NULL;
  FoDatatype *column_width_string = NULL;
  FoDatatype *column_fixed = NULL;
  FoContext  *parent_context = NULL;
  GError *tmp_error = NULL;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  column_font_size =
    fo_context_get_font_size (fo_fo_get_context (table_column));

  column_column_width =
    fo_table_column_get_column_width (table_column);

  column_width_string =
    fo_property_get_value (column_column_width);

  parent_context =
    fo_fo_get_context (FO_FO (fo_node_parent (FO_NODE (table_column))));

  column_fixed =
    fo_expr_eval (fo_string_get_value (column_width_string),
		  "column-width",
		  NULL,
		  fo_property_column_width_resolve_percent,
		  column_font_size,
		  table_column,
		  parent_context,
		  fixed_env_list,
		  &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (error, tmp_error);
      return NULL;
    }

  if (!FO_IS_LENGTH (column_fixed))
    {
      g_set_error (error,
		   FO_TABLE_ERROR,
		   FO_TABLE_ERROR_WIDTH_NOT_LENGTH,
		   fo_table_error_messages[FO_TABLE_ERROR_WIDTH_NOT_LENGTH],
		   fo_string_get_value (column_width_string));
      return NULL;
    }

  return column_fixed;
}

FoDatatype*
fo_table_eval_column_proportional_width (FoFo *table_column,
					 GError **error)
{
  FoProperty *column_font_size = NULL;
  FoProperty *column_column_width = NULL;
  FoDatatype *column_width_string = NULL;
  FoDatatype *column_proportional = NULL;
  FoContext  *parent_context = NULL;
  GError *tmp_error = NULL;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  column_font_size =
    fo_context_get_font_size (fo_fo_get_context (table_column));

  column_column_width =
    fo_table_column_get_column_width (table_column);

  column_width_string =
    fo_property_get_value (column_column_width);

  parent_context =
    fo_fo_get_context (FO_FO (fo_node_parent (FO_NODE (table_column))));

  gchar *string_value = fo_string_get_value (column_width_string);
  column_proportional =
    fo_expr_eval (string_value,
		  "column-width",
		  NULL,
		  fo_property_column_width_resolve_percent,
		  column_font_size,
		  table_column,
		  parent_context,
		  proportional_env_list,
		  &tmp_error);
  g_free (string_value);

  if (tmp_error != NULL)
    {
      g_propagate_error (error, tmp_error);
      return NULL;
    }

  return column_proportional;
}

FoDatatype*
fo_table_eval_column_proportional_fixed_width (FoFo *table_column,
					       GError **error)
{
  FoProperty *column_font_size = NULL;
  FoProperty *column_column_width = NULL;
  FoDatatype *column_width_string = NULL;
  FoDatatype *column_proportional_fixed = NULL;
  FoContext  *parent_context = NULL;
  GError *tmp_error = NULL;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  column_font_size =
    fo_context_get_font_size (fo_fo_get_context (table_column));

  column_column_width =
    fo_table_column_get_column_width (table_column);

  column_width_string =
    fo_property_get_value (column_column_width);

  parent_context =
    fo_fo_get_context (FO_FO (fo_node_parent (FO_NODE (table_column))));

  column_proportional_fixed =
    fo_expr_eval (fo_string_get_value (column_width_string),
		  "column-width",
		  NULL,
		  fo_property_column_width_resolve_percent,
		  column_font_size,
		  table_column,
		  parent_context,
		  proportional_fixed_env_list,
		  &tmp_error);

  if (tmp_error != NULL)
    {
      g_propagate_error (error, tmp_error);
      return NULL;
    }

  return column_proportional_fixed;
}

void
fo_table_resolve_proportional_widths (FoFo    *fo,
				      GError **error)
{
  FoTable *fo_table;
  FoEnumTableLayoutMethod layout_method;
  gint max_column_number;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_table = FO_TABLE (fo);

  layout_method = fo_table->layout_method;
  max_column_number = fo_table->max_column_number;

#if defined(LIBFO_DEBUG) && 0
  g_message ("resolve_proportional_widths:: max_column_number: %d",
	     max_column_number);
#endif

  if (layout_method == FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN)
    {
      g_set_error (error,
		   FO_TABLE_ERROR,
		   FO_TABLE_ERROR_LAYOUT_METHOD_UNKNOWN,
		   "%s",
		   fo_table_error_messages[FO_TABLE_ERROR_LAYOUT_METHOD_UNKNOWN]);
      return;
    }

  if (layout_method == FO_ENUM_TABLE_LAYOUT_METHOD_FIXED)
    {
      FoNode *child_node = NULL;
      FoDatatype *fixed_sum;
      FoDatatype *proportional_sum;
      FoArea *table_area;
      FoFoAreaIterator *iterator;

      if (max_column_number == 0)
	{
	  g_set_error (error,
		       FO_TABLE_ERROR,
		       FO_TABLE_ERROR_FIXED_NO_COLUMN,
		       "%s",
		       fo_table_error_messages[FO_TABLE_ERROR_FIXED_NO_COLUMN]);
	  return;
	}

      fixed_sum  = g_object_ref (fo_length_get_length_zero ());
      proportional_sum = g_object_ref (fo_pcw_get_pcw_zero ());
      child_node = fo_node_first_child (FO_NODE (fo_table));
      while (FO_IS_TABLE_COLUMN (child_node))
	{
	  FoDatatype *column_fixed_width;
	  FoDatatype *column_proportional_width;
	  GError *tmp_error = NULL;

	  column_fixed_width =
	    fo_table_eval_column_fixed_width (FO_FO (child_node),
					      &tmp_error);

	  if (tmp_error != NULL)
	    {
	      g_propagate_error (error, tmp_error);
	      return;
	    }

	  fixed_sum = fo_datatype_add (fixed_sum,
				       column_fixed_width);

	  column_proportional_width =
	    fo_table_eval_column_proportional_width (FO_FO (child_node),
						     &tmp_error);

	  if (tmp_error != NULL)
	    {
	      g_propagate_error (error, tmp_error);
	      return;
	    }

	  proportional_sum = fo_datatype_add (proportional_sum,
					      column_proportional_width);

	  child_node = fo_node_next_sibling (child_node);
	}

      iterator = fo_fo_get_area_iterator (FO_FO (fo_table));
      table_area = fo_fo_area_iterator_get_area (iterator);

      if (table_area != NULL)
	{
	  gdouble table_area_available_width;
	  gdouble table_fixed_width;

	  table_area_available_width =
	    fo_area_get_child_available_ipdim (table_area);

	  table_fixed_width =
	    fo_length_get_value (fixed_sum);

	  if (table_area_available_width > table_fixed_width)
	    {
	      fo_table->proportional_unit =
		(table_area_available_width - table_fixed_width) /
		fo_pcw_get_value (proportional_sum);
	    }
	  else
	    {
	      fo_table->proportional_unit = 0.0;
	    }

	  child_node = fo_node_first_child (FO_NODE (fo_table));
	  while (FO_IS_TABLE_COLUMN (child_node))
	    {
	      FoProperty *column_width;
	      FoDatatype *column_proportional_fixed_width;
	      GError *tmp_error = NULL;

	      column_proportional_fixed_width =
		fo_table_eval_column_proportional_fixed_width (FO_FO (child_node),
							       &tmp_error);

	      column_width = g_object_new (FO_TYPE_PROPERTY_COLUMN_WIDTH,
					   "value",
					   column_proportional_fixed_width,
					   NULL);

	      fo_table_column_set_column_width (FO_FO (child_node),
						column_width);

	      child_node = fo_node_next_sibling (child_node);
	    }
	}
      else
	{
	  g_set_error (error,
		       FO_TABLE_ERROR,
		       FO_TABLE_ERROR_NO_AREA,
		       "%s",
		       fo_table_error_messages[FO_TABLE_ERROR_NO_AREA]);
	  return;
	}

      g_free (iterator);
    }
}

void
fo_table_resolve_column_offsets (FoFo    *fo,
				 GError **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (FO_TABLE (fo)->max_column_number != 0);
  g_return_if_fail (error == NULL || *error == NULL);

  FoTable *fo_table = FO_TABLE (fo);

  gint max_column_number = fo_table->max_column_number;
  FoEnumAreaDirection ipd =
    fo_property_writing_mode_to_ipd (fo_table->writing_mode,
				     NULL);

  gint initial_column;
  gboolean increment;
  gint limit;
  /* Calculate column offsets either from 1 to max or max to 1
     depending on inline-progression-direction value. */
  switch (ipd)
    {
    case FO_ENUM_AREA_DIRECTION_LR:
      initial_column = 1;
      /* Test in 'for' is equality test, so don't stop until after max
	 column number. */
      limit = max_column_number + 1;
      increment = TRUE;
      break;
    case FO_ENUM_AREA_DIRECTION_RL:
      initial_column = max_column_number;
      /* Test in 'for' is equality test, so don't stop until after
	 first column. */
      limit = 0;
      increment = FALSE;
      break;
    default:
      g_set_error (error,
		   FO_TABLE_ERROR,
		   FO_TABLE_ERROR_INLINE_PROGRESSION_DIRECTION,
		   fo_table_error_messages[FO_TABLE_ERROR_INLINE_PROGRESSION_DIRECTION],
		   ipd);
      return;
    }

  gint column_number;
  gint key;
  FoFo *fo_column;
  gfloat cumulative_offset = 0;
  for (column_number = initial_column;
       column_number != limit;
       increment ? column_number++ : column_number--)
    {
      key = fo_table_make_column_hash_key (column_number, 1);

      fo_column = g_hash_table_lookup (fo_table->column_hash,
				       &key);

      if (!fo_column)
	{
	  g_set_error (error,
		       FO_TABLE_ERROR,
		       FO_TABLE_ERROR_MISSING_COLUMN,
		       fo_table_error_messages[FO_TABLE_ERROR_MISSING_COLUMN],
		       column_number);
	  return;
	}

      fo_table_column_set_offset (fo_column,
				  cumulative_offset);

      cumulative_offset +=
      fo_length_get_value (fo_property_get_value (fo_table_column_get_column_width (fo_column)));
    }
}

/**
 * fo_table_span_info_debug_dump:
 * @fo:    #FoTable for which to dump span info.
 * @depth: Relative indent to add to output.
 * 
 * Dump info about the spans used in the table.
 **/
void
fo_table_span_info_debug_dump (FoFo *fo,
			       gint depth)
{
  FoTable *fo_table;
  gchar *string = NULL;
  gchar *indent = g_strnfill (depth * 2, ' ');
  gint index;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));

  fo_table = FO_TABLE (fo);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%snext-column: %d",
	 indent,
	 fo_table->span_info_next_column);

  if (fo_table->span_info != NULL)
    {
      for (index = 0;
	   index < fo_table->max_column_number;
	   index ++)
	{
	  SpanInfo *span_info = &g_array_index (fo_table->span_info,
						SpanInfo,
						index);

	  string = fo_object_debug_sprintf (span_info->table_cell);
	  g_log (G_LOG_DOMAIN,
		 G_LOG_LEVEL_DEBUG,
		 "%scolumn: %d; rows spanned: %d; table-cell: %s",
		 indent,
		 index + 1,
		 span_info->rows_spanned,
		 string);
	  g_free (string);
	}
    }

  g_free (indent);
}

/**
 * fo_table_span_info_start_row:
 * @fo: #FoTable for which to reset span_info
 * @error: #GError
 * 
 * Reset span_info of @fo at the start of a row.
 **/
void
fo_table_span_info_start_row (FoFo    *fo,
			      GError **error)
{
  FoTable *fo_table;
  gint index;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_table = FO_TABLE (fo);

  for (index = 0;
       index < fo_table->max_column_number;
       index ++)
    {
      SpanInfo *span_info = &g_array_index (fo_table->span_info,
					   SpanInfo,
					   index);

      if (span_info->rows_spanned != 0)
	{
	  span_info->rows_spanned--;

	  if (span_info->rows_spanned == 0)
	    span_info->table_cell = NULL;
	}
    }

  fo_table->span_info_next_column = 0;

  for (index = 0;
       index < fo_table->max_column_number;
       index ++)
    {
      SpanInfo *span_info = &g_array_index (fo_table->span_info,
					    SpanInfo,
					    index);

      fo_table->span_info_next_column = index + 1;

      if (span_info->rows_spanned == 0)
	{
	  break;
	}
    }

  /*
  if (fo_table->span_info_next_column == fo_table->max_column_number)
    {
      g_set_error (error,
		   FO_TABLE_ERROR,
		   FO_TABLE_ERROR_SPANNING_CELLS_FILL_ROW,
		   fo_table_error_messages[FO_TABLE_ERROR_SPANNING_CELLS_FILL_ROW]);
    }
  */
}

/**
 * fo_table_span_info_resolve_column_number:
 * @fo:              The #FoTable containing @table_cell.
 * @table_cell:      The #FoTableCell for which to assign a column number.
 * @column_number:   Requested column number, or 0 if not specified.
 * @columns_spanned: Number of columns spanned by @table_cell.
 * @rows_spanned:    Number of rows spanned by @table_cell.
 * @error:           #GError indicating any error condition that occurred.
 * 
 * Determine the column-number for @table_cell.
 * 
 * Return value: The column-number to assign to @table_cell.
 **/
gint
fo_table_span_info_resolve_column_number (FoFo    *fo,
					  FoFo    *table_cell,
					  gint     column_number,
					  gint     columns_spanned,
					  gint     rows_spanned,
					  GError **error)
{
  g_return_val_if_fail (fo != NULL, 0);
  g_return_val_if_fail (FO_IS_TABLE (fo), 0);
  g_return_val_if_fail (FO_IS_TABLE_CELL (table_cell), 0);
  g_return_val_if_fail (error == NULL || *error == NULL, 0);

  FoTable *fo_table = FO_TABLE (fo);

  g_return_val_if_fail (column_number <= fo_table->max_column_number, 0);

  gint new_column_number;
  if (column_number == 0)
    {
      new_column_number = fo_table->span_info_next_column;
    }
  else
    {
      new_column_number = column_number;
    }

  gint column_index;
  for (column_index = new_column_number - 1;
       column_index < (new_column_number + columns_spanned - 1);
       column_index++)
    {
      SpanInfo *span_info = &g_array_index (fo_table->span_info,
					    SpanInfo,
					    column_index);
      span_info->rows_spanned = rows_spanned;
      span_info->table_cell = table_cell;
    }

  /* The next available column is the next column that does not have
     an intrusion from the previous row (or, when column numbers are
     not in sequence in the FO document, that has not yet been
     filled by a cell in this row). */
  /* Subtract 1 when making column_index and add it back when setting
     span_info_next_column since the span_info GArray counts from 0
     and column numbers count from 1. */
  for (column_index = new_column_number + columns_spanned - 1;
       column_index < fo_table->max_column_number;
       column_index++)
    {
      SpanInfo *span_info = &g_array_index (fo_table->span_info,
					    SpanInfo,
					    column_index);
      if (span_info->rows_spanned == 0)
	{
	  fo_table->span_info_next_column = column_index + 1;
	  break;
	}
    }

  return new_column_number;
}
/**
 * fo_table_resolve_columns:
 * @fo:    #FoTable for which to resolve columns
 * @error: #GError
 * 
 * Do housekeeping for table-column FOs now that all FoTableColumn
 * objects have been created.
 **/
void
fo_table_resolve_columns (FoFo    *fo,
			  GError **error)
{
  FoTable *fo_table;
  GError *tmp_error = NULL;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_table = FO_TABLE (fo);

  fo_table_resolve_proportional_widths (fo,
					&tmp_error);
  if (tmp_error != NULL)
    {
      g_propagate_error (error,
			 tmp_error);
      return;
    }

  fo_table_resolve_column_offsets (fo,
				   &tmp_error);
  if (tmp_error != NULL)
    {
      g_propagate_error (error,
			 tmp_error);
      return;
    }

  if (fo_table->span_info == NULL)
    {
      fo_table->span_info = g_array_sized_new (FALSE,
					       TRUE,
					       sizeof (SpanInfo),
					       fo_table->max_column_number);
      fo_table->span_info = g_array_set_size (fo_table->span_info,
					      fo_table->max_column_number);
    }
}

/**
 * fo_table_add_column:
 * @fo:                     #FoTable
 * @column_number:          Column number of @column
 * @number_columns_spanned: Number of columns spanned by @column
 * @column:                 #FoTableColumn to add to hash
 * 
 * Add a table-column object to the
 * column-number+number-columns-spanned hash maintained by @table.
 **/
void
fo_table_add_column (FoFo *fo,
		     gint column_number,
		     gint number_columns_spanned,
		     FoFo *column)
{
  FoTable *fo_table;
  gint potential_key;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (column_number > 0);
  g_return_if_fail (number_columns_spanned > 0);
  g_return_if_fail (column != NULL);
  g_return_if_fail (FO_IS_TABLE_COLUMN (column));

  fo_table = FO_TABLE (fo);

  if (column_number > fo_table->max_column_number)
    fo_table->max_column_number = column_number;

  potential_key = fo_table_make_column_hash_key (column_number,
						 number_columns_spanned);

#if defined(LIBFO_DEBUG) && 0
  g_message ("add_column:: number: %d; span: %d; key: %x; column: %s",
	     column_number,
	     number_columns_spanned,
	     potential_key,
	     fo_object_debug_sprintf (column));
#endif

  if (g_hash_table_lookup (fo_table->column_hash,
			   &column_number))
    {
      g_warning ("Column '%d' already in column hash.", column_number);
    }
  else
    {
      gint *key = g_new (int, 1);

      *key = potential_key;

      g_hash_table_insert (fo_table->column_hash,
			   key,
			   column);
    }
}

/**
 * fo_table_get_column:
 * @fo:                     #FoTable that has hash of columns
 * @column_number:          Column number to match
 * @number_columns_spanned: Number of columns spanned on which to map
 *
 * Get the column for a column number and number columns spanned
 * combination.
 * 
 * Return value: #FoTableColumn object
 **/
FoFo*
fo_table_get_column (FoFo *fo,
		     gint  column_number,
		     gint  number_columns_spanned)
{
  gint key = fo_table_make_column_hash_key (column_number, number_columns_spanned);

  g_return_val_if_fail (fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo), NULL);

  return g_hash_table_lookup (FO_TABLE (fo)->column_hash,
			      &key);
}

/**
 * fo_table_get_max_column_number:
 * @fo: #FoTable that has hash of columns
 *
 * Get highest column number of columns registered with table using
 * fo_table_add_column.
 * 
 * Return value: Highest column number registered using fo_table_add_column
 **/
gint
fo_table_get_max_column_number (FoFo *fo)
{
  g_return_val_if_fail (fo != NULL, 0);
  g_return_val_if_fail (FO_IS_TABLE (fo), 0);

  return FO_TABLE (fo)->max_column_number;
}

/**
 * fo_table_validate_content:
 * @fo:    #FoTable object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Content model: (table-column*, table-header?, table-footer?,
 *		   table-body+)
 *
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_table_validate_content (FoFo    *fo,
                           GError **error)
{
  GError *tmp_error;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_TABLE (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  /* First, check that the structure is correct. */
  FoNode *child_node = fo_node_first_child (FO_NODE (fo));

  /* Need at least one table-body. */
  gboolean have_table_body = FALSE;
  while (child_node)
    {
      FoNode *next_child = fo_node_next_sibling (child_node);

      if (FO_IS_TABLE_COLUMN (child_node))
	{
	  if (FO_IS_TABLE_COLUMN (next_child) ||
	      FO_IS_TABLE_HEADER (next_child) ||
	      FO_IS_TABLE_FOOTER (next_child) ||
	      FO_IS_TABLE_BODY (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_TABLE_HEADER (child_node))
	{
	  if (FO_IS_TABLE_FOOTER (next_child) ||
	      FO_IS_TABLE_BODY (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_TABLE_FOOTER (child_node))
	{
	  if (FO_IS_TABLE_BODY (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_TABLE_BODY (child_node))
	{
	  have_table_body = TRUE;

	  if (!next_child ||
	      FO_IS_TABLE_BODY (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else
	{
	  goto error;
	}
    }

    if (!have_table_body)
    {
      goto error;
    }

  /* Second, put any table-footer after the table-body (or bodies).*/
  child_node = fo_node_first_child (FO_NODE (fo));

  FoNode *footer = NULL;
  while (child_node)
    {
      FoNode *next_child = fo_node_next_sibling (child_node);

      if (FO_IS_TABLE_FOOTER (child_node))
	{
	  footer = child_node;
	  fo_node_unlink (footer);
	  break;
	}

      child_node = next_child;
    }

  if (footer != NULL)
    {
      fo_node_append (FO_NODE (fo),
		      footer);
    }

  return FALSE;

 error:
  tmp_error =
    g_error_new (FO_FO_ERROR,
		 FO_FO_ERROR_INVALID_CONTENT,
		 _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
		 fo_object_sprintf (FO_OBJECT (fo)));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
}

/**
 * fo_table_validate_content_table_row_table_cell:
 * @fo:    #FoRoot object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraversFunc model: %FALSE indicates content
 * model is correct, or %TRUE indicates an error.  When used with
 * fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * This is used by table-header, table-footer, and table-body.
 *
 * Content model: (table-row+ | table-cell+)
 *
 * Return value: %FALSE if content model okay, %TRUE if not
 **/
gboolean
fo_table_validate_content_table_row_table_cell (FoFo    *fo,
						GError **error)
{
  FoNode *child_node;
  GError *tmp_error;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_FO (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  child_node = fo_node_first_child (FO_NODE (fo));

  if (!child_node)
    goto error;

  while (child_node)
    {
      FoNode *next_child = fo_node_next_sibling (child_node);

      if (FO_IS_TABLE_ROW (child_node))
	{
	  if (!next_child ||
	      FO_IS_TABLE_ROW (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_TABLE_CELL (child_node))
	{
	  if (!next_child ||
	      FO_IS_TABLE_CELL (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
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
 * fo_table_resolve_layout_method:
 * @fo: #FoTable
 * 
 * Set the layout_method property of @fo depending on its
 * inline_progression_dimension and table_layout properties.
 **/
void
fo_table_resolve_layout_method (FoFo *fo)
{
  FoTable *fo_table;
  FoDatatype *table_layout_value;
  FoDatatype *ipdim_value;
  FoDatatype *ipdim_optimum;
  FoEnumTableLayoutMethod layout_method = FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN;
  guint table_layout_enum_value;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));

  fo_table = FO_TABLE (fo);

  table_layout_value =
    fo_property_get_value (fo_table->table_layout);
  ipdim_value =
    fo_property_get_value (fo_table->inline_progression_dimension);

#if defined(LIBFO_DEBUG) && 0
  g_message ("layout_method_resolve::");
  fo_object_debug_dump (table_layout_value, 0);
  fo_object_debug_dump (ipdim_value, 0);
#endif

  g_return_if_fail (FO_IS_ENUM (table_layout_value));

  table_layout_enum_value =
    fo_enum_get_value (table_layout_value);

  g_return_if_fail (FO_IS_LENGTH_RANGE (ipdim_value));

  ipdim_optimum = fo_length_range_get_optimum (ipdim_value);

  if (FO_IS_ENUM (ipdim_optimum) &&
      fo_enum_get_value (ipdim_optimum) == FO_ENUM_ENUM_AUTO)
    {
      if (table_layout_enum_value == FO_ENUM_ENUM_AUTO ||
	  table_layout_enum_value == FO_ENUM_ENUM_FIXED)
	{
	  layout_method = FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC;

	  if (table_layout_enum_value == FO_ENUM_ENUM_FIXED)
	    {
	      GError *local_error =
		g_error_new (FO_TABLE_ERROR,
			     FO_TABLE_ERROR_FIXED_BUT_AUTO,
			     "%s",
			     fo_table_error_messages[FO_TABLE_ERROR_FIXED_BUT_AUTO]);

	      fo_object_log_warning (FO_OBJECT (fo),
				     &local_error);
	    }
	}
      else
	{
	  g_assert_not_reached ();
	}
    }
  else if (FO_IS_LENGTH (ipdim_optimum) ||
	   FO_IS_PERCENTAGE (ipdim_optimum))
    {
      if (table_layout_enum_value == FO_ENUM_ENUM_AUTO)
	{
	  layout_method = FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC;
	}
      else if (table_layout_enum_value == FO_ENUM_ENUM_FIXED)
	{
	  layout_method = FO_ENUM_TABLE_LAYOUT_METHOD_FIXED;
	}
      else
	{
	  g_assert_not_reached ();
	}
    }
  else
    {
      g_assert_not_reached ();
    }

  fo_table->layout_method = layout_method;
}

/**
 * fo_table_validate:
 * @fo:              #FoTable object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_table_validate (FoFo      *fo,
                   FoContext *current_context,
                   FoContext *parent_context,
                   GError   **error)
{
  FoTable *fo_table;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_table = FO_TABLE (fo);

  fo_context_util_border_resolve (current_context, parent_context);
  fo_context_util_paddings_resolve (current_context, parent_context);
  fo_context_util_margins_indents_resolve (fo,
					   current_context,
					   parent_context);
  fo_context_util_margins_resolve (current_context, parent_context);
  fo_context_util_height_width_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_table_resolve_layout_method (fo);

  if (fo_table->layout_method == FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC)
    {
      fo_table->layout_method = FO_ENUM_TABLE_LAYOUT_METHOD_FIXED;

      GError *local_error =
	g_error_new (FO_TABLE_ERROR,
		     FO_TABLE_ERROR_FALLBACK_TO_FIXED,
		     "%s",
		     fo_table_error_messages[FO_TABLE_ERROR_FALLBACK_TO_FIXED]);

      fo_object_log_warning (FO_OBJECT (fo),
			     &local_error);
    }
}

/**
 * fo_table_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_table_update_from_context (FoFo      *fo,
                              FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_table_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_table_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_table_set_block_progression_dimension (fo,
			  fo_context_get_block_progression_dimension (context));
  fo_table_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_table_set_border_after_precedence (fo,
			  fo_context_get_border_after_precedence (context));
  fo_table_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_table_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_table_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_table_set_border_before_precedence (fo,
			  fo_context_get_border_before_precedence (context));
  fo_table_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_table_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_table_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_table_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_table_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_table_set_border_collapse (fo,
			  fo_context_get_border_collapse (context));
  fo_table_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_table_set_border_end_precedence (fo,
			  fo_context_get_border_end_precedence (context));
  fo_table_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_table_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_table_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_table_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_table_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_table_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_table_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_table_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_table_set_border_separation (fo,
			  fo_context_get_border_separation (context));
  fo_table_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_table_set_border_start_precedence (fo,
			  fo_context_get_border_start_precedence (context));
  fo_table_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_table_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_table_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_table_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_table_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  fo_table_set_break_after (fo,
			  fo_context_get_break_after (context));
  fo_table_set_break_before (fo,
			  fo_context_get_break_before (context));
  fo_table_set_end_indent (fo,
			  fo_context_get_end_indent (context));
  fo_table_set_height (fo,
			  fo_context_get_height (context));
  fo_table_set_id (fo,
			  fo_context_get_id (context));
  fo_table_set_inline_progression_dimension (fo,
			  fo_context_get_inline_progression_dimension (context));
  fo_table_set_keep_together (fo,
			  fo_context_get_keep_together (context));
  fo_table_set_keep_together_within_column (fo,
			  fo_context_get_keep_together_within_column (context));
  fo_table_set_keep_together_within_line (fo,
			  fo_context_get_keep_together_within_line (context));
  fo_table_set_keep_together_within_page (fo,
			  fo_context_get_keep_together_within_page (context));
  fo_table_set_keep_with_next (fo,
			  fo_context_get_keep_with_next (context));
  fo_table_set_keep_with_next_within_column (fo,
			  fo_context_get_keep_with_next_within_column (context));
  fo_table_set_keep_with_next_within_line (fo,
			  fo_context_get_keep_with_next_within_line (context));
  fo_table_set_keep_with_next_within_page (fo,
			  fo_context_get_keep_with_next_within_page (context));
  fo_table_set_keep_with_previous (fo,
			  fo_context_get_keep_with_previous (context));
  fo_table_set_keep_with_previous_within_column (fo,
			  fo_context_get_keep_with_previous_within_column (context));
  fo_table_set_keep_with_previous_within_line (fo,
			  fo_context_get_keep_with_previous_within_line (context));
  fo_table_set_keep_with_previous_within_page (fo,
			  fo_context_get_keep_with_previous_within_page (context));
  fo_table_set_margin_bottom (fo,
			  fo_context_get_margin_bottom (context));
  fo_table_set_margin_left (fo,
			  fo_context_get_margin_left (context));
  fo_table_set_margin_right (fo,
			  fo_context_get_margin_right (context));
  fo_table_set_margin_top (fo,
			  fo_context_get_margin_top (context));
  fo_table_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_table_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_table_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_table_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_table_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_table_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_table_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_table_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_table_set_role (fo,
			  fo_context_get_role (context));
  fo_table_set_source_document (fo,
			  fo_context_get_source_document (context));
  fo_table_set_space_after (fo,
			  fo_context_get_space_after (context));
  fo_table_set_space_before (fo,
			  fo_context_get_space_before (context));
  fo_table_set_start_indent (fo,
			  fo_context_get_start_indent (context));
  fo_table_set_table_layout (fo,
			  fo_context_get_table_layout (context));
  fo_table_set_width (fo,
			  fo_context_get_width (context));
  fo_table_set_writing_mode (fo,
			  fo_context_get_writing_mode (context));
}

/**
 * fo_table_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_table_debug_dump_properties (FoFo *fo,
                                gint  depth)
{
  FoTable *fo_table;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE (fo));

  fo_table = FO_TABLE (fo);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%slayout-method: %s",
	 indent,
	 fo_table->layout_method == FO_ENUM_TABLE_LAYOUT_METHOD_AUTOMATIC ? "automatic" : "fixed");

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%smax-column-number: %d",
	 indent,
	 fo_table->max_column_number);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%scolumn hash:",
	 indent);

  g_hash_table_foreach (fo_table->column_hash,
			fo_table_debug_dump_hash,
			GINT_TO_POINTER (depth + 1));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sspan-info:",
	 indent);

  fo_table_span_info_debug_dump (fo,
				 depth + 1);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sproportional-unit: %g",
	 indent,
	 fo_table->proportional_unit);

  fo_object_debug_dump (fo_table->background_color, depth);
  fo_object_debug_dump (fo_table->background_image, depth);
  fo_object_debug_dump (fo_table->block_progression_dimension, depth);
  fo_object_debug_dump (fo_table->border_after_color, depth);
  fo_object_debug_dump (fo_table->border_after_precedence, depth);
  fo_object_debug_dump (fo_table->border_after_style, depth);
  fo_object_debug_dump (fo_table->border_after_width, depth);
  fo_object_debug_dump (fo_table->border_before_color, depth);
  fo_object_debug_dump (fo_table->border_before_precedence, depth);
  fo_object_debug_dump (fo_table->border_before_style, depth);
  fo_object_debug_dump (fo_table->border_before_width, depth);
  fo_object_debug_dump (fo_table->border_bottom_color, depth);
  fo_object_debug_dump (fo_table->border_bottom_style, depth);
  fo_object_debug_dump (fo_table->border_bottom_width, depth);
  fo_object_debug_dump (fo_table->border_collapse, depth);
  fo_object_debug_dump (fo_table->border_end_color, depth);
  fo_object_debug_dump (fo_table->border_end_precedence, depth);
  fo_object_debug_dump (fo_table->border_end_style, depth);
  fo_object_debug_dump (fo_table->border_end_width, depth);
  fo_object_debug_dump (fo_table->border_left_color, depth);
  fo_object_debug_dump (fo_table->border_left_style, depth);
  fo_object_debug_dump (fo_table->border_left_width, depth);
  fo_object_debug_dump (fo_table->border_right_color, depth);
  fo_object_debug_dump (fo_table->border_right_style, depth);
  fo_object_debug_dump (fo_table->border_right_width, depth);
  fo_object_debug_dump (fo_table->border_separation, depth);
  fo_object_debug_dump (fo_table->border_start_color, depth);
  fo_object_debug_dump (fo_table->border_start_precedence, depth);
  fo_object_debug_dump (fo_table->border_start_style, depth);
  fo_object_debug_dump (fo_table->border_start_width, depth);
  fo_object_debug_dump (fo_table->border_top_color, depth);
  fo_object_debug_dump (fo_table->border_top_style, depth);
  fo_object_debug_dump (fo_table->border_top_width, depth);
  fo_object_debug_dump (fo_table->break_after, depth);
  fo_object_debug_dump (fo_table->break_before, depth);
  fo_object_debug_dump (fo_table->end_indent, depth);
  fo_object_debug_dump (fo_table->height, depth);
  fo_object_debug_dump (fo_table->id, depth);
  fo_object_debug_dump (fo_table->inline_progression_dimension, depth);
  fo_object_debug_dump (fo_table->keep_together, depth);
  fo_object_debug_dump (fo_table->keep_together_within_column, depth);
  fo_object_debug_dump (fo_table->keep_together_within_line, depth);
  fo_object_debug_dump (fo_table->keep_together_within_page, depth);
  fo_object_debug_dump (fo_table->keep_with_next, depth);
  fo_object_debug_dump (fo_table->keep_with_next_within_column, depth);
  fo_object_debug_dump (fo_table->keep_with_next_within_line, depth);
  fo_object_debug_dump (fo_table->keep_with_next_within_page, depth);
  fo_object_debug_dump (fo_table->keep_with_previous, depth);
  fo_object_debug_dump (fo_table->keep_with_previous_within_column, depth);
  fo_object_debug_dump (fo_table->keep_with_previous_within_line, depth);
  fo_object_debug_dump (fo_table->keep_with_previous_within_page, depth);
  fo_object_debug_dump (fo_table->margin_bottom, depth);
  fo_object_debug_dump (fo_table->margin_left, depth);
  fo_object_debug_dump (fo_table->margin_right, depth);
  fo_object_debug_dump (fo_table->margin_top, depth);
  fo_object_debug_dump (fo_table->padding_after, depth);
  fo_object_debug_dump (fo_table->padding_before, depth);
  fo_object_debug_dump (fo_table->padding_bottom, depth);
  fo_object_debug_dump (fo_table->padding_end, depth);
  fo_object_debug_dump (fo_table->padding_left, depth);
  fo_object_debug_dump (fo_table->padding_right, depth);
  fo_object_debug_dump (fo_table->padding_start, depth);
  fo_object_debug_dump (fo_table->padding_top, depth);
  fo_object_debug_dump (fo_table->role, depth);
  fo_object_debug_dump (fo_table->source_document, depth);
  fo_object_debug_dump (fo_table->space_after, depth);
  fo_object_debug_dump (fo_table->space_before, depth);
  fo_object_debug_dump (fo_table->start_indent, depth);
  fo_object_debug_dump (fo_table->table_layout, depth);
  fo_object_debug_dump (fo_table->width, depth);
  fo_object_debug_dump (fo_table->writing_mode, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);

  g_free (indent);
}

/**
 * fo_table_get_layout_method:
 * @fo_fo: The @FoFo object
 *
 * Gets the #layout-method property of @table
 *
 * Return value: The "layout-method" property value
**/
FoEnumTableLayoutMethod
fo_table_get_layout_method (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), FO_ENUM_TABLE_LAYOUT_METHOD_UNKNOWN);

  return fo_table->layout_method;
}

/**
 * fo_table_get_background_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-color" property of @fo_fo.
 *
 * Return value: The "background-color" property value.
**/
FoProperty *
fo_table_get_background_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->background_color;
}

/**
 * fo_table_set_background_color:
 * @fo_fo: The #FoFo object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color.
 **/
void
fo_table_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_background_color == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_table->background_color != NULL)
    {
      g_object_unref (fo_table->background_color);
    }
  fo_table->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_table), "background-color");*/
}

/**
 * fo_table_get_background_image:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-image" property of @fo_fo.
 *
 * Return value: The "background-image" property value.
**/
FoProperty *
fo_table_get_background_image (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->background_image;
}

/**
 * fo_table_set_background_image:
 * @fo_fo: The #FoFo object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image.
 **/
void
fo_table_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_background_image == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_table->background_image != NULL)
    {
      g_object_unref (fo_table->background_image);
    }
  fo_table->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_table), "background-image");*/
}

/**
 * fo_table_get_block_progression_dimension:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "block-progression-dimension" property of @fo_fo.
 *
 * Return value: The "block-progression-dimension" property value.
**/
FoProperty *
fo_table_get_block_progression_dimension (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->block_progression_dimension;
}

/**
 * fo_table_set_block_progression_dimension:
 * @fo_fo: The #FoFo object.
 * @new_block_progression_dimension: The new "block-progression-dimension" property value.
 * 
 * Sets the "block-progression-dimension" property of @fo_fo to @new_block_progression_dimension.
 **/
void
fo_table_set_block_progression_dimension (FoFo *fo_fo,
		         FoProperty *new_block_progression_dimension)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_block_progression_dimension == NULL) ||
		    FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION (new_block_progression_dimension));

  if (new_block_progression_dimension != NULL)
    {
      g_object_ref (new_block_progression_dimension);
    }
  if (fo_table->block_progression_dimension != NULL)
    {
      g_object_unref (fo_table->block_progression_dimension);
    }
  fo_table->block_progression_dimension = new_block_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_table), "block-progression-dimension");*/
}

/**
 * fo_table_get_border_after_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-color" property of @fo_fo.
 *
 * Return value: The "border-after-color" property value.
**/
FoProperty *
fo_table_get_border_after_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_after_color;
}

/**
 * fo_table_set_border_after_color:
 * @fo_fo: The #FoFo object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color.
 **/
void
fo_table_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_after_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_table->border_after_color != NULL)
    {
      g_object_unref (fo_table->border_after_color);
    }
  fo_table->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-after-color");*/
}

/**
 * fo_table_get_border_after_precedence:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-precedence" property of @fo_fo.
 *
 * Return value: The "border-after-precedence" property value.
**/
FoProperty *
fo_table_get_border_after_precedence (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_after_precedence;
}

/**
 * fo_table_set_border_after_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_after_precedence: The new "border-after-precedence" property value.
 * 
 * Sets the "border-after-precedence" property of @fo_fo to @new_border_after_precedence.
 **/
void
fo_table_set_border_after_precedence (FoFo *fo_fo,
		         FoProperty *new_border_after_precedence)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_after_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_PRECEDENCE (new_border_after_precedence));

  if (new_border_after_precedence != NULL)
    {
      g_object_ref (new_border_after_precedence);
    }
  if (fo_table->border_after_precedence != NULL)
    {
      g_object_unref (fo_table->border_after_precedence);
    }
  fo_table->border_after_precedence = new_border_after_precedence;
  /*g_object_notify (G_OBJECT (fo_table), "border-after-precedence");*/
}

/**
 * fo_table_get_border_after_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-style" property of @fo_fo.
 *
 * Return value: The "border-after-style" property value.
**/
FoProperty *
fo_table_get_border_after_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_after_style;
}

/**
 * fo_table_set_border_after_style:
 * @fo_fo: The #FoFo object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style.
 **/
void
fo_table_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_after_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_table->border_after_style != NULL)
    {
      g_object_unref (fo_table->border_after_style);
    }
  fo_table->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-after-style");*/
}

/**
 * fo_table_get_border_after_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-width" property of @fo_fo.
 *
 * Return value: The "border-after-width" property value.
**/
FoProperty *
fo_table_get_border_after_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_after_width;
}

/**
 * fo_table_set_border_after_width:
 * @fo_fo: The #FoFo object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width.
 **/
void
fo_table_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_after_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_table->border_after_width != NULL)
    {
      g_object_unref (fo_table->border_after_width);
    }
  fo_table->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-after-width");*/
}

/**
 * fo_table_get_border_before_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-color" property of @fo_fo.
 *
 * Return value: The "border-before-color" property value.
**/
FoProperty *
fo_table_get_border_before_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_before_color;
}

/**
 * fo_table_set_border_before_color:
 * @fo_fo: The #FoFo object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color.
 **/
void
fo_table_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_before_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_table->border_before_color != NULL)
    {
      g_object_unref (fo_table->border_before_color);
    }
  fo_table->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-before-color");*/
}

/**
 * fo_table_get_border_before_precedence:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-precedence" property of @fo_fo.
 *
 * Return value: The "border-before-precedence" property value.
**/
FoProperty *
fo_table_get_border_before_precedence (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_before_precedence;
}

/**
 * fo_table_set_border_before_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_before_precedence: The new "border-before-precedence" property value.
 * 
 * Sets the "border-before-precedence" property of @fo_fo to @new_border_before_precedence.
 **/
void
fo_table_set_border_before_precedence (FoFo *fo_fo,
		         FoProperty *new_border_before_precedence)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_before_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_PRECEDENCE (new_border_before_precedence));

  if (new_border_before_precedence != NULL)
    {
      g_object_ref (new_border_before_precedence);
    }
  if (fo_table->border_before_precedence != NULL)
    {
      g_object_unref (fo_table->border_before_precedence);
    }
  fo_table->border_before_precedence = new_border_before_precedence;
  /*g_object_notify (G_OBJECT (fo_table), "border-before-precedence");*/
}

/**
 * fo_table_get_border_before_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-style" property of @fo_fo.
 *
 * Return value: The "border-before-style" property value.
**/
FoProperty *
fo_table_get_border_before_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_before_style;
}

/**
 * fo_table_set_border_before_style:
 * @fo_fo: The #FoFo object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style.
 **/
void
fo_table_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_before_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_table->border_before_style != NULL)
    {
      g_object_unref (fo_table->border_before_style);
    }
  fo_table->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-before-style");*/
}

/**
 * fo_table_get_border_before_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-width" property of @fo_fo.
 *
 * Return value: The "border-before-width" property value.
**/
FoProperty *
fo_table_get_border_before_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_before_width;
}

/**
 * fo_table_set_border_before_width:
 * @fo_fo: The #FoFo object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width.
 **/
void
fo_table_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_before_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_table->border_before_width != NULL)
    {
      g_object_unref (fo_table->border_before_width);
    }
  fo_table->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-before-width");*/
}

/**
 * fo_table_get_border_bottom_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-color" property of @fo_fo.
 *
 * Return value: The "border-bottom-color" property value.
**/
FoProperty *
fo_table_get_border_bottom_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_bottom_color;
}

/**
 * fo_table_set_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color.
 **/
void
fo_table_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_bottom_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_table->border_bottom_color != NULL)
    {
      g_object_unref (fo_table->border_bottom_color);
    }
  fo_table->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-bottom-color");*/
}

/**
 * fo_table_get_border_bottom_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-style" property of @fo_fo.
 *
 * Return value: The "border-bottom-style" property value.
**/
FoProperty *
fo_table_get_border_bottom_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_bottom_style;
}

/**
 * fo_table_set_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style.
 **/
void
fo_table_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_bottom_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_table->border_bottom_style != NULL)
    {
      g_object_unref (fo_table->border_bottom_style);
    }
  fo_table->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-bottom-style");*/
}

/**
 * fo_table_get_border_bottom_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-width" property of @fo_fo.
 *
 * Return value: The "border-bottom-width" property value.
**/
FoProperty *
fo_table_get_border_bottom_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_bottom_width;
}

/**
 * fo_table_set_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width.
 **/
void
fo_table_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_bottom_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_table->border_bottom_width != NULL)
    {
      g_object_unref (fo_table->border_bottom_width);
    }
  fo_table->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-bottom-width");*/
}

/**
 * fo_table_get_border_collapse:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-collapse" property of @fo_fo.
 *
 * Return value: The "border-collapse" property value.
**/
FoProperty *
fo_table_get_border_collapse (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_collapse;
}

/**
 * fo_table_set_border_collapse:
 * @fo_fo: The #FoFo object.
 * @new_border_collapse: The new "border-collapse" property value.
 * 
 * Sets the "border-collapse" property of @fo_fo to @new_border_collapse.
 **/
void
fo_table_set_border_collapse (FoFo *fo_fo,
		         FoProperty *new_border_collapse)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_collapse == NULL) ||
		    FO_IS_PROPERTY_BORDER_COLLAPSE (new_border_collapse));

  if (new_border_collapse != NULL)
    {
      g_object_ref (new_border_collapse);
    }
  if (fo_table->border_collapse != NULL)
    {
      g_object_unref (fo_table->border_collapse);
    }
  fo_table->border_collapse = new_border_collapse;
  /*g_object_notify (G_OBJECT (fo_table), "border-collapse");*/
}

/**
 * fo_table_get_border_end_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-color" property of @fo_fo.
 *
 * Return value: The "border-end-color" property value.
**/
FoProperty *
fo_table_get_border_end_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_end_color;
}

/**
 * fo_table_set_border_end_color:
 * @fo_fo: The #FoFo object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color.
 **/
void
fo_table_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_end_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_table->border_end_color != NULL)
    {
      g_object_unref (fo_table->border_end_color);
    }
  fo_table->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-end-color");*/
}

/**
 * fo_table_get_border_end_precedence:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-precedence" property of @fo_fo.
 *
 * Return value: The "border-end-precedence" property value.
**/
FoProperty *
fo_table_get_border_end_precedence (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_end_precedence;
}

/**
 * fo_table_set_border_end_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_end_precedence: The new "border-end-precedence" property value.
 * 
 * Sets the "border-end-precedence" property of @fo_fo to @new_border_end_precedence.
 **/
void
fo_table_set_border_end_precedence (FoFo *fo_fo,
		         FoProperty *new_border_end_precedence)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_end_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_PRECEDENCE (new_border_end_precedence));

  if (new_border_end_precedence != NULL)
    {
      g_object_ref (new_border_end_precedence);
    }
  if (fo_table->border_end_precedence != NULL)
    {
      g_object_unref (fo_table->border_end_precedence);
    }
  fo_table->border_end_precedence = new_border_end_precedence;
  /*g_object_notify (G_OBJECT (fo_table), "border-end-precedence");*/
}

/**
 * fo_table_get_border_end_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-style" property of @fo_fo.
 *
 * Return value: The "border-end-style" property value.
**/
FoProperty *
fo_table_get_border_end_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_end_style;
}

/**
 * fo_table_set_border_end_style:
 * @fo_fo: The #FoFo object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style.
 **/
void
fo_table_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_end_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_table->border_end_style != NULL)
    {
      g_object_unref (fo_table->border_end_style);
    }
  fo_table->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-end-style");*/
}

/**
 * fo_table_get_border_end_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-width" property of @fo_fo.
 *
 * Return value: The "border-end-width" property value.
**/
FoProperty *
fo_table_get_border_end_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_end_width;
}

/**
 * fo_table_set_border_end_width:
 * @fo_fo: The #FoFo object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width.
 **/
void
fo_table_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_end_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_table->border_end_width != NULL)
    {
      g_object_unref (fo_table->border_end_width);
    }
  fo_table->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-end-width");*/
}

/**
 * fo_table_get_border_left_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-color" property of @fo_fo.
 *
 * Return value: The "border-left-color" property value.
**/
FoProperty *
fo_table_get_border_left_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_left_color;
}

/**
 * fo_table_set_border_left_color:
 * @fo_fo: The #FoFo object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color.
 **/
void
fo_table_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_left_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_table->border_left_color != NULL)
    {
      g_object_unref (fo_table->border_left_color);
    }
  fo_table->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-left-color");*/
}

/**
 * fo_table_get_border_left_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-style" property of @fo_fo.
 *
 * Return value: The "border-left-style" property value.
**/
FoProperty *
fo_table_get_border_left_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_left_style;
}

/**
 * fo_table_set_border_left_style:
 * @fo_fo: The #FoFo object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style.
 **/
void
fo_table_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_left_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_table->border_left_style != NULL)
    {
      g_object_unref (fo_table->border_left_style);
    }
  fo_table->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-left-style");*/
}

/**
 * fo_table_get_border_left_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-width" property of @fo_fo.
 *
 * Return value: The "border-left-width" property value.
**/
FoProperty *
fo_table_get_border_left_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_left_width;
}

/**
 * fo_table_set_border_left_width:
 * @fo_fo: The #FoFo object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width.
 **/
void
fo_table_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_left_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_table->border_left_width != NULL)
    {
      g_object_unref (fo_table->border_left_width);
    }
  fo_table->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-left-width");*/
}

/**
 * fo_table_get_border_right_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-color" property of @fo_fo.
 *
 * Return value: The "border-right-color" property value.
**/
FoProperty *
fo_table_get_border_right_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_right_color;
}

/**
 * fo_table_set_border_right_color:
 * @fo_fo: The #FoFo object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color.
 **/
void
fo_table_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_right_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_table->border_right_color != NULL)
    {
      g_object_unref (fo_table->border_right_color);
    }
  fo_table->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-right-color");*/
}

/**
 * fo_table_get_border_right_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-style" property of @fo_fo.
 *
 * Return value: The "border-right-style" property value.
**/
FoProperty *
fo_table_get_border_right_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_right_style;
}

/**
 * fo_table_set_border_right_style:
 * @fo_fo: The #FoFo object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style.
 **/
void
fo_table_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_right_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_table->border_right_style != NULL)
    {
      g_object_unref (fo_table->border_right_style);
    }
  fo_table->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-right-style");*/
}

/**
 * fo_table_get_border_right_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-width" property of @fo_fo.
 *
 * Return value: The "border-right-width" property value.
**/
FoProperty *
fo_table_get_border_right_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_right_width;
}

/**
 * fo_table_set_border_right_width:
 * @fo_fo: The #FoFo object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width.
 **/
void
fo_table_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_right_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_table->border_right_width != NULL)
    {
      g_object_unref (fo_table->border_right_width);
    }
  fo_table->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-right-width");*/
}

/**
 * fo_table_get_border_separation:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-separation" property of @fo_fo.
 *
 * Return value: The "border-separation" property value.
**/
FoProperty *
fo_table_get_border_separation (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_separation;
}

/**
 * fo_table_set_border_separation:
 * @fo_fo: The #FoFo object.
 * @new_border_separation: The new "border-separation" property value.
 * 
 * Sets the "border-separation" property of @fo_fo to @new_border_separation.
 **/
void
fo_table_set_border_separation (FoFo *fo_fo,
		         FoProperty *new_border_separation)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_separation == NULL) ||
		    FO_IS_PROPERTY_BORDER_SEPARATION (new_border_separation));

  if (new_border_separation != NULL)
    {
      g_object_ref (new_border_separation);
    }
  if (fo_table->border_separation != NULL)
    {
      g_object_unref (fo_table->border_separation);
    }
  fo_table->border_separation = new_border_separation;
  /*g_object_notify (G_OBJECT (fo_table), "border-separation");*/
}

/**
 * fo_table_get_border_start_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-color" property of @fo_fo.
 *
 * Return value: The "border-start-color" property value.
**/
FoProperty *
fo_table_get_border_start_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_start_color;
}

/**
 * fo_table_set_border_start_color:
 * @fo_fo: The #FoFo object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color.
 **/
void
fo_table_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_start_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_table->border_start_color != NULL)
    {
      g_object_unref (fo_table->border_start_color);
    }
  fo_table->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-start-color");*/
}

/**
 * fo_table_get_border_start_precedence:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-precedence" property of @fo_fo.
 *
 * Return value: The "border-start-precedence" property value.
**/
FoProperty *
fo_table_get_border_start_precedence (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_start_precedence;
}

/**
 * fo_table_set_border_start_precedence:
 * @fo_fo: The #FoFo object.
 * @new_border_start_precedence: The new "border-start-precedence" property value.
 * 
 * Sets the "border-start-precedence" property of @fo_fo to @new_border_start_precedence.
 **/
void
fo_table_set_border_start_precedence (FoFo *fo_fo,
		         FoProperty *new_border_start_precedence)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_start_precedence == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_PRECEDENCE (new_border_start_precedence));

  if (new_border_start_precedence != NULL)
    {
      g_object_ref (new_border_start_precedence);
    }
  if (fo_table->border_start_precedence != NULL)
    {
      g_object_unref (fo_table->border_start_precedence);
    }
  fo_table->border_start_precedence = new_border_start_precedence;
  /*g_object_notify (G_OBJECT (fo_table), "border-start-precedence");*/
}

/**
 * fo_table_get_border_start_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-style" property of @fo_fo.
 *
 * Return value: The "border-start-style" property value.
**/
FoProperty *
fo_table_get_border_start_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_start_style;
}

/**
 * fo_table_set_border_start_style:
 * @fo_fo: The #FoFo object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style.
 **/
void
fo_table_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_start_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_table->border_start_style != NULL)
    {
      g_object_unref (fo_table->border_start_style);
    }
  fo_table->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-start-style");*/
}

/**
 * fo_table_get_border_start_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-width" property of @fo_fo.
 *
 * Return value: The "border-start-width" property value.
**/
FoProperty *
fo_table_get_border_start_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_start_width;
}

/**
 * fo_table_set_border_start_width:
 * @fo_fo: The #FoFo object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width.
 **/
void
fo_table_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_start_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_table->border_start_width != NULL)
    {
      g_object_unref (fo_table->border_start_width);
    }
  fo_table->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-start-width");*/
}

/**
 * fo_table_get_border_top_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-color" property of @fo_fo.
 *
 * Return value: The "border-top-color" property value.
**/
FoProperty *
fo_table_get_border_top_color (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_top_color;
}

/**
 * fo_table_set_border_top_color:
 * @fo_fo: The #FoFo object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color.
 **/
void
fo_table_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_top_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_table->border_top_color != NULL)
    {
      g_object_unref (fo_table->border_top_color);
    }
  fo_table->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_table), "border-top-color");*/
}

/**
 * fo_table_get_border_top_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-style" property of @fo_fo.
 *
 * Return value: The "border-top-style" property value.
**/
FoProperty *
fo_table_get_border_top_style (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_top_style;
}

/**
 * fo_table_set_border_top_style:
 * @fo_fo: The #FoFo object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style.
 **/
void
fo_table_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_top_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_table->border_top_style != NULL)
    {
      g_object_unref (fo_table->border_top_style);
    }
  fo_table->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_table), "border-top-style");*/
}

/**
 * fo_table_get_border_top_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-width" property of @fo_fo.
 *
 * Return value: The "border-top-width" property value.
**/
FoProperty *
fo_table_get_border_top_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->border_top_width;
}

/**
 * fo_table_set_border_top_width:
 * @fo_fo: The #FoFo object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width.
 **/
void
fo_table_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_border_top_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_table->border_top_width != NULL)
    {
      g_object_unref (fo_table->border_top_width);
    }
  fo_table->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_table), "border-top-width");*/
}

/**
 * fo_table_get_break_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "break-after" property of @fo_fo.
 *
 * Return value: The "break-after" property value.
**/
FoProperty *
fo_table_get_break_after (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->break_after;
}

/**
 * fo_table_set_break_after:
 * @fo_fo: The #FoFo object.
 * @new_break_after: The new "break-after" property value.
 * 
 * Sets the "break-after" property of @fo_fo to @new_break_after.
 **/
void
fo_table_set_break_after (FoFo *fo_fo,
		         FoProperty *new_break_after)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_break_after == NULL) ||
		    FO_IS_PROPERTY_BREAK_AFTER (new_break_after));

  if (new_break_after != NULL)
    {
      g_object_ref (new_break_after);
    }
  if (fo_table->break_after != NULL)
    {
      g_object_unref (fo_table->break_after);
    }
  fo_table->break_after = new_break_after;
  /*g_object_notify (G_OBJECT (fo_table), "break-after");*/
}

/**
 * fo_table_get_break_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "break-before" property of @fo_fo.
 *
 * Return value: The "break-before" property value.
**/
FoProperty *
fo_table_get_break_before (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->break_before;
}

/**
 * fo_table_set_break_before:
 * @fo_fo: The #FoFo object.
 * @new_break_before: The new "break-before" property value.
 * 
 * Sets the "break-before" property of @fo_fo to @new_break_before.
 **/
void
fo_table_set_break_before (FoFo *fo_fo,
		         FoProperty *new_break_before)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_break_before == NULL) ||
		    FO_IS_PROPERTY_BREAK_BEFORE (new_break_before));

  if (new_break_before != NULL)
    {
      g_object_ref (new_break_before);
    }
  if (fo_table->break_before != NULL)
    {
      g_object_unref (fo_table->break_before);
    }
  fo_table->break_before = new_break_before;
  /*g_object_notify (G_OBJECT (fo_table), "break-before");*/
}

/**
 * fo_table_get_end_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "end-indent" property of @fo_fo.
 *
 * Return value: The "end-indent" property value.
**/
FoProperty *
fo_table_get_end_indent (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->end_indent;
}

/**
 * fo_table_set_end_indent:
 * @fo_fo: The #FoFo object.
 * @new_end_indent: The new "end-indent" property value.
 * 
 * Sets the "end-indent" property of @fo_fo to @new_end_indent.
 **/
void
fo_table_set_end_indent (FoFo *fo_fo,
		         FoProperty *new_end_indent)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_end_indent == NULL) ||
		    FO_IS_PROPERTY_END_INDENT (new_end_indent));

  if (new_end_indent != NULL)
    {
      g_object_ref (new_end_indent);
    }
  if (fo_table->end_indent != NULL)
    {
      g_object_unref (fo_table->end_indent);
    }
  fo_table->end_indent = new_end_indent;
  /*g_object_notify (G_OBJECT (fo_table), "end-indent");*/
}

/**
 * fo_table_get_height:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "height" property of @fo_fo.
 *
 * Return value: The "height" property value.
**/
FoProperty *
fo_table_get_height (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->height;
}

/**
 * fo_table_set_height:
 * @fo_fo: The #FoFo object.
 * @new_height: The new "height" property value.
 * 
 * Sets the "height" property of @fo_fo to @new_height.
 **/
void
fo_table_set_height (FoFo *fo_fo,
		         FoProperty *new_height)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_height == NULL) ||
		    FO_IS_PROPERTY_HEIGHT (new_height));

  if (new_height != NULL)
    {
      g_object_ref (new_height);
    }
  if (fo_table->height != NULL)
    {
      g_object_unref (fo_table->height);
    }
  fo_table->height = new_height;
  /*g_object_notify (G_OBJECT (fo_table), "height");*/
}

/**
 * fo_table_get_id:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_table_get_id (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->id;
}

/**
 * fo_table_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_table_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_id == NULL) ||
		    FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_table->id != NULL)
    {
      g_object_unref (fo_table->id);
    }
  fo_table->id = new_id;
  /*g_object_notify (G_OBJECT (fo_table), "id");*/
}

/**
 * fo_table_get_inline_progression_dimension:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "inline-progression-dimension" property of @fo_fo.
 *
 * Return value: The "inline-progression-dimension" property value.
**/
FoProperty *
fo_table_get_inline_progression_dimension (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->inline_progression_dimension;
}

/**
 * fo_table_set_inline_progression_dimension:
 * @fo_fo: The #FoFo object.
 * @new_inline_progression_dimension: The new "inline-progression-dimension" property value.
 * 
 * Sets the "inline-progression-dimension" property of @fo_fo to @new_inline_progression_dimension.
 **/
void
fo_table_set_inline_progression_dimension (FoFo *fo_fo,
		         FoProperty *new_inline_progression_dimension)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_inline_progression_dimension == NULL) ||
		    FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION (new_inline_progression_dimension));

  if (new_inline_progression_dimension != NULL)
    {
      g_object_ref (new_inline_progression_dimension);
    }
  if (fo_table->inline_progression_dimension != NULL)
    {
      g_object_unref (fo_table->inline_progression_dimension);
    }
  fo_table->inline_progression_dimension = new_inline_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_table), "inline-progression-dimension");*/
}

/**
 * fo_table_get_keep_together:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together" property of @fo_fo.
 *
 * Return value: The "keep-together" property value.
**/
FoProperty *
fo_table_get_keep_together (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_together;
}

/**
 * fo_table_set_keep_together:
 * @fo_fo: The #FoFo object.
 * @new_keep_together: The new "keep-together" property value.
 * 
 * Sets the "keep-together" property of @fo_fo to @new_keep_together.
 **/
void
fo_table_set_keep_together (FoFo *fo_fo,
		         FoProperty *new_keep_together)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_together == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER (new_keep_together));

  if (new_keep_together != NULL)
    {
      g_object_ref (new_keep_together);
    }
  if (fo_table->keep_together != NULL)
    {
      g_object_unref (fo_table->keep_together);
    }
  fo_table->keep_together = new_keep_together;
  /*g_object_notify (G_OBJECT (fo_table), "keep-together");*/
}

/**
 * fo_table_get_keep_together_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together-within-column" property of @fo_fo.
 *
 * Return value: The "keep-together-within-column" property value.
**/
FoProperty *
fo_table_get_keep_together_within_column (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_together_within_column;
}

/**
 * fo_table_set_keep_together_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_together_within_column: The new "keep-together-within-column" property value.
 * 
 * Sets the "keep-together-within-column" property of @fo_fo to @new_keep_together_within_column.
 **/
void
fo_table_set_keep_together_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_column)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_together_within_column == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (new_keep_together_within_column));

  if (new_keep_together_within_column != NULL)
    {
      g_object_ref (new_keep_together_within_column);
    }
  if (fo_table->keep_together_within_column != NULL)
    {
      g_object_unref (fo_table->keep_together_within_column);
    }
  fo_table->keep_together_within_column = new_keep_together_within_column;
  /*g_object_notify (G_OBJECT (fo_table), "keep-together-within-column");*/
}

/**
 * fo_table_get_keep_together_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together-within-line" property of @fo_fo.
 *
 * Return value: The "keep-together-within-line" property value.
**/
FoProperty *
fo_table_get_keep_together_within_line (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_together_within_line;
}

/**
 * fo_table_set_keep_together_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_together_within_line: The new "keep-together-within-line" property value.
 * 
 * Sets the "keep-together-within-line" property of @fo_fo to @new_keep_together_within_line.
 **/
void
fo_table_set_keep_together_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_line)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_together_within_line == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (new_keep_together_within_line));

  if (new_keep_together_within_line != NULL)
    {
      g_object_ref (new_keep_together_within_line);
    }
  if (fo_table->keep_together_within_line != NULL)
    {
      g_object_unref (fo_table->keep_together_within_line);
    }
  fo_table->keep_together_within_line = new_keep_together_within_line;
  /*g_object_notify (G_OBJECT (fo_table), "keep-together-within-line");*/
}

/**
 * fo_table_get_keep_together_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together-within-page" property of @fo_fo.
 *
 * Return value: The "keep-together-within-page" property value.
**/
FoProperty *
fo_table_get_keep_together_within_page (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_together_within_page;
}

/**
 * fo_table_set_keep_together_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_together_within_page: The new "keep-together-within-page" property value.
 * 
 * Sets the "keep-together-within-page" property of @fo_fo to @new_keep_together_within_page.
 **/
void
fo_table_set_keep_together_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_page)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_together_within_page == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (new_keep_together_within_page));

  if (new_keep_together_within_page != NULL)
    {
      g_object_ref (new_keep_together_within_page);
    }
  if (fo_table->keep_together_within_page != NULL)
    {
      g_object_unref (fo_table->keep_together_within_page);
    }
  fo_table->keep_together_within_page = new_keep_together_within_page;
  /*g_object_notify (G_OBJECT (fo_table), "keep-together-within-page");*/
}

/**
 * fo_table_get_keep_with_next:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next" property of @fo_fo.
 *
 * Return value: The "keep-with-next" property value.
**/
FoProperty *
fo_table_get_keep_with_next (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_next;
}

/**
 * fo_table_set_keep_with_next:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next: The new "keep-with-next" property value.
 * 
 * Sets the "keep-with-next" property of @fo_fo to @new_keep_with_next.
 **/
void
fo_table_set_keep_with_next (FoFo *fo_fo,
		         FoProperty *new_keep_with_next)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_next == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT (new_keep_with_next));

  if (new_keep_with_next != NULL)
    {
      g_object_ref (new_keep_with_next);
    }
  if (fo_table->keep_with_next != NULL)
    {
      g_object_unref (fo_table->keep_with_next);
    }
  fo_table->keep_with_next = new_keep_with_next;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-next");*/
}

/**
 * fo_table_get_keep_with_next_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-column" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-column" property value.
**/
FoProperty *
fo_table_get_keep_with_next_within_column (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_next_within_column;
}

/**
 * fo_table_set_keep_with_next_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_column: The new "keep-with-next-within-column" property value.
 * 
 * Sets the "keep-with-next-within-column" property of @fo_fo to @new_keep_with_next_within_column.
 **/
void
fo_table_set_keep_with_next_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_column)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_next_within_column == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (new_keep_with_next_within_column));

  if (new_keep_with_next_within_column != NULL)
    {
      g_object_ref (new_keep_with_next_within_column);
    }
  if (fo_table->keep_with_next_within_column != NULL)
    {
      g_object_unref (fo_table->keep_with_next_within_column);
    }
  fo_table->keep_with_next_within_column = new_keep_with_next_within_column;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-next-within-column");*/
}

/**
 * fo_table_get_keep_with_next_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-line" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-line" property value.
**/
FoProperty *
fo_table_get_keep_with_next_within_line (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_next_within_line;
}

/**
 * fo_table_set_keep_with_next_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_line: The new "keep-with-next-within-line" property value.
 * 
 * Sets the "keep-with-next-within-line" property of @fo_fo to @new_keep_with_next_within_line.
 **/
void
fo_table_set_keep_with_next_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_line)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_next_within_line == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (new_keep_with_next_within_line));

  if (new_keep_with_next_within_line != NULL)
    {
      g_object_ref (new_keep_with_next_within_line);
    }
  if (fo_table->keep_with_next_within_line != NULL)
    {
      g_object_unref (fo_table->keep_with_next_within_line);
    }
  fo_table->keep_with_next_within_line = new_keep_with_next_within_line;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-next-within-line");*/
}

/**
 * fo_table_get_keep_with_next_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-page" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-page" property value.
**/
FoProperty *
fo_table_get_keep_with_next_within_page (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_next_within_page;
}

/**
 * fo_table_set_keep_with_next_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_page: The new "keep-with-next-within-page" property value.
 * 
 * Sets the "keep-with-next-within-page" property of @fo_fo to @new_keep_with_next_within_page.
 **/
void
fo_table_set_keep_with_next_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_page)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_next_within_page == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (new_keep_with_next_within_page));

  if (new_keep_with_next_within_page != NULL)
    {
      g_object_ref (new_keep_with_next_within_page);
    }
  if (fo_table->keep_with_next_within_page != NULL)
    {
      g_object_unref (fo_table->keep_with_next_within_page);
    }
  fo_table->keep_with_next_within_page = new_keep_with_next_within_page;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-next-within-page");*/
}

/**
 * fo_table_get_keep_with_previous:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous" property of @fo_fo.
 *
 * Return value: The "keep-with-previous" property value.
**/
FoProperty *
fo_table_get_keep_with_previous (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_previous;
}

/**
 * fo_table_set_keep_with_previous:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous: The new "keep-with-previous" property value.
 * 
 * Sets the "keep-with-previous" property of @fo_fo to @new_keep_with_previous.
 **/
void
fo_table_set_keep_with_previous (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_previous == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (new_keep_with_previous));

  if (new_keep_with_previous != NULL)
    {
      g_object_ref (new_keep_with_previous);
    }
  if (fo_table->keep_with_previous != NULL)
    {
      g_object_unref (fo_table->keep_with_previous);
    }
  fo_table->keep_with_previous = new_keep_with_previous;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-previous");*/
}

/**
 * fo_table_get_keep_with_previous_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-column" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-column" property value.
**/
FoProperty *
fo_table_get_keep_with_previous_within_column (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_previous_within_column;
}

/**
 * fo_table_set_keep_with_previous_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_column: The new "keep-with-previous-within-column" property value.
 * 
 * Sets the "keep-with-previous-within-column" property of @fo_fo to @new_keep_with_previous_within_column.
 **/
void
fo_table_set_keep_with_previous_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_column)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_previous_within_column == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (new_keep_with_previous_within_column));

  if (new_keep_with_previous_within_column != NULL)
    {
      g_object_ref (new_keep_with_previous_within_column);
    }
  if (fo_table->keep_with_previous_within_column != NULL)
    {
      g_object_unref (fo_table->keep_with_previous_within_column);
    }
  fo_table->keep_with_previous_within_column = new_keep_with_previous_within_column;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-previous-within-column");*/
}

/**
 * fo_table_get_keep_with_previous_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-line" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-line" property value.
**/
FoProperty *
fo_table_get_keep_with_previous_within_line (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_previous_within_line;
}

/**
 * fo_table_set_keep_with_previous_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_line: The new "keep-with-previous-within-line" property value.
 * 
 * Sets the "keep-with-previous-within-line" property of @fo_fo to @new_keep_with_previous_within_line.
 **/
void
fo_table_set_keep_with_previous_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_line)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_previous_within_line == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (new_keep_with_previous_within_line));

  if (new_keep_with_previous_within_line != NULL)
    {
      g_object_ref (new_keep_with_previous_within_line);
    }
  if (fo_table->keep_with_previous_within_line != NULL)
    {
      g_object_unref (fo_table->keep_with_previous_within_line);
    }
  fo_table->keep_with_previous_within_line = new_keep_with_previous_within_line;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-previous-within-line");*/
}

/**
 * fo_table_get_keep_with_previous_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-page" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-page" property value.
**/
FoProperty *
fo_table_get_keep_with_previous_within_page (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->keep_with_previous_within_page;
}

/**
 * fo_table_set_keep_with_previous_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_page: The new "keep-with-previous-within-page" property value.
 * 
 * Sets the "keep-with-previous-within-page" property of @fo_fo to @new_keep_with_previous_within_page.
 **/
void
fo_table_set_keep_with_previous_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_page)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_keep_with_previous_within_page == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (new_keep_with_previous_within_page));

  if (new_keep_with_previous_within_page != NULL)
    {
      g_object_ref (new_keep_with_previous_within_page);
    }
  if (fo_table->keep_with_previous_within_page != NULL)
    {
      g_object_unref (fo_table->keep_with_previous_within_page);
    }
  fo_table->keep_with_previous_within_page = new_keep_with_previous_within_page;
  /*g_object_notify (G_OBJECT (fo_table), "keep-with-previous-within-page");*/
}

/**
 * fo_table_get_margin_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-bottom" property of @fo_fo.
 *
 * Return value: The "margin-bottom" property value.
**/
FoProperty *
fo_table_get_margin_bottom (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->margin_bottom;
}

/**
 * fo_table_set_margin_bottom:
 * @fo_fo: The #FoFo object.
 * @new_margin_bottom: The new "margin-bottom" property value.
 * 
 * Sets the "margin-bottom" property of @fo_fo to @new_margin_bottom.
 **/
void
fo_table_set_margin_bottom (FoFo *fo_fo,
		         FoProperty *new_margin_bottom)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_margin_bottom == NULL) ||
		    FO_IS_PROPERTY_MARGIN_BOTTOM (new_margin_bottom));

  if (new_margin_bottom != NULL)
    {
      g_object_ref (new_margin_bottom);
    }
  if (fo_table->margin_bottom != NULL)
    {
      g_object_unref (fo_table->margin_bottom);
    }
  fo_table->margin_bottom = new_margin_bottom;
  /*g_object_notify (G_OBJECT (fo_table), "margin-bottom");*/
}

/**
 * fo_table_get_margin_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-left" property of @fo_fo.
 *
 * Return value: The "margin-left" property value.
**/
FoProperty *
fo_table_get_margin_left (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->margin_left;
}

/**
 * fo_table_set_margin_left:
 * @fo_fo: The #FoFo object.
 * @new_margin_left: The new "margin-left" property value.
 * 
 * Sets the "margin-left" property of @fo_fo to @new_margin_left.
 **/
void
fo_table_set_margin_left (FoFo *fo_fo,
		         FoProperty *new_margin_left)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_margin_left == NULL) ||
		    FO_IS_PROPERTY_MARGIN_LEFT (new_margin_left));

  if (new_margin_left != NULL)
    {
      g_object_ref (new_margin_left);
    }
  if (fo_table->margin_left != NULL)
    {
      g_object_unref (fo_table->margin_left);
    }
  fo_table->margin_left = new_margin_left;
  /*g_object_notify (G_OBJECT (fo_table), "margin-left");*/
}

/**
 * fo_table_get_margin_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-right" property of @fo_fo.
 *
 * Return value: The "margin-right" property value.
**/
FoProperty *
fo_table_get_margin_right (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->margin_right;
}

/**
 * fo_table_set_margin_right:
 * @fo_fo: The #FoFo object.
 * @new_margin_right: The new "margin-right" property value.
 * 
 * Sets the "margin-right" property of @fo_fo to @new_margin_right.
 **/
void
fo_table_set_margin_right (FoFo *fo_fo,
		         FoProperty *new_margin_right)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_margin_right == NULL) ||
		    FO_IS_PROPERTY_MARGIN_RIGHT (new_margin_right));

  if (new_margin_right != NULL)
    {
      g_object_ref (new_margin_right);
    }
  if (fo_table->margin_right != NULL)
    {
      g_object_unref (fo_table->margin_right);
    }
  fo_table->margin_right = new_margin_right;
  /*g_object_notify (G_OBJECT (fo_table), "margin-right");*/
}

/**
 * fo_table_get_margin_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-top" property of @fo_fo.
 *
 * Return value: The "margin-top" property value.
**/
FoProperty *
fo_table_get_margin_top (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->margin_top;
}

/**
 * fo_table_set_margin_top:
 * @fo_fo: The #FoFo object.
 * @new_margin_top: The new "margin-top" property value.
 * 
 * Sets the "margin-top" property of @fo_fo to @new_margin_top.
 **/
void
fo_table_set_margin_top (FoFo *fo_fo,
		         FoProperty *new_margin_top)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_margin_top == NULL) ||
		    FO_IS_PROPERTY_MARGIN_TOP (new_margin_top));

  if (new_margin_top != NULL)
    {
      g_object_ref (new_margin_top);
    }
  if (fo_table->margin_top != NULL)
    {
      g_object_unref (fo_table->margin_top);
    }
  fo_table->margin_top = new_margin_top;
  /*g_object_notify (G_OBJECT (fo_table), "margin-top");*/
}

/**
 * fo_table_get_padding_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-after" property of @fo_fo.
 *
 * Return value: The "padding-after" property value.
**/
FoProperty *
fo_table_get_padding_after (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_after;
}

/**
 * fo_table_set_padding_after:
 * @fo_fo: The #FoFo object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after.
 **/
void
fo_table_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_after == NULL) ||
		    FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_table->padding_after != NULL)
    {
      g_object_unref (fo_table->padding_after);
    }
  fo_table->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_table), "padding-after");*/
}

/**
 * fo_table_get_padding_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-before" property of @fo_fo.
 *
 * Return value: The "padding-before" property value.
**/
FoProperty *
fo_table_get_padding_before (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_before;
}

/**
 * fo_table_set_padding_before:
 * @fo_fo: The #FoFo object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before.
 **/
void
fo_table_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_before == NULL) ||
		    FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_table->padding_before != NULL)
    {
      g_object_unref (fo_table->padding_before);
    }
  fo_table->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_table), "padding-before");*/
}

/**
 * fo_table_get_padding_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-bottom" property of @fo_fo.
 *
 * Return value: The "padding-bottom" property value.
**/
FoProperty *
fo_table_get_padding_bottom (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_bottom;
}

/**
 * fo_table_set_padding_bottom:
 * @fo_fo: The #FoFo object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom.
 **/
void
fo_table_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_bottom == NULL) ||
		    FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_table->padding_bottom != NULL)
    {
      g_object_unref (fo_table->padding_bottom);
    }
  fo_table->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_table), "padding-bottom");*/
}

/**
 * fo_table_get_padding_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-end" property of @fo_fo.
 *
 * Return value: The "padding-end" property value.
**/
FoProperty *
fo_table_get_padding_end (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_end;
}

/**
 * fo_table_set_padding_end:
 * @fo_fo: The #FoFo object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end.
 **/
void
fo_table_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_end == NULL) ||
		    FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_table->padding_end != NULL)
    {
      g_object_unref (fo_table->padding_end);
    }
  fo_table->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_table), "padding-end");*/
}

/**
 * fo_table_get_padding_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-left" property of @fo_fo.
 *
 * Return value: The "padding-left" property value.
**/
FoProperty *
fo_table_get_padding_left (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_left;
}

/**
 * fo_table_set_padding_left:
 * @fo_fo: The #FoFo object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left.
 **/
void
fo_table_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_left == NULL) ||
		    FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_table->padding_left != NULL)
    {
      g_object_unref (fo_table->padding_left);
    }
  fo_table->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_table), "padding-left");*/
}

/**
 * fo_table_get_padding_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-right" property of @fo_fo.
 *
 * Return value: The "padding-right" property value.
**/
FoProperty *
fo_table_get_padding_right (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_right;
}

/**
 * fo_table_set_padding_right:
 * @fo_fo: The #FoFo object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right.
 **/
void
fo_table_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_right == NULL) ||
		    FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_table->padding_right != NULL)
    {
      g_object_unref (fo_table->padding_right);
    }
  fo_table->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_table), "padding-right");*/
}

/**
 * fo_table_get_padding_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-start" property of @fo_fo.
 *
 * Return value: The "padding-start" property value.
**/
FoProperty *
fo_table_get_padding_start (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_start;
}

/**
 * fo_table_set_padding_start:
 * @fo_fo: The #FoFo object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start.
 **/
void
fo_table_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_start == NULL) ||
		    FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_table->padding_start != NULL)
    {
      g_object_unref (fo_table->padding_start);
    }
  fo_table->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_table), "padding-start");*/
}

/**
 * fo_table_get_padding_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-top" property of @fo_fo.
 *
 * Return value: The "padding-top" property value.
**/
FoProperty *
fo_table_get_padding_top (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->padding_top;
}

/**
 * fo_table_set_padding_top:
 * @fo_fo: The #FoFo object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top.
 **/
void
fo_table_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_padding_top == NULL) ||
		    FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_table->padding_top != NULL)
    {
      g_object_unref (fo_table->padding_top);
    }
  fo_table->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_table), "padding-top");*/
}

/**
 * fo_table_get_role:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "role" property of @fo_fo.
 *
 * Return value: The "role" property value.
**/
FoProperty *
fo_table_get_role (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->role;
}

/**
 * fo_table_set_role:
 * @fo_fo: The #FoFo object.
 * @new_role: The new "role" property value.
 * 
 * Sets the "role" property of @fo_fo to @new_role.
 **/
void
fo_table_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_role == NULL) ||
		    FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_table->role != NULL)
    {
      g_object_unref (fo_table->role);
    }
  fo_table->role = new_role;
  /*g_object_notify (G_OBJECT (fo_table), "role");*/
}

/**
 * fo_table_get_source_document:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "source-document" property of @fo_fo.
 *
 * Return value: The "source-document" property value.
**/
FoProperty *
fo_table_get_source_document (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->source_document;
}

/**
 * fo_table_set_source_document:
 * @fo_fo: The #FoFo object.
 * @new_source_document: The new "source-document" property value.
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document.
 **/
void
fo_table_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_source_document == NULL) ||
		    FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_table->source_document != NULL)
    {
      g_object_unref (fo_table->source_document);
    }
  fo_table->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_table), "source-document");*/
}

/**
 * fo_table_get_space_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-after" property of @fo_fo.
 *
 * Return value: The "space-after" property value.
**/
FoProperty *
fo_table_get_space_after (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->space_after;
}

/**
 * fo_table_set_space_after:
 * @fo_fo: The #FoFo object.
 * @new_space_after: The new "space-after" property value.
 * 
 * Sets the "space-after" property of @fo_fo to @new_space_after.
 **/
void
fo_table_set_space_after (FoFo *fo_fo,
		         FoProperty *new_space_after)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_space_after == NULL) ||
		    FO_IS_PROPERTY_SPACE_AFTER (new_space_after));

  if (new_space_after != NULL)
    {
      g_object_ref (new_space_after);
    }
  if (fo_table->space_after != NULL)
    {
      g_object_unref (fo_table->space_after);
    }
  fo_table->space_after = new_space_after;
  /*g_object_notify (G_OBJECT (fo_table), "space-after");*/
}

/**
 * fo_table_get_space_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-before" property of @fo_fo.
 *
 * Return value: The "space-before" property value.
**/
FoProperty *
fo_table_get_space_before (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->space_before;
}

/**
 * fo_table_set_space_before:
 * @fo_fo: The #FoFo object.
 * @new_space_before: The new "space-before" property value.
 * 
 * Sets the "space-before" property of @fo_fo to @new_space_before.
 **/
void
fo_table_set_space_before (FoFo *fo_fo,
		         FoProperty *new_space_before)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_space_before == NULL) ||
		    FO_IS_PROPERTY_SPACE_BEFORE (new_space_before));

  if (new_space_before != NULL)
    {
      g_object_ref (new_space_before);
    }
  if (fo_table->space_before != NULL)
    {
      g_object_unref (fo_table->space_before);
    }
  fo_table->space_before = new_space_before;
  /*g_object_notify (G_OBJECT (fo_table), "space-before");*/
}

/**
 * fo_table_get_start_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "start-indent" property of @fo_fo.
 *
 * Return value: The "start-indent" property value.
**/
FoProperty *
fo_table_get_start_indent (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->start_indent;
}

/**
 * fo_table_set_start_indent:
 * @fo_fo: The #FoFo object.
 * @new_start_indent: The new "start-indent" property value.
 * 
 * Sets the "start-indent" property of @fo_fo to @new_start_indent.
 **/
void
fo_table_set_start_indent (FoFo *fo_fo,
		         FoProperty *new_start_indent)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_start_indent == NULL) ||
		    FO_IS_PROPERTY_START_INDENT (new_start_indent));

  if (new_start_indent != NULL)
    {
      g_object_ref (new_start_indent);
    }
  if (fo_table->start_indent != NULL)
    {
      g_object_unref (fo_table->start_indent);
    }
  fo_table->start_indent = new_start_indent;
  /*g_object_notify (G_OBJECT (fo_table), "start-indent");*/
}

/**
 * fo_table_get_table_layout:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "table-layout" property of @fo_fo.
 *
 * Return value: The "table-layout" property value.
**/
FoProperty *
fo_table_get_table_layout (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->table_layout;
}

/**
 * fo_table_set_table_layout:
 * @fo_fo: The #FoFo object.
 * @new_table_layout: The new "table-layout" property value.
 * 
 * Sets the "table-layout" property of @fo_fo to @new_table_layout.
 **/
void
fo_table_set_table_layout (FoFo *fo_fo,
		         FoProperty *new_table_layout)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_table_layout == NULL) ||
		    FO_IS_PROPERTY_TABLE_LAYOUT (new_table_layout));

  if (new_table_layout != NULL)
    {
      g_object_ref (new_table_layout);
    }
  if (fo_table->table_layout != NULL)
    {
      g_object_unref (fo_table->table_layout);
    }
  fo_table->table_layout = new_table_layout;
  /*g_object_notify (G_OBJECT (fo_table), "table-layout");*/
}

/**
 * fo_table_get_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "width" property of @fo_fo.
 *
 * Return value: The "width" property value.
**/
FoProperty *
fo_table_get_width (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->width;
}

/**
 * fo_table_set_width:
 * @fo_fo: The #FoFo object.
 * @new_width: The new "width" property value.
 * 
 * Sets the "width" property of @fo_fo to @new_width.
 **/
void
fo_table_set_width (FoFo *fo_fo,
		         FoProperty *new_width)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_width == NULL) ||
		    FO_IS_PROPERTY_WIDTH (new_width));

  if (new_width != NULL)
    {
      g_object_ref (new_width);
    }
  if (fo_table->width != NULL)
    {
      g_object_unref (fo_table->width);
    }
  fo_table->width = new_width;
  /*g_object_notify (G_OBJECT (fo_table), "width");*/
}

/**
 * fo_table_get_writing_mode:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "writing-mode" property of @fo_fo.
 *
 * Return value: The "writing-mode" property value.
**/
FoProperty *
fo_table_get_writing_mode (FoFo *fo_fo)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_val_if_fail (fo_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE (fo_table), NULL);

  return fo_table->writing_mode;
}

/**
 * fo_table_set_writing_mode:
 * @fo_fo: The #FoFo object.
 * @new_writing_mode: The new "writing-mode" property value.
 * 
 * Sets the "writing-mode" property of @fo_fo to @new_writing_mode.
 **/
void
fo_table_set_writing_mode (FoFo *fo_fo,
		         FoProperty *new_writing_mode)
{
  FoTable *fo_table = (FoTable *) fo_fo;

  g_return_if_fail (fo_table != NULL);
  g_return_if_fail (FO_IS_TABLE (fo_table));
  g_return_if_fail ((new_writing_mode == NULL) ||
		    FO_IS_PROPERTY_WRITING_MODE (new_writing_mode));

  if (new_writing_mode != NULL)
    {
      g_object_ref (new_writing_mode);
    }
  if (fo_table->writing_mode != NULL)
    {
      g_object_unref (fo_table->writing_mode);
    }
  fo_table->writing_mode = new_writing_mode;
  /*g_object_notify (G_OBJECT (fo_table), "writing-mode");*/
}
