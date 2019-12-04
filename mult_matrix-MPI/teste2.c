#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAM 8

double **criaMatriz(int tam);

void inicializaMatriz(double **m, int tam, double val);

void imprimeMatriz(double **m, int tam);

double * mult_matriz(double *a, double **B, int tam);

void destroiMatriz(double **m);

int main(int argc, char **argv){

    double **A;
    double **B;
    double **C;

    int i, size, rank;
    
    //double *c;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double *a = malloc(sizeof(double) * TAM*TAM/size);
    if(rank == 0){
        printf("MASTER\n");
        double **A = criaMatriz(TAM);
        for(i=0; i<TAM; i++){
            for(int j=0; j<TAM; j++){
                A[i][j]=i;
            }
        }
        //imprimeMatriz(A, TAM);

        double **B = criaMatriz(TAM);
        inicializaMatriz(B, TAM, 2);
        double **C = criaMatriz(TAM);

        
        //double *a = malloc(sizeof(double) * TAM*TAM/size);
        double *c = malloc(sizeof(double) * TAM);

        //MPI_Scatter(A, TAM*TAM/size, MPI_DOUBLE, a, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        for(i=0; i<TAM; i++){
            printf("%f ", a[i]);
        }
        printf("\n");
    
/*
        MPI_Bcast(&B[0][0], TAM*TAM, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        c = mult_matriz(a, B, TAM);

        MPI_Gather(c, TAM*TAM/size, MPI_DOUBLE, C, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
        imprimeMatriz(C, TAM);
*/
        //destroiMatriz(A);
        //destroiMatriz(B);
        //destroiMatriz(C);
    }

 //   else{
 //       printf("SLAVE: %d\n", rank);
  //      double *a = malloc(sizeof(double) * TAM*TAM/size);
        /*
        double * c = malloc(sizeof(double) * TAM);
        double **B_Slave = criaMatriz(TAM);
        double **A;
        double **C;
        */
   
        //MPI_Scatter(A, TAM*TAM/size, MPI_DOUBLE, a, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

 //       int i;
  //      for(i=0; i<TAM; i++){
 //           printf("%f ", a[i]);
  //      }

  //      printf("\n\n");
  //  }

       /* 
        MPI_Bcast(&B_Slave[0][0], TAM*TAM, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        //imprimeMatriz(B_Slave, TAM);
        c = mult_matriz(a, B_Slave, TAM);
        MPI_Gather(c, TAM*TAM/size, MPI_DOUBLE, C, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        */
  //      destroiMatriz(B_Slave);
//    }
    MPI_Scatter(A, TAM*TAM/size, MPI_DOUBLE, a, TAM*TAM/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for(i=0; i<TAM; i++){
            printf("%f ", a[i]);
    }

    printf("\n\n");
    MPI_Finalize();
    return 0;
}

double **criaMatriz(int tam){
    double **m;

    int i;
    double *v;

    v = malloc(sizeof(double) * tam * tam);
    m = malloc(tam * sizeof(double *));

    for(i=0; i<tam; i++){
        m[i] = &v[i * tam];
    }
    /*
    for(i=0; i<tam; i++){
        m[i] = (double *)malloc(sizeof(double) * tam);
    }
    */
    return m;
}

void inicializaMatriz(double **m, int tam, double val){
    int i, j;

    for(i=0; i<tam; i++){
        for(j=0; j<tam; j++){
            m[i][j] = val;
        }
    }
}

void imprimeMatriz(double **m, int tam){
    int i, j;

    for(i=0; i<tam; i++){
        for(j=0; j<tam; j++){
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
     printf("\n");
}

double * mult_matriz(double *a, double **B, int tam){
    double *c, soma;
    int i, j;
    c = malloc(sizeof(double) * tam);
    soma = 0;

    for(i=0; i<tam; i++){
        for(j=0; i<tam; j++){
            soma = soma + a[j] + B[j][i];
        }
        c[i] = soma;
        soma = 0;
    }
    return c;
}

void destroiMatriz(double **m){
    free(&m[0][0]);
    free(m);
}