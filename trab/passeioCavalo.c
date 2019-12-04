#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include <mpi.h>

#define N 6

int row[] = { 2, 1, -1, -2, -2, -1,  1,  2 , 2 };
int col[] = { 1, 2,  2,  1, -1, -2, -2, -1, 1 };


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
	char * string = malloc(sizeof(char) * 196);
	int slength = 0;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			sprintf(string + slength, "%d ", visited[i][j]);
			slength=strlen(string);
		}
		/*
		slength=strlen(string);
		sprintf(string + slength, "\n");
		slength=strlen(string);
		*/
	}
	sprintf(string + slength, "\n");

	return string;
}

int **transforma1(int **visited){

	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[j][N-i-1] = visited[i][j];
        	}
    	}

	return resultado;
}

int **transforma2(int **visited){
	
	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[i][N-j-1] = visited[i][j];
        	}
    	}

	return resultado;
}

int **transforma3(int **visited){
	
	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[N-i-1][j] = visited[i][j];
        	}
    	}

	return resultado;
}

int **transforma4(int **visited){
	
	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[N-j-1][i] = visited[i][j];
        	}
    	}

	return resultado;
}

int **transforma5(int **visited){
	
	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[j][i] = visited[i][j];
        	}
    	}

	return resultado;
}

int **transforma6(int **visited){
	
	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[N-j-1][N-i-1] = visited[i][j];
        	}
    	}

	return resultado;
}

int **transforma7(int **visited){
	
	int k, i, j;
	int **resultado = malloc(N * sizeof(int *));
	resultado[0] = malloc(N * N * sizeof(int));

	for(k = 1; k < N; k++){
		resultado[k] = resultado[0] + k * N;
	}

	for(i=0; i< N; i++){       
        	for(j=0; j< N; j++){
            		resultado[N-i-1][N-j-1] = visited[i][j];
        	}
    	}

	return resultado;
}
void KnightTour(int **visited, int x, int y, int pos, MPI_File fp){
	visited[x][y] = pos;
	int k,i, j;
	
	if (pos >= N*N){
		MPI_Status statusSlave0;
		MPI_Status statusSlave1;
		MPI_Status statusSlave2;
		MPI_Status statusSlave3;
		MPI_Status statusSlave4;
		MPI_Status statusSlave5;
		MPI_Status statusSlave6;
		MPI_Status statusSlave7;

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

		int **resultado6 = transforma6(visited);
		char * string6 = converteString(resultado6);
		int slength6 = strlen(string6);

		int **resultado7 = transforma7(visited);
		char * string7 = converteString(resultado7);
		int slength7 = strlen(string7);

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

		#pragma omp critical 
        {
			MPI_File_write_shared(fp, string6, slength6, MPI_CHAR, &statusSlave6);
		}

		#pragma omp critical 
        {
			MPI_File_write_shared(fp, string7, slength7, MPI_CHAR, &statusSlave7);
		}
		visited[x][y] = 0;
		return;
	}

	for (k = 0; k < 8; k++){
		int newX = x + row[k];
		int newY = y + col[k];

		if (isValid(newX, newY) && !visited[newX][newY]){
			KnightTour(visited, newX, newY, pos + 1, fp);
		}
	}
	visited[x][y] = 0;
}


int main(int argc, char **argv){

	int taskid, ntasks;
	MPI_Status status;
	
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	MPI_File fp;
    //MPI_File_open(MPI_COMM_WORLD, "/home/udesc/passeio/saidaPasseioCavalo", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);
	MPI_File_open(MPI_COMM_WORLD, "/home/usuariompi/passeio/saidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);

	int j, k;
	int i = taskid;
 	#pragma omp parallel for firstprivate(i) private(j,k)
	//for(j=0; j<N; j++){
	for(j=0; j<(N-2); j++){
		int **visited = malloc(N * sizeof(int *));
		visited[0] = malloc(N * N * sizeof(int));
		for(k = 1; k < N; k++){
			visited[k] = visited[0] + k * N;
		}

		KnightTour(visited, i, j, 1, fp);
		free(visited[0]);
		free(visited);
    }

	MPI_File_close(&fp);

	MPI_Finalize();
	return 0;
}