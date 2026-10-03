#ifndef GROVER_OPERATIONS_H
#define GROVER_OPERATIONS_H

#include "../quantomlibrary.h"

void MCZ(Quantom_register *q);

void Oracle(Quantom_register *q, int target);

void diffusion(Quantom_register *q);

int grover_iterations_calculate(Quantom_register *q);

void Grover(Quantom_register *q, int target_index);

#endif
