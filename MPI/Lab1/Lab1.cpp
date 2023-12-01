//
// Задание. В соответствии с вариантом задания, написать на C++ программу, реализующую многопроцессность на основе технологии MPI, работающую на основе программа должна работать на основе простой передачи сообщений.
// 
// 1	Реализуйте процесс-«счётчик», (который запускается со значением 0 и
//  1) если получена - 1, то он выводит в текущее значение и заканчивает работу;
//  2) если получено любое другое сообщение, то значение увеличивается на 1 и выводится сообщение об этом.
// 



//#include <mpi.h>
//#include <iostream>
//#include <cstdlib>
//
//int main(int argc, char** argv) {
//    int rank, size, value, sig = 0;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0) {
//        // Процесс-счётчик
//        value = 0;
//        for (int i = 1; i < size; i++) {
//            MPI_Recv(&rank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            if (rank == -1) {
//                std::cout << "Current value: " << value << std::endl;
//                MPI_Finalize(); // Завершение работы с MPI
//                return 0;
//            }
//            else {
//                value = rank;
//                std::cout << "Value increased by 1. New value: " << value << std::endl;
//            }
//        }
//    }
//    else if (rank == 20)
//    {
//        // Закрытие программы если поток 4
//        sig = -1;
//        MPI_Send(&sig, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//    }
//    else {
//        // Остальные процессы
//        // Отправка сообщения процессу-счётчику
//        MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//    }
//
//}





#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>


int main(int argc, char** argv) {
	int rank, size, value, sig_plus, mode = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	while (true) {
		printf("Rank: %d\n", rank);
		if (rank == 0) {
			// Процесс-счётчик
			value = 0;
			int* mas = new int[size];
			for (int to_thread = 1; to_thread < size; to_thread++) {
				MPI_Recv(&sig_plus, 1, MPI_INT, to_thread, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				mas[to_thread] = sig_plus;
				printf("Current sig_plus: %d\n", sig_plus);
			}
			for (int i = 1; i < size; i++) {
				if (mas[i] == -1) {
					printf("Current value: %d", value);
					mode = -1;
					break;
				}
				else {
					value++;
					printf("Value increased by 1. New value: %d\n", value);
				}
			}
			for (int to_thread = 1; to_thread < size; to_thread++) {
				//printf("Send to Thread: %d\n", to_thread);
				MPI_Send(&mode, 1, MPI_INT, to_thread, 0, MPI_COMM_WORLD);
			}
			delete[] mas;
		}

		else {
			{
				//printf("Rank: %d\n", rank);
				srand(time(0));
				sig_plus = rand() % 5 - 1;
				MPI_Send(&sig_plus, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
				MPI_Recv(&mode, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				if (mode == -1) break;
			}
		}
		MPI_Finalize();
		return 0;
	}
}

//        recv
//            if(rec_int == -1)
//
//        send 
//
//    }
//    else {
//        while (true)
//        {
//            int = rand;
//            send
//                recv
//                Получается нужно добавить вторую проверку если у нас всё хорошо, то остальные процессы продолжаются, а если -1, то остальные процессы получают из нулевого сигнал на зваершение
//        }
//    }
//
//}

//#include <cstdlib>
//#include <iostream>
//#include <ctime>
//#include "mpi.h"
//
//using namespace std;
//
//int main(int argc, char** argv) {
//    srand(time(0));
//    int rank, size, count = 0;
//    int* arr = (int*)malloc(sizeof(int) * 1);
//    int* res = (int*)malloc(sizeof(int) * 1);
//    int* mode = (int*)malloc(sizeof(int) * 1);
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    mode[0] = 1;
//    while (mode[0])
//    {
//        arr[0] = rand() % 101 - 1;
//        if (rank == 0) {
//            MPI_Reduce(arr, res, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
//            printf("recv value: %d count: %d", res[0], count);
//            cout << endl;
//            if (res[0] == -1) {
//                mode[0] = 0;
//            }
//            count++;
//            MPI_Bcast(mode, 1, MPI_INT, 0, MPI_COMM_WORLD);
//        }
//        else
//        {
//            MPI_Reduce(arr, res, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
//            MPI_Bcast(mode, 1, MPI_INT, 0, MPI_COMM_WORLD);
//        }
//    }
//    free(arr);
//    free(res);
//    MPI_Finalize();
//    return 0;
//}