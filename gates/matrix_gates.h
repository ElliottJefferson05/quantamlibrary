#ifndef MATRIX_GATES_H
#define MATRIX_GATES_H

#include "../quantomlibrary.h"

typedef struct{
    Complex matrix[2][2];
}Matrix2x2;

typedef struct{
    Complex matrix[4][4];
}Matrix4x4;


typedef struct{
    Complex matrix[8][8];
}Matrix8x8;

Matrix2x2 hadamarMatrix(void);
Matrix2x2 xMatrix(void);
Matrix2x2 zMatrix(void);
Matrix4x4 CNOTMatrix(void);
Matrix2x2 yMatrix(void);
Matrix2x2 sMatrix(void);
Matrix2x2 tMatrix(void);    
Matrix4x4 swapMatrix(void);
Matrix4x4 controlledPhase(double theta);
Matrix8x8 ToffoliMatrix(void);


#endif
