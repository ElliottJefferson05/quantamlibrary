#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"

int main(void) {

    Quantom_register *Q = quantom_reg_create(2);

    if (Q == NULL) {
        printf("Failed to create quantum register\n");
        return 1;
    }

    quantom_X(Q, 1);

    printf("Before CNOT:\n");
    quantom_print(Q);

    quantom_CNOT(Q, 1, 0);

    printf("\nAfter CNOT:\n");
    quantom_print(Q);

    quantom_free(Q);

    return 0;
}