#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/stat.h>

void *crearMatriz(int, int, int **);
void imprimirMatriz(int, int, int **);
void *multiplicarMatriz(int **, int **, int **,int, int);
int filas1,columnas1,filas2,columnas2, hijos, anchoRango, status, nbytes;

int main(int argc, char const *argv[])
{
	int **A, **B, **C;
	srand(time(NULL));
//Creación pipe de los filedescriptors
	int fd[2]; 
	int n;
	int finishedPipes = 0;
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
		int pipesfd[hijos][2];
	//Calculo del ancho del rango
		anchoRango = filas1 / hijos;
		printf("ancho: %d\n", anchoRango);
		for(int i = 0; i < hijos; i++){
			pipe(pipesfd[i]);
			pid_t pid = fork();
			if(pid > 0){
			//padre, junta las matrices
				close(pipesfd[i][1]);
				if(i == (hijos-1)){
					long ig = 0;
					//Todos los hijos creados, esperamos a que multipliquen
					//while(wait(&status) > 0);
					printf("%s\n", "Mis hijos terminaron el trabajo, ahora tengo que juntar todo...");
					//Leyendo datos del pipe
					int tuplaRecibida[3];
					for (int i = 0; i < hijos; i++){
						if(i > 0){
								close(pipesfd[i-1][0]);
							}						
							while ((n = read(pipesfd[i][0], &tuplaRecibida, sizeof(tuplaRecibida))> 0)) { 
							// Read until it returns 0 (EOF) or -1 (error)
							//printf("papa: i: %d j: %d valor: %d \n", tuplaRecibida[0], tuplaRecibida[1],tuplaRecibida[2]);
							C[tuplaRecibida[0]][tuplaRecibida[1]] = tuplaRecibida [2]; 
							//printf("%s", ".");
							ig++;
						}				
					}
					
					imprimirMatriz(filas1,columnas2,C);
					printf("\n%s %d datos, con %d hijos\n","El papá termino de juntar: ", ig,hijos );
				}
			}else if(pid == 0){
			//hijo
				close(pipesfd[i][0]);
			//Calculando rago con la formula dada
				int min = (((i+1)*anchoRango)-anchoRango);
				int max = ((i+1)*anchoRango)-1;
			//Validando que el ultimo hijo tome las filas restantes cuando % regrese algo
				if((i+1) == hijos){				
					if((filas1 % hijos) > 0){
						max =(filas1 -1);
					}
				}
				printf("i: %d min: %d max: %d\n", i+1,min,max);
			//Realizando la multiplicación usando como limites a min, max
				C = multiplicarMatriz(A,B,C,min,max);
				printf("Termine: %d\n", i+1);
				//imprimirMatriz(filas1,columnas2,C);
			//Enviando información a través del pipe
				int tuplaMatriz[3];
				int pipe_i = i;
				for(int i = min; i <= max; i++){
					for(int j = 0; j < columnas2;j++){
						
						tuplaMatriz[0] = i;
						tuplaMatriz[1] = j;
						tuplaMatriz[2] = C[i][j];
						/*--printf("i: %d j: %d valor: %d \n", tuplaMatriz[0], tuplaMatriz[1],tuplaMatriz[2]);--*/
						write(pipesfd[pipe_i][1],&tuplaMatriz, sizeof(tuplaMatriz));
					}
				}

				close(pipesfd[i][1]);
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
			printf("%d  ",matriz[i][j]);
		}
		printf("\n");
	}
}

void *multiplicarMatriz(int **A, int **B,int **C, int rangoMin, int rangoMax){
	//Filas de A deben ser iguales a col de B
	for(int i = rangoMin; i <= rangoMax; i++){
		for (int j = 0; j < columnas2; j++){
			C[i][j] = 0;
			for(int k = 0; k < filas2; k++){
				C[i][j] = C[i][j] + (A[i][k]*B[k][j]);
			} 
		}
	}
	return C;
}