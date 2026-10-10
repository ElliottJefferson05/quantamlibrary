#include "unity.h"
#include "mathimatical_operations/core_operations.h"
#include "test_quantomlibrary.c"
#include "test_operations.c"

/* Declarations let Unity's generator discover tests implemented in the
 * included source files. */
void test_unity_is_working(void);
void test_complex_initialize(void);
void test_quantom_reg_create_initializes_zero_state(void);
void test_quantom_reg_create_allocates_full_state(void);
void test_quantom_free_accepts_null(void);
void test_complex_add(void);
void test_complex_multiply(void);
void test_complex_conjugate(void);
void test_quantom_hadamard(void);
void test_quantom_x(void);
void test_quantom_z(void);
void test_quantom_y(void);
void test_quantom_s(void);
void test_quantom_cnot(void);
void test_controlled_phase(void);
void test_swap(void);
void test_toffoli(void);
void test_hadamar_all(void);

void test_unity_is_working(void)
{
    TEST_ASSERT_EQUAL_INT(2, 1 + 1);
}

void setUp(void)
{
}

void tearDown(void)
{
}


