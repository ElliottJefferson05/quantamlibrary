#include <stdio.h>
#include <stdlib.h>
#include "quantomlibrary.h"
#include "circuit_Display.h"


Complex complex_initiliaze(double real, double imaginary){
    Complex c;
    c.real = real;
    c.imaginary = imaginary;
    return c;
}

void quantom_free(Quantom_register *q) {
    if (q == NULL) {
        return;
    }

    free(q->state);
    free(q);
}

void quantom_print(Quantom_register *q){
    if (q ==NULL){
        printf("register is NULL\n");
        return;
    }

    for(int i = 0; i < q->state_size; i++){
        printf("|");

        for(int j = q->num_of_qbits-1;j>=0;j--){
            int bit_val = (i >> j) & 1;
            printf("%d",bit_val);


        }
        printf("> : %.4f + %.4fi\n", q->state[i].real, q->state[i].imaginary);
    }
}




Quantom_register *quantom_reg_create(int num_of_qubits) {
    Quantom_register *q = malloc(sizeof(Quantom_register));

    if (q == NULL) {
        return NULL;
    }   

    q->num_of_qbits = num_of_qubits;
    q->state_size = 1 << num_of_qubits;

    q->state = calloc(q->state_size, sizeof(Complex));

    if (q->state == NULL) {
        free(q);
        return NULL;
    }

    q->state[0] = complex_initiliaze(1.0, 0.0);

    q-> circuit =createList();
    
    if(q->circuit == NULL){
        return NULL;
    }

    return q;
}
