/* Fo
 * fo-table-part.h: Part-level table formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TABLE_PART_H__
#define __FO_TABLE_PART_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoTablePart      FoTablePart;
typedef struct _FoTablePartClass FoTablePartClass;

#define FO_TYPE_TABLE_PART              (fo_table_part_get_type ())
#define FO_TABLE_PART(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TABLE_PART, FoTablePart))
#define FO_TABLE_PART_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TABLE_PART, FoTablePartClass))
#define FO_IS_TABLE_PART(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TABLE_PART))
#define FO_IS_TABLE_PART_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TABLE_PART))
#define FO_TABLE_PART_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TABLE_PART, FoTablePartClass))


GType         fo_table_part_get_type      (void) G_GNUC_CONST;
FoFo *fo_table_part_new (void);

void fo_table_part_update_from_context (FoFo *fo,
				   FoContext *context);

G_END_DECLS

#endif /* !__FO_TABLE_PART_H__ */
