/*1から100までの総和を任意のプロセス数で求めてプロセス0から出力するプログラム（処理時間も出力） */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    int sum = 0;
    long int i;
    int rank, size, all_sum;
    double Stime, Etime;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);
    Stime = MPI_Wtime();
    for(i=100/size*rank+1;i<=100/size*(rank+1);i++){
       sum +=i;
    }
    MPI_Reduce(&sum, &all_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    Etime = MPI_Wtime();
    if(rank == 0){
        if(100%size!=0){
            printf("100を割り切れるプロセス数で実行してください．");
        }else {
            printf("rank: %d, sum: %d\n", rank, sum);    
            printf("%d procs's sum is %d\n", size, all_sum);
            printf("処理時間: %f", Etime-Stime);
        }
    }else{
        printf("rank: %d, sum: %d\n", rank, sum);
    }

    MPI_Finalize();
    return 0;

}