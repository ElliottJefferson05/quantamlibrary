#include <math.h>
#include <stddef.h>
#include "operations.h"
#include "../gates/matrix_gates.h"

Complex complex_add(Complex a,Complex b){
    double real = a.real + b.real;
    double imaginary = a.imaginary + b.imaginary;
    return complex_initiliaze(real,imaginary);

}

Complex  complex_mutliply(Complex a, Complex b){
    double real = (a.real * b.real) - (a.imaginary * b.imaginary);
    double imaginary = (a.real * b.imaginary) + (b.real * a.imaginary);
    return complex_initiliaze(real,imaginary);
}

Complex Complex_congiguate(Complex a){

    double real = a.real;
    double imaginary = -a.imaginary;
    return complex_initiliaze(real,imaginary);

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

static void apply_gate4x4( Quantom_register *Q, Matrix4x4 gate, int target1, int target2){

    if (Q == NULL || Q->state == NULL) {
        return;
    }

    if (target1 < 0 || target1 >= Q->num_of_qbits) {
        return;
    }

    if (target2 < 0 || target2 >= Q->num_of_qbits) {
        return;
    }

    if (target1 == target2) {
        return;
    }

    int target_bit1 = 1 << target1;
    int target_bit2 = 1 << target2;

    for (int i = 0; i < Q->state_size; i++) {

        if ((i & target_bit1) == 0 && (i & target_bit2) == 0) {

            int index00 = i;
            int index01 = i | target_bit2;
            int index10 = i | target_bit1;
            int index11 = i | target_bit1 | target_bit2;

            Complex old00 = Q->state[index00];
            Complex old01 = Q->state[index01];
            Complex old10 = Q->state[index10];
            Complex old11 = Q->state[index11];

            Complex new00 = complex_add(
                complex_add(
                    complex_mutliply(gate.matrix[0][0], old00),
                    complex_mutliply(gate.matrix[0][1], old01)
                ),
                complex_add(
                    complex_mutliply(gate.matrix[0][2], old10),
                    complex_mutliply(gate.matrix[0][3], old11)
                )
            );

            Complex new01 = complex_add(
                complex_add(
                    complex_mutliply(gate.matrix[1][0], old00),
                    complex_mutliply(gate.matrix[1][1], old01)
                ),
                complex_add(
                    complex_mutliply(gate.matrix[1][2], old10),
                    complex_mutliply(gate.matrix[1][3], old11)
                )
            );

            Complex new10 = complex_add(
                complex_add(
                    complex_mutliply(gate.matrix[2][0], old00),
                    complex_mutliply(gate.matrix[2][1], old01)
                ),
                complex_add(
                    complex_mutliply(gate.matrix[2][2], old10),
                    complex_mutliply(gate.matrix[2][3], old11)
                )
            );

            Complex new11 = complex_add(
                complex_add(
                    complex_mutliply(gate.matrix[3][0], old00),
                    complex_mutliply(gate.matrix[3][1], old01)
                ),
                complex_add(
                    complex_mutliply(gate.matrix[3][2], old10),
                    complex_mutliply(gate.matrix[3][3], old11)
                )
            );

            Q->state[index00] = new00;
            Q->state[index01] = new01;
            Q->state[index10] = new10;
            Q->state[index11] = new11;
        }
    }
}

void quantom_hadamard(Quantom_register *Q, int target) {
    apply_gate2x2(Q, hadamarMatrix(), target);
}

void quantom_X(Quantom_register *Q, int target) {
    apply_gate2x2(Q, xMatrix(), target);
}


void quantom_z(Quantom_register *Q,int target){
    apply_gate2x2(Q,zMatrix(),target);
}

void quantom_y(Quantom_register *Q,int target){
    apply_gate2x2(Q,yMatrix(),target);
}

void quantom_s(Quantom_register *Q,int target){
    apply_gate2x2(Q,sMatrix(),target);
}

void quantom_CNOT(Quantom_register *Q,int target1, int target2){
    apply_gate4x4(Q,CNOTMatrix(),target1,target2);
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


void Bernstein_Vazirani_Oracle(Quantom_register * q, int secret, int length){

    if(q == NULL || q->state == NULL){
        return;
    }


    for(int i = 0; i < length; i ++){


        int secret_bit = 1 << i;

        if((secret & secret_bit) != 0){

            quantom_CNOT(q,i,length);

        }


    }

}


void Bernstein_Vazirani(Quantom_register * q, int secret, int length){

    quantom_X(q,length);

    Hadamar_all(q);

    Bernstein_Vazirani_Oracle(q,secret,length);

    Hadamar_all(q);

}



