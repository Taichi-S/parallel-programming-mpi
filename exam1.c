/* 例題1．個のプロセッサを用いた時に，なぜ通信が速くなるか */

/*1から10000までの総和を任意のプロセス数で求めてプロセス0から出力するプログラム（処理時間も出力） */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    long long int N = 10000;   // 92000(4232046000)~93000の間でMPI_INTでのオーバーフローが起きている．
    long long int sum = 0;
    long long int all_sum, i;
    int rank, size;
    double Stime, Etime;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);
    Stime = MPI_Wtime();
    for(i=N/size*rank+1;i<=N/size*(rank+1);i++){
       sum +=i;
    }
    MPI_Reduce(&sum, &all_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    Etime = MPI_Wtime();
    if(rank == 0){
        if(N%size!=0){
            printf("%lldを割り切れるプロセス数で実行してください．", N);
        }else {
            // printf("rank: %d, sum: %lld\n", rank, sum);
            printf("%d procs's sum is %lld\n", size, all_sum);
            printf("処理時間: %f", Etime-Stime);
        }
    }else{
        // printf("rank: %d, sum: %lld\n", rank, sum);
    }

    MPI_Finalize();
    return 0;

}