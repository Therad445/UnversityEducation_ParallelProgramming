// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*Задание 1. Написать на C++ программу в соответствии с вариантом задания, при этом программы должны оптимально использовать предлагающиеся вычислительные ресурсы.Для реализации многопоточности использовать технологию OpenMP.Измерять время работы программы для различных значений параметров.Результаты занести в отчёт.Также, при запуске программ, запустить диспетчер задач Windows, в нём установить счётчик потоков, и просмотреть сколько потоков выполнения использует процесс, соответствующий запущенной программе.Результаты также занести в отчёт.

Вариант-7 Исламов

1	Дана матрица из MxN натуральных(ненулевых) элементов(задаются случайно).
Написать программу, считающую количество семёрок в десятеричной записи числа всех попарных сумм элементов для каждой строки.
*/

#include <omp.h>
#include <iostream>
#include <locale.h>

const int NMAX = 5000;

static int** matrix_init(int n, int m)
{
    int** matrix;

    matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m] {};
    }

    return matrix;
}

void init_rand(int** a) {
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < NMAX; j++) {
            a[i][j] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
        }
        //std::cout << std::endl;
    }
}

void show_matrix(int** a) {
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < NMAX; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void OpenMP(int** a) {
    int i, j;
    float sum;
#pragma omp parallel shared(a) private(i)
    {
#pragma omp for private(j,sum)
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++) {
                if (j + 1 == NMAX)
                    continue;
                if (a[i][j] + a[i][j + 1] == 7) {
                    sum += 1;
                    //std::cout << a[i][j] << " " << a[i][j + 1] << std::endl;
                }
            }
            //printf("Количество сёмерок в строке %d всех попарных сумм элементов равна %f\n", i, sum);
        }
    } /* Завершение параллельного фрагмента */
}

void noOpenMP(int** a) {
    int i, j;
    float sum;
    for (i = 0; i < NMAX; i++)
    {
        sum = 0;
        for (j = 0; j < NMAX; j++) {
            if (j + 1 == NMAX)
                continue;
            if (a[i][j] + a[i][j + 1] == 7) {
                sum += 1;
                //std::cout << a[i][j] << " " << a[i][j + 1] << std::endl;
            }
        }
        //printf("Количество сёмерок в строке %d всех попарных сумм элементов равна %f\n", i, sum);
    }
} /* Завершение параллельного фрагмента */



int main()
{

    setlocale(LC_ALL, "Russian");
    int** a;
    a = matrix_init(NMAX, NMAX);
    init_rand(a);
    //show_matrix(a);
    double noopenMp_start_time = omp_get_wtime();
    noOpenMP(a);
    double noopenMp_end_time = omp_get_wtime();
    std::cout << noopenMp_end_time - noopenMp_start_time << std::endl;
    double openMp_start_time = omp_get_wtime();
    OpenMP(a);
    double openMp_end_time = omp_get_wtime();
    std::cout << openMp_end_time - openMp_start_time << std::endl;
    return 0;
}
