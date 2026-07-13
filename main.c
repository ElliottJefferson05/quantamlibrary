#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"

int main(void) {
    Quantom_register *Q = quantom_reg_create(2);

    if (Q == NULL) {
        printf("Failed to create quantum register\n");
        return 1;
    }

    printf("Initial state:\n");
    quantom_print(Q);


    quantom_hadamard(Q, 0);

    printf("Hadamard on qubit 0:\n");
    quantom_print(Q);

    quantom_X(Q,1);
    printf("x gate on qubit 1:\n");
    quantom_print(Q);

    quantom_free(Q);

    return 0;

}