//
// Задание. В соответствии с вариантом задания, написать на C++ программу, реализующую многопроцессность на основе технологии MPI, работающую на основе программа должна работать на основе простой передачи сообщений.
// 
// 1	Реализуйте процесс-«счётчик», (который запускается со значением 0 и
//  1) если получена - 1, то он выводит в текущее значение и заканчивает работу;
//  2) если получено любое другое сообщение, то значение увеличивается на 1 и выводится сообщение об этом.
// 

#include <mpi.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    int rank, size, value, num = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Процесс-счётчик
        for (int i = 1; i < size; i++) {
            MPI_Recv(&value, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (value == -1) {
                std::cout << "Current value: " << num << std::endl;
                exit(value); // Завершение выполнения программы
            }
            else {
                num++;
                std::cout << "Value increased by 1. New value: " << num << std::endl;
            }
        }
    }
    else if (rank == 5)
    {
        // Закрытие программы если поток 5
        value = -1;
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else {
        // Остальные процессы
        // Отправка сообщения процессу-счётчику
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize(); // Завершение работы с MPI
    return 0;
}