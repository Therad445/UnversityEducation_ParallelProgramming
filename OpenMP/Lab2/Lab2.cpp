// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Задание. Выполнить Пример для различных значений параметров NMAX и LIMIT, замеряя время выполнения, результаты занести в отчет. Выделить такие NMAX при LIMIT, при которых совпадает время выполнения многопоточной программы и однопоточной.
*/

#include <iostream>
#include <ctime>
#include <omp.h>
#include <stdio.h>

using namespace std;

const int NMAX = 300;
const int LIMIT = 400;

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

void function_openMP(Matrix a)
{
	int i, j;
	float sum;

	for (i = 0; i < NMAX; i++)
	{
		for (j = 0; j < NMAX; j++)
		{
			a[i][j] = i + j;
		}
	}

#pragma omp parallel shared(a) if (NMAX>LIMIT)
	{
#pragma omp for private(i,j,sum) 
		for (i = 0; i < NMAX; i++)
		{
			sum = 0;
			for (j = 0; j < NMAX; j++)
				sum += a[i][j];
			printf("Сумма элементов строки %d равна %f\n", i, sum);
		}
	}
}

void function_noOpenMP(Matrix a)
{
	int i, j;
	float sum;
	

	for (i = 0; i < NMAX; i++)
	{
		for (j = 0; j < NMAX; j++)
		{
			a[i][j] = i + j;
		}
	}

	for (i = 0; i < NMAX; i++)
	{
		sum = 0;
		for (j = 0; j < NMAX; j++)
			sum += a[i][j];
		printf("Сумма элементов строки %d равна %f\n", i, sum);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Matrix a(NMAX);
	double start_time_openMP = omp_get_wtime(); // начальное время
	cout << "Сумма единиц: " << function_openMP(a) << endl;  //вывод счётчика
	double  end_time_OpenMP = omp_get_wtime(); // конечное время OpenMP
	cout << "Задача выполнена с использованием OpenMP: " << double(end_time_OpenMP - start_time_openMP) / CLOCKS_PER_SEC << endl; // искомое время OpenMP

	double start_time_NoOpenMP = clock(); // конечное время
	cout << "Сумма единиц: " << function_noOpenMP(a) << endl;  //вывод счётчика
	double end_time_NoOpenMP = clock(); // конечное время
	cout << "Задача выполнена без использования OpenMP: " << double(end_time_NoOpenMP - start_time_NoOpenMP) / CLOCKS_PER_SEC << endl; // искомое время
	cout << "С OpenMP задача выполняется в раз быстрее: " << (double(end_time_NoOpenMP - start_time_NoOpenMP) / CLOCKS_PER_SEC) / (double(end_time_OpenMP - start_time_openMP) / CLOCKS_PER_SEC) << endl;


	return 0;
}