#include <iostream>
// #include <stdlib.h>
// #include <string.h>
#include <omp.h>

#include <mpi.h>

#define N 6

#define MASTER 0        // id do mestre

using namespace std;

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
	int i,j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%d ", visited[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
// Recursive function to perform the Knight's tour using backtracking
void KnightTour(int **visited, int x, int y, int pos, MPI_File fp){
//void KnightTour(int **visited, int x, int y, int pos){
	// mark current square as visited	
	visited[x][y] = pos;
	int k,i, j;
	
	// if all squares are visited, print the solution
	if (pos >= N*N){
		MPI_Status statusSlave;

		char string[256];
		int slength = 0;
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				sprintf(string + slength, "%d ", visited[i][j]);
				slength=strlen(string);
			}
			slength=strlen(string);
			sprintf(string + slength, "\n");
			slength=strlen(string);
		}

		//slength=strlen(string);
		sprintf(string + slength, "\n");
		slength=strlen(string);

		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string, slength, MPI_CHAR, &statusSlave);
        }
		visited[x][y] = 0;
		return;
	}

	// check for all 8 possible movements for a knight
	// and recur for each valid movement
    //#pragma omp parallel for firstprivate(visited, x, y, pos, row, col)
	for (k = 0; k < 8; k++){
		// Get the new position of Knight from current
		// position on chessboard
		int newX = x + row[k];
		int newY = y + col[k];

		// if new position is a valid and not visited yet
		if (isValid(newX, newY) && !visited[newX][newY]){
			KnightTour(visited, newX, newY, pos + 1, fp);
            //KnightTour(visited, newX, newY, pos + 1);
		}
	}

	// backtrack from current square and remove it from current path
	visited[x][y] = 0;
}


int main(int argc, char **argv){
    int i,j;

	int taskid, ntasks;
	MPI_Status status;
	
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	//int dados[2];
	
	MPI_File fp;
	//MPI_File_open(MPI_COMM_WORLD, "/home/udesc/dirTESTE/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);
    MPI_File_open(MPI_COMM_WORLD, "/home/usuariompi/passeio/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);
	if(taskid == MASTER){
		/*
		int l = 0;
		for(i=1;i<ntasks;i++){
			int dados[2];
			dados[0] = l;
			l++;
			dados[1] = l;
			l++; 
            //int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
			MPI_Send(dados, 2, MPI_INT, i, 0, MPI_COMM_WORLD);   
        }
	*/	
/*
		if(N - ntasks > 0){
			printf("\nTem mais linhas do que slaves\n");
		}
	*/
	}
	
	else{
		int dadosSlave[2];
	//	MPI_Recv(dadosSlave, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

	        int i, j, k;

		dadosSlave[0] = taskid - 1;
		dadosSlave[1] = taskid - 1;

		for(i=dadosSlave[0]; i<=dadosSlave[1]; i++){
    	    #pragma omp parallel for firstprivate(i) private(j,k)
			for(j=0; j<N; j++){
				/*
				int **visited;
				
				visited = calloc(sizeof(int *), N);
				for(k=0; k<N; k++){
					visited[k] = calloc(sizeof(int), N);
				}
				*/
				int **visited = (int **)malloc(N * sizeof(int *));
				visited[0] = (int *)malloc(N * N * sizeof(int));
				for(k = 1; k < N; k++){
					visited[k] = visited[0] + k * N;
				}

				KnightTour(visited, i, j, 1, fp);
                //KnightTour(visited, i, j, 1);
				free(visited[0]);
				free(visited[1]);
				free(visited);
        	}
    	}
			
	}

	MPI_File_close(&fp);

	MPI_Finalize();
	return 0;
}

		/*
		int teste[3];
		teste[0] = dadosSlave[0];
		teste[1] = dadosSlave[1];
		teste[2] = taskid;

		char string[256];
		int rank = taskid;
		int slength;

		printf("Proc: %d	dados[0]: %d	dados[1]: %d\n", teste[2], teste[0], teste[1]);
        
		//sprintf(string, "Proc: %d	dados[0]: %d	dados[1]: %d\n", teste[0], teste[1], teste[2]);
		sprintf(string, "Proc: %d	dados[0]: %d	dados[1]: %d", teste[2], teste[0], teste[1]);
		slength=strlen(string);
		sprintf(string + slength, " - TESTANDO\n");
		slength=strlen(string);
	    MPI_File_write_shared(fp, string, slength, MPI_CHAR, &status);

		printf("Proc: %d	dados[0]: %d	dados[1]: %d\n", teste[2], teste[0], teste[1]);
        
		//MPI_File_write_shared(fp, teste, 3, MPI_INT, MPI_STATUS_IGNORE);

		//int linhaMax;
		//int colMax = 8;
		*/
