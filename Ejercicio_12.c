#include <stdio.h>
#include <mpi.h>

// n-ésimo término de Fibonacci
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        int a = 0, b = 1, c;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int num_terms = 20; // Número de términos de Fibonacci a calcular (puedes cambiar este valor)
    if (rank == 0) {
        for (int i = 0; i < num_terms; i++) {
            int term;
            int procesador = (i % (size - 1)) + 1; // Asignar términos de forma circular entre los procesos esclavos
            // Enviar el índice del término de Fibonacci al proceso esclavo
            MPI_Send(&i, 1, MPI_INT, procesador, 0, MPI_COMM_WORLD);
            // Recibir el término de Fibonacci del proceso esclavo
            MPI_Recv(&term, 1, MPI_INT, procesador, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d, ",term);
        }
        printf("\n");
        // Enviar señal de terminación a los procesos esclavos
        int terminator = -1;
        for (int i = 1; i < size; i++) {
            MPI_Send(&terminator, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // Procesos esclavos
        while (1) {
            int index;
            // Recibir el índice del término de Fibonacci a calcular
            MPI_Recv(&index, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (index == -1) {
                // Señal de terminación
                break;
            }
            int term = fibonacci(index);
            // Enviar el término de Fibonacci al proceso maestro
            MPI_Send(&term, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}

