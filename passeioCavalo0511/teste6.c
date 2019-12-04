#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#define N 6

#define MASTER 0        // id do mestre


int main(int argc, char **argv){
    int i,j;

    int taskid, ntasks;
    MPI_Status status;
	
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	//int dados[2];
	
	MPI_File fp;
	MPI_File_open(MPI_COMM_WORLD, "/home/gustavo/OPRP/passeioCavalo3110/testeSaidaMPI", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fp);

	if(taskid == MASTER){
		int l = 0;
		for(i=1;i<ntasks;i++){
			int dados[2];
			
			dados[0] = l;
			l++;
			dados[1] = l;
			l++; 
			MPI_Send(dados, 2, MPI_INT, i, 0, MPI_COMM_WORLD);   
        	}
	}
	
	else{
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

		sprintf(string, "Proc: %d	dados[0]: %d	dados[1]: %d", teste[2], teste[0], teste[1]);
		slength=strlen(string);
		sprintf(string + slength, " - TESTANDO\n");
		slength=strlen(string);
	    	MPI_File_write_shared(fp, string, slength, MPI_CHAR, &status);

	}

	MPI_File_close(&fp);

	MPI_Finalize();
	return 0;
}