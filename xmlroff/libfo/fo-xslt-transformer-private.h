/* Fo
 * fo-xslt-transformer-private: Boxed object type for libxslt XSLT processor
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-xslt-transformer-private.h,v 1.2 2006/05/28 23:11:45 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_XSLT_TRANSFORMER_PRIVATE_H__
#define __FO_XSLT_TRANSFORMER_PRIVATE_H__

#include <libxml/tree.h>
#include "libfo/fo-xslt-transformer.h"

G_BEGIN_DECLS

xmlDocPtr fo_xslt_transformer_get_result (FoXmlDoc *fo_xslt_transformer);

#endif /* !__FO_XSLT_TRANSFORMER_PRIVATE_H__ */
