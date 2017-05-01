#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
void *Work(void*);
void *Work(void *args){
	int i;
	long tid;
	double result = 0.0;
	tid = (long)args;
	for (int i = 0; i < 1000000; ++i){
		result = result + i * (i)*200;
	}
	printf("Thread: %ld done, result: %e \n", tid,result);
	pthread_exit((void*)args);
}

int main(int argc, char const *argv[]){
	pthread_t threads[NUM_THREADS];
//Pthread Attribute Object.........(1)
	pthread_attr_t attr;
	int rc;
	long t; //Declaramos 't' fuera para que todos los threads lo vean
	void *status;
//Initialize and set attributes to (1)
	pthread_attr_init(&attr);
	//Explicit creation of a Joinable Thread
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	for(t = 0; t < NUM_THREADS; t++){
		printf("Main creating: %ld \n", t);
		rc = pthread_create(&(threads[t]),&attr,Work,(void*)t); 
		/*paso 't' y no '&t' por que long t = 0 esta en la zona de memoria compartida
		  y quiero pasar su valor, no la referencia a su valor */
	}

	for (t = 0; t < NUM_THREADS; ++t){
		rc = pthread_join(threads[t],(void *)&status);
		long st = (long) status;
		printf("Thread Joined: %ld\n",st);
	}	
	printf("%s\n", "Main Program completed!");
	return 0;
}