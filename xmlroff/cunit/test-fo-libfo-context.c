/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include "CUnit/Basic.h"
#include <libfo/fo-libfo-basic.h>
#include <libfo/fo-libfo-context.h>

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
static int
init_suite (void)
{
  fo_libfo_init ();

  return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
static int
clean_suite (void)
{
  fo_libfo_shutdown ();

  return 0;
}

static void
test_fo_libfo_context_new_finalize (void)
{
  FoLibfoContext *context = fo_libfo_context_new();

  g_object_unref (context);
}

static void
test_fo_libfo_context_format (void)
{
  FoLibfoContext *context = fo_libfo_context_new();

  /* Setting to multiple formats is not a good idea. */
  fo_libfo_context_set_format (context,
			       FO_FLAG_FORMAT_PDF | FO_FLAG_FORMAT_SVG);

  /* fo_libfo_context_set_format should use the first (lowest) value
     if more than one flag bit is set. */
  CU_ASSERT_EQUAL (fo_libfo_context_get_format (context),
		   MIN (FO_FLAG_FORMAT_PDF,
			FO_FLAG_FORMAT_SVG));

  CU_ASSERT_NOT_EQUAL (fo_libfo_context_get_format (context),
		       MAX (FO_FLAG_FORMAT_PDF,
			    FO_FLAG_FORMAT_SVG));

  g_object_unref (context);
}

static void
test_fo_libfo_context_font_embed (void)
{
  FoLibfoContext *context = fo_libfo_context_new();

  fo_libfo_context_set_font_embed (context,
			     FO_ENUM_FONT_EMBED_NONBASE);

  CU_ASSERT_EQUAL (fo_libfo_context_get_font_embed (context),
		   FO_ENUM_FONT_EMBED_NONBASE);

  g_object_unref (context);
}

static CU_TestInfo test_array[] = {
  { "FoLibfoContext new and finalize",
    test_fo_libfo_context_new_finalize },
  { "FoLibfoContext set and get format",
    test_fo_libfo_context_format },
  { "FoLibfoContext set and get font embedding",
    test_fo_libfo_context_font_embed },
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  { "fo-libfo-context", init_suite, clean_suite, test_array },
  CU_SUITE_INFO_NULL,
};

CU_SuiteInfo *
test_fo_libfo_context_get_suites (void)
{
  return suites;
}

