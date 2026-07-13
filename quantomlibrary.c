#include <stdio.h>
#include <stdlib.h>
#include "quantomlibrary.h"
#include "gates/matrix_gates.h"

Complex complex_initiliaze(double real, double imaginary){
    Complex c;
    c.real = real;
    c.imaginary = imaginary;
    return c;
}

static Complex complex_add(Complex a,Complex b){
    double real = a.real + b.real;
    double imaginary = a.imaginary + b.imaginary;
    return complex_initiliaze(real,imaginary);
    
}

static Complex  complex_mutliply(Complex a, Complex b){
    double real = (a.real * b.real) - (a.imaginary * b.imaginary);
    double imaginary = (a.real * b.imaginary) + (b.real * a.imaginary);
    return complex_initiliaze(real,imaginary);
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

    return q;
}



static void apply_gate2x2(Quantom_register *Q, Matrix2x2 gate, int target){

    if (Q == NULL) {
        return;
    }

    if (target < 0 || target >= Q->num_of_qbits) {
        return;
    }

    int target_bit = 1 << target;

    for (int i = 0; i < Q->state_size; i++) {

        if ((i & target_bit) == 0) {

            int j = i | target_bit;

            Complex old0 = Q->state[i];
            Complex old1 = Q->state[j];

            Complex new0 = complex_add(
                complex_mutliply(gate.matrix[0][0], old0),
                complex_mutliply(gate.matrix[0][1], old1)
            );

            Complex new1 = complex_add(
                complex_mutliply(gate.matrix[1][0], old0),
                complex_mutliply(gate.matrix[1][1], old1)
            );

            Q->state[i] = new0;
            Q->state[j] = new1;
        }
    }
}

 static void apply_gate4x4(Quantom_register *Q, Matrix4x4 gate, int target){
    
   }


void quantom_hadamard(Quantom_register *Q, int target) {
    apply_gate2x2(Q, hadamarMatrix(), target);
}

void quantom_X(Quantom_register *Q, int target) {
    apply_gate2x2(Q, xMatrix(), target);
}

