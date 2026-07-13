#include <math.h>
#include "operations.h"
#include "../quantomlibrary.h"


Complex Complex_congiguate(Complex a){

    double real = a.real;
    double imaginary = -a.imaginary;
    return complex_initiliaze(real,imaginary);

}



