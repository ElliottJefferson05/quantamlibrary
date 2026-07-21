#include <math.h>
#include "measurment.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


double Calculate_probability(Complex a) {
    return (a.real * a.real) + (a.imaginary * a.imaginary);
}



double Propabilty_total(Quantom_register *q, int target, int bit) {

    if (q == NULL || q->state == NULL) {
        return -1.0;
    }

    if (target < 0 || target >= q->num_of_qbits) {
        return -1.0;
    }

    if (bit != 0 && bit != 1) {
        return -1.0;
    }

    double probability = 0.0;
    int target_bit = 1 << target;

    for (int i = 0; i < q->state_size; i++) {

        int bit_value;

        if ((i & target_bit) != 0) {
            bit_value = 1;
        } else {
            bit_value = 0;
        }

        if (bit_value == bit) {
            probability += Calculate_probability(q->state[i]);
        }
    }

    return probability;
}






void Output_resut(Quantom_register *q,int amount,int target){


    if( q == NULL || q->state == NULL){
        return;
    }

    if (target < 0 || target >= q->num_of_qbits){
        return;
    }

    if(amount <= 0){
        return;
    }


    double zero_prob = Propabilty_total(q,target,0);

    int zero_amount = 0;
    int one_amount = 0;

     for (int i = 0; i < amount; i++) {
        double random_value = (double)rand() / RAND_MAX;

        if (random_value < zero_prob) {
            zero_amount++;
        } else {
            one_amount++;
        }
    }

    printf("Measurement results for q%d over %d runs:\n", target, amount);
    printf("Measured 0: %d times\n", zero_amount);
    printf("Measured 1: %d times\n", one_amount);
    


}
