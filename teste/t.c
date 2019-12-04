#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 6;

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


int main(){

    char * teste;
    int k;

    int **visited = malloc(N * sizeof(int *));

    visited[0] = malloc(N * N * sizeof(int));
	for(k = 1; k < N; k++){
			visited[k] = visited[0] + k * N;
	}

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            visited[i][j] = i;
        }
    }


    teste = converteString(visited);

    int temp = strlen(teste);
    printf("Tam: %d\n", temp);

    for(int i=0; i<temp; i++){
        printf("%c ", teste[i]);
    }

    return 0;
}