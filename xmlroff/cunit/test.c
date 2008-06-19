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

#include <string.h>
#include <stdio.h>
#include "CUnit/Basic.h"
#include "test-fo-color.h"
#include "test-fo-context.h"
#include "test-fo-doc.h"
#include "test-fo-expr-eval.h"
#include "test-fo-length-range.h"
#include "test-fo-libfo-context.h"

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main ()
{
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    {
      return CU_get_error();
    }

  CU_ErrorCode error =
    CU_register_suites (test_fo_expr_eval_get_suites());
  if (error != CUE_SUCCESS)
    {
      printf ("%s\n" ,
	      CU_get_error_msg());
      return (error);
    }

  error = CU_register_suites (test_fo_color_get_suites());
  if (error != CUE_SUCCESS)
    {
      printf ("%s\n" ,
	      CU_get_error_msg ());
      return (error);
    }


  error = CU_register_suites (test_fo_context_get_suites());
  if (error != CUE_SUCCESS)
    {
      printf ("%s\n" ,
	      CU_get_error_msg ());
      return (error);
    }

  error = CU_register_suites (test_fo_doc_get_suites());
  if (error != CUE_SUCCESS)
    {
      printf ("%s\n" ,
	      CU_get_error_msg ());
      return (error);
    }

  error = CU_register_suites (test_fo_length_range_get_suites());
  if (error != CUE_SUCCESS)
    {
      printf ("%s\n" ,
	      CU_get_error_msg ());
      return (error);
    }

  error = CU_register_suites (test_fo_libfo_context_get_suites());
  if (error != CUE_SUCCESS)
    {
      printf ("%s\n" ,
	      CU_get_error_msg ());
      return (error);
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode (CU_BRM_VERBOSE);
  CU_basic_run_tests ();
  CU_cleanup_registry ();
  return CU_get_error ();
}
