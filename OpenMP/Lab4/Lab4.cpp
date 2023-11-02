// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include <iostream>
//#include <omp.h>
//#include <vector>
//#include <ctime>
//
//double function_maxSum_atomic(const std::vector<int>& A, const std::vector<int>& B, int N)
//{
//	int maxSum = 0;
//#pragma omp parallel shared(maxSum,A,B,N) private(i,j,sum)
//	{
//#pragma omp for
//		for (int i = 0; i < N; i++)
//		{
//			int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
//#pragma omp atomic
//			if (value > 1)
//				maxSum += value;
//		}
//		return maxSum;
//	}
//}
//
//double function_maxSum_critical(const std::vector<int>& A, const std::vector<int>& B, int N)
//{
//	int maxSum = 0;
//#pragma omp parallel shared(maxSum,A,B,N) private(i,j,sum)
//	for (int i = 0; i < N; i++)
//#pragma omp for
//	{
//		int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
//#pragma omp critical
//		if (value > 1)
//			maxSum += value;
//	}
//	return maxSum;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int N = 100;
//	std::vector<int> A(N);
//	std::vector<int> B(N);
//	srand(time(0));
//	for (int i = 0; i < N; i++)
//	{
//		A[i] = rand();
//		B[i] = rand();
//	}
//	double starttime = omp_get_wtime();
//	int result_function_atomic = function_maxSum_atomic(A, B, N);
//	double end_time_atomic = omp_get_wtime();
//	double result_time_atomic = end_time_atomic - starttime;
//	int result_function_critical = function_maxSum_critical(A, B, N);
//	double end_time_critical = omp_get_wtime();
//	double result_time_critical = end_time_critical - end_time_atomic;
//	std::cout << "Результат функции с использованием atomic: " << result_function_atomic << std::endl;
//	std::cout << "Задача выполнена за время с использованием atomic: " << result_time_atomic << std::endl;
//	std::cout << "Результат функции с использованием critical: " << result_function_atomic << std::endl;
//	std::cout << "Задача выполнена за время без использованием critical: " << result_time_critical << std::endl;
//	std::cout << "С atomic задача выполняется в раз быстрее: " << result_time_critical / result_time_atomic << std::endl;
//
//	return 0;
//}


#include <omp.h>
#include <iostream>
#include <locale.h>

const int n = 500;

void init_rand(int* a) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
        //std::cout << std::endl;
    }
}

void show_matrix(int* a) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
        std::cout << std::endl;
    }
}

void critical(int a[n], int b[n]) {
    int i;
    int sum = 0;
#pragma omp parallel shared(a) 
    {
#pragma omp for private(i) reduction(+:sum)
        for (i = 0; i < n; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            if (value > 1)
#pragma omp atomic
                sum += value;
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
}

void atomic(int a[n], int b[n]) {
    int i;
    int sum = 0;
#pragma omp parallel shared(a) 
    {
#pragma omp for private(i) reduction(+:sum)
        for (i = 0; i < n; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
#pragma omp critical
            if (value > 1)
                sum += value;
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
}



int main()
{

    setlocale(LC_ALL, "Russian");
    int a[n], b[n];
    init_rand(a);
    init_rand(b);
    //show_matrix(a);
    std::cout << "Результат с использованием atomic" << std::endl;
    double atomic_start_time = omp_get_wtime();
    atomic(a, b);
    double atomic_end_time = omp_get_wtime();
    std::cout << atomic_end_time - atomic_start_time << std::endl;
    std::cout << "Результат с использованием critical" << std::endl;
    double critical_start_time = omp_get_wtime();
    critical(a, b);
    double critical_end_time = omp_get_wtime();
    std::cout << critical_end_time - critical_start_time << std::endl;
    return 0;
}
