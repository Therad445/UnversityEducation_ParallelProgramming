// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

double function_maxSum_atomic(const std::vector<int>& A, const std::vector<int>& B, int N)
{
	int maxSum = 0;
#pragma omp parallel shared(maxSum,A,B,N) private(i,j,sum)
	{
#pragma omp for
		for (int i = 0; i < N; i++)
		{
			int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
#pragma omp atomic
			if (value > 1)
				maxSum += value;
		}
		return maxSum;
	}
}

double function_maxSum_critical(const std::vector<int>& A, const std::vector<int>& B, int N)
{
	int maxSum = 0;
#pragma omp parallel shared(maxSum,A,B,N) private(i,j,sum)
	for (int i = 0; i < N; i++)
#pragma omp for
	{
		int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
#pragma omp critical
		if (value > 1)
			maxSum += value;
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
	double starttime = omp_get_wtime();
	int result_function_atomic = function_maxSum_atomic(A, B, N);
	double end_time_atomic = omp_get_wtime();
	double result_time_atomic = end_time_atomic - starttime;
	int result_function_critical = function_maxSum_critical(A, B, N);
	double end_time_critical = omp_get_wtime();
	double result_time_critical = end_time_critical - end_time_atomic;
	std::cout << "Результат функции с использованием atomic: " << result_function_atomic << std::endl;
	std::cout << "Задача выполнена за время с использованием atomic: " << result_time_atomic << std::endl;
	std::cout << "Результат функции с использованием critical: " << result_function_atomic << std::endl;
	std::cout << "Задача выполнена за время без использованием critical: " << result_time_critical << std::endl;
	std::cout << "С atomic задача выполняется в раз быстрее: " << result_time_critical / result_time_atomic << std::endl;

	return 0;
}