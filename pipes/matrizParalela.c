#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void *crearMatriz(int, int, int **);
void imprimirMatriz(int, int, int **);
void *multiplicarMatriz(int **, int **, int **,int, int);
int filas1,columnas1,filas2,columnas2, hijos, anchoRango, status;

int main(int argc, char const *argv[])
{
	int **A, **B, **C;
	srand(time(NULL));
//Creación pipe
	int fd[2]; 
	int recibi = 0;
	pipe(fd);

//Creación matriz A
	printf("%s\n", "Matriz A");
	printf("%s", "No. filas: ");
	scanf("%d",&filas1);
	printf("\n%s", "No. columnas: ");
	scanf("%d", &columnas1);
	A = crearMatriz(filas1,columnas1,A);
	imprimirMatriz(filas1,columnas1,A);
//Creación matriz B
	printf("\n%s", "Matriz B");
	printf("\n%s", "No. filas: ");
	scanf("%d",&filas2);
	printf("\n%s", "No. columnas: ");
	scanf("%d", &columnas2);
	B = crearMatriz(filas2,columnas2,B);
	imprimirMatriz(filas2,columnas2,B);

//Creacion de la matriz resultante filasA x columnasB
	C = crearMatriz(filas1,columnas2, C);
	if(columnas1 != filas2){
		printf("\n %s\n", "Error, el # de columnas de A no es igual al # de filas de B");
		return 1;
	}else{
	//Creacion de los hijos
		printf("\n%s", "# procesos hijos: ");
		scanf("%d", &hijos);
	//Calculo del ancho del rango
		anchoRango = filas1 / hijos;
		printf("ancho: %d\n", anchoRango);
		for(int i = 0; i < hijos; i++){
			pid_t pid = fork();
			if(pid > 0){
			//padre, junta las matrices
				//Cerrar escritura
				close(fd[1]); 
				while(wait(&status) > 0);
				read(fd[0], &recibi, sizeof(recibi));

			}else if(pid == 0){
			//hijo
				//Cerrar lectura en el hijo
				close(fd[0]);
				int aux = 666;
				write(fd[1],&aux, sizeof(recibi));
				printf("i: %d\n", i+1);
				//C = multiplicarMatriz(A,B,C,0,filas1); 
				//imprimirMatriz(filas1,columnas2,C);
				break; //los hijos ya no siguen el for
			}else{
				printf("%s\n","Error procesos");
				return 1;
			}
		}
		
	}
	//printf("\n %s \n", "¡Adios!");
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
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}

void *multiplicarMatriz(int **A, int **B,int **C, int rangoMin, int rangoMax){
	//Filas de A deben ser iguales a col de B
	for(int i = rangoMin; i < rangoMax; i++){
		for (int j = 0; j < columnas2; j++){
			C[i][j] = 0;
			for(int k = 0; k < filas2; k++){
				C[i][j] = C[i][j] + (A[i][k]*B[k][j]);
			} 
		}
	}
	return C;
}