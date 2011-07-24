/* Fo
 * fo-enum.h: Enum datatype
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ENUM_PRIVATE_H__
#define __FO_ENUM_PRIVATE_H__

#include <libfo/datatype/fo-enum.h>

G_BEGIN_DECLS

FoDatatype * fo_enum_new            (void);
FoDatatype * fo_enum_new_with_value (const GEnumClass *enum_class,
				     const FoEnumEnum  value);

G_END_DECLS

#endif /* !__FO_ENUM_PRIVATE_H__ */
