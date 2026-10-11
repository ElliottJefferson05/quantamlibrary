#include <math.h>
#include <limits.h>
#include <stddef.h>
#include "grover_operations.h"
#include "core_operations.h"

static int valid_search_length(int search_length)
{
    return search_length > 0 && search_length < 31;
}

static int valid_search_register(Quantom_register *Q, int search_length, int ancilla_start)
{
    if (Q == NULL || Q->state == NULL || Q->circuit == NULL ||
        !valid_search_length(search_length) ||
        !valid_search_length(Q->num_of_qbits) ||
        search_length > Q->num_of_qbits ||
        Q->state_size != (1 << Q->num_of_qbits))
    {
        return 0;
    }

    if (search_length > 3)
    {
        int ancilla_count = search_length - 3;
        if (ancilla_start < search_length || ancilla_start > Q->num_of_qbits ||
            ancilla_count > Q->num_of_qbits - ancilla_start)
        {
            return 0;
        }
    }

    return 1;
}

void MCZ_all(Quantom_register *Q, int search_length, int ancilla_start)
{
    if (!valid_search_register(Q, search_length, ancilla_start))
    {
        return;
    }

    int target = 0;

    if (search_length == 1)
    {
        quantom_hadamard(Q, target);

        quantom_X(Q, target);

        quantom_hadamard(Q, target);

        return;
    }

    if (search_length == 2)
    {
        quantom_hadamard(Q, target);

        quantom_CNOT(Q, 1, target);

        quantom_hadamard(Q, target);

        return;
    }

    if (search_length == 3)
    {
        quantom_hadamard(Q, target);

        Toffoli(Q, 1, 2, target);

        quantom_hadamard(Q, target);

        return;
    }

    quantom_hadamard(Q, target);

    Toffoli(Q, 1, 2, ancilla_start);

    for (int i = 3; i < search_length - 1; i++)
    {
        int previous_ancilla = ancilla_start + i - 3;
        int next_ancilla = ancilla_start + i - 2;

        Toffoli(Q, previous_ancilla, i, next_ancilla);
    }

    int final_ancilla = ancilla_start + search_length - 4;

    Toffoli(Q, final_ancilla, search_length - 1, target);

    for (int i = search_length - 2; i >= 3; i--)
    {
        int previous_ancilla = ancilla_start + i - 3;
        int next_ancilla = ancilla_start + i - 2;

        Toffoli(Q, previous_ancilla, i, next_ancilla);
    }

    Toffoli(Q, 1, 2, ancilla_start);

    quantom_hadamard(Q, target);
}

void Oracle(Quantom_register *Q, int target, int search_length, int ancilla_start)
{
    if (!valid_search_register(Q, search_length, ancilla_start))
    {
        return;
    }

    int search_state_size = 1 << search_length;

    if (target < 0 || target >= search_state_size)
    {
        return;
    }

    for (int q = 0; q < search_length; q++)
    {
        int target_bit = 1 << q;

        if ((target & target_bit) == 0)
        {
            quantom_X(Q, q);
        }
    }

    MCZ_all(Q, search_length, ancilla_start);

    for (int q = 0; q < search_length; q++)
    {
        int target_bit = 1 << q;

        if ((target & target_bit) == 0)
        {
            quantom_X(Q, q);
        }
    }
}

void diffusion(Quantom_register *Q, int search_length, int ancilla_start)
{
    if (!valid_search_register(Q, search_length, ancilla_start))
    {
        return;
    }

    for (int q = 0; q < search_length; q++)
    {
        quantom_hadamard(Q, q);
    }

    for (int q = 0; q < search_length; q++)
    {
        quantom_X(Q, q);
    }

    MCZ_all(Q, search_length, ancilla_start);

    for (int q = 0; q < search_length; q++)
    {
        quantom_X(Q, q);
    }

    for (int q = 0; q < search_length; q++)
    {
        quantom_hadamard(Q, q);
    }
}

int grover_iterations_calculate(int search_length)
{
    if (!valid_search_length(search_length))
    {
        return 0;
    }

    double N = (double)(1 << search_length);

    double theta = asin(1.0 / sqrt(N));
    int iterations = (int)floor(acos(-1.0) / (4.0 * theta));

    return iterations;
}

Quantom_register *Grover(int search_length, int target)
{
    if (!valid_search_length(search_length))
    {
        return NULL;
    }

    int ancilla_count = 0;

    if (search_length > 3)
    {
        ancilla_count = search_length - 3;
    }

    int ancilla_start = search_length;

    int required_qubits = search_length + ancilla_count;

    if (!valid_search_length(required_qubits))
    {
        return NULL;
    }

    int search_state_size = 1 << search_length;

    if (target < 0 || target >= search_state_size)
    {
        return NULL;
    }

    Quantom_register *Q = quantom_reg_create(required_qubits);
    if (Q == NULL)
    {
        return NULL;
    }

    int iterations = grover_iterations_calculate(search_length);

    for (int q = 0; q < search_length; q++)
    {
        quantom_hadamard(Q, q);
    }

    for (int i = 0; i < iterations; i++)
    {
        Oracle(Q, target, search_length, ancilla_start);

        diffusion(Q, search_length, ancilla_start);
    }

    return Q;
}
