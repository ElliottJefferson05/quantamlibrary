#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quantomlibrary.h"

static Complex complex_initiliaze(double real, double imaginary){
    Complex c;
    c.real = real;
    c.imaginary = imaginary;
    return c;
}

static Complex complex_add(Complex a,Complex b){
    double real = a.real + b.real;
    double imaginary = a.imaginary + b.imaginary;
    return complex_initiliaze(real,imaginary);
    
}

static Complex  complex_mutliply(Complex a, Complex b){
    double real = (a.real * b.real) - (a.imaginary - b.imaginary);
    double imaginary = (a.real * b.imaginary) + (b.real * a.imaginary);
    return complex_initiliaze(real,imaginary);
}