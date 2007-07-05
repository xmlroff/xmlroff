/* Fo
 * fo-property-keep-together-within-column.h: 'keep-together-within-column' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN_H__
#define __FO_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* keep-together-within-column */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

#define FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN              (fo_property_keep_together_within_column_get_type ())
#define FO_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN, FoPropertyKeepTogetherWithinColumn))
#define FO_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN, FoPropertyKeepTogetherWithinColumnClass))
#define FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN))
#define FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN))
#define FO_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN, FoPropertyKeepTogetherWithinColumnClass))


typedef struct _FoPropertyKeepTogetherWithinColumn      FoPropertyKeepTogetherWithinColumn;
typedef struct _FoPropertyKeepTogetherWithinColumnClass FoPropertyKeepTogetherWithinColumnClass;

GType       fo_property_keep_together_within_column_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_keep_together_within_column_new         (void);
FoProperty* fo_property_keep_together_within_column_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN_H__ */
