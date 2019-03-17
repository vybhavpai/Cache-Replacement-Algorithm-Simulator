#include <stdio.h>
#include <stdlib.h>
#define N 150
#define BLOCK_SIZE 8

double x[N][N] = {0};
double y[N][N] = {0};
double z[N][N] = {0};

double min(double a, double b)
{
    if (a < b)
    {
        return a;
    }
    else
        return b;
}

void matrix_multiply(double blockSize)
{
    int k = 0, j = 0, i = 0, K, J, r;
    for (J = 0; J < N; J += blockSize)
    {
        for (K = 0; K < N; K += blockSize)
        {
            for (i = 0; i < N; i++)
            {
                for (j = J; j < min(J + blockSize, N); j++)
                {
                    for (k = K, r = 0; k < min(K + blockSize, N); k++)
                    {
                        r += y[i][k] * z[k][j];
                    }
                    x[i][j] += r;
                }
            }
        }
    }
}


void init()
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            y[i][j] = i + j;
            z[i][j] = i * j;
        }
    }
}


int main()
{
    int i, j;
    init();
    matrix_multiply(BLOCK_SIZE);
}
