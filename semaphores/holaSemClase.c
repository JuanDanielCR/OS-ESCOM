#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semid;
struct sembuf operacion;
int zonaCritica[5];

void waitS(int);
void signalS(int);

void *producer(void* arg){
	int cont = 0;
	for (int i = 0; i < 5; ++i)
	{
		printf("Producer\n");
		waitS(0);
		for (int j = 0; j < 5; ++j)
		{
			zonaCritica[j] = cont;
			cont++;
			//printf("P[%d]", zonaCritica[j]);
		}
		printf("\n");
		signalS(1); //(1)
	}
}
void *consumer(void* argS){
	for (int i = 0; i < 5; ++i)
	{
		printf("Consumer \n");
		waitS(1); //si es 0 se dormiria aqui por eso uso ...(1)
		for (int j = 0; j < 5; ++j)
		{
			printf("%d   ", zonaCritica[j]);
		}
		printf("\n");
		signalS(0);
	}
}
void waitS(int semPosicion){
	operacion.sem_num = semPosicion;
	operacion.sem_op = -1;
	operacion.sem_flg = SEM_UNDO;
	if(semop(semid,&operacion,1) == -1){
		printf("error \n");
	}
}
void signalS(int semPosicion){
	operacion.sem_num = semPosicion;
	operacion.sem_op = 1;
	operacion.sem_flg = SEM_UNDO;
	if(semop(semid,&operacion,1) == -1){
		printf("error \n");
	}
}
int main(int argc, char const *argv[])
{
	pthread_t idProd[3];
	pthread_t idCons[3];

//Creacion de la llave
	key_t key = ftok("/bin/ls","A");
//Creacion del semaforo
	if((semid=semget(key,2,IPC_CREAT | 0666)) == -1){
		//IPC_EXCL retorna -1 si ya esta creado
		exit(1);
	}
//inicializacion
	semctl(semid,0,SETVAL,1); //1 para una sola zona critica
	semctl(semid,1,SETVAL,0); //1 para una sola zona critica

	for(int j=0;j<3;j++){  //Creacion de los hilos 
	  	//Consumidor
        pthread_create(&idProd[j],NULL,producer,NULL);
    }
    for(int i=0;i<3;i++){  //Creacion de los hilos 
	  //Consumidor
        pthread_create(&idCons[i],NULL,consumer,NULL);
    }
     
    for(int z=0;z<3;z++){
        pthread_join(idCons[z],NULL);
    }
	return 0;
}