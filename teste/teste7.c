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
	int i,j;
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%d ", visited[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

char * converteString(int **visited){
	int i,j;
	//char string[256];
	char * string = malloc(sizeof(char) * 196);
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

	return string;
}

int **transforma1(int **visited){

	int k;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(int i=0; i< N; i++){       
        for(int j=0; j< N; j++){
            resultado[j][N-i-1] = visited[i][j];
        }
    }

	return resultado;
}

int **transforma2(int **visited){
	
	int k;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(int i=0; i< N; i++){       
        for(int j=0; j< N; j++){
            resultado[i][N-j-1] = visited[i][j];
        }
    }

	return resultado;
}

int **transforma3(int **visited){
	int k;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(int i=0; i< N; i++){       
        for(int j=0; j< N; j++){
            resultado[N-i-1][N-j-1] = visited[i][j];
        }
    }

	return resultado;
}

int **transforma3(int **visited){
	int k;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(int i=0; i< N; i++){       
        for(int j=0; j< N; j++){
            resultado[N-i-1][j] = visited[i][j];
        }
    }

	return resultado;
}

int **transforma4(int **visited){
	int k;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(int i=0; i< N; i++){       
        for(int j=0; j< N; j++){
            resultado[N-j-1][i] = visited[i][j];
        }
    }

	return resultado;
}

int **transforma5(int **visited){
	int k;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(int i=0; i< N; i++){       
        for(int j=0; j< N; j++){
            resultado[j][i] = visited[i][j];
        }
    }

	return resultado;
}

// Recursive function to perform the Knight's tour using backtracking
void KnightTour(int **visited, int x, int y, int pos, MPI_File fp){
//void KnightTour(int **visited, int x, int y, int pos){
	// mark current square as visited	
	visited[x][y] = pos;
	int k,i, j;
	
	// if all squares are visited, print the solution
	if (pos >= N*N){
		MPI_Status statusSlave0;
		MPI_Status statusSlave1;
		MPI_Status statusSlave2;
		MPI_Status statusSlave3;
		MPI_Status statusSlave4;
		MPI_Status statusSlave5;

		// char string[256];
		// int slength = 0;
		// for(i=0; i<N; i++){
		// 	for(j=0; j<N; j++){
		// 		sprintf(string + slength, "%d ", visited[i][j]);
		// 		slength=strlen(string);
		// 	}
		// 	slength=strlen(string);
		// 	sprintf(string + slength, "\n");
		// 	slength=strlen(string);
		// }

		// //slength=strlen(string);
		// sprintf(string + slength, "\n");
		char * string0 = converteString(visited);
		int slength0 = strlen(string0);

		int **resultado1 = transforma1(visited);
		char * string1 = converteString(resultado1);
		int slength1 = strlen(string1);

		int **resultado2 = transforma2(visited);
		char * string2 = converteString(resultado2);
		int slength2 = strlen(string2);

		int **resultado3 = transforma3(visited);
		char * string3 = converteString(resultado3);
		int slength3 = strlen(string3);


		int **resultado4 = transforma4(visited);
		char * string4 = converteString(resultado4);
		int slength4 = strlen(string4);

		int **resultado5 = transforma5(visited);
		char * string5 = converteString(resultado5);
		int slength5 = strlen(string5);


		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string0, slength0, MPI_CHAR, &statusSlave0);
        }

		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string1, slength1, MPI_CHAR, &statusSlave1);
        }

		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string2, slength2, MPI_CHAR, &statusSlave2);
        }

		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string3, slength3, MPI_CHAR, &statusSlave3);
        }

		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string4, slength4, MPI_CHAR, &statusSlave4);
        }

		#pragma omp critical 
        {
	        MPI_File_write_shared(fp, string5, slength5, MPI_CHAR, &statusSlave5);
        }

		visited[x][y] = 0;
		return;
	}

	// check for all 8 possible movements for a knight
	// and recur for each valid movement
 //       #pragma omp parallel for firstprivate(visited, x, y, pos, row, col)
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
				// int **visited;

				// visited = calloc(sizeof(int *), N);
				// for(k=0; k<N; k++){
				// 	visited[k] = calloc(sizeof(int), N);
				// }
				int **visited = malloc(N * sizeof(int *));
				visited[0] = malloc(N * N * sizeof(int));
				for(k = 1; k < N; k++){
					visited[k] = visited[0] + k * N;
				}

				KnightTour(visited, i, j, 1, fp);
				free(visited[0]);
				free(visited);
                //KnightTour(visited, i, j, 1);
				// free(visited[0]);
				// free(visited[1]);
				// free(visited);
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
