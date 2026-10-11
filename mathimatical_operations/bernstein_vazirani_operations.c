#include <stddef.h>
#include <limits.h>
#include "bernstein_vazirani_operations.h"
#include "core_operations.h"

static int valid_bernstein_vazirani_inputs(int length, int secret)
{

    return length > 0 && length < 30 &&
           secret >= 0 && secret < (1 << length);
}

void Bernstein_Vazirani_Oracle(Quantom_register *q, int secret, int length)
{

    if (q == NULL || q->state == NULL || q->circuit == NULL ||
        !valid_bernstein_vazirani_inputs(length, secret) ||
        q->num_of_qbits <= length ||
        q->num_of_qbits >= (int)(sizeof(int) * CHAR_BIT) - 1 ||
        q->state_size != (1 << q->num_of_qbits))
    {
        return;
    }

    for (int i = 0; i < length; i++)
    {

        int secret_bit = 1 << i;

        if ((secret & secret_bit) != 0)
        {

            quantom_CNOT(q, i, length);
        }
    }
}

Quantom_register *Bernstein_Vazirani(int length, int secret)
{
    if (!valid_bernstein_vazirani_inputs(length, secret))
    {
        return NULL;
    }

    Quantom_register *q = quantom_reg_create(length + 1);
    if (q == NULL)
    {
        return NULL;
    }

    quantom_X(q, length);

    Hadamar_all(q);

    Bernstein_Vazirani_Oracle(q, secret, length);

    Hadamar_all(q);

    return q;
}
