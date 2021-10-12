#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) 
{
    MPI_Init(NULL, NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Process with Rank : %d (out of %d) and Communicator Group : %d\n", 
         rank, size, MPI_Comm_group);

    MPI_Finalize();
}