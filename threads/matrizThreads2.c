#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int **A, **B, **C;

int main(int argc, char const *argv[]){
	srand(time(NULL));
//Llenando matriz 1
	printf("%s\n", "Matriz A");
	printf("%s", "No. filas: ");
	scanf("%d",&filas1);
	printf("\n%s", "No. columnas: ");
	scanf("%d", &columnas1);
	A = crearMatriz(filas1, columnas1,A);
	imprimirMatriz(filas1, columnas1,A);
//Llenando matriz 2
	printf("\n%s", "Matriz B");
	printf("\n%s", "No. filas: ");
	scanf("%d",&filas2);
	printf("\n%s", "No. columnas: ");
	scanf("%d", &columnas2);
	B = crearMatriz(filas2,columnas2,B);
	imprimirMatriz(filas2,columnas2,B);
//Creando resultante
	C = crearMatriz(filas1,columnas2, C);
	
	return 0;
}

void *crearMatriz(int m, int n, int** matriz){
	matriz = (int **)malloc(m * sizeof(int*));
	for(int i = 0; i < m; i++){
		matriz[i] =  (int*)malloc(n * sizeof(int));
	}
	//rellenar la matriz de forma random
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			matriz[i][j] = rand()%3;
		}
	}
	//retornando el apuntador, para evitar segmentataion fault por passed by value 
	return matriz;
}

void imprimirMatriz(int m, int n, int **matriz){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			printf("%d  ",matriz[i][j]);
		}
		printf("\n");
	}
}