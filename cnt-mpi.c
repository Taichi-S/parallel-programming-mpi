/*1から1000000000まで総和を求めて出力するプログラム*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    long long int sum = 0;
    long int i;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(i=100/size*rank+1;i<=100/size*(rank+1);i++){
        // printf("i: %d ", i);
       sum +=i;
    }
    printf("%d: %d", rank, size);
    printf(" sum: %lld \n", sum);

    MPI_Finalize();
    return 0;

}