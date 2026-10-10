#include "unity.h"
#include "quantomlibrary.h"

void test_complex_initialize(void)
{
    Complex value = complex_initiliaze(1.25, -2.5);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.25, value.real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, -2.5, value.imaginary);
}

void test_quantom_reg_create_initializes_zero_state(void)
{
    Quantom_register *q = quantom_reg_create(0);

    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_EQUAL_INT(0, q->num_of_qbits);
    TEST_ASSERT_EQUAL_INT(1, q->state_size);
    TEST_ASSERT_NOT_NULL(q->state);
    TEST_ASSERT_NOT_NULL(q->circuit);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, q->state[0].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[0].imaginary);

    quantom_free(q);
}

void test_quantom_reg_create_allocates_full_state(void)
{
    Quantom_register *q = quantom_reg_create(3);

    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_EQUAL_INT(3, q->num_of_qbits);
    TEST_ASSERT_EQUAL_INT(8, q->state_size);

    for (int i = 0; i < q->state_size; i++)
    {
        double expected_real = i == 0 ? 1.0 : 0.0;
        TEST_ASSERT_DOUBLE_WITHIN(0.0000001, expected_real, q->state[i].real);
        TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[i].imaginary);
    }

    quantom_free(q);
}

void test_quantom_free_accepts_null(void)
{
    quantom_free(NULL);
    TEST_PASS();
}


