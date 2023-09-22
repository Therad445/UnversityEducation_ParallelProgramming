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

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned int start_time1 = clock(); // начальное время
	srand(time(0)); // автоматическая рандомизация

	{
		int i, j;
		float sum;
		float a[NMAX][NMAX];

		for (i = 0; i < NMAX; i++)
			for (j = 0; j < NMAX; j++)
				a[i][j] = i + j;

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

	unsigned int end_time1 = clock(); // конечное время
	unsigned int search_time1 = end_time1 - start_time1; // искомое время

	//cout << "Задача выполнена с использованием OpenMP: " << search_time1;
	//cout << endl;


	unsigned int start_time2 = clock(); // начальное время
	srand(time(0)); // автоматическая рандомизация

	{
	int i, j;
	float sum;
	float a[NMAX][NMAX];

	for (i = 0; i < NMAX; i++)
		for (j = 0; j < NMAX; j++)
			a[i][j] = i + j;

		for (i = 0; i < NMAX; i++)
		{
			sum = 0;
			for (j = 0; j < NMAX; j++)
				sum += a[i][j];
			printf("Сумма элементов строки %d равна %f\n", i, sum);
		}

	unsigned int end_time2 = clock(); // конечное время
	unsigned int search_time2 = end_time2 - start_time2; // искомое время

	cout << "Задача выполнена с использованием OpenMP: " << search_time1;
	cout << endl;

	cout << "Задача выполнена без использованием OpenMP: " << search_time2;
	cout << endl;
	}

}
