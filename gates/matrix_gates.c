#include <math.h>
#include "matrix_gates.h"



Matrix2x2 hadamarMatrix(void){

    double number = 1 / sqrt(2.0);
    Matrix2x2 hadamarM;
    hadamarM.matrix[0][0] = complex_initiliaze(number,0.0);
    hadamarM.matrix[0][1] = complex_initiliaze(number,0.0);
    hadamarM.matrix[1][0] = complex_initiliaze(number,0.0);
    hadamarM.matrix[1][1] = complex_initiliaze(-number,0);

    return hadamarM;

}

Matrix2x2 xMatrix(void){

    Matrix2x2 XM;
    XM.matrix[0][0] = complex_initiliaze(0,0.0);
    XM.matrix[0][1] = complex_initiliaze(1,0.0);
    XM.matrix[1][0] = complex_initiliaze(1,0.0);
    XM.matrix[1][1] = complex_initiliaze(0,0);

    return XM;

}

Matrix2x2 zMatrix(void){

    Matrix2x2 zM;
    zM.matrix[0][0] = complex_initiliaze(1,0.0);
    zM.matrix[0][1] = complex_initiliaze(0,0.0);
    zM.matrix[1][0] = complex_initiliaze(0,0.0);
    zM.matrix[1][1] = complex_initiliaze(-1,0);

    return zM;

}

Matrix2x2 yMatrix(void){
    Matrix2x2 yM;
    yM.matrix[0][0] = complex_initiliaze(0,0.0);
    yM.matrix[0][1] = complex_initiliaze(0,-1);
    yM.matrix[1][0] = complex_initiliaze(0,1);
    yM.matrix[1][1] = complex_initiliaze(0,0);

    return yM;
}

Matrix4x4 CNOTMatrix(void){

    Matrix4x4 CNOT;

    CNOT.matrix[0][0] = complex_initiliaze(1,0.0);
    CNOT.matrix[0][1] = complex_initiliaze(0,0.0);
    CNOT.matrix[0][2] = complex_initiliaze(0,0.0);
    CNOT.matrix[0][3] = complex_initiliaze(0,0.0);
    CNOT.matrix[1][0] = complex_initiliaze(0,0.0);
    CNOT.matrix[1][1] = complex_initiliaze(1,0.0);
    CNOT.matrix[1][2] = complex_initiliaze(0,0.0);
    CNOT.matrix[1][3] = complex_initiliaze(0,0.0);
    CNOT.matrix[2][0] = complex_initiliaze(0,0.0);
    CNOT.matrix[2][1] = complex_initiliaze(0,0.0);
    CNOT.matrix[2][2] = complex_initiliaze(1,0.0);
    CNOT.matrix[2][3] = complex_initiliaze(0,0.0);
    CNOT.matrix[3][0] = complex_initiliaze(0,0.0);
    CNOT.matrix[3][1] = complex_initiliaze(0,0.0);
    CNOT.matrix[3][2] = complex_initiliaze(0,0.0);
    CNOT.matrix[3][3] = complex_initiliaze(1,0.0);

    return CNOT;
}
