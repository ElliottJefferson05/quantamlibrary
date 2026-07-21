#ifndef QSIM_H
#define QSIM_H

typedef struct{
    double real;
    double imaginary;
}Complex;



typedef struct{
    int num_of_qbits;
    int state_size;
    Complex *state;
}Quantom_register;


Complex complex_initiliaze(double real,double imaginary);

Quantom_register *quantom_reg_create(int num_of_qubits);

Complex complex_add(Complex a,Complex b);


void quantom_free(Quantom_register *q);


void quantom_print(Quantom_register *Q);

void quantom_hadamard(Quantom_register *Q, int target);

void quantom_X(Quantom_register *Q, int target);

#endif