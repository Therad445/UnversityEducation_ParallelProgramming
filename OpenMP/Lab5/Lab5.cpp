// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

double function_maxSum_openMP(const std::vector<int>& A, const std::vector<int>& B, int start, int end)
{
	int maxSum = 0;
#pragma omp for private(i,j,sum) reduction(+:maxSum)
	for (int i = start; i < end; i++)
	{
		int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
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
	int maxSum = 0;
#pragma omp parallel shared(maxSum)
	{
		int maxSumParallel = 0;
#pragma omp sections
		{
#pragma omp section 
			{
				maxSumParallel += function_maxSum_openMP(A, B, 0, N / 2);
			}
#pragma omp section 
			{
				maxSumParallel += function_maxSum_openMP(A, B, N / 2, N);
			}
		}
		int maxSum += maxSumParallel;
	}
	double end_time_openMP = omp_get_wtime();
	double result_time_openMP = end_time_openMP - starttime;
	std::cout << "Результат функции с использованием openMP: " << maxSum << std::endl;
	std::cout << "Задача выполнена за время с использованием openMP: " << result_time_openMP << std::endl;

	return 0;
}