#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_ZONAS 8
char **zonaCritica;
int semid, columnas,numero_repeticiones, x=0,y=0,z=0;
struct sembuf operacion;

void *inicializarZonaCritica(int, int, int**);
void *productor(void *);
void *consumidor(void *);
void waitS(int);
void signalS(int);

int main(int argc, char const *argv[]){
	pthread_t productores[3];
	pthread_t consumidores[3];

	//Creación de la llave para los semaforos
	key_t key = ftok("/bin/ls","A");
	
	//Inicialización de la zona crítica
	printf("Caracteres X zona: \n"); //ancho de cada zona critica
	scanf("%d",&columnas);
	zonaCritica = inicializarZonaCritica(NUM_ZONAS,columnas,zonaCritica);

	//Creación del semaforo
	int num_semaphores = ((NUM_ZONAS*2)+2);
	if((semid=semget(key,num_semaphores,IPC_CREAT | 0666))==-1){
		printf("error creacion del semaforo");
	}
	//Inicialización de los semaforos

		//Semaforos externos
		printf("%d",num_semaphores);
		semctl(semid,0,SETVAL,NUM_ZONAS); //semaforo externo productores
		semctl(semid,(num_semaphores-1),SETVAL,0); //semaforo externo consumidores
		//Semáforos internos
			//productores - inician abiertos para que se pueda escribir
			for(int i=1;i <= NUM_ZONAS;i++){
				semctl(semid,i,SETVAL,1);
			}
			//consumidores - inician cerrados esperando que se escriba
			for(int j = NUM_ZONAS+1; j <= NUM_ZONAS*2;j++){
				semctl(semid,j,SETVAL,0);
			}
			printf("P: %d\n", semctl(semid,0,GETVAL,NULL));
			printf("C: %d\n", semctl(semid,(num_semaphores-1),GETVAL,NULL));
			for(int i=1;i <= NUM_ZONAS;i++){
				int aux = semctl(semid,i,GETVAL,NULL);
				printf("p: %d\n",aux);
			}
			//consumidores - inician cerrados esperando que se escriba
			for(int j = NUM_ZONAS+1; j <= NUM_ZONAS*2;j++){
				int aux = semctl(semid,j,GETVAL,NULL);
				printf("c: %d\n",aux);
			}
	//numeros de repeticiones
	printf("¿Cuántas veces imprimo mi caracter?\n");
	scanf("%d",&numero_repeticiones);
	//Creación de los threads
	for(int k=0;k<3;k++){
	  	//Productores
        pthread_create(&productores[k],NULL,productor,(void*)k);
    }
    for(int l=0;l<3;l++){ 
	  	//Consumidores
        pthread_create(&consumidores[l],NULL,consumidor,NULL);
    }
    
    //Esperando solo a los consumidores, pues por induccion sabemos que los productores ya terminaron también.
    for(int m=0;m<3;m++){
        pthread_join(consumidores[m],NULL);
    }

    //Verificando número de producciones
    printf("Verificando número de producciones: \n");
    printf("x: %d y: %d z: %d \n",x,y,z);
	return 0;
}

void *inicializarZonaCritica(int filas, int columnas, int **zonaCritica){
	//filas
	zonaCritica = (char**)malloc(filas * sizeof(char*));
	//columnas
	for(int i=0; i < filas; i++){
		zonaCritica[i] = (char*)malloc(columnas * sizeof(char));
	}
	return zonaCritica;
}
void *productor(void*args){
	//viendo que thread productor soy
	int thread_id = (int)args;
	int semValue;
	char caracter;
		//imprimiendo caracter n veces
	for(int n = 0; n < numero_repeticiones; n++){
		if(thread_id == 0){
			caracter = 'X';
			x++;
		}else if(thread_id == 1){
			caracter = 'Y';
			y++;
		}else{
			caracter = 'Z';
			z++;
		}
		//sleeping process
		waitS(0); // 0 - Semaforo externo productor
			//Si ya entre es por que hay alguna zona abierta
			//Recorro las zonas hasta encontrar la que esta abierta
			for(int i=1, k=NUM_ZONAS+1; i <= NUM_ZONAS; i++,k++){
				//Obtener valor del semaforo en la posicion i
				semValue = semctl(semid, i, GETVAL, NULL);
				printf("p: %d",semValue);
				//Evaluamos para ver si el semaforo de la zona critica esta abierto
				if(semValue == 1){ //Semaforo abierto
					waitS(i); //Cerramos el semaforo que nos corresponde
						//Llenamos la zona critica con el valor del caracter correspondiente al thread actual
						for(int j=0;j<columnas;j++){ 
							zonaCritica[i-1][j] = caracter; 
						}
					signalS(k);//Avisamos al semaforo del consumidor que estará en i+NUM_ZONAS que ya puede leer
					signalS((NUM_ZONAS*2)+1); //5 - Semaforo externo consumidor
					break; //Terminamos el ciclo pues ya encontramos un semaforo abierto
				}
				if(i==NUM_ZONAS){
					i = 1;
					k = NUM_ZONAS+1;
				}
			}
	}
	pthread_exit(0);
}
void *consumidor(void * args){
	int semValue;
	for(int n = 0; n < numero_repeticiones; n++){
		waitS((NUM_ZONAS*2)+1); // Semaforo externo del productor
			//Si ya entre (no estoy dormido) leo información de una zona crítica
			for(int i = NUM_ZONAS+1, k=1; i <= NUM_ZONAS*2;i++,k++){ //Ver que zona critica esta abierta para poder leer de ella
				//Obtener valor del semaforo en la posicion i
				semValue = semctl(semid, i, GETVAL, NULL);
				printf("c: %d",semValue);
				//Si esta abierto
				if(semValue == 1){
					waitS(i);//Lo cierro
						//Leemos la info
						for(int j=0;j<columnas;j++){
							printf("%c ",zonaCritica[(i-NUM_ZONAS-1)][j]);
						}
						printf("\n");
					signalS(k); //Aviso a los productores que ya lei de esta zona
					signalS(0); //Avisando al semaforo externo del productor que ya lei
					break;
				}
				if(i==(NUM_ZONAS*2)){
					i = NUM_ZONAS+1;
					k=1;
				}
			}
	}
	pthread_exit(0);
}
void waitS(int posicion){
	//printf("wait: %d \n", posicion);
	operacion.sem_num = posicion;
	operacion.sem_op = -1;
	operacion.sem_flg = SEM_UNDO;
	if(semop(semid,&operacion,1) == -1){
		printf("error wait\n");
	}
}

void signalS(int posicion){
	//printf("signal: %d \n", posicion);
	operacion.sem_num = posicion;
	operacion.sem_op = 1;
	operacion.sem_flg = SEM_UNDO;
	if(semop(semid,&operacion,1)==-1){
		printf("error signal\n");
	}
}