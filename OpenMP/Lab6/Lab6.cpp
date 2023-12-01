// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <omp.h>
#include <iostream>
#include <locale.h>

const int n = 1000000;

void init_rand(int* a) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 10;    //запись в матрицу случайных чисел от 1 до 9
    }
}

void OpenMP(int* a, int* b) {
    omp_lock_t lock;
    omp_init_lock(&lock);
    int i;
    int sum = 0;
#pragma omp parallel shared(a,b, sum) 
    {
#pragma omp for private(i)
        for (i = 0; i < n; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            omp_set_lock(&lock);
            if (value > 1)
                sum += value;
            omp_unset_lock(&lock);
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесленных по условию равна %i\n", sum);
    omp_destroy_lock(&lock);
}

void barrierOpenMP(int* a, int* b) {
    omp_lock_t lock;
    omp_init_lock(&lock);
    int i;
    int sum = 0;
#pragma omp parallel shared(a,b, sum) 
    {
#pragma omp for private(i) nowait
        for (i = 0; i < n; i++) 
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            omp_set_lock(&lock);
            if (value > 1)
                sum += value;
            omp_unset_lock(&lock);
        }
        if (omp_get_thread_num() == 15)
            printf("Поток не завершён\n");
        else
        {
            printf("Поток завершён\n");
#pragma omp barrier
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесленных по условию равна %i\n", sum);
    omp_destroy_lock(&lock);
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int* a, * b;
    a = new int[n];
    b = new int[n];
    init_rand(a);
    init_rand(b);
    printf("Программа запущена\n");
    double barrierOpenMp_start_time = omp_get_wtime();
    OpenMP(a, b);
    double barrierOpenMp_end_time = omp_get_wtime();
    double time_oper2 = barrierOpenMp_end_time - barrierOpenMp_start_time;
    printf("Время операции: %f\n", time_oper2);
    double openMp_start_time = omp_get_wtime();
    barrierOpenMP(a, b);
    double openMp_end_time = omp_get_wtime();
    double time_oper3 = openMp_end_time - openMp_start_time;
    printf("Время операции: %f\n", time_oper3);
    delete[] a;
    delete[] b;
    return 0;
}
