/*
 *  Exemplo de programa para multiplicacao de matrizes em paralelo.
 *  Para fins de simplificacao, as matrizes devem ser quadradas.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <mpi.h>
#include <math.h>
#include "matrix.h"

#define MASTER 0        // id do mestre
#define MSG_TAG 0       // tag das mensagens

matrix_t *A;

matrix_t *B;

block_t *particoes;


// Envia matriz 'm' para processo 'dest'.
void mpi_send_matrix(matrix_t *m, int dest)
{
   MPI_Send(&m->rows, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
   MPI_Send(&m->cols, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
   MPI_Send(&m->data[0][0], m->rows * m->cols, MPI_DOUBLE, dest, MSG_TAG,
            MPI_COMM_WORLD);
}

// Envia um bloco da matriz 'm' para processo 'dest'.
// Atencao: so funciona para blocos contendo linhas completas.
void mpi_send_submatrix(matrix_t *m, block_t part, int dest)
{
   int rows = part.row_end - part.row_start;
   int cols = part.col_end - part.col_start;
   assert(cols == m->cols);

   MPI_Send(&rows, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);
   MPI_Send(&cols, 1, MPI_INT, dest, MSG_TAG, MPI_COMM_WORLD);   
   MPI_Send(&m->data[part.row_start][0], rows * cols, MPI_DOUBLE, dest, 
            MSG_TAG, MPI_COMM_WORLD);
}

// Recebe matriz do processo 'source'.
matrix_t *mpi_recv_matrix(int source)
{
   MPI_Status status;
   matrix_t *m;
   int rows, cols;
   MPI_Recv(&rows, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   MPI_Recv(&cols, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   m = matrix_create(rows, cols);
   MPI_Recv(&m->data[0][0], rows * cols, MPI_DOUBLE, source, MSG_TAG,
            MPI_COMM_WORLD, &status);
   return m;
}


// Recebe um bloco da matriz 'm' calculado pelo processo 'source'.
void mpi_recv_submatrix(matrix_t *m, block_t part, int source)
{
   MPI_Status status;
   int rows, cols;
   MPI_Recv(&rows, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   MPI_Recv(&cols, 1, MPI_INT, source, MSG_TAG, MPI_COMM_WORLD,
            &status);
   assert(cols == m->cols);
   MPI_Recv(&m->data[part.row_start][0], rows * cols, MPI_DOUBLE, source, MSG_TAG,
            MPI_COMM_WORLD, &status);
}





// Funcao executada pelos processos trabalhadores
void matrix_mult_slave()
{
   //matrix_t *A = mpi_recv_matrix(MASTER);
   //matrix_t *B = mpi_recv_matrix(MASTER);
   //matrix_t *A
   int tamB;
   MPI_Bcast(&tamB, 1, MPI_INT, 0, MPI_COMM_WORLD);
   matrix_t *B = matrix_create(tamB, tamB);
   MPI_Bcast(&B->data[0][0], B->rows * B->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   /*
   matrix_t *C = matrix_multiply(A, B);
   mpi_send_matrix(C, MASTER);
   matrix_destroy(A);
   matrix_destroy(B);
   matrix_destroy(C);
   */
}

// Funcao de multiplicacao executada pelo processo mestre
matrix_t *matrix_mult_master(matrix_t *A, matrix_t *B, int ntasks, double *mres)
{

   int i;
   //block_t *part;
   matrix_t *C;
   
   assert(A->cols == B->rows);

   C = matrix_create(A->rows, B->cols);

   // Particiona matriz em 'ntasks' partes
   //part = matrix_row_partition(A, ntasks);
/*
   // Envia dados para trabalhadores
   for (i = 0; i < ntasks-1; i++) {
      mpi_send_submatrix(A, part[i], i + 1);
      //mpi_send_matrix(B, i + 1);
   }
*/

   MPI_Scatter(&A->data[0][0], A->cols * A->cols /ntasks, MPI_DOUBLE, &mres, A->cols * A->cols /ntasks, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    
   i = B->rows;
   MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Bcast(&B->data[0][0], B->rows * B->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

/*
   // Mestre calcula uma parte do produto
   //matrix_block_multiply(A, B, C, &part[ntasks-1]);

   // Recebe dados dos trabalhadores
   for (i = 0; i < ntasks-1; i++) {
      mpi_recv_submatrix(C, part[i], i + 1);
   }
   partition_destroy(part);
*/
   return C;
}





int main(int argc, char **argv)
{
   int n;
   int rc;
   int taskid, ntasks;
   double start_time, end_time;

//   MPI_Datatype mPart;
  // MPI_Type_commit(&mPart);

  // double *mres;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

   if ((argc != 2)) {
      printf("Uso: mpirun -np <nprocs> %s <ordem da matriz quadrada>\n", 
             argv[0]);
      MPI_Abort(MPI_COMM_WORLD, rc);
      exit(1);
   }

   if (taskid == MASTER) {  // Codigo executado pelo processo mestre

      n = atoi(argv[1]);

      matrix_t *C;

      

      // Cria matrizes
      A = matrix_create(n, n);
      matrix_randfill(A);
      B = matrix_create(n, n);
      matrix_fill(B, 1.);

      // Calcula C = A * B, medindo o tempo
      start_time = MPI_Wtime();
      
      C = matrix_create(n, n);


      //MPI_Scatter(&A->data[0][0], floor(A->rows / ntasks) * A->cols, MPI_DOUBLE, &mres, floor(A->rows / ntasks) * A->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   
    //broadcast second matrix to all processes
      int i = B->rows;
      MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Bcast(&B->data[0][0], B->rows * B->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

      particoes = matrix_row_partition(A, ntasks);
     
      //partition_print(particoes + 3);
      //partition_print(&(particoes[3]));
      //int nParticoes = sizeof(particoes) * sizeof(block_t *) / sizeof(block_t);
      //printf("Num particoes: %d\n", nParticoes);

      block_t *p1 = partition_create(1);
      //block_t *p1 = partition_create(ntasks);

      MPI_Scatter(&particoes, 1, MPI_INT, p1, 1, MPI_INT, 0, MPI_COMM_WORLD);
/*
      matrix_t *A_Master = matrix_submatrix(A, p1);
      
      //C = matrix_mult_master(A, B, ntasks, &mres);
      end_time = MPI_Wtime();

      // Mostra estatisticas da execucao
      printf("%d %f\n", ntasks, end_time - start_time);
      fflush(stdout);
*/
      matrix_destroy(A);
      matrix_destroy(B);
      matrix_destroy(C);

   }
   
    else { // Codigo executado pelos processos trabalhadores

    //broadcast second matrix to all processes
      int tamB;
      MPI_Bcast(&tamB, 1, MPI_INT, 0, MPI_COMM_WORLD);
      matrix_t *B_Slave = matrix_create(tamB, tamB);
      MPI_Bcast(&B_Slave->data[0][0], B_Slave->rows * B_Slave->cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

      block_t *p1 = partition_create(1);
     // block_t *p1 = partition_create(ntasks);

      MPI_Scatter(particoes, 1, MPI_INT, p1, 1, MPI_INT, 0, MPI_COMM_WORLD);

     // partition_print(p1);
/*
      matrix_t *A_Slave = matrix_submatrix(A, p1);

      matrix_t *C_Slave = matrix_create(p1->row_end - p1->row_start, p1->col_end - p1->col_start);
      
      matrix_block_multiply(A_Slave, B_Slave, C_Slave, p1);
   */
    }
   MPI_Finalize();
   return 0;
}
