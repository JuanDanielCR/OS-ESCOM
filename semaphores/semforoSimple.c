#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int zonaCritica[10];
int semaphoreId;
union semun ctlArgs; //union for semctl() - permissions on semaphores
struct semid_ds setArgs; //struct for semget() - creation/manipultaion of semaphore SET
struct sembuf opArgs; //struct fot semop() - operations con semaphores

/*---Structure for semop()---*/
union semun {
    int val; 
    struct semid_ds *buf;
    ushort *array;
};

int iniciarSemaforos(key_t key, int semNumber){
    int i;
    
    int semid; //id of my semaphore

    semid = semget(key, semNumber, IPC_CREAT | IPC_EXCL | 0666);

//create succed 
    if (semid >= 0) {
        opArgs.sem_op = 1; 
        opArgs.sem_flg = 0;
        ctlArgs.val = 1;

        printf("Semaforo Set creado\n"); 

        /* do a semop() to "free" the semaphores. */
        for(opArgs.sem_num = 0; opArgs.sem_num < semNumber; opArgs.sem_num++) { 
            if (semop(semid, &opArgs, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID); /* clean up */
                errno = e;
                return -1; /* error, check errno */
            }else{
                 printf("Semaforo %d libre \n",opArgs.sem_num);
            }
           
        }//for free - semaphores
    }
    else{
//create error
        int ready = 0;
        semid = semget(key, semNumber, 0); /* get the id */
        if (semid < 0) return semid; /* error, check errno */

        /* wait for other process to initialize the semaphore: */
        ctlArgs.buf = &setArgs;
        for(i = 0; i < 10 && !ready; i++) {
            semctl(semid, semNumber-1, IPC_STAT, ctlArgs);
            if (ctlArgs.buf->sem_otime != 0) {
                ready = 1;
            } else {
                sleep(1);
            }
        }
        if (!ready) {
            errno = ETIME;
            return -1;
        }
    }
    return semid;
}


void *productor(void* arg){
    int aux=0;
    for(int i=0;i<5;i++){
        opArgs.sem_num = 0;
        opArgs.sem_op = -1;  /* Decrement sempahore, set to allocate resource */
        opArgs.sem_flg = SEM_UNDO;
        if (semop(semaphoreId, &opArgs, 1) != -1) {
            //printf("Bloqueado productor\n");
        }
        //Bloqueo
        for(int j=0;j<10;j++){
            zonaCritica[j]=aux;
            aux++;
        }
        //Desbloqueo
        opArgs.sem_op = 1; /* free resource */
        if (semop(semaphoreId, &opArgs, 1) != -1) {
            //printf("Desbloqueado productor\n");
        }
        if(i<4){
            opArgs.sem_op = 0; /* free resource */
            if (semop(semaphoreId, &opArgs, 1) != -1) {
                printf("ESperando a que lean\n");
            }
        }
    }
}
/*----Lo que engloban mis mutex/semaphore en el productor, tambien deben englobarlo en el consumidor------*/
void *consumidor(void* arg){
    for(int i=0;i<5;i++){

        opArgs.sem_num = 0;
        opArgs.sem_op = -1;  /* Decrement sempahore, set to allocate resource */
        opArgs.sem_flg = SEM_UNDO;
        if (semop(semaphoreId, &opArgs, 1) != -1) {
            //printf("Bloqueado consumer\n");
        }
        for(int j=0;j<10;j++){
            //pthread_mutex_lock(&candado);
            printf("\t%d",zonaCritica[j]);
            //pthread_mutex_unlock(&candado);
        }
        printf("\n");
        opArgs.sem_op = 1; /* free resource */
        if (semop(semaphoreId, &opArgs, 1) != -1) {
            //printf("Desbloqueado consumer\n");
        }
        if(i < 4){
            opArgs.sem_op = 0; /* free resource */
            if (semop(semaphoreId, &opArgs, 1) != -1) {
                printf("Esperando a que escriban\n");
            }
        }
    }   
}
 
int main(int argc, char const *argv[])
{
    pthread_t idhilo[2];
    key_t key; //key for semaphores
    
//Create our key for the semaphore
    if ((key = ftok("holaSemaforo.c", 'J')) == -1) {
        perror("ftok");
        exit(1);
    }
//Create our semaphore
    if ((semaphoreId = iniciarSemaforos(key, 1)) == -1) {
        perror("initsem");
        exit(1);
    }

    for(int j=0;j<2;j++){  //Creacion de los hilos 
        if(j==0){ // Productor
            pthread_create(&idhilo[j],NULL,productor,NULL);
        }
        else{   //Consumidor
            wait(1000);
            pthread_create(&idhilo[j],NULL,consumidor,NULL);
        }
    }
 
    for(int j=0;j<2;j++){
        pthread_join(idhilo[j],NULL);
    }
 //finally
    opArgs.sem_op = 1; /* free resource */
        if (semop(semaphoreId, &opArgs, 1) != -1) {
            //printf("Desbloqueado consumer\n");
        }
    return 0;
}