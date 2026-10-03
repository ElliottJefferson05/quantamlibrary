#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"
#include "circuit_Display.h"


int main(void) {

    //q0 b1 1
    //q1 b2 0
    //q2 a1 1
    //q3 a2 0
    //q4 carry in 
    //q5 carry out
       

    Quantom_register * q = quantom_reg_create(2);

    quantom_hadamard(q,0);

    quantom_hadamard(q,1);

    printCircuitImproved(q->circuit,q);

}
