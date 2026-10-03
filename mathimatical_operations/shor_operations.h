#ifndef SHOR_OPERATIONS_H
#define SHOR_OPERATIONS_H

#include "../quantomlibrary.h"


void quantom_Forier_Transform(Quantom_register *q, int length);

int gcd(int a, int b);

void inverse_Quantum_Forier_Transform(Quantom_register *q, int length);

void inverse_Quantum_Forier_Transform_Range(Quantom_register *q, int start, int length);

void quantom_Forier_Transform_Range(Quantom_register *q, int start, int length);

void MAJ(Quantom_register *q, int target1, int target2, int control);

void UMA(Quantom_register *q, int target1, int target2, int control);

void Ripple_Adder(Quantom_register *q, int a_start, int b_start, int carry, int carry_out, int length);

void inverse_MAJ(Quantom_register *q, int target1, int target2, int control);

void inverse_UMA(Quantom_register *q, int target1, int target2, int control);

void Subtraction(Quantom_register *q, int a_start, int b_start, int carry, int carry_out, int length);

void controlled_N_To_Zero(Quantom_register *q,int n_start,int t,int N,int length);

void adderModulo(Quantom_register *q,int a_start,int b_start,int n_start,int carry,int carry_out,int t,int N,int length);

#endif
