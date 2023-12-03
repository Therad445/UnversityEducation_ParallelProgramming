#include <cstdlib>
#include <iostream>
#include <ctime>
#include "mpi.h"

using namespace std;

int main(int argc, char** argv) {
	srand(time(0));
	int rank, size, count = 0;
	int* arr = (int*)malloc(sizeof(int) * 1);
	int* res = (int*)malloc(sizeof(int) * 1);
	int* mode = (int*)malloc(sizeof(int) * 1);
	int* out = (int*)malloc(sizeof(int) * 1);
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int* globaldata = NULL;
	int localdata;
	mode[0] = 1;
	while (mode[0])
	{
		globaldata = malloc(size * sizeof(int));
		arr[0] = rand() % 101 - 1;
		if (rank == 0) {
			MPI_Allreduce(arr, res, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
			printf("recv value: %d count: %d", res[0], count);
			cout << endl;
			if (res[0] == -1) {
				mode[0] = 0;
			}
			count++;
			MPI_Bcast(mode, 1, MPI_INT, 0, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Allreduce(arr, res, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
			MPI_Bcast(mode, 1, MPI_INT, 0, MPI_COMM_WORLD);
		}

		MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);

		printf("Processor %d has data %d\n", rank, localdata);
		localdata *= 2;
		printf("Processor %d doubling the data, now has %d\n", rank, localdata);

		MPI_Gather(&localdata, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);

	}
	free(arr);
	free(res);
	MPI_Finalize();
	return 0;
} 
Использовать Gather и Scatter
https ://stackoverflow.com/questions/13867809/how-are-mpi-scatter-and-mpi-gather-used-from-c