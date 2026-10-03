#include <stdio.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"
#include "mathimatical_operations/operations.h"
#include <stdlib.h>
#include <time.h>
#include "measurment.h"
#include "circuit_Display.h"


int main(void){

    int length = 3;

    int b_start = 0;
    int a_start = 3;
    int n_start = 6;

    int carry = 9;
    int carry_out = 10;
    int t = 11;

    int N = 5;

    Quantom_register *q = quantom_reg_create(12);

    // B = 2 = 010
    quantom_X(q,b_start + 1);

    // A = 1 = 001
    quantom_X(q,a_start);

    // N = 5 = 101
    quantom_X(q,n_start);
    quantom_X(q,n_start + 2);

    printf("Before modulo addition:\n");

    Output_resut(q,100,0);
    Output_resut(q,100,1);
    Output_resut(q,100,2);
    Output_resut(q,100,3);
    Output_resut(q,100,4);
    Output_resut(q,100,5);
    Output_resut(q,100,6);
    Output_resut(q,100,7);
    Output_resut(q,100,8);
    Output_resut(q,100,9);
    Output_resut(q,100,10);
    Output_resut(q,100,11);

    adderModulo(
        q,
        a_start,
        b_start,
        n_start,
        carry,
        carry_out,
        t,
        N,
        length
    );

    printf("\nAfter modulo addition:\n");

    Output_resut(q,100,0);
    Output_resut(q,100,1);
    Output_resut(q,100,2);
    Output_resut(q,100,3);
    Output_resut(q,100,4);
    Output_resut(q,100,5);
    Output_resut(q,100,6);
    Output_resut(q,100,7);
    Output_resut(q,100,8);
    Output_resut(q,100,9);
    Output_resut(q,100,10);
    Output_resut(q,100,11);

    quantom_free(q);

    return 0;
}