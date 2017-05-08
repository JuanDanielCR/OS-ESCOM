#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <time.h>

//timer
clock_t start, end;
double cpu_time_used;

//matrices
int **A, **B, **C;
int filas1, columnas1, filas2, columnas2, numThreads, anchoRango;
void *crearMatriz(int, int, int **);
void *multiplicarMatriz(void *args){
	//printf("numThreads: %d filas1: %d col1: %d filas2: %d col2: %d \n", numThreads,filas1,columnas1,filas2,columnas2);
	
	//Calculo de los limites ahora en la funcion del thread
	int i = (int)args;
	printf("i: %d\n", i);
	int min = (((i+1)*anchoRango)-anchoRango);
	int max = ((i+1)*anchoRango)-1;
	//Validando que el ultimo hijo tome las filas restantes cuando % regrese algo
	if((i+1) == numThreads){				
		if((filas1 % numThreads) > 0){
			max =(filas1 -1);
		}
	}
	//Efecutamos la multiplicación usando solo las partes correspondientes de las matrices
	for(int i = min; i <= max; i++){ //rows resultante
		for(int j = 0; j < columnas2;j++){ //cols resultante
			C[i][j] = 0;
			for(int k = 0; k < filas2; k++){
				C[i][j] = C[i][j] + (A[i][k]*B[k][j]);
			} 
		}
	}

	pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
	start = clock();
	srand(time(NULL));
	void *returned;
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
//Numero Threads
	printf("\n%s", "Num threads: ");
	scanf("%d",&numThreads);

	pthread_t threads[numThreads];
	anchoRango = filas1 / numThreads;
	int i;
//Creacion y ejecución de mis threads
	for(i = 0; i < numThreads; i++){
		threads[i] = i;
		pthread_create(&(threads[i]),NULL,multiplicarMatriz,(void*)i); //mandamos el valor, no la direccion
	}
//Esperando a los threads
	for(i = 0; i < numThreads;i++){
		pthread_join(threads[i], (void*)&returned);
	}
	printf("%s\n", "Resultado: ");
	imprimirMatriz(filas1,columnas2, C);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Tiempo de procesamiento: %f \n",cpu_time_used);
	return 0;
}

void *crearMatriz(int m, int n, int **matriz){
//malloc para las filas que serán apuntadores
	matriz = (int **)malloc(m * sizeof(int*));
	for(int i = 0; i < m;i++){
	//para cada apuntador de fila, hacemos un malloc de n columnas
		matriz[i] = (int*)malloc(n * sizeof(int));
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