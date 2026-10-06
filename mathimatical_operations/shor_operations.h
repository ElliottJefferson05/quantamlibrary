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

void loadControlledConstant(Quantom_register *q, int control, int x_bit, int temp_start, int value, int length);

void controlledMultiplierModulo(Quantom_register *q, int control, int x_start, int result_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length);

void Swap_Registers(Quantom_register *q, int register1_start, int register2_start, int length);

int modularInverse(int a, int N);

void inverseAdderModulo(Quantom_register *q, int a_start, int b_start, int n_start, int carry, int carry_out, int t, int N, int length);

void inverseControlledMultiplierModulo(Quantom_register *q, int control, int x_start, int result_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length);

void modularExponentiation(Quantom_register *q, int exponent_start, int exponent_length, int result_start, int work_start, int temp_start, int n_start, int carry, int carry_out, int t, int a, int N, int length);

int continuedFractionPeriod(int measured, int Q, int N);

int modularPower(int base, int exponent, int mod);

int measureSubRegister(Quantom_register *q, int start, int length);

int findValidPeriod(int candidate, int a, int N);

int chooseA(int N);

int Shor(int N);

int getBitLength(int N);

#endif
