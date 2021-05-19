/*内積の並列計算 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){
    int i, N;
    int rank, size;
    double VECp[5], VECs[5];
    double sumA, sumR, sumO;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    sumA = 0.0;
    sumR = 0.0;

    N=5;
    for (i=0; i<N; i++){
        VECp[i] = 2.0;
        VECs[i] = 3.0;
    }

    sumO = 0.0;
    for (i=0; i<N; i++){
        sumO += VECp[i] * VECs[i];
    }
    printf("sumO: %f\n", sumO);

    MPI_Finalize();
    return 0;

}