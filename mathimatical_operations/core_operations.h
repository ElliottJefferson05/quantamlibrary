#ifndef CORE_OPERATIONS_H
#define CORE_OPERATIONS_H

#include "../quantomlibrary.h"

Complex complex_add(Complex a, Complex b);

Complex complex_mutliply(Complex a, Complex b);

Complex Complex_congiguate(Complex a);

void quantom_hadamard(Quantom_register *Q, int target);

void quantom_X(Quantom_register *Q, int target);

void quantom_z(Quantom_register *Q, int target);

void quantom_y(Quantom_register *Q, int target);

void quantom_s(Quantom_register *Q, int target);

void quantom_CNOT(Quantom_register *Q, int target1, int target2);

void controlled_Phase(Quantom_register *q, int target1, int target2, float theta);

void Swap(Quantom_register *q, int target1, int target2);

void Toffoli(Quantom_register *q, int control1, int control2, int target);

void Hadamar_all(Quantom_register *q);

#endif
