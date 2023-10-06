// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Исламов Вариант 7
// 
// Задание 1. В соответствии с вариантом задания, написать на C++ программу программу, реализующую многопоточность на основе технологии OpenMP: она должна вычислять значение функции с помощью редукции. Измерять время работы программ для различных значений параметра N. Результаты занести в отчёт.
// 
// Вариант 2. На основе двух равно размерных массивов A и B(длины N) функция возвращает сумму значений, больших 1.
// 
// Задание 2. Модифицировать программу, составленную по Заданию 1, убрав возможность параллельного использования вычислительных ресурсов. Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Задания 1. Результаты сравнить и занести в отчёт.




#include <iostream>
#include <omp.h>
#include <vector>
#include <ctime>

double function_maxSum_atomic(const std::vector<int>& A, const std::vector<int>& B, int N)
{
	int maxSum = 0;
#pragma omp for private(i,j,sum) reduction(+:maxSum)
	for (int i = 0; i < N; i++)
	{
		int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
		if (value > 1)
			maxSum += value;
	}
	return maxSum;
}

double function_maxSum_noOpenMP(const std::vector<int>& A, const std::vector<int>& B, int N)
{
	int maxSum = 0;
	for (int i = 0; i < N; i++)
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
	int result_function_openMP = function_maxSum_atomic(A, B, N);
	double end_time_openMP = omp_get_wtime();
	double result_time_openMP = end_time_openMP - starttime;
	int result_function_noOpenMP = function_maxSum_noOpenMP(A, B, N);
	double end_time_noOpenMP = omp_get_wtime();
	double result_time_noOpenMP = end_time_noOpenMP - end_time_openMP;
	std::cout << "Результат функции с использованием OpenMP: " << result_function_openMP << std::endl;
	std::cout << "Задача выполнена за время с использованием OpenMP: " << result_time_openMP << std::endl;
	std::cout << "Результат функции с использованием OpenMP: " << result_function_openMP << std::endl;
	std::cout << "Задача выполнена за время без использованием OpenMP: " << result_time_noOpenMP << std::endl;
	std::cout << "С OpenMP задача выполняется в раз быстрее: " << result_time_noOpenMP / result_time_openMP << std::endl;

	return 0;
}