#include <math.h>
#include "operations.h"
#include "../quantomlibrary.h"
#include <stdio.h>


Complex Complex_congiguate(Complex a){

    double real = a.real;
    double imaginary = -a.imaginary;
    return complex_initiliaze(real,imaginary);

}

void Hadamar_all(Quantom_register *q){
    
    if(q == NULL){
        return;
    }

    for(int i = 0; i < q-> num_of_qbits; i++){
        quantom_hadamard(q,i);
    }

}

void MCZ(Quantom_register *Q){
    if (Q == NULL || Q->state == NULL){
        return;
    }

    Q->state[((Q->state_size) -1)].real *= -1.0;
    Q->state[((Q->state_size) -1)].imaginary *= -1.0;


}

void Oracle(Quantom_register *Q, int target){

    if (Q == NULL || Q->state == NULL){
        return;

    }

    if (target < 0 || target >= Q->state_size){
        return;
    }

     for (int q = 0; q < Q->num_of_qbits; q++) {
        int target_bit = 1 << q;

        if ((target & target_bit) == 0) {
            quantom_X(Q, q);
        }
    }

    MCZ(Q);

    for (int q = 0; q < Q->num_of_qbits; q++) {
        int target_bit = 1 << q;

        if ((target & target_bit) == 0) {
            quantom_X(Q, q);
        }
    }
}


void diffusion(Quantom_register *Q){

    if (Q == NULL || Q->state == NULL){
        return;

    }

    Complex average = complex_initiliaze(0.0,0.0);

     for (int i = 0; i < Q->state_size; i++) {
        average = complex_add(average, Q->state[i]);
    }

    average.real /= Q->state_size;
    average.imaginary /= Q->state_size;

    for (int i = 0; i < Q->state_size; i++) {
        Q->state[i].real = (2.0 * average.real) - Q->state[i].real;
        Q->state[i].imaginary = (2.0 * average.imaginary) - Q->state[i].imaginary;
    }

}



int grover_iterations_calculate(Quantom_register *q) {

    if (q == NULL) {
        return 0;
    }

    double N = (double)q->state_size;

    int iterations = (int)((3.141592653589793 / 4.0) * sqrt(N));

    return iterations;
}


void Grover(Quantom_register *q, int target_index) {

    if (q == NULL || q->state == NULL) {
        return;
    }

    if (target_index < 0 || target_index >= q->state_size) {
        return;
    }

    int iterations = grover_iterations_calculate(q);

    Hadamar_all(q);

    for (int i = 0; i < iterations; i++) {
        Oracle(q, target_index);
        diffusion(q);
    }
}







