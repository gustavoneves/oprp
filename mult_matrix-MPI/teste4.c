#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define TAM 8

void inicializaMatriz(double *a, int linha, int coluna);

void imprimeMatriz(double *a, int linha, int coluna);

double * mult_matriz(double *a, double *B, int tam);

double * mult_matriz2(double *a, double *B, int tam, int size); 

int main(int argc, char **argv){
   
    int i, size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    

    if(rank == 0){
	double *A = malloc(sizeof(double) * TAM * TAM);
    	double *B = malloc(sizeof(double) * TAM * TAM);
    	double *C = malloc(sizeof(double) * TAM * TAM);

        inicializaMatriz(A, TAM, TAM);
        inicializaMatriz(B, TAM, TAM);
        //imprimeMatriz(C, TAM, TAM);	
	
	double *a = malloc(sizeof(double) * TAM*TAM/size); 

	MPI_Bcast(B, TAM*TAM, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    	MPI_Scatter(A, TAM*TAM/size, MPI_DOUBLE, a, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    	double *c = malloc(sizeof(double) * TAM*TAM/size); 

    	c = mult_matriz2(a, B, TAM*TAM/size, size);

    	MPI_Gather(c, TAM*TAM/size, MPI_DOUBLE, C, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
/*
        printf("A: ");
        imprimeMatriz(A, TAM, TAM);
        printf("\nB: ");
        imprimeMatriz(B, TAM, TAM);
        printf("\nC: ");
        imprimeMatriz(C, TAM, TAM);

        free(A);
        free(B);
        free(C);
        free(a);
        free(c);
*/
    }
    else{
	double *A = malloc(sizeof(double) * TAM * TAM);
    	double *B = malloc(sizeof(double) * TAM * TAM);
    	double *C = malloc(sizeof(double) * TAM * TAM);

	double *a = malloc(sizeof(double) * TAM*TAM/size); 

	MPI_Bcast(B, TAM*TAM, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    	MPI_Scatter(A, TAM*TAM/size, MPI_DOUBLE, a, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    	double *c = malloc(sizeof(double) * TAM*TAM/size); 

    	c = mult_matriz2(a, B, TAM*TAM/size, size);

    	MPI_Gather(c, TAM*TAM/size, MPI_DOUBLE, C, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	free(A);
        free(B);
        free(C);
        free(a);
        free(c);
    }

    MPI_Finalize();
    return 0;
}

void inicializaMatriz(double *a, int linha, int coluna){
    int i, j;

    for(i=0; i<(linha*coluna); i++){
            a[i] = i+1;
    }
}

void imprimeMatriz(double *a, int linha, int coluna){
    int i;
    for(i=0; i<(linha*coluna); i++){
            printf("%.2f ", a[i]);
    }
    printf("\n");
}

double * mult_matriz(double *a, double *B, int tam){
    double *c, soma;
    int i, j;
    c = malloc(sizeof(double) * tam);
    soma = 0;

    for(i=0; i<tam; i++){
        for(j=0; j<tam; j++){
            soma = soma + a[j] * B[i + j];
        }
        c[i] = soma;
        soma = 0;
    }
    return c;
}

double * mult_matriz2(double *a, double *B, int tam, int size){
    double *c, soma;
    int i, j;
    c = malloc(sizeof(double) * tam);
    soma = 0;

    for(i=0; i<tam; i++){
        for(j=0; j<tam*size; j++){
            soma = soma + a[j] * B[j * TAM + i];
        }
	
        c[i] = soma;
        soma = 0;
    }
    return c;
}