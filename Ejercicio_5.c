#include <stdio.h>
#include <mpi.h>

#define N 3  // Cambia este valor para probar con diferentes tamaños de matriz y vector

void multiplyPart(int matrix[N][N], int vector[N], int resultado_local[], int start_row, int num_rows) {
    // Multiplicación de la parte de la matriz asignada por el vector
    for (int i = 0; i < num_rows; i++) {
        resultado_local[i] = 0;
        for (int j = 0; j < N; j++) {
            resultado_local[i] += matrix[start_row + i][j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[N][N] = {{1, 2, 3},
                           {4, 5, 6},
                           {7, 8, 9}};
    
    int vector[N] = {1, 2, 3};
    
    int resultado_local[N]; // Resultados locales de cada proceso
    int resultado_final[N]; // Resultados finales (solo para el proceso maestro)

    // Cada proceso calcula su rango de filas
    int rows_per_process = N / size; // Número de filas por proceso
    int extra_rows = N % size; // Resto de filas (si N no es divisible por size)

    int start_row = rank * rows_per_process + (rank < extra_rows ? rank : extra_rows);
    int num_rows = rows_per_process + (rank < extra_rows ? 1 : 0);

    // Enviar el vector a todos los procesos si el rank es 0
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Send(vector, N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(vector, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Cada proceso realiza la multiplicación para su rango de filas
    multiplyPart(matrix, vector, resultado_local, start_row, num_rows);

    // Enviar resultados locales al proceso maestro (rank 0)
    if (rank == 0) {
            // Proceso maestro inicializa el resultado final con los resultados locales
        for (int i = 0; i < num_rows; i++) {
            resultado_final[i] = resultado_local[i];
        }

        // Proceso maestro recibe resultados locales de otros procesos
        for (int i = 1; i < size; i++) {
            int recv_start = i * rows_per_process + (i < extra_rows ? i : extra_rows);
            int recv_num_rows = rows_per_process + (i < extra_rows ? 1 : 0);
            MPI_Recv(resultado_final + recv_start, recv_num_rows, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Imprimir los resultados finales
        printf("Resultado de la multiplicación matriz-vector:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado_final[i]);
        }
        printf("\n");
    } else {
        MPI_Send(resultado_local, num_rows, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}


