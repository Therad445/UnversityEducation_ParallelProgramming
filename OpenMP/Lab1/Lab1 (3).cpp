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

const int NMAX = 1;


int function_openMP(int** arr)
{
#pragma omp parallel shared(arr) private(i)
	int out = 0; // Счётчик вывода
	{
#pragma omp for shared(out) private(i) 
		{
			for (int i = 0; i < NMAX; i += 1) {
				for (int j = 0; j < NMAX; j += 2) {
					if (arr[i][j] + arr[i][j + 1] == 7)
						out += 1;
				}
			}
		}
	}
	return out;
}

int function_noOpenMP(int** arr)
{
	int out = 0; // Счётчик вывода
	for (int i = 0; i < NMAX; i += 1) {
		for (int j = 0; j < NMAX; j += 2) {
			if (arr[i][j] + arr[i][j + 1] == 7)
				out += 1;
		}
	}
	return out;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int** dinamic_array2 = new int* [NMAX];   // создаем 
	for (int i = 0; i < NMAX; i++) {          // двумерный
		dinamic_array2[i] = new int[i + 1]; // массив 
	}                                      // !

	srand(time(0)); // автоматическая рандомизация
	for (int i = 0; i < NMAX; i++) {
		for (int j = 0; j < NMAX; j++) {
			dinamic_array2[i][j] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
		}
	}

	//printf(dinamic_array2);

	unsigned int start_time_openMP = clock(); // начальное время
	cout << "Сумма единиц: " << function_openMP(dinamic_array2) << endl;  //вывод счётчика
	unsigned int end_time_OpenMP = clock(); // конечное время OpenMP
	unsigned int search_time_OpenMP = end_time_OpenMP - start_time_openMP; // искомое время OpenMP
	cout << "Задача выполнена с использованием OpenMP: " << search_time_OpenMP << endl;
	for (int i = 0; i < NMAX; i++) {
		delete[] dinamic_array2[i];  // удаляем массив
	}
	//unsigned int start_time_NoOpenMP = clock(); // конечное время
	//cout << "Сумма единиц: " << function_noOpenMP(dinamic_array2) << endl;  //вывод счётчика
	//unsigned int end_time_NoOpenMP = clock(); // конечное время
	//unsigned int search_time_NoOpenMP = end_time_NoOpenMP - start_time_NoOpenMP; // искомое время
	//cout << "Задача выполнена без использования OpenMP: " << search_time_NoOpenMP;


	

	return 0;
}