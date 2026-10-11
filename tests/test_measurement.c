#include "unity.h"
#include "measurment.h"
#include "mathimatical_operations/core_operations.h"
#include "mathimatical_operations/shor_operations.h"

void test_calculate_probability(void)
{
    Complex amplitude = complex_initiliaze(0.3, 0.4);

    double probability = Calculate_probability(amplitude);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.25, probability);
}

void test_qubit_probability(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, Propabilty_total(q, 0, 0));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Propabilty_total(q, 0, 1));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Propabilty_total(q, 1, 0));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, Propabilty_total(q, 1, 1));

    quantom_free(q);
}

void test_hadamard_probability(void)
{
    Quantom_register *q = quantom_reg_create(1);
    TEST_ASSERT_NOT_NULL(q);

    quantom_hadamard(q, 0);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.5, Propabilty_total(q, 0, 0));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.5, Propabilty_total(q, 0, 1));

    quantom_free(q);
}

void test_measure_one(void)
{
    Quantom_register *q = quantom_reg_create(1);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0);

    int result = measureSubRegister(q, 0, 1);

    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Propabilty_total(q, 0, 1));

    quantom_free(q);
}

void test_measure_bell_state(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_hadamard(q, 0);
    quantom_CNOT(q, 0, 1);

    int first = measureSubRegister(q, 0, 1);

    TEST_ASSERT_TRUE(first == 0 || first == 1);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Propabilty_total(q, 0, first));
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, Propabilty_total(q, 1, first));

    int second = measureSubRegister(q, 1, 1);
    TEST_ASSERT_EQUAL_INT(first, second);

    quantom_free(q);
}
