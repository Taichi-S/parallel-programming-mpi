/*内積の並列計算（sleepが入っている）*/

#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv){
    long long int i, j, k;
    int rank, size;
    long long int n=500;
    // double VECp[N], VECs[N];
    double sumA, sumR, sumO;
    double Stime, Etime;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);
    Stime = MPI_Wtime();
    
    long int a[n][n], b[n][n], c[n][n];
    /*
    * 配列を初期化
    */
    for (i=0; i < n; i++) {
        for (j=0; j < n; j++) {
                a[i][j] = 0;
                b[i][j] = 3;
                c[i][j] = 2;
        }
    }
    /*
    * 行列の積の和を求める（6*k になる）
    */
   long long int count=0;
    for (i=0; i < n; i++) {
        for(j=0; j < n; j++) {
                for (k=0; k < n; k++) {
                    a[i][j] += b[i][k]*c[k][j];
                    count++;
                    // printf("a[%lld][%lld]: %d\n", i, j, a[i][j]);
                }
        }
    }
    printf("count: %lld\n", count);

    MPI_Barrier(MPI_COMM_WORLD);
    Etime = MPI_Wtime();

    // printf("rank: %d\n", rank);
    // printf("sumO: %f\n", sumO);
    // printf("Etime: %f", Etime);
    if(rank==0){
        printf("処理時間: %f", Etime-Stime);
    }

    MPI_Finalize();
    return 0;

}