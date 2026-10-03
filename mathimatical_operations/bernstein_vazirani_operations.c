#include <stddef.h>
#include "bernstein_vazirani_operations.h"
#include "core_operations.h"

void Bernstein_Vazirani_Oracle(Quantom_register *q, int secret, int length)
{

    if (q == NULL || q->state == NULL)
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

void Bernstein_Vazirani(Quantom_register *q, int secret, int length)
{

    quantom_X(q, length);

    Hadamar_all(q);

    Bernstein_Vazirani_Oracle(q, secret, length);

    Hadamar_all(q);
}
