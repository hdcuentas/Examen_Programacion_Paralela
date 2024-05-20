#include <stdio.h>
//Suma con punteros
void suma(int a, int b, int *resultado){
	*resultado = a + b;
}
//Resta con punteros
void resta(int a, int b, int *resultado){
	*resultado = a - b;
}
// Función para multiplicar a y b utilizando sumas repetidas usando punteros
void multiplicar(int *a, int *b, int *resultado) {
    *resultado = 0;
    for (int i = 0; i < *b; i++) {
        *resultado += *a;
    }
}

// Función para dividir a entre b utilizando restas repetidas usando punteros
void dividir(int *a, int *b, int *cociente, int *residuo) {
    *cociente = 0;
    *residuo = *a;
    while (*residuo >= *b) {
        *residuo -= *b;
        (*cociente)++;
    }
}
void main() {
    int a = 15;
    int b = 4;
    int resultado;
    int cociente;
    int residuo;
    //Suma
	suma(a,b,&resultado);
	printf("La suma de %d y %d es: %d\n", a, b, resultado);
	//Resta
	resta(a,b,&resultado);
	printf("La resta de %d y %d es: %d\n", a, b, resultado);
    // Multiplicación
    multiplicar(&a, &b, &resultado);
    printf("La multiplicación de %d y %d es: %d\n", a, b, resultado);

    // División
    dividir(&a, &b, &cociente, &residuo);
    printf("La división de %d entre %d da cociente: %d y residuo: %d\n", a, b, cociente, residuo);
}

