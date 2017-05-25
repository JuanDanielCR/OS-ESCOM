#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_ZONAS 8

/*Id para los recursos que serán compartidos entre diferentes procesos del sistema*/
int semid; //Id para el conjunto de semaforos
int shmid; //Id para el bloque de memoria

//Estructura que se guardará en la memoria compartida
typedef struct{
  int flag;           //Campo que indica si la struct almacena un msj o llamada en ese instante
  char compania;      //Caracter que indica la compañia emisora, el caracter será la primera letra del nombre
  char operacion[50]; //Contiene un telefono o un mensaje dependiendo del valor de flag
  char usuario[20];   //Nombre del usuario
}Zona;

//Apuntador con el que se accede a la zona de memoria compartida
Zona *Memoria;

//Union utilizada para borrar el semaforo
union semun{
    int val;                /* value for SETVAL */
    struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
    ushort *array;          /* array for GETALL & SETALL */
    struct seminfo *__buf;  /* buffer for IPC_INFO */
    void *__pad;
};

void *productor(void *);
void waitS(int);
void signalS(int);

struct sembuf operacion;
int numero_repeticiones=1, tecel = 0, movistar = 0, iusacell = 0;

int main(int argc, char **argv){
	key_t key;
	pthread_t productores[3];
	/*Creacion e inicializacion de los recursos IPC*/
  
  //Llave de acceso, se usará la misma tanto para semaforos como para sh_memory
	if((key = ftok("/bin/ls","A"))==-1){
		printf("error key\n");
	}
	
  //Creacion e inicializacion de los semaforos
  int num_semaphores = ((NUM_ZONAS*2)+2);
	if((semid = semget(key,num_semaphores,0666|IPC_CREAT|IPC_EXCL))==-1){
		
    //El semaforo ya fue creado e inicializado, solo nos conectamos a este.
		if((semid = semget(key,num_semaphores,0666))==-1){
			printf("error\n");
		}else{
      
      //Conexión con éxito a un semaforo existente
			printf("Productor ligando a un semaforo ya creado\n");
		}
	}else{
    //Inicialización
    //Semaforos externos
    semctl(semid,0,SETVAL,NUM_ZONAS); //semaforo externo productores
    semctl(semid,num_semaphores,SETVAL,0); //semaforo externo consumidores
    //Semáforos internos
    //productores - inician abiertos para que se pueda escribir
    for(int i=1;i <= NUM_ZONAS;i++){
      semctl(semid,i,SETVAL,1);
    }
    //consumidores - inician cerrados esperando que se escriba
    for(int j = NUM_ZONAS+1; j <= NUM_ZONAS*2;j++){
      semctl(semid,j,SETVAL,0);
    }
    printf("Productor cree e inicializo al semaforo\n");
    /*
      Los productores no pueden eliminar los semaforos, esta tarea es delegada a los consumidores
      para evitar fallas.
      Las únicas opreaciones faltantes para semaforos se realizarán dentro de los threads que 
      escriben en la memoria conpartida.
    */
	}
  /*Creación de la memoria compartida*/
  shmid = CreaLigaMemoria(key);

	//Creacion y llamada a los threads 
  for(int k=0;k<3;k++){
      //Productores
        pthread_create(&productores[k],NULL,productor,(void*)k);
    }

  //Esperando solo a los productores para hacer un deattached de la memoria compartida
  for(int m=0;m<3;m++){
    pthread_join(productores[m],NULL);
  }

  /*Los productores no destruyen la memoria compartida pues no saben si los consumidores terminaron 
    de leer, de esta forma despues de realizar todas la escrituras los productores solo de desconectan*/
  shmdt (Memoria);
}

void *productor(void* args) {
  //viendo que thread productor soy
  int thread_id = (int)args;
  int semValue;
  char companiaId;
  //imprimiendo caracter n veces
  for(int n = 0; n < numero_repeticiones; n++){
    if(thread_id == 0){
      companiaId = 'T'; //TELCEL
    }else if(thread_id == 1){
      companiaId = 'M'; //MOVISTAR
    }else{
      companiaId = 'I'; //IUSACELL
    }
    /*sleeping process
    waitS(0); // 0 - Semaforo externo productor
      //Si ya entre es por que hay alguna zona abierta
      //Recorro las zonas hasta encontrar la que esta abierta
      for(int i=1; i <= NUM_ZONAS; i++){
        //Obtener valor del semaforo en la posicion i
        semValue = semctl(semid, i, GETVAL, NULL);
        //Evaluamos para ver si el semaforo de la zona critica esta abierto
        if(semValue > 0){ //Semaforo abierto
          waitS(i); //Cerramos el semaforo que nos corresponde
            //Llenamos la zona critica con el valor del struct correspondiente al thread actual
            Memoria[i-1] = caracter; 
          signalS(NUM_ZONAS+i);//Avisamos al semaforo del consumidor que estará en i+NUM_ZONAS que ya puede leer
          break; //Terminamos el ciclo pues ya encontramos un semaforo abierto
        }
      }
    signalS((NUM_ZONAS*2)+1); //Semaforo externo consumidor*/
  }
  pthread_exit(0);
}

/*Función para la creación o attachment a una zona de memoria compartida*/
int CreaLigaMemoria(key_t key){ 
  //Verifica si el segmento de memoria existe (IPC_CREAT|IPC_EXCL)
  if((shmid = shmget(key, sizeof(Zona) * NUM_ZONAS, IPC_CREAT|IPC_EXCL|0666)) == -1){
      /* El segmento existe - abrir como cliente */
      if((shmid = shmget(key, sizeof(Zona) * NUM_ZONAS , 0)) == -1){
	       perror("shmget");
	       exit(1);
      }
      else{
        printf("\nProductor se ligo a una memoria ya existente\n");
      }
  }
  else{
    printf("\nProductor creo la memoria\n");
  }

  //se attachment a la zona de memoria creada
  if((Memoria = (Zona*)shmat(shmid,(Zona*) 0,0)) == (void *)-1) { 
      perror("shmat");
      exit(1);
  }
  return shmid; //regresa el identificador de la memoria
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