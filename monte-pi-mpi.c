/*
 * C言語のサンプルプログラム - Webkaru
 * - 乱数を使って円周率を求めてみよう（モンテカルロ法） -
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void calc_pi(const int rank){
  int i;
  int count = 0;
  long max = 1000000000;
  double x,y,z,pi;
  
  /* 乱数の種を初期化 */
  srand(rank);

  /* 0 〜 1 の乱数を生成・出力 */
  for(i=0;i<max;i++){
    x = (double)rand()/RAND_MAX;
    y = (double)rand()/RAND_MAX;
    z = x*x + y*y;
    if(z<1)
      count++;
  }

  /* 円周率を計算・出力 */
  pi = (double)count / max * 4;
  printf("%d: %f\n", rank, pi);
}

int main(int argc, char **argv){
  MPI_Init(&argc, &argv);
  
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  calc_pi(rank);

  MPI_Finalize();
  /*return 0;*/
}
