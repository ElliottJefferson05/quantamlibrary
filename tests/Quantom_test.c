#include "unity.h"
#include "mathimatical_operations/core_operations.h"
#include "test_operations.c"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_unity_is_working(void)
{
    TEST_ASSERT_EQUAL_INT(2, 1 + 1);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_unity_is_working);
    RUN_TEST(test_complex_add);
    RUN_TEST(test_complex_multiply);
    RUN_TEST(test_complex_conjugate);
    RUN_TEST(test_quantom_hadamard);
    RUN_TEST(test_quantom_x);
    RUN_TEST(test_quantom_z);
    RUN_TEST(test_quantom_y);
    RUN_TEST(test_quantom_s);
    RUN_TEST(test_quantom_cnot);
    RUN_TEST(test_controlled_phase);
    RUN_TEST(test_swap);
    RUN_TEST(test_toffoli);
    RUN_TEST(test_hadamar_all);

    return UNITY_END();
}
