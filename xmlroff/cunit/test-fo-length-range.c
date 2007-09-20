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
#include <libfo/datatype/fo-length.h>
#include <libfo/datatype/fo-length-range.h>

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
test_fo_length_range_copy (void)
{
  FoDatatype *length_range_1 =
    g_object_ref (fo_length_range_new_with_value (fo_length_get_length_3pt ()));
  FoDatatype *length_range_2 =
    g_object_ref (fo_datatype_copy (length_range_1));

  CU_ASSERT_EQUAL (fo_length_get_value (fo_length_get_length_3pt ()),
		   fo_length_get_value (fo_length_range_get_minimum (length_range_2)));
  CU_ASSERT_EQUAL (fo_length_get_value (fo_length_get_length_3pt ()),
		   fo_length_get_value (fo_length_range_get_optimum (length_range_2)));
  CU_ASSERT_EQUAL (fo_length_get_value (fo_length_get_length_3pt ()),
		   fo_length_get_value (fo_length_range_get_maximum (length_range_2)));

  g_object_unref (length_range_1);
  g_object_unref (length_range_2);
}

static CU_TestInfo test_array[] = {
  { "test copy of FoLengthRange", test_fo_length_range_copy },
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  { "fo-length-range", init_suite, clean_suite, test_array },
  CU_SUITE_INFO_NULL,
};

CU_SuiteInfo *
test_fo_length_range_get_suites (void)
{
  return suites;
}

