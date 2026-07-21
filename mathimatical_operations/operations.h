#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "../quantomlibrary.h"
#include "../gates/matrix_gates.h"

Complex Complex_congiguate(Complex a);

Complex Tensor_product(void);

void Hadamar_all(Quantom_register *q);

void MCZ(Quantom_register *q);

void Oracle(Quantom_register *q, int target);

void diffusion(Quantom_register *q);

int grover_iterations_calculate(Quantom_register *q);

void Grover(Quantom_register *q, int target_index);



#endif
