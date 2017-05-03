#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

struct unidadMatriz{
	int **M1;
	int **M2;
	int **R;
	int f2;
	int c2;
	int minRow;
	int maxRow;
};

void *crearMatriz(int, int, int **);
void *multiplicarMatriz(void *args){
	struct unidadMatriz *matrizData = (struct unidadMatriz*) args;
	int filas = matrizData->f2;
	int columnas = matrizData->c2;
	int min = matrizData->minRow;
	int max = matrizData->maxRow;

	int **A = matrizData->M1;
	int **B = matrizData->M2;


	int filasResultantes = (max+1)-min; 

	//Filas de A deben ser iguales a col de B
	for(int i = 0, a = min; i < filasResultantes; i++, a++){ //filas de la resultante
		/*
			i - Da acceso a la resultante por eso inicia en 0
			a - Da acceso a las matrices orginanles pro eso empezaran en el minimo de cada thread
		*/
		for (int j = 0; j < columnas; j++){ //columnas resultantes
			matrizData->R[i][j] = 0;
			for(int k = 0; k < filas; k++){//
				matrizData->R[i][j] = matrizData->R[i][j] + (A[a][k]*B[k][j]);
			} 
		}
	}
	printf("Thread: %d, filas: %d, col: %d, min: %d, max: %d \n",pthread_self(),filas,columnas,min,max);
	pthread_exit((void *)args); 
}

int main(int argc, char const *argv[]){
	srand(time(NULL));
//Variables locales a enviar para los threads
	void *devuelto;
	int **A, **B, **C;
	int filas1, columnas1, filas2, columnas2;
	int numThreads;
	int anchoRango;
	int success;
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
//Creación de threads
	printf("\n%s", "Num threads: ");
	scanf("%d",&numThreads);

	pthread_t threads[numThreads];
	struct unidadMatriz matricesHijas[numThreads];
	int i;
	//rango
	anchoRango = filas1 / numThreads;

	for(i = 0; i < numThreads; i++){
		threads[i] = i;
		//llenando estructura
		matricesHijas[i].M1 = A;
		matricesHijas[i].M2 = B;

		matricesHijas[i].f2 = filas2;
		matricesHijas[i].c2 = columnas2;
		//calculo de los limites
		int min = (((i+1)*anchoRango)-anchoRango);
		int max = ((i+1)*anchoRango)-1;
		//Validando que el ultimo hijo tome las filas restantes cuando % regrese algo
		if((i+1) == numThreads){				
			if((filas1 % numThreads) > 0){
				max =(filas1 -1);
			}
		}
		matricesHijas[i].minRow = min;
		matricesHijas[i].maxRow = max;
		printf("i: %d min: %d max: %d\n", i+1,min,max);

		//Creando mini matriz resultante
		int filasResultantes = (max+1)-min; 
		matricesHijas[i].R = (int **)malloc(filasResultantes * sizeof(int*));
		for(int j = 0; j < filasResultantes;j++){
			//para cada apuntador de fila, hacemos un malloc de n columnas
			matricesHijas[i].R[j] = (int*)malloc(columnas2 * sizeof(int));
		}

		success = pthread_create((&threads[i]),NULL,multiplicarMatriz, (void*)&matricesHijas[i]);
	}	
//Union de resultados
for(int j = 0; j < numThreads; j++){
		pthread_join(threads[j],(void*)&devuelto);
		struct unidadMatriz *matrizRegreso = (struct unidadMatriz*)devuelto;
		//llenando la matriz resultante por filas
		int min = matrizRegreso -> minRow;
		int max = matrizRegreso -> maxRow;
		//imprimirMatriz((max+1)-min,columnas2,matrizRegreso->R);
		printf("%s\n", "---------------------");
		for(int k = min, z = 0; k < (max+1);k++,z++){
			C[k] = matrizRegreso -> R[z];
		}
	}
	printf("%s\n", "Resultado: ");
	imprimirMatriz(filas1,columnas2, C);
	
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