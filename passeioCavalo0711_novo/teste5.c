#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include <mpi.h>

//#include <string.h>
//#include <pthread.h>

#define N 6

#define MASTER 0        // id do mestre

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
void KnightTour(int **visited, int x, int y, int pos, MPI_File fp){
//void KnightTour(int **visited, int x, int y, int pos){
	// mark current square as visited	
	visited[x][y] = pos;
	
	// if all squares are visited, print the solution
	if (pos >= N*N){
		MPI_Status statusSlave;
		//MPI_File_write_shared(fp, visited, N*N, MPI_INT, &status);

		char string[256];
		int slength = 0;
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				sprintf(string + slength, "%d ", visited[i][j]);
				slength=strlen(string);
			}
			slength=strlen(string);
			sprintf(string + slength, "\n");
		}

		#pragma omp critical
	    MPI_File_write_shared(fp, string, slength, MPI_CHAR, &statusSlave);

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
	//MPI_File_open(MPI_COMM_WORLD, "/home/udesc/Downloads/passeioCavalo2910/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);
	MPI_File_open(MPI_COMM_WORLD, "/home/gustavo/OPRP/passeioCavalo3110/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);

	if(taskid == MASTER){
		int l = 0;
		//MPI_File_open(MPI_COMM_WORLD, "/home/udesc/Downloads/passeioCavalo2910/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp); 
		for(i=1;i<ntasks;i++){
			int dados[2];
			
			dados[0] = l;
			l++;
			dados[1] = l;
			l++; 
			
		/*
			int dados[2];
			dados[0] = i-1;
			dados[1] = i;
			*/
            //int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
			MPI_Send(dados, 2, MPI_INT, i, 0, MPI_COMM_WORLD);   
        }
	}
	
	else{
		//int idSlave;
		//MPI_Comm_rank(MPI_COMM_WORLD, &idSlave);
        //int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
        // int dados[2];
		// MPI_Recv(dados, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		
		// MPI_Status status;
		// MPI_Offset offset;

		// int teste[3];
		// teste[0] = dados[0];
		// teste[1] = dados[1];
		// teste[2] = taskid;
		int dadosSlave[2];
		MPI_Recv(dadosSlave, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		
		MPI_Status status;
		MPI_Offset offset;

		int teste[3];
		teste[0] = dadosSlave[0];
		teste[1] = dadosSlave[1];
		teste[2] = taskid;

		char string[256];
		int rank = taskid;
		int slength;

		//sprintf(string, "Proc: %d	dados[0]: %d	dados[1]: %d\n", teste[0], teste[1], teste[2]);
		sprintf(string, "Proc: %d	dados[0]: %d	dados[1]: %d", teste[2], teste[0], teste[1]);
		slength=strlen(string);
		sprintf(string + slength, " - TESTANDO\n");
		slength=strlen(string);
	    MPI_File_write_shared(fp, string, slength, MPI_CHAR, &status);

		printf("Proc: %d	dados[0]: %d	dados[1]: %d\n", teste[2], teste[0], teste[1]);
		//MPI_File_write_shared(fp, teste, 3, MPI_INT, MPI_STATUS_IGNORE);

	/*
		int linhaMax;
		int colMax = 8;
		int k;

		for(i=dados[0]; i<=dados[1]; i++){
    	    #pragma omp parallel for firstprivate(i) private(j)
			for(j=0; j<6; j++){
				int **visited;

				visited = calloc(sizeof(int *), 6);
				for(k=0; k<6; k++){
					visited[k] = calloc(sizeof(int), 6);
				}

				//KnightTour(visited, i, j, 1, fp);
                KnightTour(visited, i, j, 1);
				free(visited[0]);
				free(visited[1]);
				free(visited);
        	}
    	}
		*/		
	}

	//if(taskid == MASTER){
		MPI_File_close(&fp);
	//}

	MPI_Finalize();
	return 0;
}