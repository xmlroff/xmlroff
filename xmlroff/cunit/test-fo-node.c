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
#include <libfo/fo-node-private.h>

typedef struct
{
  FoNode parent_instance;
} FoNodeTest;

typedef struct
{
  FoNodeClass parent_class;
} FoNodeTestClass;

#define FO_TYPE_NODE_TEST              (fo_node_test_get_type ())
#define FO_NODE_TEST(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_NODE_TEST, FoNodeTest))
#define FO_NODE_TEST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_NODE_TEST, FoNodeTestClass))
#define FO_IS_NODE_TEST(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_NODE_TEST))
#define FO_IS_NODE_TEST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_NODE_TEST))
#define FO_NODE_TEST_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_NODE_TEST, FoNodeTestClass))

static void
fo_node_test_init (FoNodeTest *self)
{
}

static void
fo_node_test_class_init (FoNodeTestClass *klass)
{
}

G_DEFINE_TYPE (FoNodeTest, fo_node_test, (FO_TYPE_NODE));

FoNodeTest *
fo_node_test_new (void)
{
  return FO_NODE_TEST (g_object_new (fo_node_test_get_type (),
				     NULL));
}

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
test_fo_node_test_new_finalize (void)
{
  FoNodeTest *node = fo_node_test_new();

  g_object_unref (node);
}

static CU_TestInfo test_array[] = {
  { "FoNode new and finalize", test_fo_node_test_new_finalize },
  CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
  { "fo-node", init_suite, clean_suite, test_array },
  CU_SUITE_INFO_NULL,
};

CU_SuiteInfo *
test_fo_node_get_suites (void)
{
  return suites;
}

