#include "unity.h"

#include <math.h>

#include "mathimatical_operations/core_operations.h"

static void assert_complex(Complex actual, double real, double imaginary)
{
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, real, actual.real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, imaginary, actual.imaginary);
}

static void assert_basis_state(Quantom_register *q, int index)
{
    for (int i = 0; i < q->state_size; i++)
    {
        assert_complex(q->state[i], i == index ? 1.0 : 0.0, 0.0);
    }
}

void test_complex_add(void)
{
    Complex output_a = complex_initiliaze(1.5, 3.2);
    Complex output_b = complex_initiliaze(2.5, 1.0);

    Complex answer = complex_add(output_a, output_b);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 4.0, answer.real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 4.2, answer.imaginary);
}

void test_complex_multiply(void)
{
    Complex output_a = complex_initiliaze(1.5, 3.2);
    Complex output_b = complex_initiliaze(2.5, 1.0);

    Complex answer = complex_mutliply(output_a, output_b);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.55, answer.real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 9.5, answer.imaginary);
}

void test_complex_conjugate(void)
{
    Complex input = complex_initiliaze(2.5, -3.0);
    Complex answer = Complex_congiguate(input);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 2.5, answer.real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 3.0, answer.imaginary);
}

void test_quantom_hadamard(void)
{
    Quantom_register *q = quantom_reg_create(1);

    quantom_hadamard(q, 0);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0 / sqrt(2.0), q->state[0].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[0].imaginary);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0 / sqrt(2.0), q->state[1].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[1].imaginary);

    quantom_free(q);
}

void test_quantom_x(void)
{
    Quantom_register *q = quantom_reg_create(1);

    quantom_X(q, 0);

    assert_basis_state(q, 1);
    quantom_free(q);
}

void test_quantom_z(void)
{
    Quantom_register *q = quantom_reg_create(1);

    quantom_X(q, 0);
    quantom_z(q, 0);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, -1.0, q->state[1].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[1].imaginary);

    quantom_free(q);
}

void test_quantom_y(void)
{
    Quantom_register *q = quantom_reg_create(1);

    quantom_y(q, 0);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[1].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, q->state[1].imaginary);

    quantom_free(q);
}

void test_quantom_s(void)
{
    Quantom_register *q = quantom_reg_create(1);

    quantom_X(q, 0);
    quantom_s(q, 0);

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[1].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, q->state[1].imaginary);

    quantom_free(q);
}

void test_quantom_cnot(void)
{
    Quantom_register *q = quantom_reg_create(2);

    quantom_X(q, 0);
    quantom_CNOT(q, 0, 1);

    assert_basis_state(q, 3);
    quantom_free(q);
}

void test_controlled_phase(void)
{
    Quantom_register *q = quantom_reg_create(2);

    quantom_X(q, 0);
    quantom_X(q, 1);
    controlled_Phase(q, 0, 1, (float)(acos(-1) / 2.0));

    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[3].real);
    TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 1.0, q->state[3].imaginary);

    quantom_free(q);
}

void test_swap(void)
{
    Quantom_register *q = quantom_reg_create(2);

    quantom_X(q, 0);
    Swap(q, 0, 1);

    assert_basis_state(q, 2);
    quantom_free(q);
}

void test_toffoli(void)
{
    Quantom_register *q = quantom_reg_create(3);

    quantom_X(q, 0);
    quantom_X(q, 1);
    Toffoli(q, 0, 1, 2);

    assert_basis_state(q, 7);
    quantom_free(q);
}

void test_hadamar_all(void)
{
    Quantom_register *q = quantom_reg_create(2);

    Hadamar_all(q);

    for (int i = 0; i < q->state_size; i++)
    {
        TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.5, q->state[i].real);
        TEST_ASSERT_DOUBLE_WITHIN(0.0000001, 0.0, q->state[i].imaginary);
    }

    quantom_free(q);
}

void test_hadamard_twice(void)
{
    Quantom_register *q = quantom_reg_create(1);
    TEST_ASSERT_NOT_NULL(q);

    quantom_hadamard(q, 0);
    quantom_hadamard(q, 0);

    // Two Hadamard gates should return the qubit to zero.
    assert_basis_state(q, 0);

    quantom_free(q);
}

void test_cnot_with_zero_control(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_CNOT(q, 0, 1);

    // The target should not change when the control is zero.
    assert_basis_state(q, 0);

    quantom_free(q);
}

void test_bell_state(void)
{
    Quantom_register *q = quantom_reg_create(2);
    TEST_ASSERT_NOT_NULL(q);

    quantom_hadamard(q, 0);
    quantom_CNOT(q, 0, 1);

    // The Bell state is (|00> + |11>) / sqrt(2).
    assert_complex(q->state[0], 1.0 / sqrt(2.0), 0.0);
    assert_complex(q->state[1], 0.0, 0.0);
    assert_complex(q->state[2], 0.0, 0.0);
    assert_complex(q->state[3], 1.0 / sqrt(2.0), 0.0);

    quantom_free(q);
}
