// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include <iostream>
//#include <omp.h>
//#include <vector>
//#include <ctime>
//
//double function_maxSum_openMP(const std::vector<int>& A, const std::vector<int>& B, int start, int end)
//{
//	int maxSum = 0;
//#pragma omp for private(i,j,sum) reduction(+:maxSum)
//	for (int i = start; i < end; i++)
//	{
//		int value = std::max(A[i] + B[i], 4 * A[i] - B[i]);
//		if (value > 1)
//			maxSum += value;
//	}
//	return maxSum;
//}
//
//int main()
//{
//	setlocale(LC_ALL, "Russian");
//	int N = 100;
//	std::vector<int> A(N);
//	std::vector<int> B(N);
//	srand(time(0));
//	for (int i = 0; i < N; i++)
//	{
//		A[i] = rand();
//		B[i] = rand();
//	}
//	double starttime = omp_get_wtime();
//	int maxSum = 0;
//#pragma omp parallel shared(maxSum)
//	{
//		int maxSumParallel = 0;
//#pragma omp sections
//		{
//#pragma omp section 
//			{
//				maxSumParallel += function_maxSum_openMP(A, B, 0, N / 2);
//			}
//#pragma omp section 
//			{
//				maxSumParallel += function_maxSum_openMP(A, B, N / 2, N);
//			}
//		}
//		int maxSum += maxSumParallel;
//	}
//	double end_time_openMP = omp_get_wtime();
//	double result_time_openMP = end_time_openMP - starttime;
//	std::cout << "Результат функции с использованием openMP: " << maxSum << std::endl;
//	std::cout << "Задача выполнена за время с использованием openMP: " << result_time_openMP << std::endl;
//
//	return 0;
//}


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
#pragma omp parallel sections
    {
        int sum = 0;
#pragma omp section
        {
            sum += sun_func(a, b, 0, n/2);
        }
#pragma omp section
        {
            sum += sun_func(a, b, n / 2, n);
        }
        printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
    }
    double sec2OpenMp_end_time = omp_get_wtime();
    std::cout << sec2OpenMp_end_time - sec2OpenMp_start_time << std::endl;
    std::cout << "Результат c 4 секциями OpenMP" << std::endl;
    double sec4OpenMp_start_time = omp_get_wtime();
#pragma omp parallel sections
    {
        int sum = 0;
#pragma omp section
        {
            sum += sun_func(a, b, 0, n / 4);
        }
#pragma omp section
        {
            sum += sun_func(a, b, n / 4, n / 2);
        }
#pragma omp section
        {
            sum += sun_func(a, b, n / 2, n / 4 * 3);
        }
#pragma omp section
        {
            sum += sun_func(a, b, n / 4 * 3, n);
        }
        printf("Сумма элементов матрицы вычесенных по условию равна %i\n", sum);
    }
    double sec4OpenMp_end_time = omp_get_wtime();
    std::cout << sec4OpenMp_end_time - sec4OpenMp_start_time << std::endl;
    return 0;
}
