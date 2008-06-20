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

#include <CUnit/Basic.h>
#include <libfo/fo-libfo-basic.h>
#include <libfo/fo-doc.h>
#include <libfo/fo-doc-gp.h>
#include <libfo/fo-doc-cairo.h>
#include <cairo/cairo.h>

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
test_fo_doc_new_finalize (void)
{
  FoDoc *doc = fo_doc_new();

  g_object_unref (doc);
}

static void
test_fo_doc_formats (void)
{
  CU_ASSERT_EQUAL (fo_doc_formats_from_name (NULL),
		   FO_FLAG_FORMAT_UNKNOWN);

  CU_ASSERT_EQUAL (fo_doc_formats_from_name ("bogus"),
		   FO_FLAG_FORMAT_UNKNOWN);

  /* Class that is not a FoDoc subtype should return unknown
     format. */
  CU_ASSERT_EQUAL (fo_doc_formats_from_name (g_type_name (fo_object_get_type ())),
		   FO_FLAG_FORMAT_UNKNOWN);

  CU_ASSERT_EQUAL (fo_doc_formats_from_name (g_type_name (fo_doc_get_type ())),
		   FO_FLAG_FORMAT_UNKNOWN);

  CU_ASSERT_EQUAL (fo_doc_formats_from_name (g_type_name (fo_doc_cairo_get_type ())),
		   ( FO_FLAG_FORMAT_PDF |
		     FO_FLAG_FORMAT_POSTSCRIPT |
		     FO_FLAG_FORMAT_SVG ));

  CU_ASSERT_EQUAL (fo_doc_formats_from_name (g_type_name (fo_doc_gp_get_type ())),
		   ( FO_FLAG_FORMAT_PDF |
		     FO_FLAG_FORMAT_POSTSCRIPT |
		     FO_FLAG_FORMAT_SVG ));
}

static void
test_fo_doc_version (void)
{
  CU_ASSERT_EQUAL (fo_doc_version_from_name (NULL),
		   0);

  CU_ASSERT_EQUAL (fo_doc_version_from_name ("bogus"),
		   0);

  /* Class that is not a FoDoc subtype should return unknown
     format. */
  CU_ASSERT_EQUAL (fo_doc_version_from_name (g_type_name (fo_object_get_type ())),
		   0);

  CU_ASSERT_EQUAL (fo_doc_version_from_name (g_type_name (fo_doc_get_type ())),
		   0);

  CU_ASSERT_EQUAL (fo_doc_version_from_name (g_type_name (fo_doc_cairo_get_type ())),
		   cairo_version ());

  CU_ASSERT_EQUAL (fo_doc_version_from_name (g_type_name (fo_doc_gp_get_type ())),
		   0);
}

static CU_TestInfo test_array[] = {
  { "FoDoc new and finalize",
    test_fo_doc_new_finalize },
  { "FoDoc get formats",
    test_fo_doc_formats },
  { "FoDoc get version",
    test_fo_doc_version },
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  { "fo-doc", init_suite, clean_suite, test_array },
  CU_SUITE_INFO_NULL,
};

CU_SuiteInfo *
test_fo_doc_get_suites (void)
{
  return suites;
}

