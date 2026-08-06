#ifndef MEASUREMENT_H
#define MEASUREMENT_H


#include "./quantomlibrary.h"



double Calculate_probability(Complex a);

double Propabilty_total(Quantom_register *q,int target, int bit);

void Output_resut(Quantom_register *q,int amount,int target);




#endif
