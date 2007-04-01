/* Fo
 * fo-footnote-body-private.h: Structures private to 'footnote-body' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-footnote-body-private.h,v 1.2 2004/03/24 11:52:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_FOOTNOTE_BODY_PRIVATE_H__
#define __FO_FOOTNOTE_BODY_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-footnote-body.h"

G_BEGIN_DECLS

struct _FoFootnoteBody
{
  FoFo parent_instance;

  FoProperty *role;
  FoProperty *source_document;
};

struct _FoFootnoteBodyClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_FOOTNOTE_BODY_PRIVATE_H__ */
