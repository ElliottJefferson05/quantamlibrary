#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"
#include "circuit_Display.h"


int main(void){

    Quantom_register *q = quantom_reg_create(6);

    quantom_X(q,2);
    quantom_X(q,3);

    quantom_X(q,0);

    printf("Before:\n");
    quantom_print(q);

    Ripple_Adder(q,2,0,4,5,2);

    printf("\nAfter:\n");
    quantom_print(q);

    quantom_free(q);

    return 0;
}