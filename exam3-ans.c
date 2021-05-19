/* 例題3. */

/*任意のプロセス数で，500*500行の行列の積を計算するプログラム（要素数を出力する）*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv){
    long long int i, j, k;
    int rank, size;
    long long int n=100;
    // double VECp[N], VECs[N];
    double sumA, sumR, sumO;
    double Stime, Etime;
    int all_count;

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
                b[i][j] = (int)rand()%3+1;
                c[i][j] = (int)rand()%3+1;
        }
    }
    /*
    * 行列の積の和を求める（6*k になる）
    */
   /* for文の中を変更．
   * 任意のプロセス数で実行
   * アンバランスを解消
   */
   long long int count=0;
    for (i=n/size*rank; i < n/size*(rank+1); i++) {
        for(j=0; j < n; j++) {
                for (k=0; k < n; k++) {
                    a[i][j] += b[i][k]*c[k][j];
                    count++;
                }
                // printf("a[%lld][%lld]: %d\n", i, j, a[i][j]);
        }
    }
    printf("count[%d]: %lld\n", rank, count);

    MPI_Reduce(&count, &all_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    Etime = MPI_Wtime();
    
    if(rank==0){
        printf("行列の要素数の合計：%d\n", all_count);
        printf("処理時間: %f", Etime-Stime);
    }

    MPI_Finalize();
    return 0;

}