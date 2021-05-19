/*内積の並列計算（sleepが入っている）*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv){
    long long int i;
    int rank, size;
    long long int N=100000;
    double VECp[N], VECs[N];
    double sumA, sumR, sumO;
    double Stime, Etime;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    sumA = 0.0;
    sumR = 0.0;

    for (i=0; i<N; i++){
        // printf("i: %d, ", i);
        VECp[i] = rand()%10+1;
        VECs[i] = rand()%10+1;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    Stime = MPI_Wtime();
    sumO = 0.0;
    for (i=N/size*rank; i<N/size*(rank+1); i++){
        sumO += VECp[i] * VECs[i];
    }
    sleep(10);

    MPI_Barrier(MPI_COMM_WORLD);
    Etime = MPI_Wtime();

    printf("rank: %d\n", rank);
    printf("sumO: %f\n", sumO);
    // printf("Etime: %f", Etime);
    if(rank==0){
        printf("処理時間: %f", Etime-Stime);
    }

    MPI_Finalize();
    return 0;

}