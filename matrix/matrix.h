#ifndef MATRIX_H
#define MATRIX_H

#include "matrix.c"

void initMatrix(Matrix *init, char *s, int rows, int cols);
void fillMatrix(Matrix *fill, char *fileName);

void printMatrix(Matrix *out);
int reNameMatrix(Matrix *reName, char *name);
int freeMatrix(Matrix *del);

Matrix * addMatrix(Matrix *a, Matrix *b);
Matrix * scalarMult(Matrix *a, int num);
Matrix * multMatrix(Matrix *a, Matrix *b);
#endif
