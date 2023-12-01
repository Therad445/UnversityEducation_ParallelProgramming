//#include <stdio.h>
//#include <mpi.h>
//
//int main(int argc, char** argv) {
//    int rank, size;
//    int local_value = 1;
//    int global_sum;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    // Если количество потоков равно 5, отправляем значение -1 и завершаем программу
//    if (rank == 2) {
//        local_value = -1;
//        MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//        MPI_Finalize();
//        return 0;
//    }
//
//    // Каждый процесс прибавляет единицу к локальному значению
//    local_value = 1;
//
//    // Выполняем операцию сокращения (reduction) с использованием MPI_Reduce
//    MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        printf("Глобальная сумма: %d\n", global_sum);
//    }
//
//    MPI_Finalize();
//    return 0;
//}

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
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    mode[0] = 1;
    while (mode[0])
    {
        arr[0] = rand() % 101 - 1;
        if (rank == 0) {
            MPI_Reduce(arr, res, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
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
            MPI_Reduce(arr, res, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
            MPI_Bcast(mode, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }
    free(arr);
    free(res);
    MPI_Finalize();
    return 0;
}

