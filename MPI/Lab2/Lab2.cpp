#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int local_value = 1;
    int global_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Если количество потоков равно 5, отправляем значение -1 и завершаем программу
    if (rank == 2) {
        local_value = -1;
        MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Finalize();
        return 0;
    }

    // Каждый процесс прибавляет единицу к локальному значению
    local_value = 1;

    // Выполняем операцию сокращения (reduction) с использованием MPI_Reduce
    MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Глобальная сумма: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}