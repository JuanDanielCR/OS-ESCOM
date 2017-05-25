#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define TAM_MEM 100
char * Memoria;

int CreaLigaMemoria(void){
  int key2,shmid; 
  key2 = ftok("/bin/ls", 3);

  //Verifica si el segmento de memoria existe (IPC_CREAT|IPC_EXCL)
  if((shmid = shmget(key2, sizeof(char) * TAM_MEM, IPC_CREAT|IPC_EXCL|0666)) == -1){
      /* El segmento existe - abrir como cliente */
      if((shmid = shmget(key2, sizeof(char) * TAM_MEM , 0)) == -1){
	       perror("shmget");
	       exit(1);
      }
      else{
        printf("\nSe ligo a la memoria\n");
      }
  }
  else{
    printf("\nCreo la memoria\n");
  }

  //se ata a la zona de memoria creada
  if((Memoria = (char *) shmat(shmid,(char *) 0, 0)) == (void *)-1) { 
      perror("shmat");
      exit(1);
  }
  //printf("%s\n",Memoria); //lee en memoria compartida

  return shmid; //regresa el identificador de la memoria
}

void DestruyeMemoriaCompartida( int id_Mem,char *buffer){
  //Terminada de usar la memoria compartida se libera
  if(id_Mem != 0 || id_Mem != -1){ //si la memoria ya fue destruida solo se des asociasa de ella
    shmdt (buffer);//des asocia la memoria compartida de la zona de datos de nuestro programa
    shmctl (id_Mem, IPC_RMID, (struct shmid_ds *)NULL);//destruye la zona de memoria compartida
    //printf("\nLa memoria compartida ha sido destruida OUT\n");
    printf("\nDestruyo la memoria\n");
  }
  else{
    shmdt (buffer);//des asocia la memoria compartida de la zona de datos de nuestro programa
    printf("\nSe Desligo de la memoria\n");
  }
}


void Productor(void) { /* codigo del productor */
  int i, j, id_Mem;

  //El productor intenta crear la memoria, s ya existe solo se liga a ella
  id_Mem = CreaLigaMemoria();
  
  for (j=0; j<100; j++){
    Memoria[j] = (char)j+41;
  }
  printf("\nPRODUCTOR:%s \n",Memoria);

  //Verifica si la memoria no ha sido destruida la destruye
  DestruyeMemoriaCompartida(id_Mem,Memoria);
  pthread_exit(0);
}

void Consumidor(void) { /* codigo del productor */
  int i, j, id_Mem;
  
  //El consumidor intenta crear la memoria, si ya existe solo se liga a ella
  id_Mem = CreaLigaMemoria();
  
  printf("\nCONSUMIDOR: ");
  for (j=0; j<100; j++){
    printf("%c",Memoria[j]);
  }
  printf("\n\n");
  
  //Verifica si la memoria no ha sido destruida la destruye
  DestruyeMemoriaCompartida(id_Mem,Memoria);
  pthread_exit(0);
}

int main(int argc, char **argv)
{
  pthread_t th1, th2;
  key_t llave;
  
  //creacion de los hilos
  pthread_create(&th1, NULL, (void *)&Productor, NULL);
  pthread_create(&th2, NULL, (void *)&Consumidor, NULL);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
}