#ifndef GROVER_OPERATIONS_H
#define GROVER_OPERATIONS_H

#include "../quantomlibrary.h"

void MCZ_all(Quantom_register *q, int search_length, int ancilla_start);

void Oracle(Quantom_register *q, int target, int search_length, int ancilla_start);

void diffusion(Quantom_register *q, int search_length, int ancilla_start);

int grover_iterations_calculate(int search_length);

Quantom_register *Grover(int search_length, int target);

#endif
