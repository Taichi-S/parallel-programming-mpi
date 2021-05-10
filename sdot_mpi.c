/*
dot product (MPI)

VC++ : cl /Ox /DMPI sdot_mpi.c msmpi.lib
gcc  : mpicc -O3 -DMPI -o sdot_mpi sdot_mpi.c

Usage:
> mpiexec -n <proc> sdot_mpi <num> <loop>
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>

static double sdot(int n, const float *a, const float *b)
{
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i] * b[i];
	}

	return sum;
}

int main(int argc, char **argv)
{
	int    comm_size = 1;
	int    comm_rank = 0;
	int    n = 1000;
	int    nloop = 1000;
	clock_t t0 = 0, t1 = 0;

	// initialize
#ifdef MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);
#endif

	// arguments
	if (argc >= 3) {
		n = atoi(argv[1]);
		nloop = atoi(argv[2]);
	}

	// block
	int block = (n + comm_size - 1) / comm_size;
	int i0 =  comm_rank      * block;
	int i1 = (comm_rank + 1) * block;
	if (i1 > n) i1 = n;

	// alloc
	size_t size = (i1 - i0) * sizeof(float);
	float *a = (float *)malloc(size);
	float *b = (float *)malloc(size);

	// setup problem
	for (int i = i0; i < i1; i++) {
		a[i - i0] = i + 1.0f;
		b[i - i0] = i + 1.0f;
	}

	// timer
	if (comm_rank == 0) {
		t0 = clock();
	}

	// calculation
	double sum = 0;
	for (int loop = 0; loop < nloop; loop++) {
		double l_c = sdot(i1 - i0, a, b);
		double g_c;
#ifdef MPI
		MPI_Reduce(&l_c, &g_c, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
#else
		g_c = l_c;
#endif
		sum += g_c;
	}

#ifdef MPI
	MPI_Finalize();
#endif

	// output
	if (comm_rank == 0) {
		// timer
		t1 = clock();
		double cpu = (double)(t1 - t0) / CLOCKS_PER_SEC;

		// output
		double exact = (double)nloop * n * (n + 1) * (2 * n + 1) / 6.0;
		printf("n=%d, nloop=%d, nproc=%d, dot=%.6e(%.6e), cpu[sec]=%.3f\n",
			n, nloop, comm_size, sum, exact, cpu);
		fflush(stdout);
	}

	// free
	free(a);
	free(b);

	return 0;
}
