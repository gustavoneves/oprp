#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
//#include <pthread.h>

#define N 8

typedef struct{
	int **visitados;
	int xInicial;
	int yInicial;
	int contadorPassos;
}parametros_t;

int **criaMatriz(int n);

void * funcThreads(void * args);

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

// Recursive function to perform the Knight's tour using backtracking
//void KnightTour(int visited[N][N], int x, int y, int pos)
void KnightTour(int **visited, int x, int y, int pos)
{
	// mark current square as visited	
	visited[x][y] = pos;
	
	// if all squares are visited, print the solution
	if (pos >= N*N){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				printf("%d ", visited[i][j]);
			}
			printf("\n");
		}
		printf("\n");
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
			KnightTour(visited, newX, newY, pos + 1);
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



    //#pragma omp parallel for private(i, j)
    for(i=0; i<N;i++){
        #pragma omp parallel for firstprivate(i) private(j)
        for(j=0; j<N; j++){
            //int visited[N][N];

			int **visited;

			visited = calloc(sizeof(int *), N);

			for(int i=0; i<N; i++){
				visited[i] = calloc(sizeof(int), N);
			}

			KnightTour(visited, i, j, 1);
			free(visited[0]);
			free(visited[1]);
			free(visited);

	
	/*
	        // initialize visited[][] by 0 (unvisited)
	        //memset(visited, 0, sizeof visited);

	        int pos = 1;
	
	        // start knight tour from corner square (0, 0)
	        KnightTour(visited, i, j, pos);
	*/
        }
    }
	
	
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