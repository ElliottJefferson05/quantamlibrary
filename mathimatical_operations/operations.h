#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "../quantomlibrary.h"

Complex complex_add(Complex a,Complex b);
Complex complex_mutliply(Complex a, Complex b);

Complex Complex_congiguate(Complex a);

void quantom_hadamard(Quantom_register *Q, int target);

void quantom_X(Quantom_register *Q, int target);

void quantom_z(Quantom_register *Q,int target);

void quantom_y(Quantom_register *Q,int target);

void quantom_s(Quantom_register *Q,int target);

void quantom_CNOT(Quantom_register *Q,int target1,int target2);

void Hadamar_all(Quantom_register *q);

void MCZ(Quantom_register *q);

void Oracle(Quantom_register *q, int target);

void diffusion(Quantom_register *q);

int grover_iterations_calculate(Quantom_register *q);

void Grover(Quantom_register *q, int target_index);

void Bernstein_Vazirani(Quantom_register * q, int secret, int length);

void Bernstein_Vazirani_Oracle(Quantom_register * q, int secret, int length);



#endif
