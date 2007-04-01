/* Fo
 * fo-table-header-private.h: Structures private to 'table-header' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-header-private.h,v 1.3 2004/03/30 22:45:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_TABLE_HEADER_PRIVATE_H__
#define __FO_TABLE_HEADER_PRIVATE_H__

#include "fo/fo-table-part-private.h"
#include "fo/fo-table-header.h"

G_BEGIN_DECLS

struct _FoTableHeader
{
  FoTablePart parent_instance;

  FoProperty *background_color;
  FoProperty *background_image;
  FoProperty *border_after_color;
  FoProperty *border_after_precedence;
  FoProperty *border_after_style;
  FoProperty *border_after_width;
  FoProperty *border_before_color;
  FoProperty *border_before_precedence;
  FoProperty *border_before_style;
  FoProperty *border_before_width;
  FoProperty *border_bottom_color;
  FoProperty *border_bottom_style;
  FoProperty *border_bottom_width;
  FoProperty *border_end_color;
  FoProperty *border_end_precedence;
  FoProperty *border_end_style;
  FoProperty *border_end_width;
  FoProperty *border_left_color;
  FoProperty *border_left_style;
  FoProperty *border_left_width;
  FoProperty *border_right_color;
  FoProperty *border_right_style;
  FoProperty *border_right_width;
  FoProperty *border_start_color;
  FoProperty *border_start_precedence;
  FoProperty *border_start_style;
  FoProperty *border_start_width;
  FoProperty *border_top_color;
  FoProperty *border_top_style;
  FoProperty *border_top_width;
  FoProperty *id;
  FoProperty *padding_after;
  FoProperty *padding_before;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_top;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoTableHeaderClass
{
  FoTablePartClass parent_class;
};

G_END_DECLS

#endif /* !__FO_TABLE_HEADER_PRIVATE_H__ */
