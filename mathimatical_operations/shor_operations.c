#include <stddef.h>
#include "shor_operations.h"
#include "core_operations.h"

#define pi 3.14159265358979323846

void quantom_Forier_Transform(Quantom_register *q, int length)
{

    for (int i = 0; i < length; i++)
    {

        quantom_hadamard(q, i);

        int k = 2;

        for (int j = i + 1; j < length; j++)
        {
            controlled_Phase(q, j, i, pi / k);
            k *= 2;
        }
    }

    int p = length - 1;

    for (int h = 0; h < length / 2; h++)
    {
        Swap(q, h, p);
        p--;
    }
}

void inverse_Quantum_Forier_Transform(Quantom_register *q, int length)
{

    if (q == NULL)
    {
        return;
    }

    if (q->num_of_qbits <= 0)
    {
        return;
    }

    if (q->state_size < 0)
    {
        return;
    }

    int p = length - 1;

    for (int h = 0; h < length / 2; h++)
    {
        Swap(q, h, p);
        p--;
    }

    for (int i = length - 1; i >= 0; i--)
    {

        int k = 2;

        for (int j = i + 1; j < length; j++)
        {
            controlled_Phase(q, j, i, -pi / k);
            k *= 2;
        }

        quantom_hadamard(q, i);
    }
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

    for (int i = start; i < end; i++)
    {

        quantom_hadamard(q, i);

        int k = 2;

        for (int j = i + 1; j < end; j++)
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

    for (int i = end - 1; i >= start; i--)
    {

        int k = 2;

        for (int j = i + 1; j < end; j++)
        {
            controlled_Phase(q, j, i, -pi / k);
            k *= 2;
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
