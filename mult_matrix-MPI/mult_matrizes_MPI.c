#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>
#include <math.h>

int TAM = 8;

void imprimeMatriz(double *a);

double * mult_matriz(double *a, double *B, int tam, int size); 

double * matrix_randfill();

int main(int argc, char **argv){

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double *A = malloc(sizeof(double) * TAM * TAM);
    double *B = malloc(sizeof(double) * TAM * TAM);
    double *C = malloc(sizeof(double) * TAM * TAM);

    if(rank == 0){
	A = matrix_randfill();
        B = matrix_randfill();
    }

    MPI_Bcast(B, TAM*TAM, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double *a = malloc(sizeof(double) * TAM*TAM/size); 
    
    MPI_Scatter(A, TAM*TAM/size, MPI_DOUBLE, a, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double *c = malloc(sizeof(double) * TAM*TAM/size); 
    c = mult_matriz(a, B, TAM*TAM/size, size);

    MPI_Gather(c, TAM*TAM/size, MPI_DOUBLE, C, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("A: ");
        imprimeMatriz(A);
        printf("\nB: ");
        imprimeMatriz(B);
        printf("\nC: ");
        imprimeMatriz(C);
    }

    free(A);
    free(B);
    free(C);
    free(a);
    free(c);
    
    MPI_Finalize();

    return 0;
}

void imprimeMatriz(double *a){
    int i;

    for(i=0; i<(TAM*TAM); i++){
        printf("%.2f ", a[i]);
    }

    printf("\n");
}

double * mult_matriz(double *a, double *B, int tam, int size){
    double *c, soma = 0;
    int i, j, k=0;
    c = malloc(sizeof(double) * tam);

    for (k = 0; k < tam; k += TAM){
        for(i = 0; i < TAM; i++){
	    for(j = 0; j < TAM; j++){
                soma = soma + a[j + k] * B[j * TAM + i];
            }
            c[i+k] = soma;
            soma = 0;	    
        }
    }

    return c;
}

double * matrix_randfill(){
   int i;
   double *a = malloc(sizeof(double) * TAM*TAM);
   for (i = 0; i < TAM*TAM; i++) {
        a[i] = random() % 10;
   }

   return a;
}