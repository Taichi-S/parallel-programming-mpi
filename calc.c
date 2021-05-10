#include <stdio.h>
// #include <mpi.h>

// int main(int argc, char **argv) {
int main(void) {
//   MPI_Init(&argc, &argv);
//   int rank;
//   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//   printf("Hello! My rank is %d\n", rank*2);
//   MPI_Finalize();
    // for(int i=12/size*rank+1;i<=12/size*(rank+1);i++){
    //    sum +=i;
    // }
    int sum;
    for(int i=1; i<=12; i++){
        sum += i;
    }
    printf(sum);

    return 0;
}