// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

// Define a semaphore variable
omp_lock_t semaphore;

double function_maxSum_semaphore(const std::vector<int>& A, const std::vector<int>& B, int N)
{
    int maxSum = 0;

#pragma omp parallel shared(maxSum, A, B, N)
    {
        int localMaxSum = 0;

#pragma omp for
        for (int i = 0; i < N; i++)
        {
            int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
            if (value > 1)
                localMaxSum += value;
        }

        // Use semaphore to update maxSum
        omp_set_lock(&semaphore);
        maxSum += localMaxSum;
        omp_unset_lock(&semaphore);
    }

    return maxSum;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int N = 100;
    std::vector<int> A(N);
    std::vector<int> B(N);
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        A[i] = rand();
        B[i] = rand();
    }

    // Initialize the semaphore
    omp_init_lock(&semaphore);

    double starttime = omp_get_wtime();
    int result_function_semaphore = function_maxSum_semaphore(A, B, N);
    double end_time_semaphore = omp_get_wtime();

    // Destroy the semaphore
    omp_destroy_lock(&semaphore);

    double result_time_semaphore = end_time_semaphore - starttime;

    std::cout << "Результат функции с использованием Semaphore: " << result_function_semaphore << std::endl;
    std::cout << "Задача выполнена за время с использованием Semaphore: " << result_time_semaphore << std::endl;

    return 0;
}

//#pragma omp parallel shared(maxSum, A, B, N)
//{
//    int localMaxSum = 0;
//
//#pragma omp for
//    for (int i = 0; i < N; i++)
//    {
//        int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
//        if (value > 1)
//            localMaxSum += value;
//    }
//
//    // Barrier synchronization
//#pragma omp barrier
//
//// Use semaphore to update maxSum
//    omp_set_lock(&semaphore);
//    maxSum += localMaxSum;
//    omp_unset_lock(&semaphore);
//}