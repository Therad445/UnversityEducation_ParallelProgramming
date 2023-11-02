﻿// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*Задание 1. Написать на C++ программу в соответствии с вариантом задания, при этом программы должны оптимально использовать предлагающиеся вычислительные ресурсы.Для реализации многопоточности использовать технологию OpenMP.Измерять время работы программы для различных значений параметров.Результаты занести в отчёт.Также, при запуске программ, запустить диспетчер задач Windows, в нём установить счётчик потоков, и просмотреть сколько потоков выполнения использует процесс, соответствующий запущенной программе.Результаты также занести в отчёт.

Вариант-7 Исламов

1	Дана матрица из MxN натуральных(ненулевых) элементов(задаются случайно).
Написать программу, считающую количество семёрок в десятеричной записи числа всех попарных сумм элементов для каждой строки.
*/

#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

const int NMAX = 10000;

class Matrix
{
	int* data;
	int size;
public:
	Matrix(int matSize)
	{
		size = matSize;
		data = new int[size * size];
	}
	~Matrix()
	{
	}
	int* operator[](int row)
	{
		return data + row * size;
	}
};

int function_openMP(Matrix arrs)
{
#pragma omp parallel shared(arrs) private(i)
	int out = 0; // Счётчик вывода
	{
#pragma omp for shared(out) private(i) 
		{
			for (int i = 0; i < NMAX; i += 1) {
				for (int j = 0; j < NMAX; j += 2) {
					if (arrs[i][j] + arrs[i][j + 1] == 7)
						out += 1;
				}
			}
		}
	}
	return out;
}

int function_noOpenMP(Matrix arrs)
{
	int out = 0; // Счётчик вывода
	for (int i = 0; i < NMAX; i += 1) {
		for (int j = 0; j < NMAX; j += 2) {
			if (arrs[i][j] + arrs[i][j + 1] == 7)
				out += 1;
		}
	}
	return out;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0)); // автоматическая рандомизация
	Matrix arr(NMAX);
	for (int i = 0; i < NMAX; i++) {
		for (int j = 0; j < NMAX; j++) {
			arr[i][j] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
		}
	}
	omp_set_num_threads(10000);
	double start_time_openMP = omp_get_wtime(); // начальное время
	cout << "Сумма единиц: " << function_openMP(arr) << endl;  //вывод счётчика
	double  end_time_OpenMP = omp_get_wtime(); // конечное время OpenMP
	cout << "Задача выполнена с использованием OpenMP: " << double(end_time_OpenMP - start_time_openMP) / CLOCKS_PER_SEC << endl; // искомое время OpenMP

	double start_time_NoOpenMP = clock(); // конечное время
	cout << "Сумма единиц: " << function_noOpenMP(arr) << endl;  //вывод счётчика
	double end_time_NoOpenMP = clock(); // конечное время
	cout << "Задача выполнена без использования OpenMP: " << double(end_time_NoOpenMP - start_time_NoOpenMP) / CLOCKS_PER_SEC  << endl; // искомое время
	cout << "С OpenMP задача выполняется в раз быстрее: " << (double(end_time_NoOpenMP - start_time_NoOpenMP) / CLOCKS_PER_SEC) / (double(end_time_OpenMP - start_time_openMP) / CLOCKS_PER_SEC) << endl;
	return 0;
}