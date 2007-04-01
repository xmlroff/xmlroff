/* Fo
 * fo-context-test.c: Test FoContext object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-context-test.c,v 1.1.1.1 2003/02/13 00:51:16 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
  FoContext *context;

  g_type_init();

  g_print("fo-context\n");

  context = fo_context_new();

  exit(0);
}
