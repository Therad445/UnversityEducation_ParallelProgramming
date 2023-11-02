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
#pragma omp parallel shared(a) 
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

void noOpenMP(int a[n], int b[n]) {
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
    omp_destroy_lock(&lock);
}

//void critical(int a[n], int b[n]) {
//    int i;
//    int sum = 0;
//#pragma omp parallel shared(a) 
//    {
//#pragma omp for private(i) reduction(+:sum)
//        for (i = 0; i < n; i++)
//        {
//            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
//            if (value > 1)
//#pragma omp atomic
//                sum += value;
//        }
//    } /* Завершение параллельного фрагмента */
//    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
//}
//
//void atomic(int a[n], int b[n]) {
//    int i;
//    int sum = 0;
//#pragma omp parallel shared(a) 
//    {
//#pragma omp for private(i) reduction(+:sum)
//        for (i = 0; i < n; i++)
//        {
//            int value = std::max(a[i] + b[i], 4 * a[i] - b[i]);
//#pragma omp critical
//            if (value > 1)
//                sum += value;
//        }
//    } /* Завершение параллельного фрагмента */
//    printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
//}


int main()
{

    setlocale(LC_ALL, "Russian");
    int a[n], b[n];
    init_rand(a);
    init_rand(b);
    //show_matrix(a);
    std::cout << "Результат без OpenMP" << std::endl;
    double noopenMp_start_time = omp_get_wtime();
    noOpenMP(a, b);
    double noopenMp_end_time = omp_get_wtime();
    std::cout << noopenMp_end_time - noopenMp_start_time << std::endl;
    std::cout << "Результат c OpenMP" << std::endl;
    double openMp_start_time = omp_get_wtime();
    OpenMP(a, b);
    double openMp_end_time = omp_get_wtime();
    std::cout << openMp_end_time - openMp_start_time << std::endl;
    std::cout << "Результат с использованием atomic" << std::endl;
    double atomic_start_time = omp_get_wtime();
    atomic(a, b);
    double atomic_end_time = omp_get_wtime();
    std::cout << atomic_end_time - atomic_start_time << std::endl;
    std::cout << "Результат с использованием critical" << std::endl;
    double critical_start_time = omp_get_wtime();
    critical(a, b);
    double critical_end_time = omp_get_wtime();
    std::cout << critical_end_time - critical_start_time << std::endl;
    return 0;
}
