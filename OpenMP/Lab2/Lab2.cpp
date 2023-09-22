﻿// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <omp.h>
#include <stdio.h>

using namespace std;

const int NMAX = 100;
const int LIMIT = 10;

int main()
{
	setlocale(LC_ALL, "Russian");
	unsigned int start_time = clock(); // начальное время
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

	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время

	cout << "Задача выполнена с использованием OpenMP: " << search_time;
	cout << endl;

}
