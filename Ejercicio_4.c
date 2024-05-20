#include <stdio.h>
#include <omp.h>

#define M 3
#define N 3

void matrix_vector_multiply(int matriz[N][N], int vector[N], int resultado[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        resultado[i] = 0;
        for (int j = 0; j < N; j++) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }
}

int main() {
    int matriz[N][N] = {{1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    int vector[N] = {1, 2, 3};
    int resultado[N];

    matrix_vector_multiply(matriz, vector, resultado);

    printf("Resultado de la multiplicacion de la matriz por el vector:\n");
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

    return 0;
}
