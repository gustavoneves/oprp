#include <mpi.h>
#include <math.h>
#include <stdio.h>

const int MAX_NUM_FILES = 4;

int main(){
    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int numProcs;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    int numProcsPerFile = ceil(((double) numProcs) / MAX_NUM_FILES);
    //int targetFile = rank / numProcsPerFile;
    int targetFile = 0;

    MPI_Comm fileComm;
    MPI_Comm_split(MPI_COMM_WORLD, targetFile, rank, &fileComm);

    int targetFileRank;
    MPI_Comm_rank(fileComm, &targetFileRank);

    char filename[20]; // Sufficient for testing purposes
    snprintf(filename, 20, "out_%d.dat", targetFile);
    printf(
        "Proc %d: writing to file %s with rank %d\n", rank, filename,
        targetFileRank);

    MPI_File outFile;
    MPI_File_open(
        fileComm, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY,
        MPI_INFO_NULL, &outFile);

    char bufToWrite[4];
    snprintf(bufToWrite, 4, "%3d", rank);

    MPI_File_write_at_all(
        outFile, targetFileRank * 3,
        bufToWrite, 3, MPI_CHAR, MPI_STATUS_IGNORE);

    MPI_File_close(&outFile);
    MPI_Finalize();
}