#include <stdio.h>
#include <omp.h>
// Función para multiplicar a y b utilizando sumas repetidas usando punteros
void multiplicar(int *a, int *b, int *resultado) {
    int res=0;
    #pragma omp parallel for
    for (int i = 0; i < *b; i++) {
        res += *a;
    }
    *resultado = res;
}

// Función para dividir a entre b utilizando restas repetidas usando punteros
void dividir(int *a, int *b, int *cociente, int *residuo) {
    *cociente = 0;
    *residuo = *a;
    #pragma omp parallel reduction(+:var)
    {
    	while (*residuo >= *b) {
			*residuo -= *b;
			(*cociente)++;
		}
    }
}
void main() {
    int a = 15;
    int b = 4;
    int resultado;
    int cociente;
    int residuo;
    // Multiplicación
    multiplicar(&a, &b, &resultado);
    printf("La multiplicación de %d y %d es: %d\n", a, b, resultado);

    // División
    dividir(&a, &b, &cociente, &residuo);
    printf("La división de %d entre %d da cociente: %d y residuo: %d\n", a, b, cociente, residuo);
}
