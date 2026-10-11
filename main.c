#include <stdio.h>
#include "quantomlibrary.h"
#include "mathimatical_operations/bernstein_vazirani_operations.h"
#include "measurment.h"

int main(void)
{

    const int secret = 123;

    Quantom_register *q = Bernstein_Vazirani(20, secret);
    if (q == NULL)
    {
        fprintf(stderr, "Could not run Bernstein-Vazirani.\n");
        return 1;
    }

    quantom_print_probabilities(q);

    quantom_free(q);
    return 0;
}
