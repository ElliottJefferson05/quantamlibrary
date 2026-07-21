#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"

int main(void) {
    
    srand(time(NULL));
    Quantom_register *Q = quantom_reg_create(3);

    if (Q == NULL) {
        printf("Failed to create quantum register\n");
        return 1;
    }


    Grover(Q,2);

 
    quantom_print(Q);

    Output_resut(Q, 100, 0);
    Output_resut(Q, 100, 1);
    Output_resut(Q, 100, 2);

    quantom_free(Q);

    return 0;

}