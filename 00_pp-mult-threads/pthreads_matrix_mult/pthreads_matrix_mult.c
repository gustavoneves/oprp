/*
 *  Exemplo de programa para multiplicacao de matrizes em paralelo, usando POSIX threads.
 *  Obs.: Somente para matrizes quadradas.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "matrix.h"
//#include <math.h>

void * ordenaMergeSortP(void * arg); 
/*
 * Estrutura que contem parametros para as threads
 */
typedef struct {
      int tid;
      int ntasks;
      matrix_t *A;
      matrix_t *B;
      matrix_t *C;
} param_t;

typedef struct {
    double *v;
   // int inicio, meio, fim;
   unsigned int inicio, fim;
    int nivel;
} param_ord;


/*
 * Calcula linhas da matriz resultante C
 */
void matrix_mult(int tid, int ntasks, matrix_t* A, matrix_t* B, matrix_t* C)
{
   int i, j, k;
   double sum;
   int n = A->rows;
   i = tid;
   // Calcula algumas linhas da matriz resultante
   while (i < n) {
      for (j = 0; j < n; j++) {
         sum = 0.0;
         for (k = 0; k < n; k++) {
            sum += A->data[i][k] * B->data[k][j];
         }
         C->data[i][j] = sum;
      }
      i += ntasks;
   }
}

/*
 * Funcao executada por uma thread
 */
void *matrix_mult_worker(void *arg)
{
   param_t *p = (param_t *) arg;
   matrix_mult(p->tid, p->ntasks, p->A, p->B, p->C);
}

/*
 * Calcula C = A * B, distribuindo o trabalho entre ntasks threads
 */
void matrix_mult_threads(matrix_t *A, matrix_t *B, matrix_t* C, int ntasks)
{
   int i;
   pthread_t *threads;
   param_t *args;

   threads = (pthread_t *) malloc(ntasks * sizeof(pthread_t));
   args = (param_t *) malloc(ntasks * sizeof(param_t));

   for (i = 0; i < ntasks; i++)
   {
      args[i].tid = i;
      args[i].ntasks = ntasks;
      args[i].A = A;
      args[i].B = B;
      args[i].C = C;
      pthread_create(&threads[i], NULL, matrix_mult_worker, (void *) (args+i));
   }
   for (i = 0; i < ntasks; i++)
   {
      pthread_join(threads[i], NULL);
   }
   free(args);
   free(threads);
}

/*
 * Tempo (wallclock) em segundos
 */
double wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec + (double) t.tv_usec / 1000000;
}


void merge(double *arr, unsigned int l, unsigned int m, unsigned int r){ 
    unsigned int i, j, k; 
    unsigned int n1 = m - l + 1; 
    unsigned int n2 =  r - m; 
    double *L;
    double *R;
  
    L = calloc(n1, sizeof(double));
    R = calloc(n2, sizeof(double));
   
    for (i = 0; i < n1; i++){ 
        L[i] = arr[l + i]; 
    }
    for (j = 0; j < n2; j++){ 
        R[j] = arr[m + 1+ j]; 
    }
    
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){ 
        if (L[i] <= R[j]){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
    free(L);
    free(R);
} 

void mergeSort(double *arr, unsigned int l, unsigned int r){ 
    if(l < r){ 
        unsigned int m = l+(r-l)/2; 
  
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

void * mergeSortP(void * arg){
   param_ord *p = (param_ord *) arg;
   pthread_t *thread;
   if(p->inicio < p->fim){ 
        if(p->nivel < 4){
           param_ord *pL = malloc(sizeof(param_ord));
           param_ord *pR = malloc(sizeof(param_ord));

           thread = malloc(2 * sizeof(pthread_t));

           pL->nivel = (p->nivel)+1;
           pL->inicio = p->inicio;
           pL->fim = (p->fim - p->inicio) / 2;
           pL->v = p->v;

           pR->nivel = (p->nivel)+1;
           pR->inicio = ((p->fim - p->inicio) / 2) + 1;
           pR->fim = p->fim;
           pR->v = p->v;

           pthread_create(&thread[0], NULL, mergeSortP, (void *) pL);
           pthread_create(&thread[1], NULL, mergeSortP, (void *) pR);
           pthread_join(thread[0], NULL);
           pthread_join(thread[1], NULL);

           free(pL);
           free(pR);

           free(thread);
        }
        else{
           unsigned int m = p->inicio + (p->fim - p->inicio)/2; 
  
           mergeSort(p->v, p->inicio, m); 
           mergeSort(p->v, m+1, p->fim); 
  
           merge(p->v, p->inicio, m, p->fim);
        } 
        unsigned int m = p->inicio + (p->fim - p->inicio)/2; 
        //mergeSort(p->v, p->inicio, m); 
        //mergeSort(p->v, m+1, p->fim); 
  
        merge(p->v, p->inicio, m, p->fim);
    } 
} 

int main(int argc, char **argv)
{
   int n;
   int rc;
   int taskid, ntasks;
   double start_time, end_time;

   if ((argc != 3)) {
      printf("Uso: %s <nthreads> <ordem da matriz quadrada>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   ntasks = atoi(argv[1]); // ntasks = nthreads
   n = atoi(argv[2]);      // ordem da matriz

   matrix_t *A = matrix_create(n, n);
   matrix_randfill(A);
   matrix_t *B = matrix_create(n, n);

   matrix_randfill(B);
   matrix_t *C = matrix_create(n, n);

   //Calcula C = A * B em ntasks
   matrix_mult_threads(A, B, C, ntasks);


   matrix_print(C);
   printf("\n\n");

   param_ord *p = malloc(sizeof(param_ord));
   p->nivel = 1;
   p->inicio = p->inicio;
   p->fim = (n*n)-1;
   p->v = C->data[0];

   start_time = wtime();
   mergeSortP(p);
   end_time = wtime();  


   matrix_print(C);

   // Mostra estatisticas da execucao
   printf("%d %f\n", ntasks, end_time - start_time);
   fflush(stdout);

   matrix_destroy(A);
   matrix_destroy(B);
   matrix_destroy(C);

   return EXIT_SUCCESS;
}
