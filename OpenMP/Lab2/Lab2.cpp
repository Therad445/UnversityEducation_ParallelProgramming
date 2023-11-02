#include <omp.h>
#include <iostream>
#include <locale.h>
#ifndef _OPENMP
static_assert(false, "openmp support required");
#endif

const int NMAX = 10000;
const int LIMIT = 10000;


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
#pragma omp parallel shared(a) private(i) if (NMAX>LIMIT)
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


int main()
{

    setlocale(LC_ALL, "Russian");
    int** a;
    a = matrix_init(NMAX, NMAX);
    init_rand(a);
    //show_matrix(a);
    double openMp_start_time = omp_get_wtime();
    OpenMP(a);
    double openMp_end_time = omp_get_wtime();
    std::cout << openMp_end_time - openMp_start_time << std::endl;
    return 0;
}
