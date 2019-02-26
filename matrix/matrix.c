#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Matrix {
	char name[100];
	int col;
	int row;
	int **array;
} Matrix;

void initMatrix(Matrix *init, char *s, int rows, int cols){
	init->array = (int **) malloc(sizeof(int *) * rows);
	for(int i = 0; i < rows; i++){
		init->array[i] = (int *) malloc(sizeof(int) * cols);
		for(int k = 0; k < cols; k++){
			init->array[i][k] = 0;
		}
	}
	strcpy(init->name, s);
	init->row = rows;
	init->col = cols;
}

void fillMatrix(Matrix *fill, char *fileName){
	FILE *file = fopen(fileName, "r");
	int rows = 0;
	int cols = 0;
	char buf[100];
	
	while(fgets(buf, 100, file)){
		cols = 0;
		fill->array = realloc(fill->array, sizeof(int *) * (rows+1));
		char *tok;
		tok = strtok(buf, " ");
		while(tok != NULL){
			fill->array[rows] = (int *) realloc(fill->array[rows], sizeof(int) * (cols+1));
			fill->array[rows][cols] = atoi(tok);
			cols++;
			tok = strtok(NULL, " ");
		}
		rows++;
	}
	fill->row = rows;
	fill->col = cols;
	strcpy(fill->name, fileName);
	fclose(file);
}

void printMatrix(Matrix *out){
	printf("%s\n", out->name);
	for(int i = 0; i < out->row; i++){
		for(int k = 0; k < out->col; k++){
			printf("%d ", out->array[i][k]);
		}
		printf("\n");
	}
}

int reNameMatrix(Matrix *reName, char *name){
	if(reName == NULL)
		return 1;
	stpcpy(reName->name, name);
	return 0;
}

int freeMatrix(Matrix *del){
	if(del->array == NULL){
		free(del);
		return 1;
	}
	for(int i = 0; i < del->row; i++){
		free(del->array[i]);
	}
	free(del->array);
	free(del);
	return 0;
}

Matrix * addMatrix(Matrix *a, Matrix *b){
	if( (a->row != b->row) || (a->col != b->col))
		return NULL;
	Matrix *c = (Matrix *) malloc(sizeof(Matrix));
	initMatrix(c, "NONAME", a->row, a->col);
	for(int i = 0; i < a->row; i++){
		for(int k = 0; k < a->col; k++){
			c->array[i][k] = a->array[i][k] + b->array[i][k];
		}
	}
	return c;
}

Matrix * scalarMult(Matrix *a, int num){
	if(a == NULL || a->array == NULL)
		return NULL;
	Matrix *re = (Matrix *) malloc(sizeof(Matrix));
	if(re == NULL)
		return NULL;
	initMatrix(re, "NONAME", a->row, a->col);
	for(int i = 0; i < a->row; i++){
		for(int k = 0; k < a->col; k++){
			re->array[i][k] = a->array[i][k] * num;
		}
	}
	return re;
}

Matrix * multMatrix(Matrix *a, Matrix *b){
	if( a->col != b->row){
		printf("ROWS AND COLS DONT MATCH\n");
		return NULL;
	}
	Matrix *c = (Matrix *) malloc(sizeof(Matrix));
	if(c == NULL)
		return NULL;
	
	stpcpy(c->name, "NONAME");
	c->row = a->row;
	c->col = b->col;
	c->array = (int **) malloc(sizeof(int *) * c->row);
	for(int i = 0; i < c->row; i++){
		c->array[i] = (int *) malloc(sizeof(int) * c->col);
		for(int j = 0; j < c->col; j++){
			int sum = 0;
			for(int m = 0; m < a->col; m++){
				sum += (a->array[i][m])*(b->array[m][j]);
			}
			c->array[i][j] = sum;
		}
	}
	return c;
}

