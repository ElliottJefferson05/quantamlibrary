#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "shor_operations.h"
#include "core_operations.h"

#define pi 3.14159265358979323846

void quantom_Forier_Transform(Quantom_register *q, int length)
{
    quantom_Forier_Transform_Range(q, 0, length);
}

void inverse_Quantum_Forier_Transform(Quantom_register *q, int length)
{
    inverse_Quantum_Forier_Transform_Range(q, 0, length);
}

void quantom_Forier_Transform_Range(Quantom_register *q, int start, int length)
{
    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (start < 0 || length <= 0)
    {
        return;
    }

    if (start + length > q->num_of_qbits)
    {
        return;
    }

    int end = start + length;

    for (int i = end - 1; i >= start; i--)
    {

        quantom_hadamard(q, i);

        int k = 2;

        for (int j = i - 1; j >= start; j--)
        {
            controlled_Phase(q, j, i, pi / k);

            k *= 2;
        }
    }

    int left = start;
    int right = end - 1;

    while (left < right)
    {
        Swap(q, left, right);

        left++;
        right--;
    }
}

void inverse_Quantum_Forier_Transform_Range(Quantom_register *q, int start, int length)
{
    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (start < 0 || length <= 0)
    {
        return;
    }

    if (start + length > q->num_of_qbits)
    {
        return;
    }

    int end = start + length;

    int left = start;
    int right = end - 1;

    while (left < right)
    {
        Swap(q, left, right);

        left++;
        right--;
    }

    for (int i = start; i < end; i++)
    {

        for (int j = start; j < i; j++)
        {

            int distance = i - j;

            controlled_Phase(q, j, i, -pi / (1 << distance));
        }

        quantom_hadamard(q, i);
    }
}
int gcd(int a, int b)
{

    if (a < 0)
    {
        a = -a;
    }

    if (b < 0)
    {
        b = -b;
    }

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void MAJ(Quantom_register *q, int target1, int target2, int control)
{
    quantom_CNOT(q, target1, target2);
    quantom_CNOT(q, target1, control);
    Toffoli(q, control, target2, target1);
}

void UMA(Quantom_register *q, int target1, int target2, int control)
{
    Toffoli(q, control, target2, target1);
    quantom_CNOT(q, target1, control);
    quantom_CNOT(q, control, target2);
}

void Ripple_Adder(Quantom_register *q, int a_start, int b_start, int carry, int carry_out, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (length <= 0)
    {
        return;
    }

    MAJ(q, a_start, b_start, carry);

    for (int i = 1; i < length; i++)
    {

        MAJ(q, a_start + i, b_start + i, a_start + i - 1);
    }

    quantom_CNOT(q, a_start + length - 1, carry_out);

    for (int i = length - 1; i >= 1; i--)
    {

        UMA(q, a_start + i, b_start + i, a_start + i - 1);
    }

    UMA(q, a_start, b_start, carry);
}

void inverse_MAJ(Quantom_register *q, int target1, int target2, int control)
{

    Toffoli(q, control, target2, target1);
    quantom_CNOT(q, target1, control);
    quantom_CNOT(q, target1, target2);
}

void inverse_UMA(Quantom_register *q, int target1, int target2, int control)
{

    quantom_CNOT(q, control, target2);
    quantom_CNOT(q, target1, control);
    Toffoli(q, control, target2, target1);
}

void Subtraction(Quantom_register *q, int a_start, int b_start, int carry, int carry_out, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    if (length <= 0)
    {
        return;
    }

    inverse_UMA(q, a_start, b_start, carry);

    for (int i = 1; i < length; i++)
    {

        inverse_UMA(q, a_start + i, b_start + i, a_start + i - 1);
    }

    quantom_CNOT(q, a_start + length - 1, carry_out);

    for (int i = length - 1; i >= 1; i--)
    {

        inverse_MAJ(q, a_start + i, b_start + i, a_start + i - 1);
    }

    inverse_MAJ(q, a_start, b_start, carry);
}

void controlled_N_To_Zero(Quantom_register *q, int n_start, int t, int N, int length)
{

    for (int i = 0; i < length; i++)
    {

        int n_bit = 1 << i;

        if ((N & n_bit) != 0)
        {

            quantom_CNOT(q, t, n_start + i);
        }
    }
}

void adderModulo(Quantom_register *q, int a_start, int b_start, int n_start, int carry, int carry_out, int t, int N, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    Ripple_Adder(q, a_start, b_start, carry, carry_out, length);

    Subtraction(q, n_start, b_start, carry, carry_out, length);

    quantom_CNOT(q, carry_out, t);

    quantom_X(q, t);

    controlled_N_To_Zero(q, n_start, t, N, length);

    Ripple_Adder(q, n_start, b_start, carry, carry_out, length);

    controlled_N_To_Zero(q, n_start, t, N, length);

    Subtraction(q, a_start, b_start, carry, carry_out, length);

    quantom_CNOT(q, carry_out, t);

    Ripple_Adder(q, a_start, b_start, carry, carry_out, length);
}

void loadControlledConstant(Quantom_register *q, int control, int x_bit, int temp_start, int value, int length)
{

    for (int i = 0; i < length; i++)
    {

        int value_bit = 1 << i;

        if ((value & value_bit) != 0)
        {

            Toffoli(q, control, x_bit, temp_start + i);
        }
    }
}

void controlledMultiplierModulo(Quantom_register *q, int control, int x_start, int result_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    int value = a % N;

    for (int i = 0; i < length; i++)
    {

        loadControlledConstant(q, control, x_start + i, temp_start, value, length);

        adderModulo(q, temp_start, result_start, n_start, carry, carry_out, t, N, length);

        loadControlledConstant(q, control, x_start + i, temp_start, value, length);

        value = (value * 2) % N;
    }

    quantom_X(q, control);

    for (int i = 0; i < length; i++)
    {

        Toffoli(q, control, x_start + i, result_start + i);
    }

    quantom_X(q, control);
}

void Swap_Registers(Quantom_register *q, int register1_start, int register2_start, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    for (int i = 0; i < length; i++)
    {

        Swap(q, register1_start + i, register2_start + i);
    }
}

int modularInverse(int a, int N)
{

    int t = 0;
    int new_t = 1;

    int r = N;
    int new_r = a;

    while (new_r != 0)
    {

        int quotient = r / new_r;

        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    if (r > 1)
    {
        return -1;
    }

    if (t < 0)
    {
        t += N;
    }

    return t;
}

void inverseAdderModulo(Quantom_register *q, int a_start, int b_start, int n_start, int carry, int carry_out, int t, int N, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    Subtraction(q, a_start, b_start, carry, carry_out, length);

    quantom_CNOT(q, carry_out, t);

    Ripple_Adder(q, a_start, b_start, carry, carry_out, length);

    controlled_N_To_Zero(q, n_start, t, N, length);

    Subtraction(q, n_start, b_start, carry, carry_out, length);

    controlled_N_To_Zero(q, n_start, t, N, length);

    quantom_X(q, t);

    quantom_CNOT(q, carry_out, t);

    Ripple_Adder(q, n_start, b_start, carry, carry_out, length);

    Subtraction(q, a_start, b_start, carry, carry_out, length);
}

void inverseControlledMultiplierModulo(Quantom_register *q, int control, int x_start, int result_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    quantom_X(q, control);

    for (int i = length - 1; i >= 0; i--)
    {

        Toffoli(q, control, x_start + i, result_start + i);
    }

    quantom_X(q, control);

    for (int i = length - 1; i >= 0; i--)
    {

        int value = a % N;

        for (int j = 0; j < i; j++)
        {

            value = (value * 2) % N;
        }

        loadControlledConstant(q, control, x_start + i, temp_start, value, length);

        inverseAdderModulo(q, temp_start, result_start, n_start, carry, carry_out, t, N, length);

        loadControlledConstant(q, control, x_start + i, temp_start, value, length);
    }
}

void modularExponentiation(Quantom_register *q, int exponent_start, int exponent_length, int result_start, int work_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return;
    }

    quantom_X(q, result_start);

    int value = a % N;

    for (int i = 0; i < exponent_length; i++)
    {

        int inverse = modularInverse(value, N);

        if (inverse == -1)
        {
            return;
        }

        controlledMultiplierModulo(q, exponent_start + i, result_start, work_start, temp_start, n_start, carry, carry_out, t, value, N, length);

        Swap_Registers(q, result_start, work_start, length);

        inverseControlledMultiplierModulo(q, exponent_start + i, result_start, work_start, temp_start, n_start, carry, carry_out, t, inverse, N, length);

        value = (value * value) % N;
    }
}

int continuedFractionPeriod(int measured, int Q, int max_denominator)
{

    int numerator = measured;
    int denominator = Q;

    int p_prev2 = 0;
    int p_prev1 = 1;

    int q_prev2 = 1;
    int q_prev1 = 0;

    while (denominator != 0)
    {

        int a = numerator / denominator;

        int p = a * p_prev1 + p_prev2;
        int q = a * q_prev1 + q_prev2;

        if (q > max_denominator)
        {
            break;
        }

        if (q != 0)
        {
            p_prev2 = p_prev1;
            p_prev1 = p;

            q_prev2 = q_prev1;
            q_prev1 = q;
        }

        int remainder = numerator % denominator;

        numerator = denominator;
        denominator = remainder;
    }

    return q_prev1;
}

int modularPower(int base, int exponent, int mod)
{

    int result = 1;

    base %= mod;

    while (exponent > 0)
    {

        if (exponent & 1)
        {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;

        exponent >>= 1;
    }

    return result;
}

int measureSubRegister(Quantom_register *q, int start, int length)
{

    if (q == NULL || q->state == NULL)
    {
        return -1;
    }

    if (start < 0 || length <= 0)
    {
        return -1;
    }

    if (start + length > q->num_of_qbits)
    {
        return -1;
    }

    int num_values = 1 << length;

    double *probabilities = calloc(num_values, sizeof(double));

    if (probabilities == NULL)
    {
        return -1;
    }

    int mask = (num_values - 1) << start;

    for (int i = 0; i < q->state_size; i++)
    {

        int value = (i & mask) >> start;

        double probability =
            q->state[i].real * q->state[i].real +
            q->state[i].imaginary * q->state[i].imaginary;

        probabilities[value] += probability;
    }

    double random_value = (double)rand() / RAND_MAX;

    double cumulative = 0.0;

    int measured = num_values - 1;

    for (int i = 0; i < num_values; i++)
    {

        cumulative += probabilities[i];

        if (random_value <= cumulative)
        {

            measured = i;
            break;
        }
    }

    double measured_probability = probabilities[measured];

    if (measured_probability <= 0.0)
    {

        free(probabilities);
        return -1;
    }

    double normalization = sqrt(measured_probability);

    for (int i = 0; i < q->state_size; i++)
    {

        int value = (i & mask) >> start;

        if (value != measured)
        {

            q->state[i].real = 0.0;
            q->state[i].imaginary = 0.0;
        }
        else
        {

            q->state[i].real /= normalization;
            q->state[i].imaginary /= normalization;
        }
    }

    free(probabilities);

    return measured;
}

int findValidPeriod(int candidate, int a, int N)
{

    if(candidate <= 0)
    {
        return -1;
    }

    for(int multiple = 1; multiple <= N; multiple++)
    {

        int r = candidate * multiple;

        if(modularPower(a, r, N) == 1)
        {
            return r;
        }
    }

    return -1;
}

int chooseA(int N)
{

    if (N <= 3)
    {
        return -1;
    }

    return 2 + rand() % (N - 2);
}

int getBitLength(int N)
{

    int length = 0;

    while (N > 0)
    {

        length++;
        N >>= 1;
    }

    return length;
}

int Shor(int N)
{

    if(N <= 1)
    {
        return -1;
    }

    if(N % 2 == 0)
    {
        return 2;
    }

    int max_attempts = 5;

    int length = getBitLength(N);

    int exponent_length = 2 * length;

    int exponent_start = 0;
    int result_start = exponent_start + exponent_length;
    int work_start = result_start + length;
    int temp_start = work_start + length;
    int n_start = temp_start + length;

    int carry = n_start + length;
    int carry_out = carry + 1;
    int t = carry_out + 1;

    int total_qubits = t + 1;

    for(int attempt = 1; attempt <= max_attempts; attempt++)
    {

        int A = chooseA(N);

        int fac = gcd(A,N);

        if(fac > 1 && fac < N)
        {
            return fac;
        }

        Quantom_register *q = quantom_reg_create(total_qubits);

        if(q == NULL)
        {
            return -1;
        }

        for(int i = 0; i < length; i++)
        {

            if((N & (1 << i)) != 0)
            {
                quantom_X(q,n_start + i);
            }
        }

        for(int i = 0; i < exponent_length; i++)
        {
            quantom_hadamard(q,exponent_start + i);
        }

        modularExponentiation(q, exponent_start, exponent_length, result_start, work_start, temp_start, n_start, carry, carry_out, t, A, N, length);

        inverse_Quantum_Forier_Transform_Range(q,exponent_start,exponent_length);

        int measured = measureSubRegister(q,exponent_start,exponent_length);

        int Q = 1 << exponent_length;

        if(measured == 0)
        {
            quantom_free(q);

            continue;
        }

        int candidate = continuedFractionPeriod(measured,Q,N);

        int r = findValidPeriod(candidate,A,N);

        if(r == -1)
        {
            quantom_free(q);

            continue;
        }

        if(r % 2 != 0)
        {
            quantom_free(q);

            continue;
        }

        int value = modularPower(A,r / 2,N);

        if(value == N - 1)
        {
            quantom_free(q);

            continue;
        }

        int factor1 = gcd(value - 1,N);
        int factor2 = gcd(value + 1,N);

        if(factor1 > 1 && factor1 < N)
        {
            quantom_free(q);

            return factor1;
        }

        if(factor2 > 1 && factor2 < N)
        {
            quantom_free(q);

            return factor2;
        }

        quantom_free(q);
    }

    return -1;
}