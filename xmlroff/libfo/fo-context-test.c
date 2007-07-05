/* Fo
 * fo-context-test.c: Test FoContext object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
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
