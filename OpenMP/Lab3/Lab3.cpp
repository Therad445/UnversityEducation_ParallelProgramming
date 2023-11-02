// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Исламов Вариант 7
// 
// Задание 1. В соответствии с вариантом задания, написать на C++ программу программу, реализующую многопоточность на основе технологии OpenMP: она должна вычислять значение функции с помощью редукции. Измерять время работы программ для различных значений параметра N. Результаты занести в отчёт.
// 
// Вариант 2. На основе двух равно размерных массивов A и B(длины N) функция возвращает сумму значений, больших 1.
// 
// Задание 2. Модифицировать программу, составленную по Заданию 1, убрав возможность параллельного использования вычислительных ресурсов. Измерять время работы программы для тех же значений параметров, что были использованы при выполнении Задания 1. Результаты сравнить и занести в отчёт.


#include <omp.h>
#include <iostream>
#include <locale.h>

const int n = 500;

void init_rand(int* a) {
    for (int i = 0; i < n; i++) {
            a[i] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
        //std::cout << std::endl;
    }
}

void show_matrix(int* a) {
    for (int i = 0; i < n; i++) {
            std::cout << a[i] << " ";
        std::cout << std::endl;
    }
}

void OpenMP(int a[n], int b[n]) {
    int i;
    int sum = 0;
#pragma omp parallel shared(a) 
    {
#pragma omp for private(i) reduction(+:sum)
        for (i = 0; i < n; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            if (value > 1)
                sum += value;
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
}

void noOpenMP(int a[n], int b[n]) {
    int i;
    int sum= 0;
#pragma omp parallel shared(a) 
    {
#pragma omp for private(i) reduction(+:sum)
        for (i = 0; i < n; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            if (value > 1)
                sum += value;
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
}



int main()
{

    setlocale(LC_ALL, "Russian");
    int a[n], b[n];
    init_rand(a);
    init_rand(b);
    //show_matrix(a);
    std::cout << "Результат без OpenMP" << std::endl;
    double noopenMp_start_time = omp_get_wtime();
    noOpenMP(a,b);
    double noopenMp_end_time = omp_get_wtime();
    std::cout << noopenMp_end_time - noopenMp_start_time << std::endl;
    std::cout << "Результат c OpenMP" << std::endl;
    double openMp_start_time = omp_get_wtime();
    OpenMP(a,b);
    double openMp_end_time = omp_get_wtime();
    std::cout << openMp_end_time - openMp_start_time << std::endl;
    return 0;
}
