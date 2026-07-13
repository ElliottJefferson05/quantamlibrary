#ifndef MATRIX_GATES_H
#define MATRIX_GATES_H

#include "../quantomlibrary.h"

typedef struct{
    Complex matrix[2][2];
}Matrix2x2;

typedef struct{
    Complex matrix[4][4];
}Matrix4x4;

Matrix2x2 hadamarMatrix(void);
Matrix2x2 xMatrix(void);
Matrix2x2 zMatrix(void);
Matrix4x4 CNOTMatrix(void);
Matrix2x2 yMatrix(void);


#endif
