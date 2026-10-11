#ifndef MEASUREMENT_H
#define MEASUREMENT_H


#include "./quantomlibrary.h"



double Calculate_probability(Complex a);

double Propabilty_total(const Quantom_register *q,int target, int bit);

void Output_resut(Quantom_register *q,int amount,int target);

/* Prints P(0) and P(1) for each qubit independently. */
void quantom_print_probabilities(const Quantom_register *q);




#endif
