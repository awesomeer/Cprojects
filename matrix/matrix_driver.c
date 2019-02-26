#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int main(int argc, char *argv[]){
	Matrix *a = (Matrix *) malloc(sizeof(Matrix));
	Matrix *b = (Matrix *) malloc(sizeof(Matrix));
	fillMatrix(a, argv[1]);
	fillMatrix(b, argv[2]);
	
	Matrix *result = ( Matrix *) multMatrix(a, b);
	if(result != NULL){
		
		reNameMatrix(result, "Matrix result");
		printMatrix(result);
		freeMatrix(result);
	}
	else printf("Matrix NULL\n");
	freeMatrix(a);
	freeMatrix(b);
	

