#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"
#include "circuit_Display.h"


int main(void) {

    srand(time(NULL));

   

    Quantom_register *Q = quantom_reg_create(2);

    quantom_hadamard(Q,1);


    quantom_print(Q);

    printCircuit(Q->circuit);
    
    quantom_free(Q);

    return 0;
}