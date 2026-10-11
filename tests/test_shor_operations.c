#include "unity.h"
#include "mathimatical_operations/core_operations.h"
#include "mathimatical_operations/shor_operations.h"

void test_qft(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_X(q, 0);
    quantom_Forier_Transform(q, 2);

    // QFT of |01>: (|00> + i|01> - |10> - i|11>) / 2.
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

    // The inverse should return us to |01>.
    assert_basis_state(q, 1);

    quantom_free(q);
}

void test_ripple_adder(void)
{
    Quantom_register *q = quantom_reg_create(6);
    TEST_ASSERT_NOT_NULL(q);

    // Qubits 0-1 hold a, 2-3 hold b, 4 is carry, 5 is carry-out.
    quantom_X(q, 0); // a = 1
    quantom_X(q, 3); // b = 2

    Ripple_Adder(q, 0, 2, 4, 5, 2);

    // 1 + 2 = 3. a stays 1, b becomes 3, both carry bits stay zero.
    // |001101> is state index 13.
    assert_basis_state(q, 13);

    quantom_free(q);
}

void test_ripple_adder_carry(void)
{
    Quantom_register *q = quantom_reg_create(6);
    TEST_ASSERT_NOT_NULL(q);

    // Same layout: a in 0-1, b in 2-3, carry in 4, carry-out in 5.
    quantom_X(q, 0);
    quantom_X(q, 1); // a = 3
    quantom_X(q, 2); // b = 1

    Ripple_Adder(q, 0, 2, 4, 5, 2);

    // 3 + 1 = 4: b becomes 0 and carry-out becomes 1.
    // a stays 3, so |100011> is state index 35.
    assert_basis_state(q, 35);

    quantom_free(q);
}

void test_subtraction(void)
{
    Quantom_register *q = quantom_reg_create(6);
    TEST_ASSERT_NOT_NULL(q);

    // Same layout: a in 0-1, b in 2-3, carry in 4, carry-out in 5.
    quantom_X(q, 0); // a = 1
    quantom_X(q, 2);
    quantom_X(q, 3); // b = 3

    Subtraction(q, 0, 2, 4, 5, 2);

    // 3 - 1 = 2. a stays 1, b becomes 2, both carry bits stay zero.
    // |001001> is state index 9.
    assert_basis_state(q, 9);

    quantom_free(q);
}

void test_gcd(void)
{
    TEST_ASSERT_EQUAL_INT(6, gcd(54, 24));
}

void test_modular_power(void)
{
    // 2^4 = 16, and 16 modulo 15 = 1.
    TEST_ASSERT_EQUAL_INT(1, modularPower(2, 4, 15));
}
