#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"


int main(void) {

    srand(time(NULL));

    int secret_length = 3;
    int secret = 0b101;

    Quantom_register *Q = quantom_reg_create(secret_length + 1);

    if (Q == NULL) {
        printf("Failed to create quantum register\n");
        return 1;
    }

    Bernstein_Vazirani(Q, secret, secret_length);

    quantom_print(Q);

    quantom_free(Q);

    return 0;
}