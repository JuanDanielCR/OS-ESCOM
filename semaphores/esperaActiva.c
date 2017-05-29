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
int semid,columnas,repeticiones,x=0,y=0,z=0;
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
	key_t key = ftok("/bin/ls","B");
	
	//Inicialización de la zona crítica
	printf("Caracteres X zona: \n"); //ancho de cada zona critica
	scanf("%d",&columnas);
	zonaCritica = inicializarZonaCritica(NUM_ZONAS,columnas,zonaCritica);

	//Creación del semaforo
	int num_semaphores = NUM_ZONAS*2;
	if((semid=semget(key,num_semaphores,IPC_CREAT | 0666))==-1){
		printf("error creacion del semaforo");
	}
	//Inicialización de los semaforos

	//productores - inician abiertos para que se pueda escribir
	for(int i=0;i < NUM_ZONAS;i++){
		semctl(semid,i,SETVAL,1);
	}
	//consumidores - inician cerrados esperando que se escriba
	for(int j = NUM_ZONAS; j < NUM_ZONAS*2;j++){
		semctl(semid,j,SETVAL,0);
	}
	//numeros de repeticiones
	printf("¿Cuántas veces imprimo mi caracter?\n");
	scanf("%d",&repeticiones);
	//Llenando la zona de memoria con 0's para que los productores puedan entrar
	for(int n=0;n<NUM_ZONAS;n++){ 
		zonaCritica[n][0] = 'a'; 
	}
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

void *productor(void*args){
	//viendo que thread productor soy
	int thread_id = (int)args;
	int filaActual;
	char caracter;
		//imprimiendo caracter n veces
	for(int n = 0; n < repeticiones; n++){
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
		//ciclo para la espera activa
		filaActual = 0;
		
		while(1){
			//Vemos si algun consumidor ha leido 
			if(zonaCritica[filaActual][0]=='a'){
				//Cuando se pueda escribir cerramos el semaforo
				waitS(filaActual);
				printf("prod: %d \n",filaActual);
				//Llenamos la zona de memoria
				for(int j=0;j<columnas;j++){ 
					zonaCritica[filaActual][j] = caracter; 
				}
				signalS((filaActual+NUM_ZONAS));
				//Salimos del bucle de espera activa, para pasar a la sig. iteración del ciclo mayor
				break;
			}
			filaActual++;
			if(filaActual==(NUM_ZONAS-1)){
				filaActual = 0;
			}
		}//bucle true			
	}//for general
	pthread_exit(0);
}

void *consumidor(void * args){
	int filaActual;
	for(int n = 0; n < repeticiones; n++){;
		filaActual = 0;
		//Bucle para encontrar una zona para leer
		while(1){
			if(zonaCritica[filaActual][0]=='X'||zonaCritica[filaActual][0]=='Y'||zonaCritica[filaActual][0]=='Z'){
				//Sabemos que podemos leer, bloquemos
				waitS(filaActual+NUM_ZONAS);
				printf("cons: %d \n",filaActual);
				//Podemos leer
				for(int j=0;j<columnas;j++){
					printf("%c ",zonaCritica[filaActual][j]);
				}
				//poniendo primer posición en 0 para espera activa
				zonaCritica[filaActual][0]='a'; 
				printf("\n");
				//Desbloqueamos
				signalS(filaActual);
				//Rompemos el bucle
				break;
			}
			filaActual++;
			if(filaActual==(NUM_ZONAS-1)){
				filaActual = 0;
			}
		}//bucle
	}//for principal
	pthread_exit(0);
}