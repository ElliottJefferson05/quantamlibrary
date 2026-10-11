#include "unity.h"
#include "mathimatical_operations/core_operations.h"
#include "test_quantomlibrary.c"
#include "test_operations.c"
#include "test_measurement.c"
#include "test_algorithms.c"
#include "test_shor_operations.c"



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
void test_hadamard_twice(void);
void test_cnot_with_zero_control(void);
void test_bell_state(void);
void test_calculate_probability(void);
void test_qubit_probability(void);
void test_hadamard_probability(void);
void test_measure_one(void);
void test_measure_bell_state(void);
void test_grover_finds_target(void);
void test_grover_invalid_target(void);
void test_bernstein_vazirani_finds_secret(void);
void test_bernstein_vazirani_invalid_secret(void);
void test_qft(void);
void test_inverse_qft(void);
void test_ripple_adder(void);
void test_ripple_adder_carry(void);
void test_subtraction(void);
void test_gcd(void);
void test_modular_power(void);


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


