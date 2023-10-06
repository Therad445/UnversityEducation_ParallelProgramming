// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

const int NMAX = 100;
int main()
{
	setlocale(LC_ALL, "Russian");
	int arr[NMAX][NMAX]; // двумерный массив
	int i, j; // счётчики и размеры матрицы
	int out_OpenMP = 0; // Счётчик вывода
	int out_NoOpenMP = 0; // Счётчик вывода
	srand(time(0)); // автоматическая рандомизация
	for (i = 0; i < NMAX; i++) {
		for (j = 0; j < NMAX; j++) {
			arr[i][j] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
		}
	}

	unsigned int start_time = clock(); // начальное время
#pragma omp parallel shared(arr) private(i)
	{
#pragma omp for shared(out_OpenMP) private(i) 
		{
			for (i = 0; i < NMAX; i += 1) {
				for (j = 0; j < NMAX; j += 2) {
					if (arr[i][j] + arr[i][j + 1] == 7)
						out_OpenMP += 1;
				}
			}
		}
	}
	cout << "Сумма единиц: " << out_OpenMP;  //вывод счётчика
	cout << endl;
	unsigned int end_time_OpenMP = clock(); // конечное время OpenMP
	unsigned int search_time_OpenMP = end_time_OpenMP - start_time; // искомое время OpenMP
	cout << "Задача выполнена с использованием OpenMP: " << search_time_OpenMP << endl;

	for (i = 0; i < NMAX; i += 1) {
		for (j = 0; j < NMAX; j += 2) {
			if (arr[i][j] + arr[i][j + 1] == 7)
				out_NoOpenMP += 1;
		}
	}
	cout << "Сумма единиц: " << out_NoOpenMP << endl;  //вывод счётчика
	unsigned int end_time_NoOpenMP = clock(); // конечное время
	unsigned int search_time_NoOpenMP = end_time_NoOpenMP - end_time_OpenMP; // искомое время
	cout << "Задача выполнена без использования OpenMP: " << search_time_NoOpenMP;
	return 0;
}