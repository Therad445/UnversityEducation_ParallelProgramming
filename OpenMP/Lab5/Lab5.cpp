// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <omp.h>
#include <iostream>
#include <locale.h>

const int n = 30000;

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

int sun_func(int a[n], int b[n], int begin, int end) {
    int i;
    int sum = 0;
        for (i = begin; i < end; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            if (value > 1)
                sum += value;
        } /* Завершение параллельного фрагмента */
        return sum;
}


int main()
{

    setlocale(LC_ALL, "Russian");
    int a[n], b[n];
    init_rand(a);
    init_rand(b);
    //show_matrix(a);
    std::cout << "Результат c 2 секциями OpenMP" << std::endl;
    double sec2OpenMp_start_time = omp_get_wtime();
    int total = 0;
#pragma omp parallel sections
    {
        
#pragma omp section
        {
            total += sun_func(a, b, 0, n/2);
        }
#pragma omp section
        {
            total += sun_func(a, b, n / 2, n);
        }
        
    }
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", total);
    double sec2OpenMp_end_time = omp_get_wtime();
    std::cout << sec2OpenMp_end_time - sec2OpenMp_start_time << std::endl;
    std::cout << "Результат c 4 секциями OpenMP" << std::endl;
    double sec4OpenMp_start_time = omp_get_wtime();
    total = 0;
#pragma omp parallel sections
    {
        
#pragma omp section
        {
            total += sun_func(a, b, 0, n / 4);
        }
#pragma omp section
        {
            total += sun_func(a, b, n / 4, n / 2);
        }
#pragma omp section
        {
            total += sun_func(a, b, n / 2, n / 4 * 3);
        }
#pragma omp section
        {
            total += sun_func(a, b, n / 4 * 3, n);
        }
    }
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", total);
    double sec4OpenMp_end_time = omp_get_wtime();
    std::cout << sec4OpenMp_end_time - sec4OpenMp_start_time << std::endl;
    return 0;
}
