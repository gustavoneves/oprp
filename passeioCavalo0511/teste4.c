#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#include <mpi.h>

//#include <string.h>
//#include <pthread.h>

#define N 6

#define MASTER 0        // id do mestre
/*
typedef struct{
	int **visitados;
	int xInicial;
	int yInicial;
	int contadorPassos;
}parametros_t;

int **criaMatriz(int n);

void * funcThreads(void * args);
*/
//MPI_File fp;


// Below arrays details all 8 possible movements for a knight.
// It is important to avoid changing sequence of below arrays
int row[] = { 2, 1, -1, -2, -2, -1,  1,  2 , 2 };
int col[] = { 1, 2,  2,  1, -1, -2, -2, -1, 1 };

// Check if (x, y) is valid chess board coordinates
// Note that a knight cannot go out of the chessboard
int isValid(int x, int y)
{
	if (x < 0 || y < 0 || x >= N || y >= N)
		return 0;

	return 1;
}

void imprime(int **visited){
	for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				printf("%d ", visited[i][j]);
			}
			printf("\n");
		}
		printf("\n");
}
// Recursive function to perform the Knight's tour using backtracking
//void KnightTour(int visited[N][N], int x, int y, int pos)
void KnightTour(int **visited, int x, int y, int pos, MPI_File fp)
{
	// mark current square as visited	
	visited[x][y] = pos;
	
	// if all squares are visited, print the solution
	if (pos >= N*N){
		/*
		FILE *fp;
		
		char processor_name[MPI_MAX_PROCESSOR_NAME];
		char nomeArqSaida[MPI_MAX_PROCESSOR_NAME+1];
    	int name_len;
		int id;
    	//MPI_Get_processor_name(processor_name, &name_len);
		MPI_Get_processor_name(nomeArqSaida, &name_len);
		*/
		int id;
		//MPI_Comm_rank(MPI_COMM_WORLD, &id);

		//MPI_Send(visited,N*N,MPI_INT,0, id, MPI_COMM_WORLD);
		//MPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
		MPI_Status status;
		MPI_File_write_shared(fp, visited, N*N, MPI_INT, &status);

		//MPI_File_write_shared(fp, visited, N*N, MPI_INT, MPI_STATUS_IGNORE);
		//MPI_File_write_ordered(fp, visited, N*N, MPI_INT, MPI_STATUS_IGNORE);
		/*
		nomeArqSaida[name_len+1] = id;

		//memcpy(nomeArqSaida, processor_name, strlen(processor_name)+1);
		//fp = fopen(processor_name, "a");
		fp = fopen(nomeArqSaida, "a");
      
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				//printf("%d ", visited[i][j]);
				fprintf(fp, "%d ", visited[i][j]);
			}
			//printf("\n");
			fprintf(fp, "\n");
		}
		//printf("\n");
		fprintf(fp, "\n");

		fclose(fp);
		*/
		// backtrack before returning
		visited[x][y] = 0;
		return;
	}

	// check for all 8 possible movements for a knight
	// and recur for each valid movement
    //#pragma omp parallel for firstprivate(visited, x, y, pos, row, col)
	for (int k = 0; k < 8; k++){
		// Get the new position of Knight from current
		// position on chessboard
		int newX = x + row[k];
		int newY = y + col[k];

		// if new position is a valid and not visited yet
		if (isValid(newX, newY) && !visited[newX][newY]){
			KnightTour(visited, newX, newY, pos + 1, fp);
		}
	}

	// backtrack from current square and remove it from current path
	visited[x][y] = 0;
}

/*
// Print all Possible Knight's Tours in a chessboard
int main()
{
	// visited[][] serves two purpose -
	// 1. It keep track of squares involved the Knight's tour.
	// 2. It stores the order in which the squares are visited
	int visited[N][N];
	
	// initialize visited[][] by 0 (unvisited)
	memset(visited, 0, sizeof visited);

	int pos = 1;
	
	// start knight tour from corner square (0, 0)
	KnightTour(visited, 0, 0, pos);
	
	return 0;
}
*/

int main(int argc, char **argv){
	// visited[][] serves two purpose -
	// 1. It keep track of squares involved the Knight's tour.
	// 2. It stores the order in which the squares are visited
    int i,j;

//	parametros_t * p = malloc(sizeof(parametros_t) * 8);

//	pthread_t * threads = malloc(sizeof(pthread_t) * 8);
	int taskid, ntasks;
	MPI_Status status;
	
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	int dados[2];
	int l = 0;
	MPI_File fp;

	//if(taskid == 0){ // for o master
	if(taskid == MASTER){
		//printf("ntasks: %d\n", ntasks);
		MPI_File_open(MPI_COMM_WORLD, "/home/udesc/Downloads/passeioCavalo2410/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp); 
		for(i=1;i<ntasks;i++){
			dados[0] = l;
			l++;
			dados[1] = l;
			l++; 
			MPI_Send(dados,2,MPI_INT,i,0, MPI_COMM_WORLD);
		}

		/*
		for(i=1;i<size;i++){
			dados[0] = l;
			l++;
			dados[1] = l;
			l++; 
			MPI_Send(dados,2,MPI_INT,i,0, MPI_COMM_WORLD);
		}
		*/
	/*
		}
	} else {
		printf("%d esta esperando\n", rank);
		MPI_Recv(msg,20,MPI_CHAR,0,tag, MPI_COMM_WORLD, &status);
		printf("Message received: %s\n", msg);
	}
	*/
	}
	
	else{
		MPI_Recv(dados,2,MPI_INT,0,0, MPI_COMM_WORLD, &status);
		printf("Proc: %d	dados[0]: %d	dados[1]: %d\n", taskid, dados[0], dados[1]);
	
		int linhaMax;
		int colMax = 8;
		int k;
    	//for(i=0; i<N;i++){
		for(i=dados[0]; i<=dados[1]; i++){
    	    #pragma omp parallel for firstprivate(i) private(j)
    	    //for(j=0; j<colMax; j++){
			for(j=0; j<6; j++){
				int **visited;

				visited = calloc(sizeof(int *), 6);
				for(k=0; k<6; k++){
					visited[k] = calloc(sizeof(int), 6);
				}
/*
				visited = calloc(sizeof(int *), N);
				for(int i=0; i<N; i++){
					visited[i] = calloc(sizeof(int), N);
				}
*/
				KnightTour(visited, i, j, 1, fp);
				free(visited[0]);
				free(visited[1]);
				free(visited);
        	}
    	}
			
	}

	if(taskid == MASTER){
		MPI_File_close(&fp);
	}

/*
		for(i=1;i<ntasks;i++){
			int **resposta;

			resposta = calloc(sizeof(int *), 6);
			for(k=0; k<6; k++){
				resposta[k] = calloc(sizeof(int), 6);
			}
			MPI_Recv(resposta,N*N, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
		}
	}
	
*/
	MPI_Finalize();
	return 0;
}

/*
int **criaMatriz(int n){
	int **m = calloc(sizeof(int *), n);
	for(int i=0; i<n; i++){
		m[i] = calloc(sizeof(int), n);
	}

	return m;
}

void * funcThreads(void * args){
	parametros_t * p = (parametros_t *) args;
	KnightTour(p->visitados, p->xInicial, p->yInicial, p->contadorPassos);
}
*/

/* sequencial com printfs
real	0m1.966s
user	0m1.956s
sys	0m0.008s
*/

/* openmp com printfs
real	0m0.561s
user	0m2.424s
sys	0m0.004s
*/