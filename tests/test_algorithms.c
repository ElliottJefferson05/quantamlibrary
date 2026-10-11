#include "unity.h"
#include "measurment.h"
#include "mathimatical_operations/grover_operations.h"
#include "mathimatical_operations/bernstein_vazirani_operations.h"

void test_grover_finds_target(void)
{
    Quantom_register *q = Grover(2, 3);
    TEST_ASSERT_NOT_NULL(q);

    TEST_ASSERT_EQUAL_INT(2, q->num_of_qbits);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, Calculate_probability(q->state[0]));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, Calculate_probability(q->state[1]));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, Calculate_probability(q->state[2]));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Calculate_probability(q->state[3]));

    quantom_free(q);
}

void test_grover_invalid_target(void)
{
    Quantom_register *q = Grover(2, 4);

    TEST_ASSERT_NULL(q);
}

void test_bernstein_vazirani_finds_secret(void)
{
    Quantom_register *q = Bernstein_Vazirani(3, 5);
    TEST_ASSERT_NOT_NULL(q);

    TEST_ASSERT_EQUAL_INT(4, q->num_of_qbits);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Calculate_probability(q->state[13]));

    quantom_free(q);
}

void test_bernstein_vazirani_invalid_secret(void)
{
    Quantom_register *q = Bernstein_Vazirani(3, 8);

    TEST_ASSERT_NULL(q);
}
