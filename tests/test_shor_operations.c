#include "unity.h"
#include "mathimatical_operations/core_operations.h"
#include "mathimatical_operations/shor_operations.h"

void test_qft(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0);
    quantom_Forier_Transform(q, 2);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.5, q->state[0].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[0].imaginary);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[1].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.5, q->state[1].imaginary);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, -0.5, q->state[2].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[2].imaginary);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[3].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, -0.5, q->state[3].imaginary);

    quantom_free(q);
}

void test_inverse_qft(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0);
    quantom_Forier_Transform(q, 2);
    inverse_Quantum_Forier_Transform(q, 2);

    assert_basis_state(q, 1);

    quantom_free(q);
}

void test_ripple_adder(void)
{
    Quantom_register *q = quantom_reg_create(6);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0); 
    quantom_X(q, 3); 

    Ripple_Adder(q, 0, 2, 4, 5, 2);


    assert_basis_state(q, 13);

    quantom_free(q);
}

void test_ripple_adder_carry(void)
{
    Quantom_register *q = quantom_reg_create(6);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0);
    quantom_X(q, 1); 
    quantom_X(q, 2); 

    Ripple_Adder(q, 0, 2, 4, 5, 2);

    assert_basis_state(q, 35);

    quantom_free(q);
}

void test_subtraction(void)
{
    Quantom_register *q = quantom_reg_create(6);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0); 
    quantom_X(q, 2);
    quantom_X(q, 3); 

    Subtraction(q, 0, 2, 4, 5, 2);

    assert_basis_state(q, 9);

    quantom_free(q);
}

void test_gcd(void)
{
    TEST_ASSERT_EQUAL_INT(6, gcd(54, 24));
}

void test_modular_power(void)
{

    TEST_ASSERT_EQUAL_INT(1, modularPower(2, 4, 15));
}
