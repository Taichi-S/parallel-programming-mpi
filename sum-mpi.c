/*1から100までの総和を2つのプロセスで求めてプロセス0から出力するプログラム*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    int sum = 0;
    long int i;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    for(i=100/size*rank+1;i<=100/size*(rank+1);i++){
        // printf("i: %d ", i);
       sum +=i;
    }
    // printf("rank: %d", rank);
    if (rank != 0){
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        int recv; 
        MPI_Recv(&recv, size, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        // printf("I recieved: %d\n", recv);
        // printf("my sum: %d \n", sum);
        int all_sum = recv + sum;
        printf("%d procs's sum is %d", size, all_sum);
    }

    MPI_Finalize();
    return 0;

}