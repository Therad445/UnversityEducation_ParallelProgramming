// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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
    omp_lock_t lock;
    omp_init_lock(&lock);
    int i;
    int sum = 0;
#pragma omp parallel shared(a,b) 
    {
#pragma omp for private(i) reduction(+:sum)
        for (i = 0; i < n; i++)
        {
            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
            omp_set_lock(&lock);
            if (value > 1)
                sum += value;
            omp_unset_lock(&lock);
        }
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
    omp_destroy_lock(&lock);
}

void barrierOpenMP(int a[n], int b[n]) {
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
        #pragma omp barrier
    } /* Завершение параллельного фрагмента */
    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
    omp_destroy_lock(&lock);
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int a[n], b[n];
    init_rand(a);
    init_rand(b);
    void omp_set_dynamic(int dynamic);
    //show_matrix(a);
    double openMp_start_time = omp_get_wtime();
    OpenMP(a, b);
    double openMp_end_time = omp_get_wtime();
    double time_oper1 = openMp_end_time - openMp_start_time;
    printf("Время операции: %f\n", time_oper1);
    double noopenMp_start_time = omp_get_wtime();
    barrierOpenMP(a, b);
    double noopenMp_end_time = omp_get_wtime();
    double time_oper2 = noopenMp_end_time - noopenMp_start_time;
    printf("Время операции: %f\n", time_oper2);
    return 0;
}
